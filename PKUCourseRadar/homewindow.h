#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include "utils.h"
#include "coursemanager.h"
#include "debug_utils.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HomeWindow;
}
QT_END_NAMESPACE

class HomeWindow : public QDialog
{
    Q_OBJECT

public:
    HomeWindow(QWidget *parent = nullptr);
    void readCourses();
    ~HomeWindow();
    CourseManager course_manager;
    QString config_path;

private slots:
    void on_btn_import_clicked();

private:
    Ui::HomeWindow *ui;
};
#endif // HOMEWINDOW_H
