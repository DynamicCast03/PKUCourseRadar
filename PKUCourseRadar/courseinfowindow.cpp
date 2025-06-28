#include "courseinfowindow.h"
#include "mycourseswindow.h"
#include "radarwindow.h"
#include "ui_courseinfowindow.h"
#include "ui_mycourseswindow.h"
#include "commentbrowserwindow.h"

CourseInfoWindow::CourseInfoWindow(QWidget* parent, QVector<QUuid> courseIds, int day, int session)
    : QDialog(parent)
    , ui(new Ui::CourseInfoWindow)
    , courseIds(courseIds)
    , day(day)
    , session(session)
{
    ui->setupUi(this);
    lastRow = -1;
    // courses 是 QListWidget 的镜像, 需要保证二者一致, 因此修改 courses 时需要同步到 QListWidget, 调用 sync_list() 函数
    sync_list();
    ui->l_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->l_list, &QListWidget::customContextMenuRequested, this, &CourseInfoWindow::onItemRightClicked);
}

CourseInfoWindow::~CourseInfoWindow()
{
    delete ui;
}

void CourseInfoWindow::sync_list()
{
    std::sort(courseIds.begin(), courseIds.end(), [](QUuid a, QUuid b){
        if(CourseManager::theManager.AllCourses[a].rating() == CourseManager::theManager.AllCourses[b].rating())
            return CourseManager::theManager.AllCourses[a].id > CourseManager::theManager.AllCourses[b].id;
        return CourseManager::theManager.AllCourses[a].rating() > CourseManager::theManager.AllCourses[b].rating();
    });
    ui->l_list->clear();
    for (QUuid courseId : courseIds) {
        Course &course = CourseManager::theManager.AllCourses[courseId];
        if (course.id == CourseManager::theManager.getSelectedCourse(day, session))
            ui->l_list->addItem(new QListWidgetItem("👉 " + course.name));
        else if (course.marked)
            ui->l_list->addItem(new QListWidgetItem("⭐ " + course.name));
        else
            ui->l_list->addItem(new QListWidgetItem(course.name));
    }
}

void CourseInfoWindow::on_l_list_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(!current) return;
    int row = ui->l_list->row(current);
    lastRow = row;
    ui->b_info->setText(CourseManager::theManager.AllCourses[courseIds[row]].description());
    emit changed();
}

void CourseInfoWindow::onItemRightClicked(const QPoint& pos)
{
    QListWidgetItem* item = ui->l_list->itemAt(pos);
    if(!item) return;
    int row = ui->l_list->row(item);
    Course &course = CourseManager::theManager.AllCourses[courseIds[row]];
    course.marked = !course.marked;
    if (!course.marked){
        for(int i = 1; i <= 7; i++){
            for(int j = 1; j <= 12; j++){
                if(CourseManager::theManager.getSelectedCourse(i, j) == course.id){
                    CourseManager::theManager.getSelectedCourse(i, j) = QUuid();
                }
            }
        }
    }
    sync_list();
    emit changed();
}

void CourseInfoWindow::on_l_list_itemDoubleClicked(QListWidgetItem* item)
{
    if(!item) return;
    int row = ui->l_list->row(item);
    Course &course = CourseManager::theManager.AllCourses[courseIds[row]];
    // 此处 if 目的是保证同一时间只能有一个课程被选中
    if (CourseManager::theManager.getSelectedCourse(day, session) != course.id) {
        if(!course.marked) return; // 如果没有收藏, 就不能选中
        CourseManager::theManager.getSelectedCourse(day, session) = course.id;
    } else {
        CourseManager::theManager.getSelectedCourse(day, session) = QUuid(); // 空 uuid, 全 0
    }
    sync_list();
    emit changed();
}

void CourseInfoWindow::on_btn_view_comment_clicked()
{
    int row = ui->l_list->row(ui->l_list->currentItem());
    if(row >= 0){
        CommentBrowserWindow *cbw = new CommentBrowserWindow(courseIds[row], this);
        cbw->exec();
    } else if(lastRow >= 0){
        CommentBrowserWindow *cbw = new CommentBrowserWindow(courseIds[lastRow], this);
        cbw->exec();
    }
}

