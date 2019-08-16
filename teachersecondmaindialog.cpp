#include "teachersecondmaindialog.h"
#include "ui_teachersecondmaindialog.h"

teachersecondmaindialog::teachersecondmaindialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teachersecondmaindialog)
{
    ui->setupUi(this);
    //----------------------------------------------------------------
        QString username = TeacherChangePassword::strUserTeacher;

        ui->label_TeacherCode->setText(username);






}

teachersecondmaindialog::~teachersecondmaindialog()
{
    delete ui;
}
