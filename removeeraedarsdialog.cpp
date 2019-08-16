#include "removeeraedarsdialog.h"
#include "ui_removeeraedarsdialog.h"

RemoveEraeDarsDialog::RemoveEraeDarsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveEraeDarsDialog)
{
    ui->setupUi(this);

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery("Select TeacherCode as 'کد کارمندی', FirstName + ' ' + LastName as 'نام', EducationDegree as 'مدرک تحصیلی' \
                        From tblPerson , tblTeacher \
                        Where tblPerson.ID = tblTeacher.ID");

            ui->treeView->setModel(qryModel);
}

RemoveEraeDarsDialog::~RemoveEraeDarsDialog()
{
    delete ui;
}

QString RemoveEraeDars2Dialog::name;
QString RemoveEraeDars2Dialog::teacherCode;

void RemoveEraeDarsDialog::on_pushButton_search_clicked()
{
    if(ui->lineEdit_teachCode->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");
        ui->label_name->clear();
        ui->label_teacherCode->clear();
    }else{

        QString strTeachCode = ui->lineEdit_teachCode->text();

        QSqlQuery qry("Select TeacherCode, FirstName, LastName \
                       From tblPerson , tblTeacher \
                       Where tblPerson.ID = tblTeacher.ID AND \
                             ( tblTeacher.TeacherCode like '" + strTeachCode + "%' OR \
                               tblPerson.Firstname like N'" + strTeachCode + "%' OR \
                               tblPerson.Lastname like N'" + strTeachCode + "%' )");

        if(qry.numRowsAffected() != 0){
            if(qry.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیش از یک مورد " + strTeachCode + " وجود دارد.");
            }
            while (qry.next()){
                RemoveEraeDars2Dialog::teacherCode = qry.value(0).toString();
                RemoveEraeDars2Dialog::name = qry.value(1).toString() + " " + qry.value(2).toString();
            }

            ui->label_teacherCode->setText(RemoveEraeDars2Dialog::teacherCode);
            ui->label_name->setText(RemoveEraeDars2Dialog::name);

        }else{
                QMessageBox::warning(this, "warning", "لطفا یک کد یا نام صحیح وارد کنید.");
                ui->label_name->clear();
                ui->label_teacherCode->clear();
        }
    }
}

void RemoveEraeDarsDialog::on_pushButton_choose_clicked()
{
    QSqlQuery qry;
    int row;


    row = ui->treeView->currentIndex().row();

    qry.exec("Select TeacherCode, FirstName, LastName \
              From tblPerson , tblTeacher \
              Where tblPerson.ID = tblTeacher.ID");

        qry.seek(row);

        RemoveEraeDars2Dialog::teacherCode = qry.value(0).toString();
        RemoveEraeDars2Dialog::name = qry.value(1).toString() + "  " + qry.value(2).toString();

    ui->label_teacherCode->setText(RemoveEraeDars2Dialog::teacherCode);
    ui->label_name->setText(RemoveEraeDars2Dialog::name);
}

void RemoveEraeDarsDialog::on_pushButton_nextPage_clicked()
{
    rmvErae2Dialog = new RemoveEraeDars2Dialog(this);
    rmvErae2Dialog->show();
}
