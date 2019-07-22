#include "removestudentdialog.h"
#include "ui_removestudentdialog.h"

RemoveStudentDialog::RemoveStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveStudentDialog)
{
    ui->setupUi(this);
}

RemoveStudentDialog::~RemoveStudentDialog()
{
    delete ui;
}

void RemoveStudentDialog::on_pushButton_search_clicked()
{
    ui->label_name->clear();
    ui->label_stuCode->clear();
    ui->label_fathersName->clear();
    ui->label_nationalCode->clear();
    ui->label_field->clear();

    if(ui->lineEdit_stuCode->text().isEmpty()){
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

        stuCode = ui->lineEdit_stuCode->text();

        QSqlQuery qry1("Select FathersName, StudentCode, FirstName, LastName, NationalCode, Field \
                      From Student.dbo.tblStudent , Student.dbo.tblPerson \
                      Where tblPerson.ID = tblStudent.ID AND ( \
                      tblStudent.StudentCode like '" + stuCode +"%' OR \
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
            ui->label_name->setText(name);
            ui->label_nationalCode->setText(nationalCode);
            ui->label_fathersName->setText(fathersName);
            ui->label_stuCode->setText(strStuCode);
            ui->label_field->setText(field);
        }
    }
}

void RemoveStudentDialog::on_pushButton_remove_clicked()
{

    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString stuCode;
    QString currID;
    QString strQry;

    if(!(ui->label_stuCode->text().isEmpty())){
        stuCode = ui->label_stuCode->text();

        strQry = "SELECT ID FROM Student.dbo.tblStudent WHERE Student.dbo.tblStudent.StudentCode = " + stuCode;

        qry1.exec(strQry);
        while(qry1.next()){
            currID = qry1.value(0).toString();
        }

        qry2.prepare("Delete From Student.dbo.tblStudent\
                     Where Student.dbo.tblStudent.StudentCode = :stucode");
        qry2.bindValue(":stucode", stuCode);
        if(qry2.exec()){
            qry3.prepare("Delete From Student.dbo.tblPerson \
                         Where Student.dbo.tblPerson.ID = :id");
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

    ui->label_name->clear();
    ui->label_stuCode->clear();
    ui->label_fathersName->clear();
    ui->label_nationalCode->clear();
    ui->label_field->clear();
}

void RemoveStudentDialog::on_pushButton_showAllStu_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}
