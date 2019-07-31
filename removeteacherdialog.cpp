#include "removeteacherdialog.h"
#include "ui_removeteacherdialog.h"

RemoveTeacherDialog::RemoveTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveTeacherDialog)
{
    ui->setupUi(this);
}

RemoveTeacherDialog::~RemoveTeacherDialog()
{
    delete ui;
}

void RemoveTeacherDialog::on_pushButton_search_clicked()
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

    ui->label_name->clear();
    ui->label_degree->clear();
    ui->label_nationalCode->clear();
    ui->label_teachCode->clear();

    if(ui->lineEdit_teachCode->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد یا نام وارد کنید.");
    }else{
        teacherCode = ui->lineEdit_teachCode->text();

        QSqlQuery qry("Select  TeacherCode, EducationDegree, FirstName, LastName, NationalCode \
                       From tblPerson , Student.dbo.tblTeacher \
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

                ui->label_name->setText(name);
                ui->label_nationalCode->setText(nationalCode);
                ui->label_degree->setText(eduDegree);
                ui->label_teachCode->setText(strTeachCode);
            }else {
                QMessageBox::warning(this, "warning", "بیشتر از یک مورد وجود دارد" + teacherCode + " وجود دارد.");

                while (qry.next()){
                strTeachCode = qry.value(0).toString();
                eduDegree = qry.value(1).toString();
                firstName = qry.value(2).toString();
                lastName = qry.value(3).toString();
                nationalCode = qry.value(4).toString();
                }

                name = firstName + " " + lastName;

                ui->label_name->setText(name);
                ui->label_nationalCode->setText(nationalCode);
                ui->label_degree->setText(eduDegree);
                ui->label_teachCode->setText(strTeachCode);
            }
        }else{
            QMessageBox::warning(this, "warning", "لطفا یک نام یا کد کارمندی صحیح وارد کنید.");
        }
    }
}

void RemoveTeacherDialog::on_pushButton_remove_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString teachCode;
    QString currID;
    QString strQry;

    if(!(ui->label_teachCode->text().isEmpty())){
        teachCode = ui->label_teachCode->text();

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
                ui->lineEdit_teachCode->clear();
                ui->label_name->clear();
                ui->label_degree->clear();
                ui->label_teachCode->clear();
                ui->label_nationalCode->clear();
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

void RemoveTeacherDialog::on_pushButton_showTeacher_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}
