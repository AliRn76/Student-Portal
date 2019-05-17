#include "teachermaindialog.h"
#include "ui_teachermaindialog.h"

TeacherMainDialog::TeacherMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherMainDialog)
{
    ui->setupUi(this);
}

TeacherMainDialog::~TeacherMainDialog()
{
    delete ui;
}
