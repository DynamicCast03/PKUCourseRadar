#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "homewindow.h"
#include "jsondataaccessor.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
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
        QMessageBox::warning(this, "登录/注册", "用户名或密码不能为空。");
        return;
    }
    QString user_uuid_str = JsonDataAccessor::userLogin(username, password);
    if (!user_uuid_str.isEmpty()) {
        QMessageBox::information(this, "登录成功", "登录成功！");
        QUuid user_uuid = QUuid(user_uuid_str);
        JsonDataAccessor::initManager(user_uuid);
        HomeWindow* home_window = new HomeWindow(user_uuid);
        home_window->show();
        this->close();
    } else {
        bool registered = JsonDataAccessor::userRegister(username, password);
        if (registered) {
            QMessageBox::information(this, "注册成功", "用户注册成功！");
            user_uuid_str = JsonDataAccessor::userLogin(username, password);
            if (!user_uuid_str.isEmpty()) {
                QUuid user_uuid = QUuid(user_uuid_str);
                JsonDataAccessor::initManager(user_uuid);
                HomeWindow* home_window = new HomeWindow(user_uuid);
                home_window->show();
                this->close();
            } else {
                QMessageBox::critical(this, "错误", "注册成功但登录失败，请联系管理员。");
            }
        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误。");
        }
    }
}

void LoginWindow::on_btn_import_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "选择数据库文件", "", "JSON Files (*.json)");
    if (file_path.isEmpty()) {
        return;
    }

    QFile source_file(file_path);
    if (!source_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "导入失败", "无法打开源文件进行读取。");
        return;
    }

    QByteArray file_content = source_file.readAll();
    source_file.close();

    QString database_file_path = QCoreApplication::applicationDirPath() + "/database.json";
    QFile destination_file(database_file_path);

    if (!destination_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "导入失败", "无法打开目标数据库文件进行写入。");
        return;
    }

    if (destination_file.write(file_content) == -1) {
        QMessageBox::critical(this, "导入失败", "写入数据库文件失败。");
        destination_file.close();
        return;
    }

    destination_file.close();
    QMessageBox::information(this, "导入成功", "数据库已成功导入并覆盖。");
}

void LoginWindow::on_btn_export_clicked()
{
    QString database_file_path = QCoreApplication::applicationDirPath() + "/database.json";
    QFile source_file(database_file_path);

    if (!source_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "导出失败", "无法打开源数据库文件进行读取。");
        return;
    }

    QString file_path = QFileDialog::getSaveFileName(this, "保存数据库文件", "", "JSON Files (*.json)");
    if (file_path.isEmpty()) {
        source_file.close();
        return;
    }

    QByteArray file_content = source_file.readAll();
    source_file.close();

    QFile destination_file(file_path);
    if (!destination_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "导出失败", "无法打开目标文件进行写入。");
        return;
    }

    if (destination_file.write(file_content) == -1) {
        QMessageBox::critical(this, "导出失败", "写入文件失败。");
        destination_file.close();
        return;
    }

    destination_file.close();
    QMessageBox::information(this, "导出成功", "数据库已成功导出。");
}

