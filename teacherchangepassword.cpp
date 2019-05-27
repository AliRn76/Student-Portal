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
<<<<<<< HEAD

void TeacherChangePassword::on_pushButton_Exit_clicked()
{
    this->close();
}

void TeacherChangePassword::on_pushButton_ChangePass_clicked()
{
    QString oldPass= ui->lineEdit_oldPass->text();
    QString newPass = ui->lineEdit_newPass->text();
    QString repNewPass = ui->lineEdit_repeatNewPass->text();
    QString checkOldPass;
    QSqlQuery qry1;
    QSqlQuery qry2;

    qry1.prepare("Select Password From Student.dbo.tblTeacher \
                  Where tblTeacher.TeacherCode = :teacode");
            qry1.bindValue(":teacode", strUserTeacher);
            qry1.exec();

        if(qry1.next()){
            checkOldPass = qry1.value(0).toString();
        }

        if(checkOldPass == oldPass){
            if(newPass != repNewPass){
                QMessageBox::warning(this, "warning", "اطلاعات را صحیح وارد کنید.");

            }else{
                qry2.prepare("Update Student.dbo.tblTeacher \
                             Set Password = :pass \
                             Where tblTeacher.TeacherCode = :teacode");
                        qry2.bindValue(":pass", newPass);
                        qry2.bindValue(":teacode", strUserTeacher);
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
=======
>>>>>>> refs/remotes/vozhde3/master
