#include "addteacherdialog.h"
#include "ui_addteacherdialog.h"

AddTeacherDialog::AddTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeacherDialog)
{
    ui->setupUi(this);
}

AddTeacherDialog::~AddTeacherDialog()
{
    delete ui;
}

void AddTeacherDialog::on_pushButton_showTeacher_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}

void AddTeacherDialog::on_pushButton_apply_clicked()
{
    if(!(ui->lineEdit_firstName->text().isEmpty() || ui->lineEdit_lastName->text().isEmpty() || ui->lineEdit_nationalCode->text().isEmpty() || ui->lineEdit_degree->text().isEmpty())){

        QSqlQuery qry1;
        QSqlQuery qry2;
        QSqlQuery qry3;
        QSqlQuery qry4;

        QString strName;
        QString strLastname;
        QString strNationalcode;
        QString strEduDegree;
        QString teachCode;
        QVariant correntID;
     //   QDate birthDate;
        bool bGender;

        strName = ui->lineEdit_firstName->text();
        strLastname = ui->lineEdit_lastName->text();
        strNationalcode = ui->lineEdit_nationalCode->text();
        strEduDegree = ui->lineEdit_degree->text();

        if(ui->radioButton_male->isChecked()){
            bGender =  true;
        }else if(ui->radioButton_female->isChecked()){
            bGender = false;
        }

        if(strNationalcode.toInt()){
            if(strNationalcode.length() == 10){

                qry1.prepare("Insert Into Student.dbo.tblPerson \
                             (FirstName \
                             ,LastName \
                             ,Nationalcode \
                             ,Gender) \
                             Values(:name , :lastname , :nationalcode , :gender)");
                             qry1.bindValue(":name", strName);
                             qry1.bindValue(":lastname", strLastname);
                             qry1.bindValue(":nationalcode", strNationalcode);
                             qry1.bindValue(":gender", bGender );
                             qry1.exec();

                correntID = qry2.lastInsertId().toString();

                qry3.prepare("Insert Into Student.dbo.tblTeacher \
                             (ID \
                             ,EducationDegree \
                             ,Password) \
                             Values(:id , :edudegree , :password)");
                            qry3.bindValue(":id", correntID);
                            qry3.bindValue(":edudegree", strEduDegree);
                            qry3.bindValue(":password", strNationalcode);

                            if(qry3.exec()){

                                qry4.prepare("Select TeacherCode From Student.dbo.tblTeacher \
                                              Where tblTeacher.ID = :id");
                                        qry4.bindValue(":id", correntID);
                                        qry4.exec();

                                if(qry4.next()){
                                    teachCode = qry4.value(0).toString();
                                }

                                QMessageBox::information(this, "OK", "استاد با موفقیت اضافه شد ، کد کارمندی : " + teachCode);
                            }else{
                                QMessageBox::information(this, "Complete", "ثبت استاد با مشکل موجه شد.");
                            }
            }else{
                QMessageBox::warning(this, "خطا", "لطفا کد ملی خود را به صورت 10 رقمی وارد کنید.");
            }
        }else{
            QMessageBox::warning(this, "خطا", "لطفا کد ملی خود را تصحیح کنید.");
        }
    }else{
        QMessageBox::warning(this, "خطا", "لطفا موارد بالا پر کنید.");
    }
}
