#include "courseinfowindow.h"
#include "ui_courseinfowindow.h"
#include "radarwindow.h"

CourseInfoWindow::CourseInfoWindow(QWidget *parent, RadarWindow *radarWindow, int x, int y)
    : QDialog(parent)
    , ui(new Ui::CourseInfoWindow)
    , radar(radarWindow)
    , x(x)
    , y(y)
{
    ui->setupUi(this);
    QSet<Course> coursesSet = radar->nowTable[x - 1][y - 1];
    for(Course course : coursesSet)
    {
        courses.push_back(course);
        ui -> l_list -> addItem(new QListWidgetItem(course.name));
    }

}

CourseInfoWindow::~CourseInfoWindow(){
    delete ui;
}

void CourseInfoWindow::on_l_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int row = ui -> l_list -> row(current);
    ui -> b_info -> setText(courses[row].description());
}

