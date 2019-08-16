#include "showstudentdialog.h"
#include "ui_showstudentdialog.h"

ShowStudentDialog::ShowStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowStudentDialog)
{
    ui->setupUi(this);

    qry = new QSqlQueryModel(this);

    qry->setQuery("Select StudentCode as 'شماره دانشجویی', Concat(FirstName , ' ' , LastName) as 'نام', FathersName as 'نام پدر', NationalCode as 'کد ملی', SaalVoroud as 'سال ورود', Password as 'رمز عبور' \
                   From tblPerson , tblStudent \
                   Where tblPerson.ID = tblStudent.ID");
    ui->treeView->setModel(qry);
}

ShowStudentDialog::~ShowStudentDialog()
{
    delete ui;
}


