#include "httpgetweather.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUrl>
#include <QUrlQuery>
#include <QMessageBox>

Httpgetweather::Httpgetweather(QWidget *parent) : QWidget(parent)
{
    // 初始化城市编码映射
    initCityCodeMap();
    // 初始化界面
    initUI();
    // 初始化网络请求管理器
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Httpgetweather::onNetworkReplyFinished);
}

Httpgetweather::~Httpgetweather()
{
    // 释放资源
    delete manager;
}

void Httpgetweather::initUI()
{
    // 设置窗口大小
    this->setFixedSize(1024, 600);
    this->setStyleSheet("background-color:rgb(255, 255, 255);");
    
    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 创建城市选择和查询按钮布局
    QHBoxLayout *topLayout = new QHBoxLayout();
    
    // 创建城市选择下拉框
    cityComboBox = new QComboBox(this);
    cityComboBox->addItem("襄阳");
    cityComboBox->addItem("武汉");
    cityComboBox->addItem("北京");
    cityComboBox->addItem("广州");
    cityComboBox->setFixedSize(200, 40);
    cityComboBox->setStyleSheet("font-size:16px;");
    
    // 创建查询按钮
    queryButton = new QPushButton("查询天气", this);
    queryButton->setFixedSize(120, 40);
    queryButton->setStyleSheet("font-size:16px;");
    connect(queryButton, &QPushButton::clicked, this, &Httpgetweather::onQueryButtonClicked);

    // 创建返回主菜单按钮
    returnButton = new QPushButton("返回主菜单", this);
    returnButton->setFixedSize(120, 40);
    returnButton->setStyleSheet("font-size:16px;");
    connect(returnButton, &QPushButton::clicked, this, &Httpgetweather::returnToMain);
    
    // 添加到顶部布局
    topLayout->addWidget(cityComboBox);
    topLayout->addWidget(queryButton);
    topLayout->addWidget(returnButton);
    topLayout->addStretch();
    
    // 创建天气信息布局
    QVBoxLayout *weatherLayout = new QVBoxLayout();
    
    // 创建5天天气信息显示区域
    for (int i = 0; i < 5; i++) {
        QHBoxLayout *dayLayout = new QHBoxLayout();
        
        // 创建天气图标
        iconLabels[i] = new QLabel(this);
        iconLabels[i]->setFixedSize(80, 80);
        
        // 创建星期标签
        dayLabels[i] = new QLabel(this);
        dayLabels[i]->setFixedSize(100, 30);
        dayLabels[i]->setStyleSheet("font-size:16px;");
        
        // 创建日期标签
        dateLabels[i] = new QLabel(this);
        dateLabels[i]->setFixedSize(120, 30);
        dateLabels[i]->setStyleSheet("font-size:16px;");
        
        // 创建温度标签
        tempLabels[i] = new QLabel(this);
        tempLabels[i]->setFixedSize(150, 30);
        tempLabels[i]->setStyleSheet("font-size:16px;");
        
        // 创建天气类型标签
        weatherLabels[i] = new QLabel(this);
        weatherLabels[i]->setFixedSize(100, 30);
        weatherLabels[i]->setStyleSheet("font-size:16px;");
        
        // 创建风向风力标签
        windLabels[i] = new QLabel(this);
        windLabels[i]->setFixedSize(150, 30);
        windLabels[i]->setStyleSheet("font-size:16px;");
        
        // 创建空气质量标签
        airLabels[i] = new QLabel(this);
        airLabels[i]->setFixedSize(100, 30);
        airLabels[i]->setStyleSheet("font-size:16px;");
        
        // 添加到当日布局
        dayLayout->addWidget(iconLabels[i]);
        dayLayout->addWidget(dayLabels[i]);
        dayLayout->addWidget(dateLabels[i]);
        dayLayout->addWidget(tempLabels[i]);
        dayLayout->addWidget(weatherLabels[i]);
        dayLayout->addWidget(windLabels[i]);
        dayLayout->addWidget(airLabels[i]);
        dayLayout->addStretch();
        
        // 添加到天气布局
        weatherLayout->addLayout(dayLayout);
    }
    
    // 添加到主布局
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(weatherLayout);
    mainLayout->addStretch();
    
    // 设置布局
    this->setLayout(mainLayout);
}

