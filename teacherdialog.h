#ifndef ADDTEACHERDIALOG_H
#define ADDTEACHERDIALOG_H

#include <QDialog>
#include <showteacherdialog.h>
#include <QMessageBox>

namespace Ui {
class AddTeacherDialog;
}

class AddTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeacherDialog(QWidget *parent = nullptr);
    ~AddTeacherDialog();

private slots:

    void on_pushButton_showTeacher_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_searchTab2_clicked();

    void on_pushButton_applyTab2_clicked();

    void on_pushButton_showAllStudentTab2_clicked();

    void on_pushButton_searchTab3_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_showTeacherTab3_clicked();

private:
    Ui::AddTeacherDialog *ui;
    ShowTeacherDialog *showTeachDialog;
};

#endif // ADDTEACHERDIALOG_H
