#include "studentmaindialog.h"
#include "ui_studentmaindialog.h"

StudentMainDialog::StudentMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentMainDialog)
{
    ui->setupUi(this);
/*
    QString name;
    QString lastName;
    QString cpyStrUser = StudentChangePasswordDialog::strUserStu;
    QSqlQuery qry1;
    QSqlQuery qry2;
    int currentID;

    qry1.prepare("Select ID \
                  From Student.dbo.tblStudent \
                  Where tblStudent.StudentCode = :stucode");
            qry1.bindValue(":stucode", cpyStrUser);
            qry1.exec();
    if(qry1.next()){
        currentID = qry1.value(0).toInt();
    }

    qry2.prepare("Select FirstName, LastName \
                  From Student.dbo.tblPerson \
                  Where tblPerson.ID = :id");
            qry2.bindValue(":id", currentID);
            qry2.exec();
    if(qry2.next()){
        name = qry2.value(0).toString();
        lastName = qry2.value(1).toString();
    }

    ui->label_name->setText(name + " " + lastName);
    ui->label_employeeCode->setText(cpyStrUser);
    */
}

StudentMainDialog::~StudentMainDialog()
{
    delete ui;
}

void StudentMainDialog::on_pushButton_setting_clicked()
{
    stuChangeDialog = new StudentChangePasswordDialog(this);
    stuChangeDialog->show();
}
