#ifndef REMOVESTUDENTDIALOG_H
#define REMOVESTUDENTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showstudentdialog.h>

namespace Ui {
class RemoveStudentDialog;
}

class RemoveStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveStudentDialog(QWidget *parent = nullptr);
    ~RemoveStudentDialog();

private slots:
    void on_pushButton_remove_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_showAllStu_clicked();

private:
    Ui::RemoveStudentDialog *ui;
    ShowStudentDialog *showStuDialog;
};

#endif // REMOVESTUDENTDIALOG_H
