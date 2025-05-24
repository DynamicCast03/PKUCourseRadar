#ifndef COURSEINFOWINDOW_H
#define COURSEINFOWINDOW_H

#include "utils.h"
class RadarWindow;
class Course;

namespace Ui {
class CourseInfoWindow;
}

class CourseInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CourseInfoWindow(QWidget *parent = nullptr, RadarWindow *radarWindow = nullptr, int x = 0, int y = 0);
    ~CourseInfoWindow();
    RadarWindow *radar;
    int x, y;
    QVector<Course> courses;

private slots:
    void on_l_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::CourseInfoWindow *ui;
};

#endif // COURSEINFOWINDOW_H
