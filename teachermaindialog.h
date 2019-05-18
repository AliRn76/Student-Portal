#ifndef TEACHERMAINDIALOG_H
#define TEACHERMAINDIALOG_H

#include <QDialog>
#include <teacherchangepassword.h>
#include <QtSql>
#include <sendjozvedialog.h>

namespace Ui {
class TeacherMainDialog;
}

class TeacherMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherMainDialog(QWidget *parent = nullptr);
    ~TeacherMainDialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TeacherMainDialog *ui;
    TeacherChangePassword *teacherChangePassword ;
    SendJozveDialog *sendJozve ;
    QSqlQueryModel *model;
};

#endif // TEACHERMAINDIALOG_H
