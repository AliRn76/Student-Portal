#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"

AddStudentDialog::AddStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);
}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}


///---------------Tab1-------------------------------------------------------------------------------->


void AddStudentDialog::on_pushButton_add_clicked()
{
    if(ui->lineEdit_name->text().isEmpty() || ui->lineEdit_lastName->text().isEmpty() || ui->lineEdit_nationalCode->text().isEmpty() || ui->lineEdit_saalevoroud->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "لطفا موارد بالا پر کنید.");
    }else{
        QSqlQuery qry1;
        QSqlQuery qry2;
        QSqlQuery qry3;
        QSqlQuery qry4;

        QString strName;
        QString strLastname;
        QString strNationalcode;
        QString strFathersname;
        QString strSaalvoroud;
        QString stuCode;
        QString strField;
        QVariant currentID;
        QDate birthDate;
        bool blGender;

        strName = ui->lineEdit_name->text();
        strLastname = ui->lineEdit_lastName->text();
        strNationalcode = ui->lineEdit_nationalCode->text();
        strFathersname = ui->lineEdit_fathersName->text();
        strSaalvoroud = ui->lineEdit_saalevoroud->text();
        birthDate.setDate(ui->comboBox_saal->currentText().toInt(), ui->comboBox_maah->currentText().toInt(), ui->comboBox_rouz->currentText().toInt());
        if(ui->radioButton_male->isChecked()){
            blGender =  true;
        }else if(ui->radioButton_female->isChecked()){
            blGender = false;
        }
        strField = ui->comboBox_field->currentText();

        if(strSaalvoroud.toInt()){
            if(strNationalcode.toULongLong()){
                if(strNationalcode.length() != 10){
                    QMessageBox::warning(this, "خطا", "لطفا کد ملی خود را به صورت 10 رقمی وارد کنید.");
                }else{
                    qry1.prepare("Insert Into tblPerson \
                                 (FirstName, LastName, Nationalcode, Gender) \
                                 Values(:name, :lastname, :nationalcode, :gender)"); //  , :birthdate  ,BirthDate
                                qry1.bindValue(":name", strName);
                                qry1.bindValue(":lastname", strLastname);
                                qry1.bindValue(":nationalcode", strNationalcode);
                                qry1.bindValue(":gender", blGender );
                               // qry1.bindValue(":birthdate", birthDate);
                                qry1.exec();

                    currentID = qry1.lastInsertId().toString();
                    qDebug() << currentID;
                    qry2.prepare("Insert Into tblStudent \
                                 (ID, FathersName, SaalVoroud, Password, Field) \
                                 Values(:id, :fathersname, :saalvoroud, :password, :field)");
                                qry2.bindValue(":id" , currentID);
                                qry2.bindValue(":fathersname" , strFathersname );
                                qry2.bindValue(":saalvoroud", strSaalvoroud);
                                qry2.bindValue(":password", strNationalcode);
                                qry2.bindValue(":field", strField);

                                if(qry2.exec()){
                                    qry4.prepare("Select StudentCode From tblStudent \
                                                  Where tblStudent.ID = :id");
                                            qry4.bindValue(":id", currentID);
                                            qry4.exec();

                                    if(qry4.next()){
                                        stuCode = qry4.value(0).toString();
                                    }

                                    QMessageBox::information(this, "OK", "دانشجو اضافه شد ، شماره داشجویی : " + stuCode);

                                    ui->lineEdit_name->clear();
                                    ui->lineEdit_lastName->clear();
                                    ui->lineEdit_fathersName->clear();
                                    ui->lineEdit_saalevoroud->clear();
                                    ui->lineEdit_nationalCode->clear();
                                }else{
                                    qDebug()<< qry2.lastError().text();
                                    QMessageBox::warning(this, "خطا", "یه مشکلی پیش اومده ، برنامه رو نشون علی بده.");
                                }
                }
            }else{
                QMessageBox::warning(this, "خطا", "لطفا کد ملی خود را تصحیح کنید.");
                qDebug()<<"National Code: " << strNationalcode << "   National Code ToInt: " << strNationalcode.toULongLong();
            }
        }else{
            QMessageBox::warning(this, "خطا", "لطفا سال ورود خود را تصحیح کنید.");
        }
    }
}

void AddStudentDialog::on_pushButton_showAllStu_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}


///---------------Tab2-------------------------------------------------------------------------------->



