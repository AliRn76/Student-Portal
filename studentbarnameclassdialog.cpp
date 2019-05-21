#include "studentbarnameclassdialog.h"
#include "ui_studentbarnameclassdialog.h"

StudentBarnameClassDialog::StudentBarnameClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentBarnameClassDialog)
{
    ui->setupUi(this);

    QSqlQuery qry;
    QString stuID;

    qry.prepare("Select ID \
                 From Student.dbo.tblStudent \
                 Where tblStudent.StudentCode = :stucode");
            qry.bindValue(":stucode", stuCodeBarname);
            qry.exec();

    if(qry.next()){
        stuID = qry.value(0).toString();
    }

    qryModel = new QSqlQueryModel(this);

    qDebug() << stuID << stuCodeBarname;

    qryModel->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                       From Student.dbo.tblPerson, Student.dbo.tblErae, Student.dbo.tblTeacher, Student.dbo.tblLesson, Student.dbo.tblStudent, Student.dbo.tblEntekhabVahed \
                       Where tblPerson.ID = tblTeacher.ID AND \
                            tblTeacher.ID = tblErae.ID_Teacher AND \
                            tblErae.ID_Lesson = tblLesson.ID AND \
                            tblLesson.Field = tblStudent.Field AND \
                            tblEntekhabVahed.ID_Erae = tblErae.ID AND \
                            tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                            tblStudent.ID = " +  stuID);

    ui->treeView->setModel(qryModel);
}

StudentBarnameClassDialog::~StudentBarnameClassDialog()
{
    delete ui;
}
