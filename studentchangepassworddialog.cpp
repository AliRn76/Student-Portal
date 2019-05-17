#include "studentchangepassworddialog.h"
#include "ui_studentchangepassworddialog.h"

StudentChangePasswordDialog::StudentChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentChangePasswordDialog)
{
    ui->setupUi(this);
}

StudentChangePasswordDialog::~StudentChangePasswordDialog()
{
    delete ui;
}

void StudentChangePasswordDialog::on_pushButton_clicked()
{
    QString newPass = ui->lineEdit_newPass->text();
    QString repNewPass = ui->lineEdit_repeatNewPass->text();

    if(newPass != repNewPass){
        QMessageBox::warning(this, "warning", "اطلاعات را صحیح وارد کنید.");
        ui->lineEdit_repeatNewPass->text().clear();
    }else{
        QSqlQuery qry;
        qry.prepare("Update Student.dbo.tblStudent \
                     Set Password = :pass \
                     Where tblStudent.StudentCode = :stucode");
                qry.bindValue(":pass", newPass);
                qry.bindValue(":stucode", strUserStu);
                qry.exec();

        QMessageBox::information(this, "OK", "رمز عبور شما با موفقیت تغییر کرد.");
    }
}
