QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutus.cpp \
    betterbutton.cpp \
    course.cpp \
    coursecell.cpp \
    courseinfowindow.cpp \
    coursemanager.cpp \
    coursetablewidget.cpp \
    coursetime.cpp \
    debug_utils.cpp \
    main.cpp \
    homewindow.cpp \
    mylesson.cpp \
    mylike.cpp \
    radarwindow.cpp \
    utils.cpp

HEADERS += \
    aboutus.h \
    betterbutton.h \
    course.h \
    coursecell.h \
    courseinfowindow.h \
    coursemanager.h \
    coursetablewidget.h \
    coursetime.h \
    debug_utils.h \
    en_US.h \
    homewindow.h \
    mylesson.h \
    mylike.h \
    radarwindow.h \
    stdc++.h \
    utils.h \
    zh_CN.h

FORMS += \
    aboutus.ui \
    courseinfowindow.ui \
    homewindow.ui \
    mylesson.ui \
    radarwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    PKUCourseRadar_en_US.ts \
    PKUCourseRadar_zh_CN.ts

RESOURCES += \
    picture.qrc
