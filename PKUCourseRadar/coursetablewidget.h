#ifndef COURSETABLEWIDGET_H
#define COURSETABLEWIDGET_H

#include "utils.h"
#include "coursecell.h"


class CourseTableWidget : public QWidget
{
    Q_OBJECT
public:
    bool frommy=0;
    explicit CourseTableWidget(QWidget *parent /*= nullptr*/);
    QVector<QVector<CourseCell*>> cells; // 两个下标都从1开始, 0行0列是表头
    void refreshAllCells();
signals:
    void cellClicked(int x, int y);
    void cellRightClicked(int x, int y, bool disabled);
private slots:
    void handleCellClicked();
    void handleCellRightClicked(bool disabled);
private:
    QGridLayout *layout;
};

#endif // COURSETABLEWIDGET_H
