#include "showclassmembers.h"
#include "ui_showclassmembers.h"

ShowClassMembers::ShowClassMembers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowClassMembers)
{
    ui->setupUi(this);
}

ShowClassMembers::~ShowClassMembers()
{
    delete ui;
}
