#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QDialog>

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
    ~HomeWindow();

private:
    Ui::HomeWindow *ui;
};
#endif // HOMEWINDOW_H
