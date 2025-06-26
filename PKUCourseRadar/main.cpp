#include "homewindow.h"
#include "coursemanager.h"
#include "mycourseswindow.h"
#include "loginwindow.h"
#include "bettermessagebox.h"
int main(int argc, char *argv[])
{
    QIcon::setThemeName("breeze");
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}
