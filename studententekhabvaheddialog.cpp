#include "studententekhabvaheddialog.h"
#include "ui_studententekhabvaheddialog.h"

StudentEntekhabVahedDialog::StudentEntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentEntekhabVahedDialog)
{
    ui->setupUi(this);

    QSqlQuery qry;

    qry.prepare("Select StudentCode, FirstName, LastName, NumberOfTerm \
                 From Student.dbo.tblPerson, Student.dbo.tblStudent, Student.dbo.tblEntekhabVahed \
                 Where tblPerson.ID = tblStudent.ID AND \
                       tblStudent.ID = tblEntekhabVahed.ID_Student AND \
                       tblStudent.StudentCode = :stucode");
            qry.bindValue(":stucode", stuCode);
            qry.exec();

    while(qry.next()){
        ui->label_stuCode->setText(qry.value(0).toString());
        ui->label_name->setText(qry.value(1).toString() + " " + qry.value(2).toString());
        ui->label_nTerm->setText(qry.value(3).toString());
    }

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                       From Student.dbo.tblPerson, \
                            Student.dbo.tblErae, \
                            Student.dbo.tblTeacher, \
                            Student.dbo.tblLesson, \
                            Student.dbo.tblStudent \
                       Where tblPerson.ID = tblTeacher.ID AND \
                             tblTeacher.ID = tblErae.ID_Teacher AND \
                             tblErae.ID_Lesson = tblLesson.ID AND \
                             tblLesson.Field = tblStudent.Field AND \
                             tblStudent.Field = N'" + stuFieldEntekhab + "'");

    ui->treeView->setModel(qryModel);

}

StudentEntekhabVahedDialog::~StudentEntekhabVahedDialog()
{
    delete ui;
}

void StudentEntekhabVahedDialog::on_treeView_clicked(const QModelIndex &index)
{
    QSqlQuery qry;

    qry.exec("Select Distinct tblErae.ID, Title , FirstName + ' ' + LastName, DaysOfWeek, TimeOfClass \
              From Student.dbo.tblPerson, \
                   Student.dbo.tblErae, \
                   Student.dbo.tblTeacher, \
                   Student.dbo.tblLesson, \
                   Student.dbo.tblStudent \
             Where tblPerson.ID = tblTeacher.ID AND \
                   tblTeacher.ID = tblErae.ID_Teacher AND \
                   tblErae.ID_Lesson = tblLesson.ID AND \
                   tblLesson.Field = tblStudent.Field AND \
                   tblStudent.Field = N'" + stuFieldEntekhab + "'");

    qry.seek(index.row());

    ui->label_entekhabID->setText(qry.value(0).toString());
    ui->label_lessonName->setText(qry.value(1).toString());
    ui->label_teacher->setText(qry.value(2).toString());
    ui->label_rouz->setText(qry.value(3).toString());
    ui->label_time->setText(qry.value(4).toString());
}

void StudentEntekhabVahedDialog::on_pushButton_3_clicked()
{
    QSqlQuery qry1;
    QString strQry;
    QString field = stuFieldEntekhab;
    qryModel2 = new QSqlQueryModel(this);

    if(ui->lineEdit->text().toInt()){
        qry1.prepare("Select tblErae.ID, Title, FirstName + " " + LastName, DaysOfWeek, TimeOfClass \
                      From Student.dbo.tblPerson, \
                            Student.dbo.tblErae, \
                            Student.dbo.tblTeacher, \
                            Student.dbo.tblLesson, \
                            Student.dbo.tblStudent \
                      Where tblPerson.ID = tblTeacher.ID AND \
                            tblTeacher.ID = tblErae.ID_Teacher AND \
                            tblErae.ID_Lesson = tblLesson.ID AND \
                            tblLesson.Field = tblStudent.Field AND \
                            tblStudent.Field = N'" + field + "' AND \
                            tblErae.ID = :id");

                qry1.bindValue(":id", ui->lineEdit->text());
                qry1.exec();

        while(qry1.next()){
            ui->label_entekhabID->setText(qry1.value(0).toString());
            ui->label_lessonName->setText(qry1.value(1).toString());
            ui->label_teacher->setText(qry1.value(2).toString());
            ui->label_rouz->setText(qry1.value(3).toString());
            ui->label_time->setText(qry1.value(4).toString());
        }
    }else{
        strQry = "Select Distinct tblErae.ID, Title , FirstName + ' ' + LastName, DaysOfWeek, TimeOfClass \
                  From Student.dbo.tblPerson, \
                       Student.dbo.tblErae, \
                       Student.dbo.tblTeacher, \
                       Student.dbo.tblLesson, \
                       Student.dbo.tblStudent \
                 Where tblPerson.ID = tblTeacher.ID AND \
                       tblTeacher.ID = tblErae.ID_Teacher AND \
                       tblErae.ID_Lesson = tblLesson.ID AND \
                       tblLesson.Field = tblStudent.Field AND \
                       tblStudent.Field = N'" + stuFieldEntekhab + "' AND \
                       tblLesson.Title like N'" + ui->lineEdit->text() + "%'";

        qryModel2->setQuery(strQry);
        qDebug() << qryModel2->lastError();

        ui->treeView->setModel(qryModel2);
    }
}


void StudentEntekhabVahedDialog::on_pushButton_apply_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QSqlQuery qry4;
    int stuID;
    int eraeID = ui->label_entekhabID->text().toInt();

    if(ui->label_entekhabID->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "لطفا ابتدا یک درس را انتخاب کنید.");
    }else{
        qry1.prepare("Select ID From Student.dbo.tblStudent \
                      Where tblStudent.StudentCode = :stucode");

                qry1.bindValue(":stucode", stuCode);
                qry1.exec();

                while(qry1.next()){
                    stuID = qry1.value(0).toInt();
                }

        qry2.prepare("Select tblEntekhabVahed.ID \
                      From Student.dbo.tblEntekhabVahed, \
                           Student.dbo.tblErae, \
                           Student.dbo.tblLesson \
                      Where tblEntekhabVahed.ID_Student = :idstudent AND \
                            tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                            tblErae.ID_Lesson = tblLesson.ID AND \
                            ( tblEntekhabVahed.ID_Erae = :iderae OR tblLesson.Title = N'" + ui->label_lessonName->text()+ "')");
                qry2.bindValue(":iderae", eraeID);
                qry2.bindValue(":idstudent", stuID);
                qry2.exec();

            if(qry2.numRowsAffected() > 0){
                QMessageBox::warning(this, "هشدار" , "این درس قبلا برای این دانشجو انتخاب شده است.");
            }else{
                qry3.prepare("Insert Into Student.dbo.tblEntekhabVahed \
                              (ID_Erae, ID_Student) \
                              Values(:iderae, :idstu) ");

                             qry3.bindValue(":iderae", eraeID);
                             qry3.bindValue(":idstu", stuID);

                    if(qry3.exec()){
                            QMessageBox::information(this, "OK", "درس با موفقیت انتخاب شد.");
                            ui->label_entekhabID->clear();
                            ui->label_lessonName->clear();
                            ui->label_teacher->clear();
                            ui->label_rouz->clear();
                            ui->label_time->clear();
                    }else{
                        QMessageBox::warning(this, "Warning", "انتخاب درس با شکست مواجه شد.");
                    }
            }
    }
}
