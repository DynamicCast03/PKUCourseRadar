#include "homewindow.h"
#include "ui_homewindow.h"
#include "aboutus.h"
#include "mycourseswindow.h"
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
    DataAccessor::theDataAccessor->saveManager(user_uuid);
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

