#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

public slots:
    void on_btn_reg_or_login_clicked();
private slots:
    void on_btn_import_clicked();
    void on_btn_export_clicked();
    void on_language_clicked();
};

#endif // LOGINWINDOW_H
