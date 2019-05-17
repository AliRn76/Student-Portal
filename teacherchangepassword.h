#ifndef TEACHERCHANGEPASSWORD_H
#define TEACHERCHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class TeacherChangePassword;
}

class TeacherChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherChangePassword(QWidget *parent = nullptr);
    ~TeacherChangePassword();

private:
    Ui::TeacherChangePassword *ui;
};

#endif // TEACHERCHANGEPASSWORD_H
