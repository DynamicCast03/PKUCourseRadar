QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutus.cpp \
    course.cpp \
    coursecell.cpp \
    courseinfowindow.cpp \
    coursemanager.cpp \
    coursetablewidget.cpp \
    coursetime.cpp \
    debug_utils.cpp \
    main.cpp \
    homewindow.cpp \
    radarwindow.cpp

HEADERS += \
    aboutus.h \
    course.h \
    coursecell.h \
    courseinfowindow.h \
    coursemanager.h \
    coursetablewidget.h \
    coursetime.h \
    debug_utils.h \
    homewindow.h \
    radarwindow.h \
    stdc++.h \
    utils.h

FORMS += \
    aboutus.ui \
    courseinfowindow.ui \
    homewindow.ui \
    radarwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS +=

RESOURCES += \
    picture.qrc
