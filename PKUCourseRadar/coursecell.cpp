#include "coursecell.h"

CourseCell::CourseCell(QWidget *parent, const QString& displayText)
    : QWidget{parent},textLabel(new QLabel()),layout(new QVBoxLayout()),
      baseColor(QColor(230, 230, 230)),
      hoverColor(QColor(200, 200, 200)),
      pressedColor(QColor(150, 150, 150)),
      disabledColor(QColor(100, 100, 100)),
      currentColor(baseColor),
      colorAnimation(new QVariantAnimation(this))
{
    layout->addWidget(textLabel);
    if(!displayText.isEmpty()){
        constText = displayText;
        isConstText = true;
    } else {
        isConstText = false;
    }
    this->textLabel->setAlignment(Qt::AlignCenter);
    this->textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textLabel -> setStyleSheet("color: black;");
    setLayout(layout);
    connect(colorAnimation, &QVariantAnimation::valueChanged, this, &CourseCell::onAnimationValueChanged);
    colorAnimation->setDuration(500);
}

void CourseCell::setDisplayText(const QString& str){
    this->textLabel->setText(str);
}

void CourseCell::mousePressEvent(QMouseEvent* e){
    if(!disabled && e->button() == Qt::LeftButton){
        emit clicked();
        colorAnimation->setDuration(100);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(pressedColor);
        colorAnimation->start();
    } else if(e->button() == Qt::RightButton){
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
    if(!disabled && e->button() == Qt::LeftButton){
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
    if(isConstText){
        setDisplayText(constText);
    } else if(!disabled){
        setDisplayText(QString::number(num));
    } else{
        setDisplayText(tr("没空:("));
    }
    QWidget::paintEvent(e);
}

void CourseCell::onAnimationValueChanged(const QVariant& value){
    currentColor = value.value<QColor>();
    update();
}

void CourseCell::enterEvent(QEnterEvent* e){
    if(!disabled){
        colorAnimation->setDuration(100);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(hoverColor);
        colorAnimation->start();
    }
    QWidget::enterEvent(e);
}

void CourseCell::leaveEvent(QEvent* e){
    if(!disabled){
        colorAnimation->setDuration(200);
        colorAnimation->setStartValue(currentColor);
        colorAnimation->setEndValue(baseColor);
        colorAnimation->start();
    }
    QWidget::leaveEvent(e);
}

