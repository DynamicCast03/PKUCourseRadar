#include "coursecell.h"

CourseCell::CourseCell(QWidget *parent, const QString& displayText)
    : QWidget{parent},textLabel(new QLabel()),layout(new QVBoxLayout()),
      baseColor(QColor(230, 230, 230)),
      hoverColor(QColor(200, 200, 200)),
      pressedColor(QColor(150, 150, 150)),
      currentColor(baseColor),
      colorAnimation(new QVariantAnimation(this))
{
    layout->addWidget(textLabel);
    this->textLabel->setText(displayText);
    this->textLabel->setAlignment(Qt::AlignCenter);
    this->textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setLayout(layout);
    connect(colorAnimation, &QVariantAnimation::valueChanged, this, &CourseCell::onAnimationValueChanged);
    colorAnimation->setDuration(500);
}

void CourseCell::setDisplayText(const QString& str){
    this->textLabel->setText(str);
}

void CourseCell::mousePressEvent(QMouseEvent* e){
    if(e->button() == Qt::LeftButton){
        emit clicked();
        colorAnimation->setDuration(100);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(pressedColor);
        colorAnimation->start();
    }
    QWidget::mousePressEvent(e);
}

void CourseCell::mouseReleaseEvent(QMouseEvent* e){
    if(e->button() == Qt::LeftButton){
        colorAnimation->setDuration(300);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(baseColor);
        colorAnimation->start();
    }
    QWidget::mouseReleaseEvent(e);
}

void CourseCell::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    painter.fillRect(0, 0, width() - 1, height() - 1, currentColor);
    painter.setPen(QPen(QColor(100, 100, 100), 1));
    painter.drawRect(0, 0, width() - 1, height() - 1);
    QWidget::paintEvent(e);
}

void CourseCell::onAnimationValueChanged(const QVariant& value){
    currentColor = value.value<QColor>();
    update();
}

void CourseCell::enterEvent(QEnterEvent* e){
    colorAnimation->setDuration(100);
    colorAnimation->setStartValue(currentColor);
    colorAnimation->setEndValue(hoverColor);
    colorAnimation->start();
    QWidget::enterEvent(e);
}

void CourseCell::leaveEvent(QEvent* e){
    colorAnimation->setDuration(200);
    colorAnimation->setStartValue(currentColor);
    colorAnimation->setEndValue(baseColor);
    colorAnimation->start();
    QWidget::leaveEvent(e);
}
