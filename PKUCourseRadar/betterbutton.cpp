#include "betterbutton.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>

BetterButton::BetterButton(QWidget *parent)
    : QPushButton{parent}
{
    setMouseTracking(true);
    color_bg = QColor(255, 255, 255, 255);
    corner_radius = qMin(width(), height()) * 0.2;
    content_padding = 5;

    color_grad_start_default = QColor(255, 255, 255, 255);
    color_grad_start_hover = QColor(200, 200, 200, 200);
    color_grad_stop = QColor(255, 255, 255, 255);
    grad_mid_pos = 0.86;
    grad_radius_factor = 5;

    color_shadow_light = QColor(230, 230, 230, 255);
    color_shadow_dark = QColor(200, 200, 200, 255);
    shadow_offset_default = qMin(width(), height()) * 0.05;
    shadow_offset_hover = shadow_offset_default * 0.3;
    shadow_blur_radius = shadow_offset_hover * 12;
    shadow_margin = shadow_offset_default + shadow_blur_radius;

    mouse_pos = QPointF(-1, -1);
    anim_duration = 500;

    color_current_grad_outer = color_grad_stop;
    cur_shadow_offset = shadow_offset_default;

    setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_TranslucentBackground);

    setupAnimations();
    updateGeometry();
}

void BetterButton::setupAnimations(){
    anim_grad_outer_color = new QPropertyAnimation(this, "color_current_grad_outer", this);
    anim_grad_outer_color -> setDuration(anim_duration);

    anim_shadow_offset = new QPropertyAnimation(this, "cur_shadow_offset", this);
    anim_shadow_offset -> setDuration(anim_duration);
}

void BetterButton::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    qreal ratio = 1.0 * shadow_margin / qMin(width(), height());
    QRectF body_rect = rect().adjusted(ratio * width(), ratio * height(), -ratio * width(), -ratio * height());
    if(body_rect.width() <= 0 || body_rect.height() <= 0) body_rect = rect();

    // 左上方浅色阴影
    QRectF upper_shadow_base_rect = body_rect.translated(-cur_shadow_offset, -cur_shadow_offset);
    QImage blurred_upper_shadow = createBlurredShadow(QRectF(QPointF(0,0), upper_shadow_base_rect.size()), color_shadow_light, shadow_blur_radius);
    painter.drawImage(upper_shadow_base_rect.topLeft() - QPointF(qCeil(shadow_blur_radius * 1.5), qCeil(shadow_blur_radius * 1.5)), blurred_upper_shadow);

    // 右下方深色阴影
    QRectF lower_shadow_base_rect = body_rect.translated(cur_shadow_offset, cur_shadow_offset);
    QImage blurred_lower_shadow = createBlurredShadow(QRectF(QPointF(0,0), lower_shadow_base_rect.size()), color_shadow_dark, shadow_blur_radius);
    painter.drawImage(lower_shadow_base_rect.topLeft() - QPointF(qCeil(shadow_blur_radius * 1.5), qCeil(shadow_blur_radius * 1.5)), blurred_lower_shadow);

    QPainterPath clip_path;
    clip_path.addRoundedRect(body_rect, corner_radius, corner_radius);
    painter.setClipPath(clip_path);
    painter.fillPath(clip_path, color_bg);

    if(is_hovered || is_pressed){
        // 径向过渡
        QRadialGradient radial_grad(mouse_pos, qMin(body_rect.width(), body_rect.height()) * grad_radius_factor);
        radial_grad.setCenter(mouse_pos);
        radial_grad.setFocalPoint(mouse_pos);
        radial_grad.setColorAt(0, color_grad_start_hover);
        radial_grad.setColorAt(1, color_current_grad_outer);
        painter.fillPath(clip_path, radial_grad);
    } else {
        // 线性过渡
        QLinearGradient linear_grad(body_rect.width() * (-0.1) + body_rect.left(), body_rect.height() * -0.1 + body_rect.top(),
                                    body_rect.width() + body_rect.left(), body_rect.height() + body_rect.top());
        linear_grad.setColorAt(0.0, color_grad_start_default);
        linear_grad.setColorAt(grad_mid_pos, color_grad_stop);
        linear_grad.setColorAt(1.0, color_grad_stop);
        painter.fillPath(clip_path, linear_grad);
    }
    QRectF content_rect = body_rect.adjusted(content_padding, content_padding, -content_padding, -content_padding);
    if(is_pressed) content_rect.translate(1, 1);
    painter.setFont(this->font());
    painter.drawText(content_rect, Qt::AlignCenter | Qt::TextWordWrap, text());
}

