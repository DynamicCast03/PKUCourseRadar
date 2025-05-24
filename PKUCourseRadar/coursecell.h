#ifndef COURSECELL_H
#define COURSECELL_H

#include "utils.h"

class CourseCell : public QWidget
{
    Q_OBJECT
public:
    explicit CourseCell(QWidget *parent = nullptr, const QString& displayText = "");
    void setDisplayText(const QString& str);
    int x, y;
signals:
    void clicked();

protected:
    void enterEvent(QEnterEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
private:
    QLabel* textLabel;
    QVBoxLayout* layout;
    QColor baseColor;
    QColor hoverColor;
    QColor pressedColor;
    QColor currentColor;
    QVariantAnimation* colorAnimation;
private slots:
    void onAnimationValueChanged(const QVariant& value);
};

#endif // COURSECELL_H
