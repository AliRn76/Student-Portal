#include "studentsrequestdialog.h"
#include "ui_studentsrequestdialog.h"

StudentsRequestDialog::StudentsRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsRequestDialog)
{
    ui->setupUi(this);
}

StudentsRequestDialog::~StudentsRequestDialog()
{
    delete ui;
}
