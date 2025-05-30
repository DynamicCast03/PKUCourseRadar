#ifndef MYLESSON_H
#define MYLESSON_H

#include <QDialog>
#include "course.h"
#include "utils.h"
#include "courseinfowindow.h"

namespace Ui {
class MyLesson;
}

class MyLesson : public QDialog
{
    Q_OBJECT

public:
    friend class CourseInfoWindow;
    QVector<QVector<QSet<Course>>> lesson_table;
    explicit MyLesson(QWidget *parent = nullptr);
    ~MyLesson();
signals:
    void clicked();
private slots:
    void cellclicked(int x,int y);

private:
    Ui::MyLesson *ui;

};

#endif // MYLESSON_H
