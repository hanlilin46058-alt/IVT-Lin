#include "mypushbutton.h"
#include <QMouseEvent>

/**
 * @brief 构造函数
 * @param normal_path 正常状态图片路径
 * @param press_path 按下状态图片路径
 * @param pixwidth 按钮宽度
 * @param pixheight 按钮高度
 * @param parent 父窗口
 */
myPushButton::myPushButton(const QString &normal_path, const QString &press_path, int pixwidth, int pixheight, QWidget *parent)
    : QPushButton(parent),
      m_normalPath(normal_path),
      m_pressPath(press_path),
      m_width(pixwidth),
      m_height(pixheight)
{
    // 设置按钮样式为无边框
    setStyleSheet("QPushButton{border: none; background: transparent;}");
    
    // 设置按钮大小
    if (m_width > 0 && m_height > 0) {
        setFixedSize(m_width, m_height);
    }
    
    // 设置正常状态图片
    QPixmap pixmap(normal_path);
    if (!pixmap.isNull()) {
        // 如果指定了尺寸，缩放图片
        if (m_width > 0 && m_height > 0) {
            pixmap = pixmap.scaled(m_width, m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        setIcon(pixmap);
        setIconSize(pixmap.size());
    }
}

/**
 * @brief 按下动画
 * 实现按钮按下时的向下弹跳效果
 */
void myPushButton::zoom1()
{
    // 创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    
    // 设置动画持续时间
    animation->setDuration(100);
    
    // 设置动画起始位置
    animation->setStartValue(geometry());
    
    // 设置动画结束位置（向下移动5像素）
    QRect endRect = geometry();
    endRect.translate(0, 5);
    animation->setEndValue(endRect);
    
    // 设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    
    // 启动动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

/**
 * @brief 松开动画
 * 实现按钮松开时的向上回弹效果
 */
void myPushButton::zoom2()
{
    // 创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    
    // 设置动画持续时间
    animation->setDuration(100);
    
    // 设置动画起始位置
    animation->setStartValue(geometry());
    
    // 设置动画结束位置（向上移动5像素，回到原始位置）
    QRect endRect = geometry();
    endRect.translate(0, -5);
    animation->setEndValue(endRect);
    
    // 设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    
    // 启动动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

/**
 * @brief 鼠标按下事件
 * @param e 鼠标事件
 */
void myPushButton::mousePressEvent(QMouseEvent *e)
{
    // 如果提供了按下图
    if (!m_pressPath.isEmpty()) {
        QPixmap pixmap(m_pressPath);
        if (!pixmap.isNull()) {
            // 如果指定了尺寸，缩放图片
            if (m_width > 0 && m_height > 0) {
                pixmap = pixmap.scaled(m_width, m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            setIcon(pixmap);
            setIconSize(pixmap.size());
        }
    }
    
    // 触发按下动画
    zoom1();
    
    // 调用父类的鼠标按下事件
    QPushButton::mousePressEvent(e);
}

/**
 * @brief 鼠标释放事件
 * @param e 鼠标事件
 */
void myPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 恢复正常状态图片
    QPixmap pixmap(m_normalPath);
    if (!pixmap.isNull()) {
        // 如果指定了尺寸，缩放图片
        if (m_width > 0 && m_height > 0) {
            pixmap = pixmap.scaled(m_width, m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        setIcon(pixmap);
        setIconSize(pixmap.size());
    }
    
    // 触发松开动画
    zoom2();
    
    // 调用父类的鼠标释放事件
    QPushButton::mouseReleaseEvent(e);
}
