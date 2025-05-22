#include "homewindow.h"
#include "coursemanager.h"
#include "debug_utils.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeWindow w;
    w.show();

    return a.exec();
}
