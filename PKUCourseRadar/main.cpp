#include "homewindow.h"
#include "coursemanager.h"
#include "mycourseswindow.h"
#include "loginwindow.h"
#include "bettermessagebox.h"
#include "jsondataaccessor.h"
#include "dataaccessor.h"
int main(int argc, char *argv[])
{
    QIcon::setThemeName("breeze");
    QApplication a(argc, argv);
    DataAccessor::theDataAccessor = new JsonDataAccessor();
    LoginWindow w;
    w.show();
    return a.exec();
}
