#include "homewindow.h"
#include "ui_homewindow.h"

HomeWindow::HomeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    readCourses();
}

HomeWindow::~HomeWindow()
{
    QFile file(config_path);
    course_manager.writeToFile(file);
    delete ui;
}

void HomeWindow::readCourses(){
    config_path = QDir(QCoreApplication::applicationDirPath()).filePath("courses.json");
    qDebug() << config_path << Qt::endl;
    QFile file(config_path);
    if(file.exists()){
        course_manager.readFromFile(file);
    } else {
        file.open(QFile::WriteOnly | QFile::Text);
    }
    displayCourses(course_manager);
}


void HomeWindow::on_btn_import_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("选择包含课程信息的文件"), "", tr("JSON (*.json);;所有文件 (*)"));
    QFile file(filepath);
    bool success = course_manager.readFromFile(file);
    if(success){
        QMessageBox::information(this, tr("导入成功"), tr("已导入课程信息！"));
    } else {
        QMessageBox::critical(this, tr("导入失败"), tr("导入失败，请检查Json格式是否符合要求，以及是否存在重复的课程名称。"));
    }
}

