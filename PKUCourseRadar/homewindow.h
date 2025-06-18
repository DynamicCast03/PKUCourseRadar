#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include "utils.h"
#include "coursemanager.h"
#include "debug_utils.h"
#include "radarwindow.h"
#include "mycourseswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HomeWindow;
}
QT_END_NAMESPACE

class HomeWindow : public QDialog
{
    Q_OBJECT

public:
    HomeWindow(QUuid user_uuid, QWidget *parent = nullptr);
    void readCourses();
    ~HomeWindow();
    QString config_path;
    RadarWindow *radar_window;
    MyCoursesWindow* my_like=new MyCoursesWindow;
    QUuid user_uuid;
    void closeEvent(QCloseEvent* e) override;
private slots:
    void on_btn_import_clicked();
    void on_btn_start_clicked();
    void on_btn_about_clicked();

    void on_radio_english_clicked();

    void on_radio_chinese_clicked();

    void on_btn_mylesson_clicked();

private:
    Ui::HomeWindow *ui;
};
#endif // HOMEWINDOW_H
