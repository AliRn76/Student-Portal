#ifndef TEACHERMAINDIALOG_H
#define TEACHERMAINDIALOG_H

#include <QDialog>
#include <teacherchangepassword.h>
#include <sendjozvedialog.h>
#include <showclassmembers.h>

namespace Ui {
class TeacherMainDialog;
}

class TeacherMainDialog : public QDialog
{
    Q_OBJECT

public:
    int NumberOfRow_Lesson ;
    int NumberOfRow_Student;
    QString StuCode ;
    explicit TeacherMainDialog(QWidget *parent = nullptr);
    ~TeacherMainDialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_refresh_clicked();

    void on_tableView_Lesson_clicked(const QModelIndex &index);

    void on_tableView_Student_clicked(const QModelIndex &index);

    void on_pushButton_Guide_clicked();

    void on_pushButton_SetScores_clicked();

    void on_radioButton_Day_clicked();

    void on_radioButton_Title_clicked();

    void on_radioButton_Day_2_clicked();

private:
    Ui::TeacherMainDialog *ui;
    TeacherChangePassword *teacherChangePassword ;
    SendJozveDialog *sendJozve ;
    QSqlQueryModel *model ;
    ShowClassMembers *showClass;
};

#endif // TEACHERMAINDIALOG_H
