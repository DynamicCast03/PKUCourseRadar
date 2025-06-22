#include "homewindow.h"
#include "ui_homewindow.h"
#include "aboutus.h"
#include "mycourseswindow.h"
#include "en_US.h"
#include "zh_CN.h"
#include "jsondataaccessor.h"
#include "loginwindow.h"

HomeWindow::HomeWindow(QUuid user_uuid, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HomeWindow), user_uuid(user_uuid)
{
    ui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::closeEvent(QCloseEvent* e){
    JsonDataAccessor::saveManager(user_uuid);
    QDialog::closeEvent(e);
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
    if (translator->load(PKUCourseRadar_en_US_qm, PKUCourseRadar_en_US_qm_len)) {
        QCoreApplication::installTranslator(translator);
    }
    ui->retranslateUi(this);
}


void HomeWindow::on_radio_chinese_clicked()
{
    QTranslator* translator = new QTranslator();
    if (translator->load(PKUCourseRadar_zh_CN_qm, PKUCourseRadar_zh_CN_qm_len)) {
        QCoreApplication::installTranslator(translator);
    }
    ui->retranslateUi(this);
}


void HomeWindow::on_btn_mylesson_clicked()
{
    my_like=new MyCoursesWindow(this);
    my_like->exec();
}


void HomeWindow::on_btn_exit_clicked()
{
    LoginWindow* w = new LoginWindow();
    w->show();
    close();
}

