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
    QString oldPass= ui->lineEdit_oldPass->text();
    QString newPass = ui->lineEdit_newPass->text();
    QString repNewPass = ui->lineEdit_repeatNewPass->text();
    QString checkOldPass;
    QSqlQuery qry1;
    QSqlQuery qry2;

    qry1.prepare("Select Password From Student.dbo.tblStudent \
                  Where tblStudent.StudentCode = :stucode");
            qry1.bindValue(":stucode", strUserStu);
            qry1.exec();

        if(qry1.next()){
            checkOldPass = qry1.value(0).toString();
        }

        if(checkOldPass == oldPass){
            if(newPass != repNewPass){
                QMessageBox::warning(this, "warning", "اطلاعات را صحیح وارد کنید.");

            }else{
                qry2.prepare("Update Student.dbo.tblStudent \
                             Set Password = :pass \
                             Where tblStudent.StudentCode = :stucode");
                        qry2.bindValue(":pass", newPass);
                        qry2.bindValue(":stucode", strUserStu);
                        qry2.exec();

                QMessageBox::information(this, "OK", "رمز عبور شما با موفقیت تغییر کرد.");
            }
        }else {
            QMessageBox::warning(this, "خطا" , "رمز عبور فعلی را نادرست وارد کرده اید.");
        }

        ui->lineEdit_oldPass->clear();
        ui->lineEdit_newPass->clear();
        ui->lineEdit_repeatNewPass->clear();
}
