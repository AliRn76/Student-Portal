#include "removeeraedars2dialog.h"
#include "ui_removeeraedars2dialog.h"

QString RemoveEraeDars2Dialog::teachID;

RemoveEraeDars2Dialog::RemoveEraeDars2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveEraeDars2Dialog)
{
    ui->setupUi(this);

    QSqlQuery qry("Select ID From Student.dbo.tblTeacher Where TeacherCode = " + teacherCode);
        if(qry.next()){
            teachID = qry.value(0).toString();
        }

    QString strQry = "Select tblErae.ID as 'مشخصه درس', Title as 'نام درس', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                      From Student.dbo.tblTeacher, Student.dbo.tblLesson, Student.dbo.tblErae \
                      Where tblLesson.ID = tblErae.ID_Lesson AND tblErae.ID_Teacher = tblTeacher.ID AND tblTeacher.ID = " + teachID;

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery(strQry);

    ui->label_name->setText(name);
    ui->label_teacherCode->setText(teacherCode);
    ui->treeView->setModel(qryModel);

}

RemoveEraeDars2Dialog::~RemoveEraeDars2Dialog()
{
    delete ui;
}

void RemoveEraeDars2Dialog::on_pushButton_choose_clicked()
{
    QSqlQuery qry;
    int row;

    row = ui->treeView->currentIndex().row();

    qry.exec("Select tblErae.ID, Title, DaysOfWeek, TimeOfClass, LessonCode \
             From Student.dbo.tblTeacher, Student.dbo.tblLesson, Student.dbo.tblErae \
             Where tblLesson.ID = tblErae.ID_Lesson AND tblErae.ID_Teacher = tblTeacher.ID AND tblTeacher.ID = " + teachID );

    qry.seek(row);

    ui->label_entakhabID->setText(qry.value(0).toString());
    ui->label_lessonName->setText(qry.value(1).toString());
    ui->label_rouz->setText(qry.value(2).toString());
    ui->label_time->setText(qry.value(3).toString());
    ui->label_lessonCode->setText(qry.value(4).toString());
}

void RemoveEraeDars2Dialog::on_pushButton_remove_clicked()
{
    QString teacherID = teachID;
    QString lessID = ui->label_lessonCode->text();
    QString day = ui->label_rouz->text();
    QString time = ui->label_time->text();

    QSqlQuery qry("Delete From tblErae \
                   Where tblErae.ID_Teacher like " + teacherID + " AND \
                         tblErae.ID_Lesson like " + lessID + " AND \
                         tblErae.DaysOfWeek like N'" + day + "' AND \
                         tblErae.TimeOfClass like '" + time + "'");

        if(qry.exec()){
            QMessageBox::information(this, "OK", "درس مورد نظر از دروس ارائه شده حذف شد.");

            QString strQry = "Select tblErae.ID as 'مشخصه درس', Title as 'نام درس', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                              From tblTeacher, tblLesson, tblErae \
                              Where tblLesson.ID = tblErae.ID_Lesson AND tblErae.ID_Teacher = tblTeacher.ID AND tblTeacher.ID = " + teachID;

            qryModel = new QSqlQueryModel(this);

            qryModel->setQuery(strQry);
            ui->treeView->setModel(qryModel);
            ui->label_entakhabID->clear();
            ui->label_lessonName->clear();
            ui->label_rouz->clear();
            ui->label_time->clear();
        }else{
          QMessageBox::warning(this, "خطا", "نمیدونم چرا ولی شما قادر به حذف این درس ارائه شده نمیباشید.");
        }
}
