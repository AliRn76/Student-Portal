#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

EditStudentDialog::EditStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog)
{
    ui->setupUi(this);
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::on_pushButton_search_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_lastname->clear();
    ui->lineEdit_birthdate->clear();
    ui->lineEdit_fathersname->clear();
    ui->lineEdit_saalevoroud->clear();
    ui->lineEdit_nationalcode->clear();
    ui->comboBox_gender->setCurrentIndex(0);
    ui->label_stuCode->clear();
    ui->comboBox_field->setCurrentIndex(0);

    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");
    }else{
        QString arrStr[9];

        QString strStuCode = ui->lineEdit->text();

        QSqlQuery qry("Select StudentCode, FirstName, LastName, Gender as 'Is Male', FathersName, NationalCode, BirthDate, SaalVoroud, Field \
                       From Student.dbo.tblPerson , Student.dbo.tblStudent \
                       Where tblPerson.ID = tblStudent.ID AND( Student.dbo.tblStudent.StudentCode like '" + strStuCode + "%' OR \
                       Student.dbo.tblPerson.Firstname like N'" + strStuCode + "%' OR \
                       Student.dbo.tblPerson.Lastname like N'" + strStuCode + "%' )");

        if(qry.numRowsAffected() != 0){
            if(qry.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیش از یک مورد " + strStuCode + " وجود دارد.");
            }
            while (qry.next()){
                for(int i=0 ; i<9 ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }

            ui->label_stuCode->setText(arrStr[0]);
            ui->lineEdit_name->setText(arrStr[1]);
            ui->lineEdit_lastname->setText(arrStr[2]);
            if(arrStr[3] == "1"){
                ui->comboBox_gender->setCurrentText("مرد");
            }else{
                ui->comboBox_gender->setCurrentText("زن");
            }
            ui->lineEdit_fathersname->setText(arrStr[4]);
            ui->lineEdit_nationalcode->setText(arrStr[5]);
            ui->lineEdit_birthdate->setText(arrStr[6]);
            ui->lineEdit_saalevoroud->setText(arrStr[7]);
            ui->comboBox_field->setCurrentText(arrStr[8]);

        }else{
                QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
        }
    }
}

void EditStudentDialog::on_pushButton_apply_clicked()
{
    if(!(ui->label_stuCode->text().isEmpty())){
        QSqlQuery qry1;
        QSqlQuery qry2;
        QSqlQuery qry3;
        QString strQry;
        QString currID;

        strQry = "Select ID \
                  From student.dbo.tblStudent \
                  Where tblStudent.StudentCode = " + ui->label_stuCode->text();

        qry1.exec(strQry);
        while(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Update Student.dbo.tblPerson \
                      Set FirstName = :name, LastName = :lastname, NationalCode = :nationalcode, BirthDate = :birthdate, Gender = :gender \
                      Where tblPerson.ID = :id");

        qry2.bindValue(":id", currID);
        qry2.bindValue(":name", ui->lineEdit_name->text());
        qry2.bindValue(":lastname", ui->lineEdit_lastname->text());
        qry2.bindValue(":nationalcode", ui->lineEdit_nationalcode->text());
        qry2.bindValue(":birthdate", ui->lineEdit_birthdate->text());
        if(ui->comboBox_gender->currentText() == "مرد"){
            qry2.bindValue(":gender", true);
        }else{
            qry2.bindValue(":gender", false);
        }
        qry2.exec();

        qry3.prepare("Update Student.dbo.tblStudent \
                      Set FathersName = :fathersname, SaalVoroud = :saalevoroud, Field = :field \
                      Where tblStudent.StudentCode = :stucode");
        qry3.bindValue(":stucode", ui->label_stuCode->text());
        qry3.bindValue(":fathersname", ui->lineEdit_fathersname->text());
        qry3.bindValue(":saalevoroud", ui->lineEdit_saalevoroud->text());
        qry3.bindValue(":field", ui->comboBox_field->currentText());
        qry3.exec();

        QMessageBox::information(this, "OK", "اطلاعات دانشجو به روز شد.");
        ui->lineEdit_name->clear();
        ui->lineEdit_lastname->clear();
        ui->lineEdit_birthdate->clear();
        ui->lineEdit_fathersname->clear();
        ui->lineEdit_saalevoroud->clear();
        ui->lineEdit_nationalcode->clear();
        ui->comboBox_gender->setCurrentIndex(0);
        ui->label_stuCode->clear();
        ui->comboBox_field->setCurrentIndex(0);
    }
}

void EditStudentDialog::on_pushButton_showAllStudent_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}
