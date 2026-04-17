#ifndef HTTPGETWEATHER_H
#define HTTPGETWEATHER_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Httpgetweather : public QWidget
{
    Q_OBJECT

public:
    Httpgetweather(QWidget *parent = nullptr);
    ~Httpgetweather();

private slots:
    void onQueryButtonClicked();
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    // 城市选择下拉框
    QComboBox *cityComboBox;
    // 查询按钮
    QPushButton *queryButton;
    // 天气信息标签数组
    QLabel *dayLabels[5];      // 星期标签
    QLabel *dateLabels[5];      // 日期标签
    QLabel *tempLabels[5];      // 温度标签
    QLabel *weatherLabels[5];   // 天气类型标签
    QLabel *windLabels[5];      // 风向风力标签
    QLabel *airLabels[5];       // 空气质量标签
    QLabel *iconLabels[5];      // 天气图标标签
    // 网络请求管理器
    QNetworkAccessManager *manager;
    // 城市编码映射
    QMap<QString, QString> cityCodeMap;
    // 初始化界面
    void initUI();
    // 初始化城市编码映射
    void initCityCodeMap();
    // 解析天气数据
    void parseWeatherData(const QJsonDocument &doc);
};

#endif // HTTPGETWEATHER_H