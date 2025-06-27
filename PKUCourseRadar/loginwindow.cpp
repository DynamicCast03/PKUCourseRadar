#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "homewindow.h"
#include "jsondataaccessor.h"
#include "bettermessagebox.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>
#include "en_US.h"
#include "zh_CN.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    if(CourseManager::theManager.curLanguage){
        ui->language->setText("🌏English");

    } else {
        ui->language->setText("🌏简体中文");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btn_reg_or_login_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_pwd->text();

    if (username.isEmpty() || password.isEmpty()) {
        BetterMessageBox::info(this, tr("登录/注册"), tr("用户名或密码不能为空。"));
        return;
    }
    QString user_uuid_str = DataAccessor::theDataAccessor->userLogin(username, password);
    if (!user_uuid_str.isEmpty()) {
        BetterMessageBox::info(this, tr("登录成功"), tr("登录成功！"));
        QUuid user_uuid = QUuid(user_uuid_str);
        DataAccessor::theDataAccessor->initManager(user_uuid);
        HomeWindow* home_window = new HomeWindow(user_uuid);
        home_window->show();
        this->close();
    } else {
        bool registered = DataAccessor::theDataAccessor->userRegister(username, password);
        if (registered) {
            BetterMessageBox::info(this, tr("注册成功"), tr("用户注册成功！"));
            user_uuid_str = DataAccessor::theDataAccessor->userLogin(username, password);
            if (!user_uuid_str.isEmpty()) {
                QUuid user_uuid = QUuid(user_uuid_str);
                DataAccessor::theDataAccessor->initManager(user_uuid);
                HomeWindow* home_window = new HomeWindow(user_uuid);
                home_window->show();
                this->close();
            } else {
                BetterMessageBox::info(this, tr("错误"), tr("注册成功但登录失败，请联系管理员。"));
            }
        } else {
            BetterMessageBox::info(this, tr("登录失败"), tr("用户名或密码错误。"));
        }
    }
}

void LoginWindow::on_btn_import_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("选择数据库文件"), "", tr("JSON Files (*.json)"));
    if (file_path.isEmpty()) {
        return;
    }

    QFile source_file(file_path);
    if (!source_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        BetterMessageBox::info(this, tr("导入失败"), tr("无法打开源文件进行读取。"));
        return;
    }

    QByteArray file_content = source_file.readAll();
    source_file.close();

    QString database_file_path = QCoreApplication::applicationDirPath() + "/database.json";
    QFile destination_file(database_file_path);

    if (!destination_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        BetterMessageBox::info(this, tr("导入失败"), tr("无法打开目标数据库文件进行写入。"));
        return;
    }

    if (destination_file.write(file_content) == -1) {
        BetterMessageBox::info(this, tr("导入失败"), tr("写入数据库文件失败。"));
        destination_file.close();
        return;
    }

    destination_file.close();
    BetterMessageBox::info(this, tr("导入成功"), tr("数据库已成功导入并覆盖。"));
}

void LoginWindow::on_btn_export_clicked()
{
    QString database_file_path = QCoreApplication::applicationDirPath() + "/database.json";
    QFile source_file(database_file_path);

    if (!source_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        BetterMessageBox::info(this, tr("导出失败"), tr("无法打开源数据库文件进行读取。"));
        return;
    }

    QString file_path = QFileDialog::getSaveFileName(this, tr("保存数据库文件"), "", tr("JSON Files (*.json)"));
    if (file_path.isEmpty()) {
        source_file.close();
        return;
    }

    QByteArray file_content = source_file.readAll();
    source_file.close();

    QFile destination_file(file_path);
    if (!destination_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        BetterMessageBox::info(this, tr("导出失败"), tr("无法打开目标文件进行写入。"));
        return;
    }

    if (destination_file.write(file_content) == -1) {
        BetterMessageBox::info(this, tr("导出失败"), tr("写入文件失败。"));
        destination_file.close();
        return;
    }

    destination_file.close();
    BetterMessageBox::info(this, tr("导出成功"), tr("数据库已成功导出。"));
}

void LoginWindow::on_language_clicked()
{
    CourseManager::theManager.curLanguage ^= 1;
    if(CourseManager::theManager.curLanguage){
        QTranslator* translator = new QTranslator();
        if (translator->load(PKUCourseRadar_en_US_qm, PKUCourseRadar_en_US_qm_len)) {
            QCoreApplication::installTranslator(translator);
        }
        ui->retranslateUi(this);
        ui->language->setText("🌏English");

    } else {
        QTranslator* translator = new QTranslator();
        if (translator->load(PKUCourseRadar_zh_CN_qm, PKUCourseRadar_zh_CN_qm_len)) {
            QCoreApplication::installTranslator(translator);
        }
        ui->retranslateUi(this);
        ui->language->setText("🌏简体中文");

    }

}

