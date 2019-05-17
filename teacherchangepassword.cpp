#include "teacherchangepassword.h"
#include "ui_teacherchangepassword.h"

TeacherChangePassword::TeacherChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherChangePassword)
{
    ui->setupUi(this);
}

TeacherChangePassword::~TeacherChangePassword()
{
    delete ui;
}

void TeacherChangePassword::on_pushButton_2_clicked()
{
    this->close();
}
//fust for test
