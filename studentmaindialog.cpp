#include "studentmaindialog.h"
#include "ui_studentmaindialog.h"

QString ShowStudentEraeListDialog::stuField;
QString StudentEntekhabVahedDialog::stuFieldEntekhab;
QString StudentEntekhabVahedDialog::stuCode;
QString StudentBarnameClassDialog::stuCodeBarname;
QString StudentKarnameDialog::stuIDKarname;

StudentMainDialog::StudentMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentMainDialog)
{
    ui->setupUi(this);

    QSqlQuery qry;
    QString name;
    QString field;
    QString id;
    QString userName = StudentChangePasswordDialog::strUserStu;
    StudentEntekhabVahedDialog::stuCode = userName;
    StudentBarnameClassDialog::stuCodeBarname = userName;

    qry.prepare("Select FirstName, LastName, Field, tblStudent.ID \
                 From Student.dbo.tblPerson, Student.dbo.tblStudent \
                 Where tblPerson.ID = tblStudent.ID AND tblStudent.StudentCode = :stucode");
            qry.bindValue(":stucode", userName);
            qry.exec();

    while(qry.next()){
        name = qry.value(0).toString() + " " + qry.value(1).toString();
        field = qry.value(2).toString();
        id = qry.value(3).toString();
    }

    ShowStudentEraeListDialog::stuField = field;
    StudentEntekhabVahedDialog::stuFieldEntekhab = field;
    StudentKarnameDialog::stuIDKarname = id;
    ui->label_name->setText(name);
    ui->label_stuCode->setText(userName);
    ui->label_field->setText(field);
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

void StudentMainDialog::on_pushButton_listErae_clicked()
{
    showStuEraListDialog = new ShowStudentEraeListDialog(this);
    showStuEraListDialog->show();
}

void StudentMainDialog::on_pushButton_entekhabVahed_clicked()
{
    stuEntekhabDialog = new StudentEntekhabVahedDialog(this);
    stuEntekhabDialog->show();
}

void StudentMainDialog::on_pushButton_barnameClass_clicked()
{
    stuBarnameDialog = new StudentBarnameClassDialog(this);
    stuBarnameDialog->show();
}

void StudentMainDialog::on_pushButton_karname_clicked()
{
    stuKarnameDialog = new StudentKarnameDialog(this);
    stuKarnameDialog->show();
}
