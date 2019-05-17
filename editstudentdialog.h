#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showstudentdialog.h>

namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:

    explicit EditStudentDialog(QWidget *parent = nullptr);
    ~EditStudentDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_showAllStudent_clicked();

private:
    Ui::EditStudentDialog *ui;
    ShowStudentDialog *showStuDialog;
};

#endif // EDITSTUDENTDIALOG_H
