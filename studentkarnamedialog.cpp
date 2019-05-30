#include "studentkarnamedialog.h"
#include "ui_studentkarnamedialog.h"

StudentKarnameDialog::StudentKarnameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentKarnameDialog)
{
    ui->setupUi(this);

    qryModel = new QSqlQueryModel(this);
    qryModel->setQuery("Select Title as 'نام درس', Type as 'نوع درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', NumberOfTerm as 'ترم', Score as 'نمره' \
                       From Student.dbo.tblPerson, \
                            Student.dbo.tblTeacher, \
                            Student.dbo.tblLesson, \
                            Student.dbo.tblErae, \
                            Student.dbo.tblEntekhabVahed, \
                            Student.dbo.tblStudent \
                       Where tblPerson.ID = tblTeacher.ID \
                        AND tblTeacher.ID = tblErae.ID_Teacher \
                        AND tblErae.ID_Lesson = tblLesson.ID \
                        AND tblStudent.ID = tblEntekhabVahed.ID_Student \
                        AND tblEntekhabVahed.ID_Erae = tblErae.ID \
                        AND tblStudent.ID =" + stuIDKarname);
}

StudentKarnameDialog::~StudentKarnameDialog()
{
    delete ui;
}
