#include "showclassmembers.h"
#include "ui_showclassmembers.h"

ShowClassMembers::ShowClassMembers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowClassMembers)
{
    ui->setupUi(this);
//--------------------------------------------------
    QSqlQuery qry;
    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
            qry.bindValue(":lesscode",SendJozveDialog::lessCode);
    qry.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry);
    ui->tableView->setModel(model);

//--------------------------------------------------

}

ShowClassMembers::~ShowClassMembers()
{
    delete ui;
}
