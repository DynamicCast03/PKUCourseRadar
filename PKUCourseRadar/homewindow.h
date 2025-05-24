#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include "utils.h"
#include "coursemanager.h"
#include "debug_utils.h"
#include "radarwindow.h"

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
    QString config_path;
    RadarWindow *radar_window;
private slots:
    void on_btn_import_clicked();
    void on_btn_start_clicked();
    void on_btn_about_clicked();

private:
    Ui::HomeWindow *ui;
};
#endif // HOMEWINDOW_H
