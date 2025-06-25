#ifndef BETTERBUTTON_H
#define BETTERBUTTON_H

#include "utils.h"

class BetterButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor color_current_grad_outer READ get_color_current_grad_outer WRITE set_color_current_grad_outer)
    Q_PROPERTY(qreal cur_shadow_offset READ get_cur_shadow_offset WRITE set_cur_shadow_offset)

public:
    explicit BetterButton(QWidget *parent = nullptr);
    // general
    QColor color_bg;
    qreal corner_radius;
    int content_padding; // 内容与边缘的边距

    // 渐变相关
    QColor color_grad_start_default, color_grad_start_hover, color_grad_stop;
    qreal grad_mid_pos; // 过渡点（中间点）的位置
    qreal grad_radius_factor; // 渐变色大小因子

    // 阴影
    QColor color_shadow_light, color_shadow_dark;
    qreal shadow_offset_default, shadow_offset_hover;
    qreal shadow_blur_radius;
    int shadow_margin;

    int anim_duration;

    // 用于动画
    QColor color_current_grad_outer;
    QColor get_color_current_grad_outer();
    void set_color_current_grad_outer(const QColor& c);

    qreal cur_shadow_offset;
    qreal get_cur_shadow_offset();
    void set_cur_shadow_offset(const qreal& c);

    // 一堆事件的重载
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



private:
    void setupAnimations();
    QImage createBlurredShadow(const QRectF& shadow_base_rect, const QColor& shadow_color, qreal blur_radius);

    bool is_hovered = false;
    bool is_pressed = false;
    QPointF mouse_pos;

    QPropertyAnimation *anim_grad_outer_color;
    QPropertyAnimation *anim_shadow_offset;
signals:
};

#endif // BETTERBUTTON_H
