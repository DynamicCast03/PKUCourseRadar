#ifndef COURSEINFOWINDOW_H
#define COURSEINFOWINDOW_H

#include "utils.h"
class RadarWindow;
class Course;
class MyLesson;

namespace Ui {
class CourseInfoWindow;
}

class CourseInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CourseInfoWindow(QWidget *parent = nullptr, RadarWindow *radarWindow = nullptr, int x = 0, int y = 0);
    explicit CourseInfoWindow(QWidget *parent = nullptr, MyLesson *mylesson = nullptr, int x = 0, int y = 0);
    bool comefromMy=false;
    ~CourseInfoWindow();
    RadarWindow *radar;
    MyLesson* my;
    int x, y;
    QVector<Course> courses;

private slots:
    void on_l_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_l_list_itemDoubleClicked(QListWidgetItem *item);

    //void on_l_list_itemClicked(QListWidgetItem *item);

private:
    Ui::CourseInfoWindow *ui;
private slots:
    void onItemRightClicked(const QPoint& pos);

private:
    void moveItemToTop(const QString& courseName);
};

#endif // COURSEINFOWINDOW_H
