#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <employeemaindialog.h>
#include <employeechangepassworddialog.h>
#include <studentmaindialog.h>
#include <studentchangepassworddialog.h>

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
    void on_pushButton_manager_clicked();

    void on_pushButton_teacher_clicked();

    void on_pushButton_stu_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    EmployeeMainDialog *emploMainDialog;
    StudentMainDialog *stuMainDialog;
};
#endif // MAINWINDOW_H
