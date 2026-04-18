#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QAction>
#include<QPainter>
#include"mypushbutton.h"
#include<QString>
#include<QPushButton>
#include<QProcess>
#include<QDebug>
#include<QPainter>
#include<QTimer>
#include<QTime>
#include<QThread>
#include<QLabel>
#include "QDate"
#include "mainwindow.h"
#include <sys/signal.h>



/**
 * @brief MainWindow::MainWindow
 * @param parent 父窗口指针
 * 主窗口构造函数，初始化界面和功能按钮
 */
 MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
{
    //[] 创建 Menu 项目
    // 实现主窗口基础布局
    // 1024x600 分辨率设置
    // 顶部/左侧装饰标签
    // 时间/日期显示

        /*主窗口基础布局*/
        this->setFixedSize(1024,600);
        this->setStyleSheet("background-color:rgb(255, 255, 255);");
        
        // 创建堆叠控件
        stackedWidget = new QStackedWidget(this);
        
        // 1. 创建主页面容器
        QWidget *mainPage = new QWidget(this);
        
        /*创建顶部和左侧装饰性标签*/
        QLabel *Huilabel = new QLabel(mainPage);  // 改为mainPage的子控件
        QLabel *Vuilabel = new QLabel(mainPage);  // 改为mainPage的子控件
        Huilabel->setGeometry(0,0,1024,20);
        
        QPixmap pix(":/images/hui.png");
        if(pix.isNull()){
            qDebug() << "图片加载失败";
        }else{
            Huilabel->setPixmap(pix);
            qDebug() << "图片加载成功";
        }
    
        Vuilabel->setGeometry(0,20,70,580);
        Vuilabel->setPixmap(QPixmap(":/images/vui.png"));
    
        // 创建音乐播放器界面
        musicPage = new MusicPlayerWidget(this);
        connect(musicPage, &MusicPlayerWidget::returnToMain, [=](){
            stackedWidget->setCurrentWidget(mainPage);
        });

        // 创建天气界面
        weatherPage = new Httpgetweather(this);
        connect(weatherPage, &Httpgetweather::returnToMain, [=](){
            stackedWidget->setCurrentWidget(mainPage);
        });
        
        // 将主页面和音乐页面添加到堆叠控件
        stackedWidget->addWidget(mainPage);  // 主页面作为第一个页面
        stackedWidget->addWidget(musicPage); // 音乐页面作为第二个页面
        stackedWidget->addWidget(weatherPage); // 天气页面作为第三个页面
        

        // 设置默认显示主页面
        stackedWidget->setCurrentWidget(mainPage);
        
        this->setCentralWidget(stackedWidget);
    
     
        // 创建时间显示label
        QLabel *time_label = new QLabel(mainPage);
        time_label->setGeometry(90,30,240,60);
        time_label->setStyleSheet("font-size:40px;color:green");
        time_label->setAlignment(Qt::AlignCenter);
        
        // 创建日期显示label
        QLabel *date_label = new QLabel(mainPage);
        date_label->setGeometry(90,90,240,30);
        date_label->setStyleSheet("font-size:18px;color:green");
        date_label->setAlignment(Qt::AlignCenter);
        
        // 定时器刷新时间和日期
        QTimer *timer = new QTimer(this);
        timer->start(1000); // 每秒更新一次
        
        connect(timer, &QTimer::timeout, [=](){
            // 更新时间
            QTime currentTime = QTime::currentTime();
            QString timeText = currentTime.toString("HH:mm:ss");
            time_label->setText(timeText);
            
            // 更新日期
            QDate currentDate = QDate::currentDate();
            QString dateText = currentDate.toString("yyyy-MM-dd");
            date_label->setText(dateText);
        });
        
        // 初始更新一次
        QTime currentTime = QTime::currentTime();
        QString timeText = currentTime.toString("HH:mm:ss");
        time_label->setText(timeText);
        
        QDate currentDate = QDate::currentDate();
        QString dateText = currentDate.toString("yyyy-MM-dd");
        date_label->setText(dateText);
    
        // 创建音乐按钮，设置父对象为mainPage
        myPushButton *music_button = new myPushButton(":/images/music.png","",180,200);
        time1 = new QTimer(this);
        music_button->setParent(mainPage);  // 改为mainPage的子控件
        music_button->move(310,20);
    
        connect(music_button, &myPushButton::clicked, [=](){
            music_button->zoom1();
            music_button->zoom2();

            time1->start(500);
            connect(time1, &QTimer::timeout, [=](){
                time1->stop();
                stackedWidget->setCurrentWidget(musicPage); // 切换到音乐页面
            });
        });

        // 创建天气按钮，设置父对象为mainPage
        myPushButton *weather_button = new myPushButton(":/images/weather.png","",180,200);
        time2 = new QTimer(this);
        weather_button->setParent(mainPage);  // 改为mainPage的子控件
        weather_button->move(310,180);

        connect(weather_button, &myPushButton::clicked, [=](){
            weather_button->zoom1();
            weather_button->zoom2();

            time2->start(500);
            connect(time2, &QTimer::timeout, [=](){
                time2->stop();
                stackedWidget->setCurrentWidget(weatherPage); // 切换到天气页面
            });
        });

    

    

}

/**
 * @brief MainWindow::~MainWindow
 * 主窗口析构函数，释放UI资源
 */
MainWindow::~MainWindow()
{

}

