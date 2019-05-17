#ifndef TEACHERMAINDIALOG_H
#define TEACHERMAINDIALOG_H

#include <QDialog>
#include <teacherchangepassword.h>

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

private:
    Ui::TeacherMainDialog *ui;
    TeacherChangePassword *teacherChangePassword ;
};

#endif // TEACHERMAINDIALOG_H
