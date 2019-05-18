#include "teacherchangepassword.h"
#include "ui_teacherchangepassword.h"

TeacherChangePassword::TeacherChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherChangePassword)
{
    ui->setupUi(this);
}

TeacherChangePassword::~TeacherChangePassword()
{
    delete ui;
}

void TeacherChangePassword::on_pushButton_2_clicked()
{
    this->close();
}

void TeacherChangePassword::on_pushButton_clicked()
{
    QString newpass = ui->lineEdit_newPass->text();
    QString rep_newpass = ui->lineEdit_repeatNewPass->text();
    QString oldpass = ui->lineEdit_oldPass->text();
    QString pass ;
    if(newpass == rep_newpass){
        QSqlQuery qry1;
        qry1.prepare("Select Password from Student.dbo.tblTeacher where TeacherCode = :user");
        qry1.bindValue(":user" , strUserTeach);
        qry1.exec();
        while(qry1.next()){
            pass = qry1.value(0).toString();
        }
        if(pass == oldpass){
            QSqlQuery qry;
            qry.prepare("Update Student.dbo.tblTeacher set Password = :newpass where TeacherCode = :user");
            qry.bindValue(":newpass" , newpass);
            qry.bindValue(":user" , strUserTeach);
            if(qry.exec()){
                QMessageBox::warning(this , "Done" , "رمز عبور با موفقیت تغییر کرد");
            }
            else {
                QMessageBox::warning(this , "Error" , "تغییر رمز عبور با مشکل مواجه شد");
            }
        }
        else {
            QMessageBox::warning(this , "Error" , "رمز عبور اشتباه است .");
        }

    }
    else {
        QMessageBox::warning(this , "Error" , "لطفا اطلاعات را صحیح وارد کنید");
    }
}
