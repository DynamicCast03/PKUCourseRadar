#ifndef MYCOURSESWINDOW_H
#define MYCOURSESWINDOW_H

#include <QDialog>
#include "course.h"
#include "utils.h"
#include "courseinfowindow.h"

namespace Ui {
class MyLesson;
}

class MyCoursesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MyCoursesWindow(QWidget *parent = nullptr);
    ~MyCoursesWindow();
    void syncCells();
signals:
    void clicked();
private slots:
    void cellclicked(int x,int y);
private:
    Ui::MyLesson *ui;

};

#endif // MYCOURSESWINDOW_H