QImage BetterButton::createBlurredShadow(const QRectF& shadow_base_rect, const QColor& shadow_color, qreal blur_radius){
    int margin = qCeil(blur_radius * 1.5);
    QSize image_size = shadow_base_rect.size().toSize() + QSize(2 * margin, 2 * margin);
    QImage image(image_size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter img_painter(&image);
    img_painter.setRenderHint(QPainter::Antialiasing);
    img_painter.setCompositionMode(QPainter::CompositionMode_Source);
    img_painter.translate(margin, margin);

    QPainterPath path;
    path.addRoundedRect(QRectF(QPointF(0,0), shadow_base_rect.size()), corner_radius, corner_radius);
    img_painter.fillPath(path, shadow_color);
    img_painter.end();

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(image));

    QGraphicsBlurEffect *blur_effect = new QGraphicsBlurEffect;
    blur_effect->setBlurRadius(blur_radius);
    item.setGraphicsEffect(blur_effect);
    scene.addItem(&item);

    QImage result_image(image_size, QImage::Format_ARGB32_Premultiplied);
    result_image.fill(Qt::transparent);

    QPainter result_painter(&result_image);
    result_painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene.render(&result_painter, QRectF(), QRectF(0,0, image_size.width(), image_size.height()));
    result_painter.end();
    return result_image;
}

void BetterButton::enterEvent(QEnterEvent *e){
    QPushButton::enterEvent(e);
    is_hovered = true;
    mouse_pos = e->position();

    anim_grad_outer_color->stop();
    anim_grad_outer_color->setStartValue(color_current_grad_outer);
    anim_grad_outer_color->setEndValue(color_grad_start_default);
    anim_grad_outer_color->start();

    anim_shadow_offset->stop();
    anim_shadow_offset->setStartValue(cur_shadow_offset);
    anim_shadow_offset->setEndValue(shadow_offset_hover);
    anim_shadow_offset->start();

    update();
}

void BetterButton::leaveEvent(QEvent *e){
    QPushButton::leaveEvent(e);
    is_hovered = false;
    mouse_pos = QPointF(-1, -1);

    anim_grad_outer_color->stop();
    anim_grad_outer_color->setStartValue(color_current_grad_outer);
    anim_grad_outer_color->setEndValue(color_grad_stop);
    anim_grad_outer_color->start();

    anim_shadow_offset->stop();
    anim_shadow_offset->setStartValue(cur_shadow_offset);
    anim_shadow_offset->setEndValue(shadow_offset_default);
    anim_shadow_offset->start();

    update();
}

void BetterButton::mouseMoveEvent(QMouseEvent *e){
    QPushButton::mouseMoveEvent(e);
    if(is_hovered){
        mouse_pos = e->pos();
        update();
    }
}

void BetterButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if (e->button() == Qt::LeftButton) {
        is_pressed = true;
        mouse_pos = e->pos();

        anim_shadow_offset->stop();
        anim_shadow_offset->setStartValue(cur_shadow_offset);
        anim_shadow_offset->setEndValue(shadow_offset_hover * 0.5);
        anim_shadow_offset->setDuration(anim_duration / 2);
        anim_shadow_offset->start();

        update();
    }
}

void BetterButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if (e->button() == Qt::LeftButton && is_pressed) {
        is_pressed = false;
        mouse_pos = e->pos();

        anim_shadow_offset->stop();
        anim_shadow_offset->setStartValue(cur_shadow_offset);
        cur_shadow_offset = is_hovered ? shadow_offset_hover : shadow_offset_default;
        anim_shadow_offset->setEndValue(shadow_offset_hover * 0.5);
        anim_shadow_offset->setDuration(anim_duration / 2);
        anim_shadow_offset->start();

        update();
    }
}

QColor BetterButton::get_color_current_grad_outer(){
    return color_current_grad_outer;
}

void BetterButton::set_color_current_grad_outer(const QColor& c){
    color_current_grad_outer = c;
}

qreal BetterButton::get_cur_shadow_offset(){
    return cur_shadow_offset;
}

void BetterButton::set_cur_shadow_offset(const qreal& c){
    cur_shadow_offset = c;
}

















