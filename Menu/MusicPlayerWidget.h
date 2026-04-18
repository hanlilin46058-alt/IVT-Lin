// 防止头文件被重复包含（必须写，避免编译报错）
#ifndef MUSICPLAYERWIDGET_H
#define MUSICPLAYERWIDGET_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QDebug>
#include <QStackedWidget>

// 前置声明：歌曲信息结构体，真正定义在 cpp 里
struct MediaObjectInfo;

// 音乐播放器类：继承 QWidget → 普通子页面/控件
class MusicPlayerWidget : public QWidget
{
    // Qt 宏：必须加，支持信号槽、对象树机制
    Q_OBJECT

public:
    // 构造函数：创建界面
    explicit MusicPlayerWidget(QWidget *parent = nullptr);
    // 析构函数：释放资源
    ~MusicPlayerWidget() override;

signals:
    void returnToMain();

// 私有槽函数：按钮点击、播放器状态更新
private slots:
    void btn_play_clicked();                // 播放/暂停
    void btn_next_clicked();                // 下一曲
    void btn_previous_clicked();            // 上一曲
    void mediaPlayerStateChanged(QMediaPlayer::State state); // 播放状态改变
    void listWidgetCliked(QListWidgetItem *item);       // 点击列表播放
    void mediaPlaylistCurrentIndexChanged(int index);    // 切歌同步列表高亮
    void musicPlayerDurationChanged(qint64 duration);    // 总时长更新
    void mediaPlayerPositionChanged(qint64 position);   // 当前进度更新
    void durationSliderReleased();          // 拖动进度条跳播

// 保护成员：窗口重绘/大小变化事件
protected:
    void resizeEvent(QResizeEvent *event) override;

// 私有函数：只在内部使用，外部不能调用
private:
    void musicLayout();          // 界面布局（所有按钮、文字、列表排版）
    void mediaPlayerInit();      // 播放器初始化
    void scanSongs();            // 扫描 myMusic 文件夹里的 MP3

    // 媒体播放核心
    QMediaPlayer *musicPlayer;    // 播放器 （播放音乐）    
    QMediaPlaylist *mediaPlaylist;// 播放列表

    // 废弃不用的变量（原主窗口退出按钮，子页面已删除）
    QPushButton *exit_button;

    // 核心控件
    QSlider *durationSlider;     // 进度条
    QListWidget *listWidget;     // 歌曲列表
    QWidget *listMask;           // 列表遮罩（美化）

    // 控件数组：批量管理按钮、标签、布局
    QPushButton *pushButton[7];  // 7个功能按钮
    QLabel *label[4];            // 4个文字标签

    // 布局容器：垂直布局3组、水平布局4组
    QWidget *vWidget[3];
    QVBoxLayout *vBoxLayout[3];
    QWidget *hWidget[4];
    QHBoxLayout *hBoxLayout[4];
};

#endif
