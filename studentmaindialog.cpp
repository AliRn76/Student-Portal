#include "studentmaindialog.h"
#include "ui_studentmaindialog.h"

QString ShowStudentEraeListDialog::stuField;
QString StudentEntekhabVahedDialog::stuFieldEntekhab;
QString StudentEntekhabVahedDialog::stuCode;


StudentMainDialog::StudentMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentMainDialog)
{
    ui->setupUi(this);

    QSqlQuery qry;
    QString name;
    QString field;
    QString userName = StudentChangePasswordDialog::strUserStu;
    StudentEntekhabVahedDialog::stuCode = StudentChangePasswordDialog::strUserStu;

    qry.prepare("Select FirstName, LastName, Field \
                 From Student.dbo.tblPerson, Student.dbo.tblStudent \
                 Where tblPerson.ID = tblStudent.ID AND tblStudent.StudentCode = :stucode");
            qry.bindValue(":stucode", userName);
            qry.exec();

    while(qry.next()){
        name = qry.value(0).toString() + " " + qry.value(1).toString();
        field = qry.value(2).toString();
    }

    ShowStudentEraeListDialog::stuField = field;
    StudentEntekhabVahedDialog::stuFieldEntekhab = field;

    ui->label_name->setText(name);
    ui->label_stuCode->setText(userName);
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
