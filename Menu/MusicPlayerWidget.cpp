#include "MusicPlayerWidget.h"      // 引入自定义播放器头文件
#include <QCoreApplication>         // Qt核心应用类，用于获取程序路径
#include <QFileInfoList>            // 文件信息列表，存储扫描到的歌曲文件信息
#include <QDir>                     // 目录操作类，用于扫描 myMusic 文件夹
#include <QProcess>                 // 进程类（本代码未直接使用，可保留）
#include <QResizeEvent>             // 窗口大小变化事件
#include <QDebug>                   // 调试输出，打印日志信息
#include <QMediaPlayer>             // Qt 多媒体播放器，负责音频播放控制
#include <QMediaPlaylist>           // 播放列表类，管理多首歌曲顺序
#include <QListWidgetItem>          // 列表控件项，歌曲列表单首歌UI对象
#include <QPalette>                 // 调色板，设置控件颜色（文字颜色）
#include <QFont>                    // 字体类，设置文字大小、样式
#include <QImage>                   // 图片类，加载封面图片
#include <QPixmap>                  // 像素图，用于UI显示图片
#include <QVBoxLayout>              // 垂直布局管理器

/* 自定义歌曲信息结构体
 * 存储每首歌的 显示名称 + 绝对路径，方便管理歌曲数据
 */
struct MediaObjectInfo
{
    QString fileName;   // 歌曲显示名称（界面列表显示）
    QString filePath;   // 歌曲文件绝对路径（播放器播放用）
};

/* 构造函数
 * 作用：初始化所有控件、布局、播放器、信号槽连接
 * 父组件 parent 默认为 nullptr
 */
MusicPlayerWidget::MusicPlayerWidget(QWidget *parent)
    : QWidget(parent)    // 调用父类 QWidget 构造函数
{
    // 所有指针初始化为空，防止野指针（未初始化指针导致崩溃）
    musicPlayer = nullptr;      // 媒体播放器对象
    mediaPlaylist = nullptr;    // 播放列表对象
    exit_button = nullptr;      // 退出按钮（本代码未使用）
    durationSlider = nullptr;   // 播放进度条
    listWidget = nullptr;       // 歌曲列表控件
    listMask = nullptr;         // 歌曲列表底部遮罩层

    // 数组批量清 0，将按钮、标签、布局等数组全部初始化为空
    memset(pushButton, 0, sizeof(pushButton));   // 功能按钮数组清0
    memset(label, 0, sizeof(label));             // 文本标签数组清0
    memset(vWidget, 0, sizeof(vWidget));         // 垂直布局容器清0
    memset(vBoxLayout, 0, sizeof(vBoxLayout));    // 垂直布局管理器清0
    memset(hWidget, 0, sizeof(hWidget));         // 水平布局容器清0
    memset(hBoxLayout, 0, sizeof(hBoxLayout));    // 水平布局管理器清0

    // 1. 初始化 UI 布局：创建所有控件并排版
    musicLayout();

    // 2. 初始化媒体播放器与播放列表
    mediaPlayerInit();

    // 3. 扫描 myMusic 文件夹下的 MP3 歌曲，加载到列表
    scanSongs();

    // ===================== 信号槽连接：按钮控制播放 =====================
    // 按钮信号槽：上一曲 按钮点击 → 执行上一曲槽函数
    connect(pushButton[0], &QPushButton::clicked,
            this, &MusicPlayerWidget::btn_previous_clicked);

    // 按钮信号槽：播放/暂停 按钮点击 → 执行播放暂停槽函数
    connect(pushButton[1], &QPushButton::clicked,
            this, &MusicPlayerWidget::btn_play_clicked);

    // 按钮信号槽：下一曲 按钮点击 → 执行下一曲槽函数
    connect(pushButton[2], &QPushButton::clicked,
            this, &MusicPlayerWidget::btn_next_clicked);

    // ===================== 播放器状态同步UI =====================
    // 播放器状态改变 → 更新播放按钮状态（按下/弹起）
    connect(musicPlayer, &QMediaPlayer::stateChanged,
            this, &MusicPlayerWidget::mediaPlayerStateChanged);

    // 播放列表当前歌曲切换 → 同步高亮列表对应歌曲
   connect(mediaPlaylist, &QMediaPlaylist::currentIndexChanged,
            this, &MusicPlayerWidget::mediaPlaylistCurrentIndexChanged);

    // 歌曲总时长变化 → 更新进度条最大值和总时间显示
    connect(musicPlayer, &QMediaPlayer::durationChanged,
            this, &MusicPlayerWidget::musicPlayerDurationChanged);

    // 歌曲当前播放进度变化 → 实时更新进度条和当前时间
    connect(musicPlayer, &QMediaPlayer::positionChanged,
            this, &MusicPlayerWidget::mediaPlayerPositionChanged);

    // ===================== UI交互控制播放 =====================
    // 点击列表歌曲 → 播放对应歌曲
    connect(listWidget, &QListWidget::itemClicked,
            this, &MusicPlayerWidget::listWidgetCliked);

    // 进度条拖动后松开 → 跳转到对应位置播放
    connect(durationSlider, &QSlider::sliderReleased,
            this, &MusicPlayerWidget::durationSliderReleased);

    // 设置当前窗口获得焦点
    this->setFocus();

    QFile file(":/style.qss");  // 无前缀就这么写
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString qss = QLatin1String(file.readAll());
            this->setStyleSheet(qss);
            file.close();
        }
}

