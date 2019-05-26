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
    explicit TeacherMainDialog(QWidget *parent = nullptr);
    ~TeacherMainDialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_clicked();

    void on_treeView_Lesson_doubleClicked(const QModelIndex &index);

private:
    Ui::TeacherMainDialog *ui;
    TeacherChangePassword *teacherChangePassword ;
    SendJozveDialog *sendJozve ;
    ShowClassMembers *showClassMem ;
    QSqlQueryModel *model ;
};

#endif // TEACHERMAINDIALOG_H
