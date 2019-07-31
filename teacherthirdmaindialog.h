#ifndef TEACHERTHIRDMAINDIALOG_H
#define TEACHERTHIRDMAINDIALOG_H

#include <QDialog>
#include <teacherchangepassword.h>
#include <sendjozvedialog.h>
#include <showclassmembers.h>
#include <teachershowlesson.h>

namespace Ui {
class teacherthirdmaindialog;
}

class teacherthirdmaindialog : public QDialog
{
    Q_OBJECT

public:
    explicit teacherthirdmaindialog(QWidget *parent = nullptr);
    ~teacherthirdmaindialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::teacherthirdmaindialog *ui;
    TeacherChangePassword *teacherChangePassword ;
    SendJozveDialog *sendJozve ;
    QSqlQueryModel *model ;
    ShowClassMembers *showClass;
    teachershowlesson *showless ;
};

#endif // TEACHERTHIRDMAINDIALOG_H
