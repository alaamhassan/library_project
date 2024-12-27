QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_adminssectionwindow.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    signinwindow.cpp \
    stylesSheetGlobal.cpp \
    subwindow_addmember.cpp \
    subwindow_editmember.cpp

HEADERS += \
    admin_adminssectionwindow.h \
    global.h \
    mainwindow.h \
    signinwindow.h \
    stylesSheetGlobal.h \
    subwindow_addmember.h \
    subwindow_editmember.h

FORMS += \
    admin_adminssectionwindow.ui \
    mainwindow.ui \
    signinwindow.ui \
    subwindow_addmember.ui \
    subwindow_editmember.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background_resources.qrc \
    backgrounds.qrc
