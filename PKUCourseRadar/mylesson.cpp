#include "mylesson.h"
#include "ui_mylesson.h"
#include "mylike.h"


MyLesson::MyLesson(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyLesson)
{
    ui->setupUi(this);
    lesson_table = QVector<QVector<QSet<Course>>>(7, QVector<QSet<Course>>(12));
    for(auto pt=MyLike::the_liked.All_Liked.begin();pt!=MyLike::the_liked.All_Liked.end();pt++){
        for(int i=0;i<7;i++){
            for(int j=0;j<12;j++){
                if(pt->ct.table[i][j]){
                    ui->MyTable->cells[i][j]->num++;
                    lesson_table[i][j].insert(*pt);

                }
            }
        }
    }
    for(int i=0;i<7;i++){
        for(int j=0;j<12;j++){
            if(ui->MyTable->cells[i][j]->num){
                ui->MyTable->cells[i][j]->FirstLesson=lesson_table[i][j].begin()->name;
            }
        }
    }
    for(int i=0;i<=6;i++){
        for(int j=0;j<=11;j++){
            if(ui->MyTable->cells[i][j]->num==0){
                ui->MyTable->cells[i][j]->disabled=true;
                ui->MyTable->cells[i][j]->dontwanted=true;
            }
        }
    }
    connect(ui->MyTable,&CourseTableWidget::cellClicked,this,&MyLesson::cellclicked);
}

void MyLesson::cellclicked(int x,int y){
    CourseInfoWindow* window=new CourseInfoWindow(this,this,x,y);
    window->exec();
}

MyLesson::~MyLesson()
{
    delete ui;
}