/* 布局函数：创建所有控件并完成排版
 * 整体分为左右两大块：
 * 左侧 = 歌曲列表 + 上一曲/播放/下一曲控制按钮
 * 右侧 = CD 封面 + 进度条 + 时间显示 + 收藏/模式等小按钮
 */
void MusicPlayerWidget::musicLayout()
{
    QPalette pal;    // 调色板对象，用于设置文字颜色

    // 创建 7 个功能按钮：上一曲、播放、下一曲、收藏、播放模式、菜单、音量
    for (int i = 0; i < 7; i++)
        pushButton[i] = new QPushButton(this);   // 父组件为当前播放器窗口

    // 创建 4 个文本标签：标题、CD封面、当前时间、总时间
    for (int i = 0; i < 4; i++)
        label[i] = new QLabel(this);

    // 创建 3 组垂直容器 + 垂直布局，用于垂直排版控件
    for (int i = 0; i < 3; i++) {
        vWidget[i] = new QWidget(this);          // 垂直容器
        vWidget[i]->setAutoFillBackground(true); // 自动填充背景
        vBoxLayout[i] = new QVBoxLayout(vWidget[i]); // 绑定垂直布局
    }

    // 创建 4 组水平容器 + 水平布局，用于水平排版控件
    for (int i = 0; i < 4; i++) {
        hWidget[i] = new QWidget(this);          // 水平容器
        hWidget[i]->setAutoFillBackground(true); // 自动填充背景
        hBoxLayout[i] = new QHBoxLayout(hWidget[i]); // 绑定水平布局
    }

    // ====================== 创建进度条 ======================
    durationSlider = new QSlider(Qt::Horizontal, this); // 水平进度条
    durationSlider->setMinimumSize(300, 15);           // 最小尺寸
    durationSlider->setMaximumHeight(15);              // 最大高度
    durationSlider->setObjectName("durationSlider");    // 对象名（用于QSS样式）

    // ====================== 创建歌曲列表 ======================
    listWidget = new QListWidget(this);                // 列表控件
    listWidget->setObjectName("listWidget");          // 对象名
    listWidget->resize(310, 265);                     // 初始大小
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 隐藏垂直滚动条
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);// 隐藏水平滚动条

    // 列表底部遮罩层（美化界面使用，渐变遮罩）
    listMask = new QWidget(listWidget);               // 父组件为列表
    listMask->setMinimumSize(310, 50);                // 最小尺寸
    listMask->setMinimumHeight(50);                   // 最小高度
    listMask->setObjectName("listMask");              // 对象名
    listMask->setGeometry(0, listWidget->height() - 50, 310, 50); // 固定在列表底部

    // ====================== 给按钮设置对象名（QSS样式表识别用） ======================
    pushButton[0]->setObjectName("btn_previous");    // 上一曲
    pushButton[1]->setObjectName("btn_play");        // 播放暂停
    pushButton[2]->setObjectName("btn_next");        // 下一曲
    pushButton[3]->setObjectName("btn_favorite");     // 收藏
    pushButton[4]->setObjectName("btn_mode");         // 播放模式
    pushButton[5]->setObjectName("btn_menu");         // 菜单
    pushButton[6]->setObjectName("btn_volume");       // 音量

    // 播放按钮、收藏按钮支持选中/取消状态（可按下/弹起）
    pushButton[1]->setCheckable(true);
    pushButton[3]->setCheckable(true);

    // ====================== 最外层水平布局：左右排版 ======================
    vWidget[0]->setMinimumSize(310, 480);    // 左侧区域最小尺寸
    vWidget[0]->setMaximumWidth(310);        // 左侧区域最大宽度
    vWidget[1]->setMinimumSize(320, 480);    // 右侧区域最小尺寸

    // 弹簧占位，控制左右模块之间的间距，使界面更美观
    QSpacerItem *hSpacer0 = new QSpacerItem(70, 480, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer1 = new QSpacerItem(65, 480, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer2 = new QSpacerItem(60, 480, QSizePolicy::Minimum, QSizePolicy::Maximum);

    // 最外层水平布局添加控件：左弹簧 + 左侧区域 + 中间弹簧 + 右侧区域 + 右弹簧
    hBoxLayout[0]->addSpacerItem(hSpacer0);
    hBoxLayout[0]->addWidget(vWidget[0]);
    hBoxLayout[0]->addSpacerItem(hSpacer1);
    hBoxLayout[0]->addWidget(vWidget[1]);
    hBoxLayout[0]->addSpacerItem(hSpacer2);
    hBoxLayout[0]->setContentsMargins(0, 0, 0, 0); // 去掉外边距

    // 给当前Widget设置主布局，替代QMainWindow的中心部件
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(hWidget[0]);           // 添加最外层布局
    mainLayout->setContentsMargins(0, 0, 0, 0);  // 无边距
    mainLayout->setSpacing(0);                   // 无间距

    // ====================== 左侧垂直布局 ======================
    listWidget->setMinimumSize(310, 265);        // 歌曲列表最小尺寸
    hWidget[1]->setMinimumSize(310, 80);         // 按钮区域最小尺寸
    hWidget[1]->setMaximumHeight(80);            // 按钮区域最大高度
    label[0]->setMinimumSize(310, 95);           // 标题标签最小尺寸
    label[0]->setMaximumHeight(95);             // 标题标签最大高度

    // 垂直弹簧，控制控件之间间距
    QSpacerItem *vSpacer0 = new QSpacerItem(310, 10, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *vSpacer1 = new QSpacerItem(310, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);

    // 左侧布局：标题标签 + 歌曲列表 + 弹簧 + 控制按钮 + 弹簧
    vBoxLayout[0]->addWidget(label[0]);
    vBoxLayout[0]->addWidget(listWidget);
    vBoxLayout[0]->addSpacerItem(vSpacer0);
    vBoxLayout[0]->addWidget(hWidget[1]);
    vBoxLayout[0]->addSpacerItem(vSpacer1);
    vBoxLayout[0]->setContentsMargins(0, 0, 0, 0); // 无边距

    // ====================== 上一曲/播放/下一曲 水平布局 ======================
    // 设置三个按钮大小一致
    for (int i = 0; i < 3; i++) {
        pushButton[i]->setMinimumSize(80, 80);
    }

    // 水平弹簧，让按钮均匀分布
    QSpacerItem *hSpacer3 = new QSpacerItem(40, 80, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *hSpacer4 = new QSpacerItem(40, 80, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 按钮布局：上一曲 + 弹簧 + 播放 + 弹簧 + 下一曲
    hBoxLayout[1]->addWidget(pushButton[0]);
    hBoxLayout[1]->addSpacerItem(hSpacer3);
    hBoxLayout[1]->addWidget(pushButton[1]);
    hBoxLayout[1]->addSpacerItem(hSpacer4);
    hBoxLayout[1]->addWidget(pushButton[2]);
    hBoxLayout[1]->setContentsMargins(0, 0, 0, 0); // 无边距

    // ====================== 右侧布局：封面 + 进度条 ======================
    // 垂直弹簧，控制上下间距
    QSpacerItem *vSpacer2 = new QSpacerItem(320, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *vSpacer3 = new QSpacerItem(320, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *vSpacer4 = new QSpacerItem(320, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);

    // CD 封面图片显示标签
    label[1]->setMinimumSize(320, 320);
    QImage Image;
    Image.load(":/images/cd.png");              // 从资源文件加载CD封面图片
    QPixmap pixmap = QPixmap::fromImage(Image); // 转换为像素图
    int with = 320;                             // 图片宽度
    int height = 320;                           // 图片高度
    // 图片自适应缩放，平滑处理
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label[1]->setPixmap(fitpixmap);             // 设置图片到标签
    label[1]->setAlignment(Qt::AlignCenter);    // 图片居中显示

    vWidget[2]->setMinimumSize(300, 80);         // 右侧底部容器尺寸
    vWidget[2]->setMaximumHeight(80);           // 最大高度

    // 右侧布局：弹簧 + CD封面 + 弹簧 + 进度条 + 时间/小按钮容器 + 弹簧
    vBoxLayout[1]->addSpacerItem(vSpacer2);
    vBoxLayout[1]->addWidget(label[1]);
    vBoxLayout[1]->addSpacerItem(vSpacer3);
    vBoxLayout[1]->addWidget(durationSlider);
    vBoxLayout[1]->addWidget(vWidget[2]);
    vBoxLayout[1]->addSpacerItem(vSpacer4);
    vBoxLayout[1]->setContentsMargins(0, 0, 0, 0); // 无边距

    // ====================== 时间显示 + 底部小按钮布局 ======================
    QSpacerItem *vSpacer5 = new QSpacerItem(300, 10, QSizePolicy::Minimum, QSizePolicy::Maximum);
    hWidget[2]->setMinimumSize(320, 20);        // 时间显示区域尺寸
    hWidget[3]->setMinimumSize(320, 60);        // 小按钮区域尺寸

    // 布局：时间显示 + 弹簧 + 小按钮
    vBoxLayout[2]->addWidget(hWidget[2]);
    vBoxLayout[2]->addSpacerItem(vSpacer5);
    vBoxLayout[2]->addWidget(hWidget[3]);
    vBoxLayout[2]->setContentsMargins(0, 0, 0, 0); // 无边距

    // 字体设置：设置时间文字大小为10像素
    QFont font;
    font.setPixelSize(10);

    // 标签文字初始化
    label[0]->setText("Q Music，Enjoy it！");    // 标题文字
    label[2]->setText("00:00");                 // 当前播放时间初始值
    label[3]->setText("00:00");                 // 歌曲总时间初始值

    // 时间标签大小策略：自动拉伸
    label[2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label[3]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label[3]->setAlignment(Qt::AlignRight);     // 总时间右对齐
    label[2]->setAlignment(Qt::AlignLeft);      // 当前时间左对齐
    label[2]->setFont(font);                    // 设置时间字体
    label[3]->setFont(font);

    // 设置文字颜色为白色
    pal.setColor(QPalette::WindowText, Qt::white);
    label[0]->setPalette(pal);
    label[2]->setPalette(pal);
    label[3]->setPalette(pal);

    // 时间显示水平布局：当前时间 + 总时间
    hBoxLayout[2]->addWidget(label[2]);
    hBoxLayout[2]->addWidget(label[3]);
    hBoxLayout[2]->setContentsMargins(0, 0, 0, 0); // 无边距

    // ====================== 底部小按钮：收藏、模式、菜单、音量 ======================
    // 水平弹簧，控制小按钮间距和居中显示
    QSpacerItem *hSpacer5 = new QSpacerItem(0, 60, QSizePolicy::Minimum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer6 = new QSpacerItem(80, 60, QSizePolicy::Maximum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer7 = new QSpacerItem(80, 60, QSizePolicy::Maximum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer8 = new QSpacerItem(80, 60, QSizePolicy::Maximum, QSizePolicy::Maximum);
    QSpacerItem *hSpacer9 = new QSpacerItem(0, 60, QSizePolicy::Minimum, QSizePolicy::Maximum);

    // 设置4个小按钮大小一致
    for (int i = 3; i < 7; i++) {
        pushButton[i]->setMinimumSize(25, 25);
        pushButton[i]->setMaximumSize(25, 25);
    }

    // 小按钮水平布局：弹簧 + 收藏 + 弹簧 + 模式 + 弹簧 + 菜单 + 弹簧 + 音量 + 弹簧
    hBoxLayout[3]->addSpacerItem(hSpacer5);
    hBoxLayout[3]->addWidget(pushButton[3]);
    hBoxLayout[3]->addSpacerItem(hSpacer6);
    hBoxLayout[3]->addWidget(pushButton[4]);
    hBoxLayout[3]->addSpacerItem(hSpacer7);
    hBoxLayout[3]->addWidget(pushButton[5]);
    hBoxLayout[3]->addSpacerItem(hSpacer8);
    hBoxLayout[3]->addWidget(pushButton[6]);
    hBoxLayout[3]->addSpacerItem(hSpacer9);
    hBoxLayout[3]->setContentsMargins(0, 0, 0, 0); // 无边距
    hBoxLayout[3]->setAlignment(Qt::AlignHCenter);  // 水平居中
}

/* 析构函数
 * 作用：程序退出时释放播放器资源，停止播放，防止内存泄漏
 */
MusicPlayerWidget::~MusicPlayerWidget()
{
    if (musicPlayer) {        // 若播放器存在
        musicPlayer->stop();  // 停止播放
        delete musicPlayer;   // 释放播放器对象
    }
    if (mediaPlaylist) {      // 若播放列表存在
        mediaPlaylist->clear();// 清空播放列表
        delete mediaPlaylist; // 释放播放列表对象
    }
}

/* 播放/暂停按钮点击槽函数
 * 功能：根据当前播放器状态自动切换播放/暂停
 * 停止→播放，播放→暂停，暂停→播放
 */
void MusicPlayerWidget::btn_play_clicked()
{
    if (!musicPlayer) return; // 播放器为空直接返回，防止崩溃

    int state = musicPlayer->state(); // 获取当前播放状态

    // 判断状态并执行对应操作
    switch (state) {
    case QMediaPlayer::StoppedState:   // 停止状态 → 播放
        musicPlayer->play();
        break;
    case QMediaPlayer::PlayingState:   // 播放状态 → 暂停
        musicPlayer->pause();
        break;
    case QMediaPlayer::PausedState:    // 暂停状态 → 播放
        musicPlayer->play();
        break;
    }
}

/* 下一曲按钮点击槽函数
 * 功能：切换到下一首歌曲并播放
 */
void MusicPlayerWidget::btn_next_clicked()
{
    // 播放器或播放列表为空直接返回
    if (!musicPlayer || !mediaPlaylist) return;

    musicPlayer->stop(); // 停止当前歌曲
    int count = mediaPlaylist->mediaCount(); // 获取歌曲总数
    if (count == 0) return; // 无歌曲直接返回

    mediaPlaylist->next(); // 切换到下一曲
    musicPlayer->play();   // 播放
}

/* 上一曲按钮点击槽函数
 * 功能：切换到上一首歌曲并播放
 */
void MusicPlayerWidget::btn_previous_clicked()
{
    if (!musicPlayer || !mediaPlaylist) return;

    musicPlayer->stop(); // 停止当前歌曲
    int count = mediaPlaylist->mediaCount();
    if (count == 0) return;

    mediaPlaylist->previous(); // 切换到上一曲
    musicPlayer->play();       // 播放
}

/* 播放器状态变化槽函数
 * 功能：同步播放按钮显示状态
 * 播放 → 按钮按下
 * 暂停/停止 → 按钮弹起
 */
void MusicPlayerWidget::mediaPlayerStateChanged(QMediaPlayer::State state)
{
    if (!pushButton[1]) return; // 按钮为空直接返回

    switch (state) {
    case QMediaPlayer::StoppedState:   // 停止 → 按钮弹起
        pushButton[1]->setChecked(false);
        break;
    case QMediaPlayer::PlayingState:   // 播放 → 按钮按下
        pushButton[1]->setChecked(true);
        break;
    case QMediaPlayer::PausedState:    // 暂停 → 按钮弹起
        pushButton[1]->setChecked(false);
        break;
    }
}

/* 点击歌曲列表项槽函数
 * 功能：点击列表歌曲，播放对应歌曲
 */
void MusicPlayerWidget::listWidgetCliked(QListWidgetItem *item)
{
    // 播放器、列表、点击项为空都直接返回
    if (!musicPlayer || !mediaPlaylist || !item) return;

    musicPlayer->stop(); // 停止当前歌曲
    // 设置播放列表为点击项的索引
    mediaPlaylist->setCurrentIndex(listWidget->row(item));
    musicPlayer->play(); // 播放选中歌曲
}

/* 播放列表歌曲切换槽函数
 * 功能：歌曲切换时，同步高亮列表对应项
 */
void MusicPlayerWidget::mediaPlaylistCurrentIndexChanged(int index)
{
    if (index == -1 || !listWidget) return; // 索引无效返回

    listWidget->setCurrentRow(index); // 高亮对应行
}

/* 歌曲总时长更新槽函数
 * 功能：设置进度条范围，并显示总时间
 */
void MusicPlayerWidget::musicPlayerDurationChanged(qint64 duration)
{
    if (!durationSlider || !label[3]) return; // 控件为空返回

    durationSlider->setRange(0, duration / 1000); // 进度条范围：0 ~ 总秒数

    // 毫秒转 分:秒
    int second = duration / 1000;
    int minute = second / 60;
    second %= 60;

    QString mediaDuration;
    mediaDuration.sprintf("%02d:%02d", minute, second); // 格式化时间
    label[3]->setText(mediaDuration); // 显示总时间
}

/* 歌曲当前播放进度更新槽函数
 * 功能：同步进度条与当前时间显示
 */
void MusicPlayerWidget::mediaPlayerPositionChanged(qint64 position)
{
    if (!durationSlider || !label[2]) return;

    // 进度条未被拖动时，自动更新进度条位置
    if (!durationSlider->isSliderDown())
        durationSlider->setValue(position / 1000);

    // 毫秒转 分:秒
    int second = position / 1000;
    int minute = second / 60;
    second %= 60;

    QString mediaPosition;
    mediaPosition.sprintf("%02d:%02d", minute, second);
    label[2]->setText(mediaPosition); // 显示当前播放时间
}

/* 窗口大小变化事件
 * 功能：保证列表底部遮罩层始终在列表最下方
 */
void MusicPlayerWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event); // 调用父类事件

    // 重新设置遮罩层位置
    if (listMask && listWidget) {
        listMask->setGeometry(0, listWidget->height() - 50, 310, 50);
    }
}

/* 进度条拖动松开槽函数
 * 功能：跳转到拖动的时间点播放
 */
void MusicPlayerWidget::durationSliderReleased()
{
    if (!musicPlayer || !durationSlider) return;

    // 进度条值 ×1000 转为毫秒，设置播放位置
    musicPlayer->setPosition(durationSlider->value() * 1000);
}

/* 扫描歌曲函数
 * 功能：扫描程序目录下 myMusic 文件夹中的 MP3
 * 添加到播放列表与界面列表
 */
void MusicPlayerWidget::scanSongs()
{
    // 获取程序执行目录下的 myMusic 文件夹
    QDir dir(QCoreApplication::applicationDirPath() + "/myMusic");

    if (!dir.exists()) { // 目录不存在，打印日志并返回
        qDebug() << "目录不存在: " << dir.absolutePath();
        return;
    }

    // 只扫描 .mp3 格式文件
    QStringList filter;
    filter << "*.mp3";

    // 获取目录下所有MP3文件信息
    QFileInfoList files = dir.entryInfoList(filter, QDir::Files);
    QList<MediaObjectInfo> mediaObjectInfo; // 存储歌曲信息列表

    // 遍历所有MP3文件
    for (const QFileInfo &file : files) {
        MediaObjectInfo info;
        // 文件名去掉 .mp3 后缀
        QString fileName = file.fileName().replace(".mp3", "");

        // 显示名称：文件名 + 换行 + 歌手（按 - 分割）
        info.fileName = fileName + "\n" + fileName.split("-").at(1);
        info.filePath = file.filePath(); // 文件绝对路径

        // 添加到播放列表，成功则添加到UI列表
        if (mediaPlaylist->addMedia(QUrl::fromLocalFile(info.filePath))) {
            mediaObjectInfo.append(info);
            listWidget->addItem(info.fileName);
        } else {
            // 添加失败打印错误信息
            qDebug() << "添加歌曲失败: " << mediaPlaylist->errorString();
        }
    }
}

/* 媒体播放器初始化
 * 功能：创建播放器 + 播放列表，设置循环播放模式
 */
void MusicPlayerWidget::mediaPlayerInit()
{
    musicPlayer = new QMediaPlayer(this);    // 创建播放器
    mediaPlaylist = new QMediaPlaylist(this);// 创建播放列表

    mediaPlaylist->clear();                  // 清空播放列表
    musicPlayer->setPlaylist(mediaPlaylist); // 播放器绑定播放列表

    // 设置循环播放模式：列表循环
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
}
