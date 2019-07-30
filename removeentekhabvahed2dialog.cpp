#include "removeentekhabvahed2dialog.h"
#include "ui_removeentekhabvahed2dialog.h"

QString RemoveEntekhabVahed2Dialog::stuID;

RemoveEntekhabVahed2Dialog::RemoveEntekhabVahed2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveEntekhabVahed2Dialog)
{
    ui->setupUi(this);

    QSqlQuery qry("Select ID From Student.dbo.tblStudent Where StudentCode = " + studentCode);
        if(qry.next()){
            stuID = qry.value(0).toString();
        }

    QString strQry = "Select tblErae.ID as 'مشخصه درس', Title as 'نام درس', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                      From tblPerson, tblTeacher, tblLesson, tblErae, tblEntekhabVahed \
                      Where tblPerson.ID = tblTeacher.ID AND \
                            tblLesson.ID = tblErae.ID_Lesson AND \
                            tblErae.ID_Teacher = tblTeacher.ID AND \
                            tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                            tblEntekhabVahed.ID_Student = " + stuID;

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery(strQry);

    ui->label_name->setText(name);
    ui->label_studentCode->setText(studentCode);
    ui->treeView->setModel(qryModel);

}

RemoveEntekhabVahed2Dialog::~RemoveEntekhabVahed2Dialog()
{
    delete ui;
}

void RemoveEntekhabVahed2Dialog::on_pushButton_choose_clicked()
{
    QSqlQuery qry;
    int row;

    row = ui->treeView->currentIndex().row();

    qry.exec("Select tblErae.ID, Title, DaysOfWeek, TimeOfClass \
              From tblTeacher, tblLesson, tblErae, tblEntekhabVahed \
              Where tblLesson.ID = tblErae.ID_Lesson AND \
                    tblErae.ID_Teacher = tblTeacher.ID AND \
                    tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                    tblEntekhabVahed.ID_Student = " + stuID );

    qry.seek(row);

    ui->label_entakhabID->setText(qry.value(0).toString());
    ui->label_lessonName->setText(qry.value(1).toString());
    ui->label_rouz->setText(qry.value(2).toString());
    ui->label_time->setText(qry.value(3).toString());
}

void RemoveEntekhabVahed2Dialog::on_pushButton_remove_clicked()
{
    QSqlQuery qry;

    qry.prepare("Delete From tblEntekhabVahed \
                 Where ID_Erae = :iderae AND \
                       ID_Student = :idstu");
            qry.bindValue(":iderae", ui->label_entakhabID->text());
            qry.bindValue(":idstu", stuID);

        if(qry.exec()){
            QMessageBox::information(this, "OK", "درس مورد نظر از دروس انتخاب شده حذف شد.");

            QString strQry = "Select tblErae.ID as 'مشخصه درس', Title as 'نام درس', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                              From tblPerson, tblTeacher, tblLesson, tblErae, tblEntekhabVahed \
                              Where tblPerson.ID = tblTeacher.ID AND \
                                    tblLesson.ID = tblErae.ID_Lesson AND \
                                    tblErae.ID_Teacher = tblTeacher.ID AND \
                                    tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                                    tblEntekhabVahed.ID_Student = " + stuID;

            qryModel = new QSqlQueryModel(this);

            qryModel->setQuery(strQry);
            ui->treeView->setModel(qryModel);
            ui->label_entakhabID->clear();
            ui->label_lessonName->clear();
            ui->label_rouz->clear();
            ui->label_time->clear();
        }
}

