#ifndef REMOVETEACHERDIALOG_H
#define REMOVETEACHERDIALOG_H

#include <QDialog>
#include <showteacherdialog.h>
#include <QMessageBox>

namespace Ui {
class RemoveTeacherDialog;
}

class RemoveTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveTeacherDialog(QWidget *parent = nullptr);
    ~RemoveTeacherDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_remove_clicked();


    void on_pushButton_showTeacher_clicked();

private:
    Ui::RemoveTeacherDialog *ui;
    ShowTeacherDialog *showTeachDialog;
};

#endif // REMOVETEACHERDIALOG_H
