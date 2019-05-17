#include "studententekhabvaheddialog.h"
#include "ui_studententekhabvaheddialog.h"

StudentEntekhabVahedDialog::StudentEntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentEntekhabVahedDialog)
{
    ui->setupUi(this);
}

StudentEntekhabVahedDialog::~StudentEntekhabVahedDialog()
{
    delete ui;
}
