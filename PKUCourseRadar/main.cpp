#include "homewindow.h"
#include "coursemanager.h"
#include "debug_utils.h"
#include "mycourseswindow.h"
#include "loginwindow.h"
int main(int argc, char *argv[])
{
    QIcon::setThemeName("breeze");
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

    return a.exec();
}
