#ifndef TEACHERCHANGEPASSWORD_H
#define TEACHERCHANGEPASSWORD_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class TeacherChangePassword;
}

class TeacherChangePassword : public QDialog
{
    Q_OBJECT

public:
    static QString strUserTeach;

    explicit TeacherChangePassword(QWidget *parent = nullptr);
    ~TeacherChangePassword();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TeacherChangePassword *ui;
};

#endif // TEACHERCHANGEPASSWORD_H
