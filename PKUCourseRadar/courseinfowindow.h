#ifndef COURSEINFOWINDOW_H
#define COURSEINFOWINDOW_H

#include "utils.h"
class RadarWindow;
class Course;
class MyCoursesWindow;

namespace Ui {
class CourseInfoWindow;
}

class CourseInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CourseInfoWindow(QWidget *parent, QVector<QUuid> courseIds, int day, int session);
    ~CourseInfoWindow();
    QVector<QUuid> courseIds;
    void sync_list();
    int day, session;
private slots:
    void on_l_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_l_list_itemDoubleClicked(QListWidgetItem *item);
    void onItemRightClicked(const QPoint& pos);
private:
    Ui::CourseInfoWindow *ui;
signals:
    void changed();
};

#endif // COURSEINFOWINDOW_H
