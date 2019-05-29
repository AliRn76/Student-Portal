#include "entekhabvaheddialog.h"
#include "ui_entekhabvaheddialog.h"

EntekhabVahedDialog::EntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntekhabVahedDialog)
{
    ui->setupUi(this);
}

EntekhabVahedDialog::~EntekhabVahedDialog()
{
    delete ui;
}

void EntekhabVahedDialog::on_pushButton_findStu_clicked()
{
    ui->label_stuCode->clear();
    ui->label_stuName->clear();

    QString arrStr[3];
    QString strStuCode = ui->lineEdit_stuCode->text();

    QSqlQuery qry("Select FirstName, LastName, StudentCode \
                   From Student.dbo.tblStudent, Student.dbo.tblPerson \
                   Where tblStudent.ID = tblPerson.ID AND ( \
                   tblStudent.StudentCode like '" + strStuCode + "%' OR \
                   tblPerson.FirstName like N'" + strStuCode + "%' OR \
                   tblPerson.LastName like N'" + strStuCode + "%' OR \
                   tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + strStuCode + "%')");

    if(qry.numRowsAffected() != 0){
        if(qry.numRowsAffected() == 1){
            while(qry.next()){
                for(int i=0 ; i<3 ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }
            ui->label_stuName->setText(arrStr[0] + " " + arrStr[1]);
            ui->label_stuCode->setText(arrStr[2]);
        }else{
            QMessageBox::warning(this, "warning", "بیشتر از یک مورد وجود دارد.");
        }
    }else{
        if(ui->lineEdit_stuCode->text().isEmpty()){
            QMessageBox::warning(this, "warning", "ابتدا یک شماره دانشجویی وارد کنید.");

        }else{
            QMessageBox::warning(this, "warning", "لطفا یک شماره دانشجویی صحیح وارد کنید.");
        }
    }
}

void EntekhabVahedDialog::on_pushButton_findLesson_clicked()
{
    ui->label_entekhabID->clear();
    ui->label_lessonName->clear();
    ui->label_roozeHafte->clear();
    ui->label_time->clear();

    QString entekhabID;
    QSqlQuery qry1;

    entekhabID = ui->lineEdit_entekhabID->text();

    if(entekhabID.isEmpty()){
        QMessageBox::warning(this, "warning", "ابتدا یک مشخصه وارد کنید.");

    }else{
        if(entekhabID.toInt()){
            qry1.prepare("Select tblErae.ID, Title, DaysOfWeek, TimeOfClass \
                         From Student.dbo.tblLesson, Student.dbo.tblErae \
                         Where tblErae.ID_Lesson = tblLesson.ID \
                         AND tblErae.ID = :entekhabID");
                    qry1.bindValue(":entekhabID", entekhabID);
                    qry1.exec();

            if(qry1.numRowsAffected() != 0){
                while(qry1.next()){
                        ui->label_entekhabID->setText(qry1.value(0).toString());
                        ui->label_lessonName->setText(qry1.value(1).toString());
                        ui->label_roozeHafte->setText(qry1.value(2).toString());
                        ui->label_time->setText(qry1.value(3).toString());
                }
            }else{
                QMessageBox::warning(this, "خطا", "لطفا یک مشخصه صحیح وارد کنید.");
            }
        }else{
            QMessageBox::warning(this, "Warning", "لطفا یک مشخصه صحیح وارد کنید.");
        }
    }
}

void EntekhabVahedDialog::on_pushButton_showStu_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}

void EntekhabVahedDialog::on_pushButton_showErae_clicked()
{
    showEraeDialog = new ShowEraeListDialog(this);
    showEraeDialog->show();
}

void EntekhabVahedDialog::on_pushButton_apply_clicked()
{

    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString stuCode;
    QString eraeID;
    int stuID;

    eraeID = ui->label_entekhabID->text();
    stuCode = ui->label_stuCode->text();

    if(ui->label_stuCode->text().isEmpty() || ui->label_entekhabID->text().isEmpty()){

        if(ui->label_stuCode->text().isEmpty()){

            QMessageBox::warning(this, "Warning", "ابتدا یک دانشجو را جستجو کنید.");
        }else{
            QMessageBox::warning(this, "Warning", "ابتدا یک مشخصه درس را جستجو کنید.");
        }
    }else{    
        qry1.prepare("Select ID From Student.dbo.tblStudent \
                      Where tblStudent.StudentCode = :stucode");

                qry1.bindValue(":stucode", stuCode);
                qry1.exec();

                while(qry1.next()){
                    stuID = qry1.value(0).toInt();
                }

        qry3.prepare("Select ID From Student.dbo.tblEntekhabVahed \
                      Where ID_Erae = :iderae AND ID_Student = :idstudent");
                qry3.bindValue(":iderae", eraeID);
                qry3.bindValue(":idstudent", stuID);
                qry3.exec();

            if(qry3.numRowsAffected() > 0 ){
                QMessageBox::warning(this, "هشدار" , "این درس قبلا برای این دانشجو انتخاب شده است.");

            }else{
                qry2.prepare("Insert Into Student.dbo.tblEntekhabVahed \
                              (ID_Erae, ID_Student) \
                              Values(:iderae, :idstu) ");

                             qry2.bindValue(":iderae", eraeID);
                             qry2.bindValue(":idstu", stuID);

                    if(qry2.exec()){
                            QMessageBox::information(this, "OK", "درس با موفقیت انتخاب شد.");
                            ui->label_stuCode->clear();
                            ui->label_stuName->clear();
                            ui->label_entekhabID->clear();
                            ui->label_lessonName->clear();
                            ui->label_roozeHafte->clear();
                            ui->label_time->clear();
                    }else{
                        QMessageBox::warning(this, "Warning", "انتخاب درس با شکست مواجه شد.");
                    }
            }
    }
}

