#ifndef COURSETABLEWIDGET_H
#define COURSETABLEWIDGET_H

#include "utils.h"
#include "coursecell.h"

class CourseTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CourseTableWidget(QWidget *parent = nullptr);
    QVector<QVector<CourseCell*>> cells; // 两个下标都从1开始, 0行0列是表头
signals:
    void cellClicked(int x, int y);
private slots:
    void handleCellClicked();
private:
    QGridLayout *layout;
};

#endif // COURSETABLEWIDGET_H
