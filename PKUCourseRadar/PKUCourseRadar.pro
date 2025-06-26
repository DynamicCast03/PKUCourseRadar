QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutus.cpp \
    addcommentwindow.cpp \
    betterbutton.cpp \
    bettermessagebox.cpp \
    commentbrowserwindow.cpp \
    course.cpp \
    coursecell.cpp \
    courseinfowindow.cpp \
    coursemanager.cpp \
    coursetablewidget.cpp \
    coursetime.cpp \
    dataaccessor.cpp \
    jsondataaccessor.cpp \
    loginwindow.cpp \
    main.cpp \
    homewindow.cpp \
    mycourseswindow.cpp \
    radarwindow.cpp \
    utils.cpp

HEADERS += \
    aboutus.h \
    addcommentwindow.h \
    betterbutton.h \
    bettermessagebox.h \
    commentbrowserwindow.h \
    course.h \
    coursecell.h \
    courseinfowindow.h \
    coursemanager.h \
    coursetablewidget.h \
    coursetime.h \
    dataaccessor.h \
    en_US.h \
    homewindow.h \
    jsondataaccessor.h \
    loginwindow.h \
    mycourseswindow.h \
    radarwindow.h \
    stdc++.h \
    utils.h \
    zh_CN.h

FORMS += \
    aboutus.ui \
    addcommentwindow.ui \
    commentbrowserwindow.ui \
    courseinfowindow.ui \
    homewindow.ui \
    loginwindow.ui \
    mycourseswindow.ui \
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

RC_FILE += \
    app.rc
