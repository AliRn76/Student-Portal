#include "editteacherdialog.h"
#include "ui_editteacherdialog.h"

EditTeacherDialog::EditTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeacherDialog)
{
    ui->setupUi(this);
}

EditTeacherDialog::~EditTeacherDialog()
{
    delete ui;
}

void EditTeacherDialog::on_pushButton_search_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_lastName->clear();
    ui->lineEdit_birthDate->clear();
    ui->lineEdit_eduDegree->clear();
    ui->lineEdit_nationalCode->clear();
    ui->comboBox_gender->setCurrentIndex(0);

    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد یا نام وارد کنید.");
    }else{
        QString arrStr[8];

        QString strTeachCode = ui->lineEdit->text();

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

              ui->label_teachCode->setText(arrStr[0]);
              ui->lineEdit_name->setText(arrStr[1]);
              ui->lineEdit_lastName->setText(arrStr[2]);
              if(arrStr[3] == "1"){
                  ui->comboBox_gender->setCurrentText("مرد");
              }else{
                  ui->comboBox_gender->setCurrentText("زن");
              }
              ui->lineEdit_eduDegree->setText(arrStr[4]);
              ui->lineEdit_nationalCode->setText(arrStr[5]);
          //    ui->lineEdit_birthDate->setText(arrStr[6]);
          }else{
              QMessageBox::warning(this, "warning", "بیش از یک مورد " + strTeachCode + " وجود دارد.");

              while (qry.next()){
                  for(int i=0 ; i<7 ; i++){
                      arrStr[i] = qry.value(i).toString();
                  }
              }

              ui->label_teachCode->setText(arrStr[0]);
              ui->lineEdit_name->setText(arrStr[1]);
              ui->lineEdit_lastName->setText(arrStr[2]);
              if(arrStr[3] == "1"){
                  ui->comboBox_gender->setCurrentText("مرد");
              }else{
                  ui->comboBox_gender->setCurrentText("زن");
              }
              ui->lineEdit_eduDegree->setText(arrStr[4]);
              ui->lineEdit_nationalCode->setText(arrStr[5]);
          //    ui->lineEdit_birthDate->setText(arrStr[6]);
          }
        }else{
          QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
        }
    }
}

void EditTeacherDialog::on_pushButton_showAllStudent_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}

void EditTeacherDialog::on_pushButton_apply_clicked()
{
    if(!(ui->label_teachCode->text().isEmpty())){
        QSqlQuery qry1;
        QSqlQuery qry2;
        QSqlQuery qry3;
        QString strQry;
        QString currID;

        strQry = "Select ID \
                  From tblTeacher \
                  Where tblTeacher.TeacherCode = " + ui->label_teachCode->text();

        qry1.exec(strQry);

        if(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Update tblPerson \
                      Set FirstName = :name, LastName = :lastname, NationalCode = :nationalcode, BirthDate = :birthdate, Gender = :gender \
                      Where tblPerson.ID = :id");

        qry2.bindValue(":id", currID);
        qry2.bindValue(":name", ui->lineEdit_name->text());
        qry2.bindValue(":lastname", ui->lineEdit_lastName->text());
        qry2.bindValue(":nationalcode", ui->lineEdit_nationalCode->text());
        qry2.bindValue(":birthdate", ui->lineEdit_birthDate->text());
        if(ui->comboBox_gender->currentText() == "مرد"){
            qry2.bindValue(":gender", true);
        }else{
            qry2.bindValue(":gender", false);
        }

        if(qry2.exec()){

            qry3.prepare("Update tblTeacher \
                          Set EducationDegree = :educationdegree, Password = :password\
                          Where tblTeacher.TeacherCode = :teachcode");
            qry3.bindValue(":teachcode", ui->label_teachCode->text());
            qry3.bindValue(":educationdegree", ui->lineEdit_eduDegree->text());
            qry3.bindValue(":password", ui->lineEdit_nationalCode->text());

            if(qry3.exec()){
                QMessageBox::information(this, "OK", "اطلاعات استاد به روز شد.");
                ui->lineEdit_name->clear();
                ui->lineEdit_lastName->clear();
                ui->lineEdit_birthDate->clear();
                ui->lineEdit_eduDegree->clear();
                ui->lineEdit_nationalCode->clear();
                ui->comboBox_gender->setCurrentIndex(0);
                ui->label_teachCode->clear();
            }else{
                QMessageBox::warning(this, "OK", "به روز کردن اطلاعات استاد با شکست مواجه شد.");
            }
        }else{
            QMessageBox::warning(this, "OK", "به روز کردن اطلاعات استاد با شکست مواجه شد.");
        }
    }
}
