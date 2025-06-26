#include "coursecell.h"

CourseCell::CourseCell(QWidget *parent, const QString& displayText)
    : QWidget{parent},textLabel(new QLabel()),layout(new QVBoxLayout()),
      baseColor(QColor(245, 245, 245, 100)),
      hoverColor(QColor(230, 230, 230)),
      pressedColor(QColor(200, 200, 200)),
      disabledColor(QColor(150, 150, 150)),
      currentColor(baseColor),
      colorAnimation(new QVariantAnimation(this))
{
    layout->addWidget(textLabel);
    this->textLabel->setAlignment(Qt::AlignCenter);
    this->textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QFont font = textLabel->font();
    font.setPixelSize(12);
    this->textLabel->setFont(font);
    setLayout(layout);
    connect(colorAnimation, &QVariantAnimation::valueChanged, this, &CourseCell::onAnimationValueChanged);
    colorAnimation->setDuration(500);
    setDisplayText(displayText);
}

void CourseCell::setDisplayText(const QString& str) {
    nowOriginalText = str;
    QFontMetrics fontMetrics(textLabel -> font());
    QString showText = fontMetrics.elidedText(nowOriginalText, Qt::ElideRight, textLabel -> width());
    textLabel -> setText(showText);
}

void CourseCell::resizeEvent(QResizeEvent *event) {
    setDisplayText(nowOriginalText);
    QWidget::resizeEvent(event);
}

void CourseCell::mousePressEvent(QMouseEvent* e){
    if(!(canDisable && disabled) && e->button() == Qt::LeftButton){
        emit clicked();
        colorAnimation->setDuration(100);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(pressedColor);
        colorAnimation->start();
    } else if(canDisable && e->button() == Qt::RightButton){
        if(!disabled){
            disabled = true;
            colorAnimation->setDuration(300);
            colorAnimation->setStartValue(currentColor);
            colorAnimation->setEndValue(disabledColor);
            colorAnimation->start();
        } else {
            disabled = false;
            colorAnimation->setDuration(300);
            colorAnimation->setStartValue(currentColor);
            colorAnimation->setEndValue(baseColor);
            colorAnimation->start();
        }
        emit rightClicked(disabled);
        update();
    }
    QWidget::mousePressEvent(e);
}

void CourseCell::mouseReleaseEvent(QMouseEvent* e){
    if(!(canDisable && disabled) && e->button() == Qt::LeftButton){
        colorAnimation->setDuration(300);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(baseColor);
        colorAnimation->start();
    }
    QWidget::mouseReleaseEvent(e);
}

void CourseCell::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    textLabel->setStyleSheet("background: none;");
    painter.fillRect(1, 1, width() - 2, height() - 2, currentColor);
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    painter.drawRect(1, 1, width() - 2, height() - 2);
    QWidget::paintEvent(e);
}

void CourseCell::onAnimationValueChanged(const QVariant& value){
    currentColor = value.value<QColor>();
    update();
}

void CourseCell::enterEvent(QEnterEvent* e){
    if(!(canDisable && disabled)){
        colorAnimation->setDuration(100);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(hoverColor);
        colorAnimation->start();
    }
    QWidget::enterEvent(e);
}

void CourseCell::leaveEvent(QEvent* e){
    if(!(canDisable && disabled)){
        colorAnimation->setDuration(200);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(baseColor);
        colorAnimation->start();
    }
    QWidget::leaveEvent(e);
}

void CourseCell::refresh(){
    if(!disabled){
        colorAnimation->setDuration(200);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(baseColor);
        colorAnimation->start();
    }
}
