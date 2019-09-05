#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <employeemainwindow.h>
#include <employeechangepassworddialog.h>
#include <studentmaindialog.h>
#include <studentchangepassworddialog.h>
#include <teachermaindialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    EmployeeMainWindow *emploMainWindow;
    StudentMainDialog *stuMainDialog;
    TeacherMainDialog *teamaindialog;
};
#endif // MAINWINDOW_H
