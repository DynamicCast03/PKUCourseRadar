#ifndef RADARWINDOW_H
#define RADARWINDOW_H

#include "utils.h"
#include "course.h"
#include "coursemanager.h"
#include "courseinfowindow.h"
#include "mylesson.h"

namespace Ui {
class RadarWindow;
}

class RadarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RadarWindow(QWidget *parent = nullptr);
    ~RadarWindow();
    void reSearchCourses();
    void showTags();
    bool isFree(const Course& course);
    QVector<QVector<QSet<Course>>> nowTable;
    QVector<QVector<int>> nowDisabled;
private slots:
    void on_i_name_textChanged(const QString &str);
    void on_i_teacher_textChanged(const QString &str);
    void on_i_building_textChanged(const QString &str);
    void on_i_room_textChanged(const QString &str);
    void on_i_tags_textChanged(const QString &str);
    void on_l_all_tags_itemDoubleClicked(QListWidgetItem *item);
    void on_l_selected_tags_itemDoubleClicked(QListWidgetItem *item);
    void cellClicked(int x, int y);
    void cellRightClicked(int x, int y, bool disabled);
private:
    Ui::RadarWindow *ui;
    QString nowName;
    QString nowTeacher;
    QString nowBuilding;
    QString nowRoom;
    QSet<QString> nowReadyTags, nowSelectedTags;
    QSet<Course> nowCourses;
    MyLesson my_like_lesson;
    QString nowSearchingTags;
};

#endif // RADARWINDOW_H
