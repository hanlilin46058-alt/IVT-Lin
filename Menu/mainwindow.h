#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "MusicPlayerWidget.h"
#include "httpgetweather.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    myPushButton *btn;
     QTimer *time1;
     QTimer *time2;

    QStackedWidget *stackedWidget;
    MusicPlayerWidget *musicPage;
    Httpgetweather *weatherPage;
};
#endif // MAINWINDOW_H
