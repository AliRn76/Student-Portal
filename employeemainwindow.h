#ifndef EMPLOYEEMAINWINDOW_H
#define EMPLOYEEMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <studentdialog.h>
#include <removestudentdialog.h>
#include <editstudentdialog.h>
#include <entekhabvaheddialog.h>
#include <employeechangepassworddialog.h>
#include <lessondialog.h>
#include <teacherdialog.h>
#include <eraedarsdialog.h>
#include <showstudentdialog.h>
#include <showteacherdialog.h>
#include <showlessondialog.h>
#include <showeraelistdialog.h>
#include <showentekhabvaheddialog.h>
#include <removeentekhabvaheddialog.h>
#include <removeeraedarsdialog.h>
#include <studentsrequestdialog.h>

namespace Ui {
class EmployeeMainWindow;
}

class EmployeeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeMainWindow(QWidget *parent = nullptr);
    ~EmployeeMainWindow();

private slots:
    void on_pushButton_addStu_clicked();

    void on_pushButton_entekhabVahed_clicked();

    void on_pushButton_setting_clicked();

    void on_pushButton_addLesson_clicked();

    void on_pushButton_addTeacher_clicked();

    void on_pushButton_eraeDars_clicked();

    void on_pushButton_removeErae_clicked();

    void on_pushButton_showStu_clicked();

    void on_pushButton_showEntekhab_clicked();

    void on_pushButton_showLesson_clicked();

    void on_pushButton_showTeacher_clicked();

    void on_pushButton_showErae_clicked();

    void on_pushButton_stuReqs_clicked();

private:
    Ui::EmployeeMainWindow *ui;

    AddStudentDialog *addStuDialog;
    RemoveStudentDialog *rmvStuDialog;
    EditStudentDialog *editStuDialog;
    EntekhabVahedDialog *entekhVahedDialog;
    EmployeeChangePasswordDialog *empChangeDialog;
    AddLessonDialog *addLessDialog;
    AddTeacherDialog *addTeachDialog;
    EraeDarsDialog *eraeDialog;
    ShowStudentDialog *showStuDialog;
    ShowTeacherDialog *showTeachDialog;
    ShowLessonDialog *showLessDialog;
    ShowEraeListDialog *showEraeDialog;
    ShowEntekhabVahedDialog *showEntekhabDialog;
    RemoveEntekhabVahedDialog *rmvEntekhabDialog;
    RemoveEraeDarsDialog *rmvEraeDialog;
    StudentsRequestDialog *stuReqsDialog;

};

#endif // EMPLOYEEMAINWINDOW_H
