#ifndef TEACHERTHIRDMAINDIALOG_H
#define TEACHERTHIRDMAINDIALOG_H

#include <QDialog>
#include <teacherchangepassword.h>
#include <sendjozvedialog.h>
#include <showclassmembers.h>
#include <teachershowlesson.h>
#include <teacherrequest.h>

namespace Ui {
class teacherthirdmaindialog;
}

class teacherthirdmaindialog : public QDialog
{
    Q_OBJECT

public:

    int NumberOfRow_Lesson ;
    QString LessonCode;


    explicit teacherthirdmaindialog(QWidget *parent = nullptr);
    ~teacherthirdmaindialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_exit_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_SetScore_clicked();

    void on_pushButton_req_dars_clicked();

    void on_pushButton_req_parking_clicked();

    void on_pushButton_req_vam_clicked();

private:
    Ui::teacherthirdmaindialog *ui;
    TeacherChangePassword *teacherChangePassword ;
    SendJozveDialog *sendJozve ;
    QSqlQueryModel *model ;
    ShowClassMembers *showClass;
    teachershowlesson *showless ;
    teacherRequest *teareq ;
};

#endif // TEACHERTHIRDMAINDIALOG_H
