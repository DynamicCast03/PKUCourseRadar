#ifndef BETTERMESSAGEBOX_H
#define BETTERMESSAGEBOX_H

#include "utils.h"

class BetterMessageBox : QObject{
    Q_OBJECT
public:
    static void info(QWidget *parent, const QString &title, const QString &text);
};

#endif // BETTERMESSAGEBOX_H
