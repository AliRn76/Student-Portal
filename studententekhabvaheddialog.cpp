#include "studententekhabvaheddialog.h"
#include "ui_studententekhabvaheddialog.h"

QString StudentEntekhabVahedDialog::stuID;

StudentEntekhabVahedDialog::StudentEntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentEntekhabVahedDialog)
{
    ui->setupUi(this);

    QSqlQuery qry;

    qry.prepare("Select StudentCode, FirstName, LastName, NumberOfTerm, tblStudent.ID \
                 From tblPerson, tblStudent, tblEntekhabVahed \
                 Where tblPerson.ID = tblStudent.ID AND \
                       tblStudent.ID = tblEntekhabVahed.ID_Student AND \
                       tblStudent.StudentCode = :stucode");
            qry.bindValue(":stucode", stuCode);
            qry.exec();

    while(qry.next()){
        ui->label_stuCode->setText(qry.value(0).toString());
        ui->label_name->setText(qry.value(1).toString() + " " + qry.value(2).toString());
        ui->label_nTerm->setText(qry.value(3).toString());
        stuID = qry.value(4).toString();
    }

    qryModel = new QSqlQueryModel(this);
    qryModel3 = new QSqlQueryModel(this);

    qryModel->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                       From tblPerson,  \
                            tblErae,    \
                            tblTeacher, \
                            tblLesson,  \
                            tblStudent  \
                       Where tblPerson.ID = tblTeacher.ID AND \
                             tblTeacher.ID = tblErae.ID_Teacher AND \
                             tblErae.ID_Lesson = tblLesson.ID AND \
                             tblLesson.Field = tblStudent.Field AND \
                             tblStudent.Field = N'" + stuFieldEntekhab + "'");

    ui->treeView->setModel(qryModel);

    qryModel3->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                         From tblPerson, tblErae, tblTeacher, tblLesson, tblStudent, tblEntekhabVahed \
                         Where tblPerson.ID = tblTeacher.ID AND \
                               tblTeacher.ID = tblErae.ID_Teacher AND \
                               tblErae.ID_Lesson = tblLesson.ID AND \
                               tblLesson.Field = tblStudent.Field AND \
                               tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                               tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                               tblStudent.ID = " + stuID);

    ui->treeView_acceptedLesson->setModel(qryModel3);

}

StudentEntekhabVahedDialog::~StudentEntekhabVahedDialog()
{
    delete ui;
}

