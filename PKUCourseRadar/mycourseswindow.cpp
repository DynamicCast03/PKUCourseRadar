#include "mycourseswindow.h"
#include "mylike.h"
#include "coursemanager.h"
#include "ui_mycourseswindow.h"

MyCoursesWindow::MyCoursesWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::MyLesson)
{
    ui->setupUi(this);
    connect(ui->Table, &CourseTableWidget::cellClicked, this, &MyCoursesWindow::cellclicked);
    syncCells();
}

void MyCoursesWindow::syncCells()
{
    for (int i = 1; i <= 7; i++) {
        for (int j = 1; j <= 12; j++) {
            CourseCell* cell = ui->Table->getCell(i, j);
            if(CourseManager::theManager.getSelectedCourse(i, j) != QUuid()){
                QUuid uuid = CourseManager::theManager.getSelectedCourse(i, j);
                cell -> setDisplayText(CourseManager::theManager.AllCourses[uuid].name);
                continue;
            }
            int markedCourseNum = 0;
            for(Course &course : CourseManager::theManager.AllCourses) {
                if (course.include(i, j) && course.marked) {
                    markedCourseNum++;
                }
            }
            if(markedCourseNum) {
                cell -> setDisplayText(QString::number(markedCourseNum));
            } else {
                cell -> setDisplayText("---");
            }
            cell -> canDisable = cell -> disabled = false;
        }

    }
}
void MyCoursesWindow::cellclicked(int x, int y)
{
    QVector<QUuid> markedCourses;
    for(Course &course : CourseManager::theManager.AllCourses) {
        if (course.include(x, y) && course.marked) {
            markedCourses.push_back(course.id);
        }
    }
    CourseInfoWindow* window = new CourseInfoWindow(this, markedCourses, x, y);
    connect(window, &CourseInfoWindow::changed, this, &MyCoursesWindow::syncCells);
    window->show();
    syncCells();
}

MyCoursesWindow::~MyCoursesWindow()
{
    delete ui;
}
