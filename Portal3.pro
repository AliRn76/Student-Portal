#-------------------------------------------------
#
# Project created by QtCreator 2019-04-20T21:14:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Portal2
TEMPLATE = app

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
    addteacherdialog.cpp \
    editlessondialog.cpp \
    editteacherdialog.cpp \
    eraedarsdialog.cpp \
        main.cpp \
        mainwindow.cpp \
    employeemaindialog.cpp \
    addstudentdialog.cpp \
    removeentekhabvahed2dialog.cpp \
    removeentekhabvaheddialog.cpp \
    removeeraedars2dialog.cpp \
    removeeraedarsdialog.cpp \
    removelessondialog.cpp \
    removestudentdialog.cpp \
    editstudentdialog.cpp \
    entekhabvaheddialog.cpp \
    addlessondialog.cpp \
    employeechangepassworddialog.cpp \
    removeteacherdialog.cpp \
    showentekhabvaheddialog.cpp \
    showeraelistdialog.cpp \
    showlessondialog.cpp \
    showstudentdialog.cpp \
    studentchangepassworddialog.cpp \
    studententekhabvaheddialog.cpp \
    studentmaindialog.cpp \
    showteacherdialog.cpp \
    teachermaindialog.cpp

HEADERS += \
    addteacherdialog.h \
    editlessondialog.h \
    editteacherdialog.h \
    eraedarsdialog.h \
        mainwindow.h \
    employeemaindialog.h \
    addstudentdialog.h \
    removeentekhabvahed2dialog.h \
    removeentekhabvaheddialog.h \
    removeeraedars2dialog.h \
    removeeraedarsdialog.h \
    removelessondialog.h \
    removestudentdialog.h \
    editstudentdialog.h \
    entekhabvaheddialog.h \
    addlessondialog.h \
    employeechangepassworddialog.h \
    removeteacherdialog.h \
    showentekhabvaheddialog.h \
    showeraelistdialog.h \
    showlessondialog.h \
    showstudentdialog.h \
    studentchangepassworddialog.h \
    studententekhabvaheddialog.h \
    studentmaindialog.h \
    showteacherdialog.h \
    teachermaindialog.h

FORMS += \
    addteacherdialog.ui \
    editlessondialog.ui \
    editteacherdialog.ui \
    eraedarsdialog.ui \
        mainwindow.ui \
    employeemaindialog.ui \
    addstudentdialog.ui \
    removeentekhabvahed2dialog.ui \
    removeentekhabvaheddialog.ui \
    removeeraedars2dialog.ui \
    removeeraedarsdialog.ui \
    removelessondialog.ui \
    removestudentdialog.ui \
    editstudentdialog.ui \
    entekhabvaheddialog.ui \
    addlessondialog.ui \
    employeechangepassworddialog.ui \
    removeteacherdialog.ui \
    showentekhabvaheddialog.ui \
    showeraelistdialog.ui \
    showlessondialog.ui \
    showstudentdialog.ui \
    studentchangepassworddialog.ui \
    studententekhabvaheddialog.ui \
    studentmaindialog.ui \
    showteacherdialog.ui \
    teachermaindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc
