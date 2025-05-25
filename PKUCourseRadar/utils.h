#ifndef UTILS_H
#define UTILS_H

#include "stdc++.h"
#include <QDialog>
#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGridLayout>
#include <QtGui>
#include <QListWidgetItem>

class Utils{
public:
    static void setupWindow(QDialog* dialog, double xfactor, double ratio){
        QScreen *screen = QGuiApplication::primaryScreen();

        QRect screenGeometry = screen->geometry();

        int screenW = screenGeometry.width();
        int screenH = screenGeometry.height();
        int windowW = screenW * xfactor;
        int windowH = windowW * ratio;

        dialog -> setFixedSize(windowW, windowH);

        int x = (screenW - windowW) / 2;
        int y = (screenH - windowH) / 2;

        dialog -> move(x, y);
    }
    static inline void IgnorePolicy(QDialog* dialog){
        QList<QWidget*> widgets = dialog->findChildren<QWidget*>();
        for(QWidget* widget : widgets){
            widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        }
    }
};

#endif // UTILS_H
