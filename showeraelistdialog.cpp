#include "showeraelistdialog.h"
#include "ui_showeraelistdialog.h"

ShowEraeListDialog::ShowEraeListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowEraeListDialog)
{
    ui->setupUi(this);

    qry = new QSqlQueryModel(this);

    qry->setQuery("Select tblErae.ID as 'مشخصه', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', FirstName + ' ' + LastName as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'زمان کلاس' \
                   From tblPerson, tblErae, tblTeacher, tblLesson \
                   Where (tblPerson.ID = tblTeacher.ID) AND \
                         (tblTeacher.ID = tblErae.ID_Teacher) AND \
                         (tblErae.ID_Lesson = tblLesson.ID)");


    ui->treeView->setModel(qry);
}

ShowEraeListDialog::~ShowEraeListDialog()
{
    delete ui;
}
