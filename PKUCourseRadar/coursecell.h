#ifndef COURSECELL_H
#define COURSECELL_H

#include "utils.h"
#include "mycourseswindow.h"


class CourseCell : public QWidget
{
    Q_OBJECT
public:
    explicit CourseCell(QWidget *parent = nullptr, const QString& displayText = "");
    void setDisplayText(const QString& str);
    int x, y, num = 0;
    bool disabled, canDisable;
    void refresh();
signals:
    void clicked();
    void rightClicked(bool disabled);
protected:
    void enterEvent(QEnterEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent* e) override;
private:
    QLabel* textLabel;
    QVBoxLayout* layout;
    QColor baseColor;
    QColor hoverColor;
    QColor pressedColor;
    QColor disabledColor;
    QColor currentColor;
    QVariantAnimation* colorAnimation;
    QString nowOriginalText;
private slots:
    void onAnimationValueChanged(const QVariant& value);
};

#endif // COURSECELL_H