void StudentEntekhabVahedDialog::on_treeView_clicked(const QModelIndex &index)
{
    QSqlQuery qry;

    qry.exec("Select Distinct tblErae.ID, Title , FirstName + ' ' + LastName, DaysOfWeek, TimeOfClass \
              From tblPerson, \
                   tblErae, \
                   tblTeacher, \
                   tblLesson, \
                   tblStudent \
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
        qry1.prepare("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                      From tblPerson,   \
                            tblErae,    \
                            tblTeacher, \
                            tblLesson,  \
                            tblStudent  \
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
        strQry = "Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                  From tblPerson,  \
                       tblErae,    \
                       tblTeacher, \
                       tblLesson,  \
                       tblStudent  \
                 Where tblPerson.ID = tblTeacher.ID AND \
                       tblTeacher.ID = tblErae.ID_Teacher AND \
                       tblErae.ID_Lesson = tblLesson.ID AND \
                       tblLesson.Field = tblStudent.Field AND \
                       tblStudent.Field = N'" + stuFieldEntekhab + "' AND \
                       (tblLesson.Title like N'" + ui->lineEdit->text() + "%' OR \
                       tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + ui->lineEdit->text() + "%' OR \
                       tblPerson.FirstName like N'" + ui->lineEdit->text() + "%' OR \
                       tblPerson.LastName like N'" + ui->lineEdit->text() + "%')";

        qryModel2->setQuery(strQry);
        qDebug() << qryModel2->lastError();

        ui->treeView->setModel(qryModel2);
    }
}


void StudentEntekhabVahedDialog::on_pushButton_apply_clicked()
{
//   QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QSqlQuery qry4;
    QString strQry;
    int eraeID = ui->label_entekhabID->text().toInt();

    if(ui->label_entekhabID->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "لطفا ابتدا یک درس را انتخاب کنید.");
    }else{

        qry2.prepare("Select tblEntekhabVahed.ID \
                      From tblEntekhabVahed, \
                           tblErae, \
                           tblLesson \
                      Where tblEntekhabVahed.ID_Student = :idstudent AND \
                            tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                            tblErae.ID_Lesson = tblLesson.ID AND \
                            ( tblEntekhabVahed.ID_Erae = :iderae OR tblLesson.Title = N'" + ui->label_lessonName->text()+ "')");
                qry2.bindValue(":iderae", eraeID);
                qry2.bindValue(":idstudent", stuID);
                qry2.exec();

            if(qry2.numRowsAffected() > 0){
                QMessageBox::warning(this, "هشدار" , "این درس را قبلا انتخاب کرده اید.");
            }else{
                qry3.prepare("Insert Into tblEntekhabVahed \
                              (ID_Erae, ID_Student) \
                              Values(:iderae, :idstu) ");

                             qry3.bindValue(":iderae", eraeID);
                             qry3.bindValue(":idstu", stuID);

                    if(qry3.exec()){
                            QMessageBox::information(this, "OK", "درس با موفقیت انتخاب شد.");

                            qryModel4 = new QSqlQueryModel(this);

                            qryModel4->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                                                 From tblPerson, tblErae, tblTeacher, tblLesson, tblStudent, tblEntekhabVahed \
                                                 Where tblPerson.ID = tblTeacher.ID AND \
                                                      tblTeacher.ID = tblErae.ID_Teacher AND \
                                                      tblErae.ID_Lesson = tblLesson.ID AND \
                                                      tblLesson.Field = tblStudent.Field AND \
                                                      tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                                                      tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                                                      tblStudent.ID = " +  stuID);

                            ui->treeView_acceptedLesson->setModel(qryModel4);

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

void StudentEntekhabVahedDialog::on_pushButton_remove_clicked()
{
    QSqlQuery qry;

    qry.prepare("Delete From tblEntekhabVahed \
                 Where ID_Erae = :iderae AND ID_Student = :idstu");
            qry.bindValue(":iderae", ui->label_entekhabID->text());
            qry.bindValue(":idstu", stuID);

        if(qry.exec()){
            if(qry.numRowsAffected() > 0){
                QMessageBox::information(this, "OK", "درس مورد نظر از دروس انتخاب شده حذف شد.");

                qryModel5 = new QSqlQueryModel(this);

                qryModel5->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                                     From tblPerson, tblErae, tblTeacher, tblLesson, tblStudent, tblEntekhabVahed \
                                     Where tblPerson.ID = tblTeacher.ID AND \
                                          tblTeacher.ID = tblErae.ID_Teacher AND \
                                          tblErae.ID_Lesson = tblLesson.ID AND \
                                          tblLesson.Field = tblStudent.Field AND \
                                          tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                                          tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                                          tblStudent.ID = " +  stuID);

                ui->treeView_acceptedLesson->setModel(qryModel5);

                ui->label_entekhabID->clear();
                ui->label_lessonName->clear();
                ui->label_teacher->clear();
                ui->label_rouz->clear();
                ui->label_time->clear();
            }else{
                QMessageBox::warning(this, "خطا", "لطفا ابتدا یک درس از 'دروس انتخاب شده' انتخاب کنید.");
            }
        }else{
            QMessageBox::warning(this, "خطا", "امکان حذف درس نمیباشد.");
        }
}

void StudentEntekhabVahedDialog::on_treeView_acceptedLesson_clicked(const QModelIndex &index)
{
    QSqlQuery qry;

    qry.exec("Select Distinct tblErae.ID, Title , FirstName + ' ' + LastName, DaysOfWeek, TimeOfClass \
              From tblPerson, tblErae, tblTeacher, tblLesson, tblStudent, tblEntekhabVahed \
              Where tblPerson.ID = tblTeacher.ID AND \
                    tblTeacher.ID = tblErae.ID_Teacher AND \
                    tblErae.ID_Lesson = tblLesson.ID AND \
                    tblLesson.Field = tblStudent.Field AND \
                    tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                    tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                    tblStudent.ID = " + stuID);

    qry.seek(index.row());

    ui->label_entekhabID->setText(qry.value(0).toString());
    ui->label_lessonName->setText(qry.value(1).toString());
    ui->label_teacher->setText(qry.value(2).toString());
    ui->label_rouz->setText(qry.value(3).toString());
    ui->label_time->setText(qry.value(4).toString());
}
