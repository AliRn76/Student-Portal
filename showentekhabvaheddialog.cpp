#include "showentekhabvaheddialog.h"
#include "ui_showentekhabvaheddialog.h"

ShowEntekhabVahedDialog::ShowEntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowEntekhabVahedDialog)
{
    ui->setupUi(this);

    qryModel = new QSqlQueryModel(this);

    QString strQry;

    strQry = "Select StudentCode as 'شماره دانشجویی', FirstName + ' ' + LastName as 'نام', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', Score as 'نمره' \
              From Student.dbo.tblPerson, Student.dbo.tblStudent, Student.dbo.tblEntekhabVahed, Student.dbo.tblLesson, Student.dbo.tblErae \
              Where tblPerson.ID = tblStudent.ID \
              AND tblEntekhabVahed.ID_Erae = tblErae.ID \
              AND tblEntekhabVahed.ID_Student = tblStudent.ID \
              AND tblErae.ID_Lesson = tblLesson.ID ";

    qryModel->setQuery(strQry);

    ui->treeView->setModel(qryModel);
}

ShowEntekhabVahedDialog::~ShowEntekhabVahedDialog()
{
    delete ui;
}
