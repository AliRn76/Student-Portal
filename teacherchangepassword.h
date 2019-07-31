#ifndef TEACHERCHANGEPASSWORD_H
#define TEACHERCHANGEPASSWORD_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class TeacherChangePassword;
}

class TeacherChangePassword : public QDialog
{
    Q_OBJECT

public:
    static QString strUserTeacher ;

    explicit TeacherChangePassword(QWidget *parent = nullptr);
    ~TeacherChangePassword();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_ChangePass_clicked();

private:
    Ui::TeacherChangePassword *ui;
};

#endif // TEACHERCHANGEPASSWORD_H
