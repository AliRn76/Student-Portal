#include "removeentekhabvaheddialog.h"
#include "ui_removeentekhabvaheddialog.h"

RemoveEntekhabVahedDialog::RemoveEntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveEntekhabVahedDialog)
{
    ui->setupUi(this);

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery("Select StudentCode as 'شماره دانشجویی', FirstName + ' ' + LastName as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود' \
                        From student.dbo.tblPerson , student.dbo.tblStudent \
                        Where tblPerson.ID = tblStudent.ID");

            ui->treeView->setModel(qryModel);
}

RemoveEntekhabVahedDialog::~RemoveEntekhabVahedDialog()
{
    delete ui;
}

QString RemoveEntekhabVahed2Dialog::name;
QString RemoveEntekhabVahed2Dialog::studentCode;

void RemoveEntekhabVahedDialog::on_pushButton_search_clicked()
{

    if(ui->lineEdit_stuCode->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");
        ui->label_name->clear();
        ui->label_studentCode->clear();
    }else{

        QString strStuCode = ui->lineEdit_stuCode->text();

        QSqlQuery qry("Select StudentCode, FirstName, LastName \
                       From Student.dbo.tblPerson , Student.dbo.tblStudent \
                       Where tblPerson.ID = tblStudent.ID AND( Student.dbo.tblStudent.StudentCode like '" + strStuCode + "%' OR \
                       Student.dbo.tblPerson.Firstname like N'" + strStuCode + "%' OR \
                       Student.dbo.tblPerson.Lastname like N'" + strStuCode + "%' )");

        if(qry.numRowsAffected() != 0){
            if(qry.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیش از یک مورد " + strStuCode + " وجود دارد.");
            }
            while (qry.next()){
                RemoveEntekhabVahed2Dialog::studentCode = qry.value(0).toString();
                RemoveEntekhabVahed2Dialog::name = qry.value(1).toString() + " " + qry.value(2).toString();
            }

            ui->label_studentCode->setText(RemoveEntekhabVahed2Dialog::studentCode);
            ui->label_name->setText(RemoveEntekhabVahed2Dialog::name);

        }else{
                QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
                ui->label_name->clear();
                ui->label_studentCode->clear();
        }
    }
}

void RemoveEntekhabVahedDialog::on_pushButton_choose_clicked()
{
    QSqlQuery qry;
    int row;


    row = ui->treeView->currentIndex().row();

    qry.exec("Select StudentCode, FirstName, LastName \
             From student.dbo.tblPerson , student.dbo.tblStudent \
             Where tblPerson.ID = tblStudent.ID");

        qry.seek(row);

        RemoveEntekhabVahed2Dialog::studentCode = qry.value(0).toString();
        RemoveEntekhabVahed2Dialog::name = qry.value(1).toString() + "  " + qry.value(2).toString();

    ui->label_studentCode->setText(RemoveEntekhabVahed2Dialog::studentCode);
    ui->label_name->setText(RemoveEntekhabVahed2Dialog::name);
}

void RemoveEntekhabVahedDialog::on_pushButton_nextPage_clicked()
{
    rmvEntekhab2Dialog = new RemoveEntekhabVahed2Dialog(this);
    rmvEntekhab2Dialog->show();
}
