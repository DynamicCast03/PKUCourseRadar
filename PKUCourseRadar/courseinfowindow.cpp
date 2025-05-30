#include "courseinfowindow.h"
#include "ui_courseinfowindow.h"
#include "radarwindow.h"
#include "mylesson.h"
#include "mylike.h"
#include "ui_mylesson.h"

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
        if(course.liked)ui -> l_list -> addItem(new QListWidgetItem("⭐ "+course.name));
        else ui -> l_list -> addItem(new QListWidgetItem(course.name));
    }

}

CourseInfoWindow::CourseInfoWindow(QWidget*parent,MyLesson* mylesson,int x,int y)
    :QDialog(parent)
    ,ui(new Ui::CourseInfoWindow)
    ,my(mylesson)
    ,x(x)
    ,y(y)
    ,comefromMy(true){
    ui->setupUi(this);
    QSet<Course>coursesSet=my->lesson_table[x-1][y-1];
    for(Course course:coursesSet){
        courses.push_back(course);
        ui->l_list->addItem((new QListWidgetItem(course.name)));
    }
    ui->l_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->l_list, &QListWidget::customContextMenuRequested,
            this, &CourseInfoWindow::onItemRightClicked);

}

void CourseInfoWindow::onItemRightClicked(const QPoint& pos) {
    QListWidgetItem* item = ui->l_list->itemAt(pos);
    if(item) {
        moveItemToTop(item->text());
    }
}
CourseInfoWindow::~CourseInfoWindow(){
    delete ui;
}

void CourseInfoWindow::moveItemToTop(const QString&coursename){
    my->ui->MyTable->cells[x-1][y-1]->FirstLesson=coursename;
    QMessageBox::information(this, "提示", "已置顶！");
}

void CourseInfoWindow::on_l_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int row = ui -> l_list -> row(current);
    ui -> b_info -> setText(courses[row].description());
}

void CourseInfoWindow::on_l_list_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui -> l_list -> row(item);
    if(!courses[row].liked){
        QMessageBox::information(this, "提示", "已选中！");
        for(int i=0;i<7;i++){
            for(int j=0;j<12;j++){
                for(auto& course: radar->nowTable[i][j]){
                    if(course.name==courses[row].name&&course.room==courses[row].room){
                        Course another=course;
                        another.liked=true;
                        radar->nowTable[i][j].remove(course);
                        radar->nowTable[i][j].insert(another);
                    }
                }
            }
        }
        QString originalText = item->text();
        if (!originalText.startsWith("⭐")) {
            item->setText("⭐ " + originalText);
        }
        courses[row].liked=true;
        MyLike::the_liked.All_Liked.push_back(courses[row]);
    }else{
        MyLike::the_liked.All_Liked.removeOne(courses[row]);
        QMessageBox::information(this, "提示", "已退选！");
        QString currentText = item->text();
        if(currentText.startsWith("⭐")){
            QString originalText = currentText.mid(2);
            item->setText(originalText);
        }
        courses[row].liked=false;
        if(comefromMy){
            item->setHidden(true);
            ui->b_info->setText("");
            for(int i=0;i<7;i++){
                for(int j=0;j<12;j++){
                    for(auto &course:my->lesson_table[i][j]){
                        if(course.name==courses[row].name&&course.room==courses[row].room){
                            my->lesson_table[i][j].remove(course);
                        }
                    }
                }
            }
            for(int i=0;i<7;i++){
                for(int j=0;j<12;j++){
                    if(!my->lesson_table[i][j].size()){
                        my->ui->MyTable->cells[i][j]->disabled=1;
                        my->ui->MyTable->cells[i][j]->dontwanted=1;
                    }else{
                        my->ui->MyTable->cells[i][j]->FirstLesson=my->lesson_table[i][j].begin()->name;
                    }
                }
            }
            //my->ui->MyTable->cells[0][0]->update();
           //my->ui->MyTable->cells[0][0]->setDisplayText("???");
        }
    }
}



