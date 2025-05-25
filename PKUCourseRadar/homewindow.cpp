#include "homewindow.h"
#include "ui_homewindow.h"
#include "aboutus.h"
#include "en_US.h"
#include "zh_CN.h"

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
    CourseManager::theManager.writeToFile(file);
    delete ui;
}

void HomeWindow::readCourses(){
    config_path = QDir(QCoreApplication::applicationDirPath()).filePath("courses.json");
    qDebug() << config_path << Qt::endl;
    QFile file(config_path);
    if(file.exists()){
        CourseManager::theManager.readFromFile(file);
    } else {
        file.open(QFile::WriteOnly | QFile::Text);
    }
}


void HomeWindow::on_btn_import_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("选择包含课程信息的文件"), "", tr("JSON (*.json);;所有文件 (*)"));
    if(filepath.isEmpty()) return;
    QFile file(filepath);
    bool success = CourseManager::theManager.readFromFile(file);
    if(success){
        QMessageBox::information(this, tr("导入成功"), tr("已导入课程信息！"));
    } else {
        QMessageBox::critical(this, tr("导入失败"), tr("导入失败，请检查Json格式是否符合要求，以及是否存在重复的课程名称。"));
    }
}


void HomeWindow::on_btn_start_clicked()
{
    radar_window = new RadarWindow(this);
    radar_window->exec();
}


void HomeWindow::on_btn_about_clicked()
{
    AboutUs* about = new AboutUs();
    about->exec();
}


void HomeWindow::on_radio_english_clicked()
{
    QTranslator* translator = new QTranslator();
    if (translator->load(en_US_qm, en_US_qm_len)) {
        QCoreApplication::installTranslator(translator);
    }
    ui->retranslateUi(this);
}


void HomeWindow::on_radio_chinese_clicked()
{
    QTranslator* translator = new QTranslator();
    if (translator->load(zh_CN_qm, zh_CN_qm_len)) {
        QCoreApplication::installTranslator(translator);
    }
    ui->retranslateUi(this);
}

