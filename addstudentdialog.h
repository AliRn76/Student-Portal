#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showstudentdialog.h>

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

private:
    Ui::AddStudentDialog *ui;
    ShowStudentDialog *showStuDialog;
};

#endif // ADDSTUDENTDIALOG_H
