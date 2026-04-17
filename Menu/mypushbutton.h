#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

/**
 * @brief 自定义图片按钮类
 * 实现无边框纯图片按钮，支持两张图片自动切换和弹跳交互动画
 */
class myPushButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param normal_path 正常状态图片路径
     * @param press_path 按下状态图片路径
     * @param pixwidth 按钮宽度
     * @param pixheight 按钮高度
     * @param parent 父窗口
     */
    explicit myPushButton(const QString &normal_path, const QString &press_path = "",
                         int pixwidth = 0, int pixheight = 0, QWidget *parent = nullptr);

    /**
     * @brief 按下动画
     * 实现按钮按下时的向下弹跳效果
     */
    void zoom1();

    /**
     * @brief 松开动画
     * 实现按钮松开时的向上回弹效果
     */
    void zoom2();

protected:
    /**
     * @brief 鼠标按下事件
     * @param e 鼠标事件
     */
    void mousePressEvent(QMouseEvent *e) override;

    /**
     * @brief 鼠标释放事件
     * @param e 鼠标事件
     */
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QString m_normalPath;   // 正常状态图片路径
    QString m_pressPath;    // 按下状态图片路径
    int m_width;            // 按钮宽度
    int m_height;           // 按钮高度
};

#endif // MYPUSHBUTTON_H
