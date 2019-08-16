#include "showstudenteraelistdialog.h"
#include "ui_showstudenteraelistdialog.h"

ShowStudentEraeListDialog::ShowStudentEraeListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowStudentEraeListDialog)
{
    ui->setupUi(this);

    qryModel = new QSqlQueryModel(this);

    qryModel->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                       From tblPerson, \
                            tblErae, \
                            tblTeacher, \
                            tblLesson, \
                            tblStudent \
                       Where tblPerson.ID = tblTeacher.ID AND \
                             tblTeacher.ID = tblErae.ID_Teacher AND \
                             tblErae.ID_Lesson = tblLesson.ID AND \
                             tblLesson.Field = tblStudent.Field AND \
                             tblStudent.Field = N'" + stuField + "'");

    ui->treeView->setModel(qryModel);
}

ShowStudentEraeListDialog::~ShowStudentEraeListDialog()
{
    delete ui;
}
