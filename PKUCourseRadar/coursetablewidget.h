#ifndef COURSETABLEWIDGET_H
#define COURSETABLEWIDGET_H

#include "utils.h"
#include "coursecell.h"


class CourseTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CourseTableWidget(QWidget *parent /*= nullptr*/);
    QVector<QVector<CourseCell*>> cells; // 两个下标都从1开始, 0行0列是表头
    void refreshAllCells();
    CourseCell* getCell(int day, int session);
    void setCanDisable(bool canDisable);
signals:
    void cellClicked(int x, int y); // x:[1, 7], y:[1, 12]
    void cellRightClicked(int x, int y, bool disabled); // x:[1, 7], y:[1, 12]
private slots:
    void handleCellClicked();
    void handleCellRightClicked(bool disabled);
private:
    QGridLayout *layout;
};

#endif // COURSETABLEWIDGET_H