void AddStudentDialog::on_pushButton_searchTab2_clicked()
{
    ui->lineEdit_nameTab2->clear();
    ui->lineEdit_lastnameTab2->clear();
    ui->lineEdit_birthdateTab2->clear();
    ui->lineEdit_fathersnameTab2->clear();
    ui->lineEdit_saalevoroudTab2->clear();
    ui->lineEdit_nationalcodeTab2->clear();
    ui->comboBox_genderTab2->setCurrentIndex(0);
    ui->label_stuCodeTab2->clear();
    ui->comboBox_fieldTab2->setCurrentIndex(0);

    if(ui->lineEditTab2->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");
    }else{
        QString arrStr[9];

        QString strStuCode = ui->lineEditTab2->text();

        QSqlQuery qry("Select StudentCode, FirstName, LastName, Gender as 'Is Male', FathersName, NationalCode, BirthDate, SaalVoroud, Field \
                       From tblPerson , tblStudent \
                       Where tblPerson.ID = tblStudent.ID AND( tblStudent.StudentCode like '" + strStuCode + "%' OR \
                       tblPerson.Firstname like N'" + strStuCode + "%' OR \
                       tblPerson.Lastname like N'" + strStuCode + "%' OR \
                       tblPerson.Firstname + ' ' + tblPerson.Lastname like N'" + strStuCode + "%')");

        if(qry.numRowsAffected() != 0){
            if(qry.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیش از یک مورد " + strStuCode + " وجود دارد.");
            }
            while (qry.next()){
                for(int i=0 ; i<9 ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }

            ui->label_stuCodeTab2->setText(arrStr[0]);
            ui->lineEdit_nameTab2->setText(arrStr[1]);
            ui->lineEdit_lastnameTab2->setText(arrStr[2]);
            if(arrStr[3] == "\u0001"){
                ui->comboBox_genderTab2->setCurrentText("مرد");
            }else{
                ui->comboBox_genderTab2->setCurrentText("زن");
            }
            ui->lineEdit_fathersnameTab2->setText(arrStr[4]);
            ui->lineEdit_nationalcodeTab2->setText(arrStr[5]);
            ui->lineEdit_birthdateTab2->setText(arrStr[6]);
            ui->lineEdit_saalevoroudTab2->setText(arrStr[7]);
            ui->comboBox_fieldTab2->setCurrentText(arrStr[8]);
            qDebug() << arrStr[3];

        }else{
                QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
        }
    }
}

void AddStudentDialog::on_pushButton_applyTab2_clicked()
{
    QString nationalCode = ui->lineEdit_nationalcodeTab2->text();

    if(!(ui->label_stuCodeTab2->text().isEmpty())){
        if(nationalCode.length() != 10){
            QMessageBox::warning(this, "خطا", "لطفا کد ملی خود را به صورت 10 رقمی وارد کنید.");
        }else{
            QSqlQuery qry1;
            QSqlQuery qry2;
            QSqlQuery qry3;
            QString strQry;
            QString currID;

            strQry = "Select ID \
                      From tblStudent \
                      Where tblStudent.StudentCode = " + ui->label_stuCodeTab2->text();

            qry1.exec(strQry);
            while(qry1.next()){
                currID = qry1.value(0).toString();
            }

            qry2.prepare("Update tblPerson \
                          Set FirstName = :name, LastName = :lastname, NationalCode = :nationalcode, BirthDate = :birthdate, Gender = :gender \
                          Where tblPerson.ID = :id");

            qry2.bindValue(":id", currID);
            qry2.bindValue(":name", ui->lineEdit_nameTab2->text());
            qry2.bindValue(":lastname", ui->lineEdit_lastnameTab2->text());
            qry2.bindValue(":nationalcode", ui->lineEdit_nationalcodeTab2->text());
            qry2.bindValue(":birthdate", ui->lineEdit_birthdateTab2->text());
            if(ui->comboBox_genderTab2->currentText() == "مرد"){
                qry2.bindValue(":gender", true);
            }else{
                qry2.bindValue(":gender", false);
            }
            qry2.exec();

            qry3.prepare("Update tblStudent \
                          Set FathersName = :fathersname, SaalVoroud = :saalevoroud, Field = :field, Password = :password \
                          Where tblStudent.StudentCode = :stucode");
            qry3.bindValue(":stucode", ui->label_stuCodeTab2->text());
            qry3.bindValue(":fathersname", ui->lineEdit_fathersnameTab2->text());
            qry3.bindValue(":saalevoroud", ui->lineEdit_saalevoroudTab2->text());
            qry3.bindValue(":field", ui->comboBox_fieldTab2->currentText());
            qry3.bindValue(":password", ui->lineEdit_nationalcodeTab2->text());
            qry3.exec();

            QMessageBox::information(this, "OK", "اطلاعات دانشجو به روز شد.");
            ui->lineEdit_nameTab2->clear();
            ui->lineEdit_lastnameTab2->clear();
            ui->lineEdit_birthdateTab2->clear();
            ui->lineEdit_fathersnameTab2->clear();
            ui->lineEdit_saalevoroudTab2->clear();
            ui->lineEdit_nationalcodeTab2->clear();
            ui->comboBox_genderTab2->setCurrentIndex(0);
            ui->label_stuCodeTab2->clear();
            ui->comboBox_fieldTab2->setCurrentIndex(0);
        }
    }
}

void AddStudentDialog::on_pushButton_showAllStudentsTab2_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}


