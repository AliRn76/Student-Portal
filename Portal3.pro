#-------------------------------------------------
#
# Project created by QtCreator 2019-04-20T21:14:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Portal3
TEMPLATE = app
RC_ICONS = hnet.com-image.ico
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    employeemainwindow.cpp \
    eraedarsdialog.cpp \
    lessondialog.cpp \
    main.cpp \
    mainwindow.cpp \
    removeentekhabvahed2dialog.cpp \
    removeentekhabvaheddialog.cpp \
    removeeraedars2dialog.cpp \
    removeeraedarsdialog.cpp \
    entekhabvaheddialog.cpp \
    employeechangepassworddialog.cpp \
    showentekhabvaheddialog.cpp \
    showeraelistdialog.cpp \
    showlessondialog.cpp \
    showstudentdialog.cpp \
    showstudenteraelistdialog.cpp \
    studentbarnameclassdialog.cpp \
    studentchangepassworddialog.cpp \
    studentdialog.cpp \
    studententekhabvaheddialog.cpp \
    studentkarnamedialog.cpp \
    studentmaindialog.cpp \
    showteacherdialog.cpp \
    teacherdialog.cpp \
    teachermaindialog.cpp \
    sendjozvedialog.cpp \
    teacherchangepassword.cpp \
    showclassmembers.cpp
HEADERS += \
    employeemainwindow.h \
    eraedarsdialog.h \
    lessondialog.h \
    mainwindow.h \
    removeentekhabvahed2dialog.h \
    removeentekhabvaheddialog.h \
    removeeraedars2dialog.h \
    removeeraedarsdialog.h \
    entekhabvaheddialog.h \
    employeechangepassworddialog.h \
    showentekhabvaheddialog.h \
    showeraelistdialog.h \
    showlessondialog.h \
    showstudentdialog.h \
    showstudenteraelistdialog.h \
    studentbarnameclassdialog.h \
    studentchangepassworddialog.h \
    studentdialog.h \
    studententekhabvaheddialog.h \
    studentkarnamedialog.h \
    studentmaindialog.h \
    showteacherdialog.h \
    teacherdialog.h \
    teachermaindialog.h \
    sendjozvedialog.h \
    teacherchangepassword.h \
    showclassmembers.h

FORMS += \
    employeemainwindow.ui \
    eraedarsdialog.ui \
    lessondialog.ui \
    mainwindow.ui \
    removeentekhabvahed2dialog.ui \
    removeentekhabvaheddialog.ui \
    removeeraedars2dialog.ui \
    removeeraedarsdialog.ui \
    entekhabvaheddialog.ui \
    employeechangepassworddialog.ui \
    showentekhabvaheddialog.ui \
    showeraelistdialog.ui \
    showlessondialog.ui \
    showstudentdialog.ui \
    showstudenteraelistdialog.ui \
    studentbarnameclassdialog.ui \
    studentchangepassworddialog.ui \
    studentdialog.ui \
    studententekhabvaheddialog.ui \
    studentkarnamedialog.ui \
    studentmaindialog.ui \
    showteacherdialog.ui \
    teacherdialog.ui \
    teachermaindialog.ui \
    sendjozvedialog.ui \
    teacherchangepassword.ui \
    showclassmembers.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc
