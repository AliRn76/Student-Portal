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

private:
    Ui::AddTeacherDialog *ui;
    ShowTeacherDialog *showTeachDialog;
};

#endif // ADDTEACHERDIALOG_H