///---------------Tab2-------------------------------------------------------------------------------->




void AddStudentDialog::on_pushButton_searchTab3_clicked()
{
    ui->label_nameTab3->clear();
    ui->label_stuCodeTab3->clear();
    ui->label_fathersNameTab3->clear();
    ui->label_nationalCodeTab3->clear();
    ui->label_fieldTab3->clear();

    if(ui->lineEdit_stuCodeTab3->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "ابتدا یک نام یا شماره شماره دانشجویی وارد کنید.");

    }else{
        QSqlQuery qry2;
        QSqlQuery qry3;
        QString strStuCode;
        QString currID;
        QString fathersName;
        QString name;
        QString nationalCode;
        QString stuCode;
        QString field;

        stuCode = ui->lineEdit_stuCodeTab3->text();

        QSqlQuery qry1("Select FathersName, StudentCode, FirstName, LastName, NationalCode, Field \
                        From tblStudent , tblPerson \
                        Where tblPerson.ID = tblStudent.ID AND \
                              ( tblStudent.StudentCode like '" + stuCode +"%' OR \
                                tblPerson.FirstName like N'" + stuCode + "%' OR \
                                tblPerson.LastName like N'" + stuCode + "%' OR \
                                tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + stuCode + "%')");

        if(qry1.numRowsAffected() == 0){
            QMessageBox::warning(this, "خطا" , "لطفا یک نام یا شماره دانشجویی صحیح وارد کنید.");

        }else{
            if(qry1.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیشتر از یک مورد دارد.");
            }
            while(qry1.next()){
                fathersName = qry1.value(0).toString();
                strStuCode = qry1.value(1).toString();
                name = qry1.value(2).toString() + " " + qry1.value(3).toString();
                nationalCode = qry1.value(4).toString();
                field = qry1.value(5).toString();
            }
            ui->label_nameTab3->setText(name);
            ui->label_nationalCodeTab3->setText(nationalCode);
            ui->label_fathersNameTab3->setText(fathersName);
            ui->label_stuCodeTab3->setText(strStuCode);
            ui->label_fieldTab3->setText(field);
        }
    }
}

void AddStudentDialog::on_pushButton_removeTab3_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString stuCode;
    QString currID;
    QString strQry;

    if(!(ui->label_stuCodeTab3->text().isEmpty())){
        stuCode = ui->label_stuCodeTab3->text();

        strQry = "SELECT ID \
                  FROM tblStudent \
                  WHERE tblStudent.StudentCode = " + stuCode;

        qry1.exec(strQry);
        while(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Delete From tblStudent\
                      Where tblStudent.StudentCode = :stucode");
        qry2.bindValue(":stucode", stuCode);
        if(qry2.exec()){
            qry3.prepare("Delete From tblPerson \
                         Where tblPerson.ID = :id");
            qry3.bindValue(":id", currID);
            if(qry3.exec()){
                QMessageBox::information(this, "OK", "دانشجوی مورد نظر حذف شد.");
            }else{
                QMessageBox::warning(this,"Error", "به دلیل اینکه این دانشجو دروسی را انتخاب واحد کرده است شما قادر به حذف آن نمیباشید.");
            }
        }else{
            QMessageBox::warning(this,"Error", "به دلیل اینکه این دانشجو دروسی را انتخاب واحد کرده است شما قادر به حذف آن نمیباشید.");
        }
    }else{
        QMessageBox::warning(this, "Warning", "لطفا اول یک کد دانشجویی را جستجو کنید.");
    }

    ui->label_nameTab3->clear();
    ui->label_stuCodeTab3->clear();
    ui->label_fathersNameTab3->clear();
    ui->label_nationalCodeTab3->clear();
    ui->label_fieldTab3->clear();
}

void AddStudentDialog::on_pushButton_showAllStuTab3_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}
