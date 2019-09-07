#include "teacherdialog.h"
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


///---------------Tab1-------------------------------------------------------------------------------->



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

        if(strNationalcode.toULongLong()){
            if(strNationalcode.length() == 10){

                qry1.prepare("Insert Into tblPerson \
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

                correntID = qry1.lastInsertId().toString();

                qry3.prepare("Insert Into tblTeacher \
                             (ID \
                             ,EducationDegree \
                             ,Password) \
                             Values(:id , :edudegree , :password)");
                            qry3.bindValue(":id", correntID);
                            qry3.bindValue(":edudegree", strEduDegree);
                            qry3.bindValue(":password", strNationalcode);

                            if(qry3.exec()){

                                qry4.prepare("Select TeacherCode From tblTeacher \
                                              Where tblTeacher.ID = :id");
                                        qry4.bindValue(":id", correntID);
                                        qry4.exec();

                                if(qry4.next()){
                                    teachCode = qry4.value(0).toString();
                                }
                                QMessageBox::information(this, "OK", "استاد با موفقیت اضافه شد ، کد کارمندی : " + teachCode);
                                ui->lineEdit_firstName->clear();
                                ui->lineEdit_lastName->clear();
                                ui->lineEdit_nationalCode->clear();
                                ui->lineEdit_degree->clear();
//                                ui->comboBox_day
//                                ui->comboBox_month
//                                ui->comboBox_year
                                ui->radioButton_male->click();

                            }else{
                                QMessageBox::warning(this, "Warning", "ثبت استاد با مشکل موجه شد.");
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


///---------------Tab2-------------------------------------------------------------------------------->



void AddTeacherDialog::on_pushButton_searchTab2_clicked()
{
    ui->lineEdit_nameTab2->clear();
    ui->lineEdit_lastNameTab2->clear();
    ui->lineEdit_birthDateTab2->clear();
    ui->lineEdit_eduDegreeTab2->clear();
    ui->lineEdit_nationalCodeTab2->clear();
    ui->comboBox_genderTab2->setCurrentIndex(0);

    if(ui->lineEdit_Tab2->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد یا نام وارد کنید.");
    }else{
        QString arrStr[8];

        QString strTeachCode = ui->lineEdit_Tab2->text();

        QSqlQuery qry("Select TeacherCode, FirstName, LastName, Gender, EducationDegree, NationalCode, BirthDate \
                       From tblPerson , tblTeacher \
                       Where ( tblPerson.ID = tblTeacher.ID ) AND ( tblTeacher.TeacherCode like '" + strTeachCode + "%' OR \
                       tblPerson.Firstname like N'" + strTeachCode + "%' OR \
                       tblPerson.Lastname like N'" + strTeachCode + "%' OR \
                       tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + strTeachCode + "')");

        if(qry.numRowsAffected() != 0){

          if(qry.numRowsAffected() == 1){

              while (qry.next()){
                  for(int i=0 ; i<7 ; i++){
                      arrStr[i] = qry.value(i).toString();
                  }
              }

              ui->label_teachCodeTab2->setText(arrStr[0]);
              ui->lineEdit_nameTab2->setText(arrStr[1]);
              ui->lineEdit_lastNameTab2->setText(arrStr[2]);
              if(arrStr[3] == "\u0001"){
                  ui->comboBox_genderTab2->setCurrentText("مرد");
              }else{
                  ui->comboBox_genderTab2->setCurrentText("زن");
              }
              ui->lineEdit_eduDegreeTab2->setText(arrStr[4]);
              ui->lineEdit_nationalCodeTab2->setText(arrStr[5]);
          //    ui->lineEdit_birthDate->setText(arrStr[6]);
          }else{
              QMessageBox::warning(this, "warning", "بیش از یک مورد " + strTeachCode + " وجود دارد.");

              while (qry.next()){
                  for(int i=0 ; i<7 ; i++){
                      arrStr[i] = qry.value(i).toString();
                  }
              }

              ui->label_teachCodeTab2->setText(arrStr[0]);
              ui->lineEdit_nameTab2->setText(arrStr[1]);
              ui->lineEdit_lastNameTab2->setText(arrStr[2]);
              if(arrStr[3] == "\u0001"){
                  ui->comboBox_genderTab2->setCurrentText("مرد");
              }else{
                  ui->comboBox_genderTab2->setCurrentText("زن");
              }
              ui->lineEdit_eduDegreeTab2->setText(arrStr[4]);
              ui->lineEdit_nationalCodeTab2->setText(arrStr[5]);
          //    ui->lineEdit_birthDate->setText(arrStr[6]);
          }
        }else{
          QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
        }
    }
}

void AddTeacherDialog::on_pushButton_applyTab2_clicked()
{
    if(!(ui->label_teachCodeTab2->text().isEmpty())){
        QSqlQuery qry1;
        QSqlQuery qry2;
        QSqlQuery qry3;
        QString strQry;
        QString currID;

        strQry = "Select ID \
                  From tblTeacher \
                  Where tblTeacher.TeacherCode = " + ui->label_teachCodeTab2->text();

        qry1.exec(strQry);

        if(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Update tblPerson \
                      Set FirstName = :name, LastName = :lastname, NationalCode = :nationalcode, BirthDate = :birthdate, Gender = :gender \
                      Where tblPerson.ID = :id");

        qry2.bindValue(":id", currID);
        qry2.bindValue(":name", ui->lineEdit_nameTab2->text());
        qry2.bindValue(":lastname", ui->lineEdit_lastNameTab2->text());
        qry2.bindValue(":nationalcode", ui->lineEdit_nationalCodeTab2->text());
        qry2.bindValue(":birthdate", ui->lineEdit_birthDateTab2->text());
        if(ui->comboBox_genderTab2->currentText() == "مرد"){
            qry2.bindValue(":gender", true);
        }else{
            qry2.bindValue(":gender", false);
        }

        if(qry2.exec()){

            qry3.prepare("Update tblTeacher \
                          Set EducationDegree = :educationdegree, Password = :password\
                          Where tblTeacher.TeacherCode = :teachcode");
            qry3.bindValue(":teachcode", ui->label_teachCodeTab2->text());
            qry3.bindValue(":educationdegree", ui->lineEdit_eduDegreeTab2->text());
            qry3.bindValue(":password", ui->lineEdit_nationalCodeTab2->text());

            if(qry3.exec()){
                QMessageBox::information(this, "OK", "اطلاعات استاد به روز شد.");
                ui->lineEdit_nameTab2->clear();
                ui->lineEdit_lastNameTab2->clear();
                ui->lineEdit_birthDateTab2->clear();
                ui->lineEdit_eduDegreeTab2->clear();
                ui->lineEdit_nationalCodeTab2->clear();
                ui->comboBox_genderTab2->setCurrentIndex(0);
                ui->label_teachCodeTab2->clear();
            }else{
                QMessageBox::warning(this, "OK", "به روز کردن اطلاعات استاد با شکست مواجه شد.");
            }
        }else{
            QMessageBox::warning(this, "OK", "به روز کردن اطلاعات استاد با شکست مواجه شد.");
        }
    }
}

void AddTeacherDialog::on_pushButton_showAllStudentTab2_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}


///---------------Tab3-------------------------------------------------------------------------------->




void AddTeacherDialog::on_pushButton_searchTab3_clicked()
{
    QSqlQuery qry;

    QString currID;
    QString eduDegree;
    QString strTeachCode;
    QString teacherCode;
    QString nationalCode;
    QString firstName;
    QString lastName;
    QString name;

    ui->label_nameTab3->clear();
    ui->label_degreeTab3->clear();
    ui->label_nationalCodeTab3->clear();
    ui->label_teachCodeTab3->clear();

    if(ui->lineEdit_teachCodeTab3->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد یا نام وارد کنید.");
    }else{
        teacherCode = ui->lineEdit_teachCodeTab3->text();

        QSqlQuery qry("Select  TeacherCode, EducationDegree, FirstName, LastName, NationalCode \
                       From tblPerson , tblTeacher \
                       Where ( tblPerson.ID = tblTeacher.ID ) AND \
                             ( tblTeacher.TeacherCode like '" + teacherCode + "%' OR \
                               tblPerson.Firstname like N'" + teacherCode + "%' OR \
                               tblPerson.Lastname like N'" + teacherCode + "%' OR \
                               tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + teacherCode + "%')");

        if(qry.numRowsAffected() != 0){

            if(qry.numRowsAffected() == 1){

                while (qry.next()){
                  strTeachCode = qry.value(0).toString();
                  eduDegree = qry.value(1).toString();
                  firstName = qry.value(2).toString();
                  lastName = qry.value(3).toString();
                  nationalCode = qry.value(4).toString();
                }

                name = firstName + " " + lastName;

                ui->label_nameTab3->setText(name);
                ui->label_nationalCodeTab3->setText(nationalCode);
                ui->label_degreeTab3->setText(eduDegree);
                ui->label_teachCodeTab3->setText(strTeachCode);
            }else {
                QMessageBox::warning(this, "warning", "بیشتر از یک مورد وجود دارد " + teacherCode + " وجود دارد.");

                while (qry.next()){
                strTeachCode = qry.value(0).toString();
                eduDegree = qry.value(1).toString();
                firstName = qry.value(2).toString();
                lastName = qry.value(3).toString();
                nationalCode = qry.value(4).toString();
                }

                name = firstName + " " + lastName;

                ui->label_nameTab3->setText(name);
                ui->label_nationalCodeTab3->setText(nationalCode);
                ui->label_degreeTab3->setText(eduDegree);
                ui->label_teachCodeTab3->setText(strTeachCode);
            }
        }else{
            QMessageBox::warning(this, "warning", "لطفا یک نام یا کد کارمندی صحیح وارد کنید.");
        }
    }
}

void AddTeacherDialog::on_pushButton_remove_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString teachCode;
    QString currID;
    QString strQry;

    if(!(ui->label_teachCodeTab3->text().isEmpty())){
        teachCode = ui->label_teachCodeTab3->text();

        qry1.prepare("SELECT ID \
                      FROM tblTeacher \
                      WHERE tblTeacher.TeacherCode = :teachercode");
                qry1.bindValue(":teachercode", teachCode);
                qry1.exec();

        if(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Delete From tblTeacher\
                      Where tblTeacher.TeacherCode = :teachercode");
                qry2.bindValue(":teachercode", teachCode);

        if(qry2.exec()){
            qry3.prepare("Delete From tblPerson \
                          Where tblPerson.ID = :id");
                    qry3.bindValue(":id", currID);

            if(qry3.exec()){
                QMessageBox::information(this, "OK", "استاد مورد نظر حذف شد.");
                ui->lineEdit_teachCodeTab3->clear();
                ui->label_nameTab3->clear();
                ui->label_degreeTab3->clear();
                ui->label_teachCodeTab3->clear();
                ui->label_nationalCodeTab3->clear();
            }else{
                QMessageBox::warning(this,"Error", "There is Something Wrong In Database");
            }
        }else{
            QMessageBox::warning(this,"Error", "There is Something Wrong In Database");
        }
    }else{
        QMessageBox::warning(this, "Warning", "لطفا اول یک کد کارمندی را جستجو کنید.");
    }
}

void AddTeacherDialog::on_pushButton_showTeacherTab3_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}