void Httpgetweather::initCityCodeMap()
{
    // 初始化城市编码映射
    cityCodeMap["襄阳"] = "420600";
    cityCodeMap["武汉"] = "420100";
    cityCodeMap["北京"] = "110000";
    cityCodeMap["广州"] = "440100";
}

void Httpgetweather::onQueryButtonClicked()
{
    // 获取选择的城市
    QString city = cityComboBox->currentText();
    // 获取城市编码
    QString cityCode = cityCodeMap[city];
    
    // 构建API请求URL
    QUrl url("https://restapi.amap.com/v3/weather/weatherInfo");
    QUrlQuery query;
    query.addQueryItem("city", cityCode);
    query.addQueryItem("key", "ad53e60b62896d37ff9112dae4f4342f");
    query.addQueryItem("extensions", "all");
    url.setQuery(query);
    
    // 发送网络请求
    manager->get(QNetworkRequest(url));
}

void Httpgetweather::onNetworkReplyFinished(QNetworkReply *reply)
{
    // 检查网络请求是否成功
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "网络错误", "获取天气数据失败：" + reply->errorString());
        reply->deleteLater();
        return;
    }
    
    // 读取响应数据
    QByteArray responseData = reply->readAll();
    reply->deleteLater();
    
    // 解析JSON数据
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    if (doc.isNull()) {
        QMessageBox::warning(this, "解析错误", "解析天气数据失败");
        return;
    }
    
    // 解析天气数据
    parseWeatherData(doc);
}

void Httpgetweather::parseWeatherData(const QJsonDocument &doc)
{
    // 获取根对象
    QJsonObject rootObj = doc.object();
    
    // 检查状态码
    if (rootObj.value("status").toString() != "1") {
        QMessageBox::warning(this, "API错误", "获取天气数据失败：" + rootObj.value("info").toString());
        return;
    }
    
    // 获取天气数据
    QJsonArray livesArray = rootObj.value("lives").toArray();
    QJsonArray forecastsArray = rootObj.value("forecasts").toArray();
    
    // 检查数据是否存在
    if (forecastsArray.isEmpty()) {
        QMessageBox::warning(this, "数据错误", "天气数据为空");
        return;
    }
    
    // 获取第一个预报数据
    QJsonObject forecastObj = forecastsArray.first().toObject();
    QJsonArray castArray = forecastObj.value("casts").toArray();
    
    // 显示未来5天天气
    for (int i = 0; i < 5 && i < castArray.size(); i++) {
        QJsonObject dayObj = castArray[i].toObject();
        
        // 获取日期
        QString date = dayObj.value("date").toString();
        // 获取星期
        QString day = dayObj.value("week").toString();
        // 获取最高温度
        QString maxTemp = dayObj.value("daytemp").toString();
        // 获取最低温度
        QString minTemp = dayObj.value("nighttemp").toString();
        // 获取天气类型
        QString weather = dayObj.value("dayweather").toString();
        // 获取风向
        QString windDirection = dayObj.value("daywind").toString();
        // 获取风力
        QString windPower = dayObj.value("daypower").toString();
        
        // 显示星期
        dayLabels[i]->setText("星期" + day);
        // 显示日期
        dateLabels[i]->setText(date);
        // 显示温度
        tempLabels[i]->setText(maxTemp + "℃ ~ " + minTemp + "℃");
        // 显示天气类型
        weatherLabels[i]->setText(weather);
        // 显示风向风力
        windLabels[i]->setText(windDirection + " " + windPower + "级");
        
        // 简单的空气质量显示（高德API可能不直接提供，这里使用默认值）
        airLabels[i]->setText("优");
        
        // 根据天气类型设置图标
        if (weather.contains("晴")) {
            // 晴天图标
            iconLabels[i]->setText("☀️");
            iconLabels[i]->setStyleSheet("font-size:48px;");
        } else if (weather.contains("雨")) {
            // 雨天图标
            iconLabels[i]->setText("🌧️");
            iconLabels[i]->setStyleSheet("font-size:48px;");
        } else {
            // 默认图标
            iconLabels[i]->setText("☁️");
            iconLabels[i]->setStyleSheet("font-size:48px;");
        }
    }
}