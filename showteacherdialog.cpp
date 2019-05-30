#include "showteacherdialog.h"
#include "ui_showteacherdialog.h"

ShowTeacherDialog::ShowTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTeacherDialog)
{
    ui->setupUi(this);

    qry = new QSqlQueryModel(this);

    qry->setQuery("Select TeacherCode as 'کد کارمندی', FirstName + ' ' + LastName as 'نام و نام خانوادگی', EducationDegree as 'مدرک تحصیلی', NationalCode as 'کد ملی', Age as 'سن', Password as 'رمز عبور' \
                   From Student.dbo.tblPerson , Student.dbo.tblTeacher \
                   Where tblPerson.ID = tblTeacher.ID");
    ui->treeView->setModel(qry);
}

ShowTeacherDialog::~ShowTeacherDialog()
{
    delete ui;
}
