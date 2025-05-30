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
    /*if(!displayText.isEmpty()&&!nonono){
        constText = displayText;
        isConstText = true;
    } else {
        isConstText = false;
    }*/
    constText=displayText;
    this->textLabel->setAlignment(Qt::AlignCenter);
    this->textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textLabel -> setStyleSheet("color: black;");
    setLayout(layout);
    connect(colorAnimation, &QVariantAnimation::valueChanged, this, &CourseCell::onAnimationValueChanged);
    colorAnimation->setDuration(500);
}

void CourseCell::setDisplayText(const QString& str, bool hasCourse) {
    QString displayText=str;
    if(str.length() > 10) {
        int midPoint = str.length() / 2;
        while(midPoint > 0 && str[midPoint] != ' ' && str[midPoint] != '-') {
            midPoint--;
        }
        if(midPoint == 0) midPoint = str.length() / 2;

        displayText = str.left(midPoint) + "\n" + str.mid(midPoint);
    }

    this->textLabel->setText(displayText);
    this->textLabel->setWordWrap(true);

    if (hasCourse) {
        this->textLabel->setStyleSheet("color: rgb(25, 118, 210);");
    } else {
        this->textLabel->setStyleSheet("color: rgb(0, 0, 0);");
    }
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
        if(FirstLesson.isEmpty()) setDisplayText(QString::number(num));
        else{
            setDisplayText(FirstLesson,true);
        }
    } else if(!dontwanted){
        setDisplayText(tr("没空:("));
    } else{
        setDisplayText(tr("--"));
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

