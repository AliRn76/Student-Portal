#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showstudentdialog.h>
#include <QDebug>

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_showAllStu_clicked();

    void on_pushButton_searchTab2_clicked();

    void on_pushButton_applyTab2_clicked();

    void on_pushButton_showAllStudentsTab2_clicked();

    void on_pushButton_searchTab3_clicked();

    void on_pushButton_removeTab3_clicked();

    void on_pushButton_showAllStuTab3_clicked();

private:
    Ui::AddStudentDialog *ui;
    ShowStudentDialog *showStuDialog;
};

#endif // ADDSTUDENTDIALOG_H
