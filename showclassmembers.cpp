#include "showclassmembers.h"
#include "ui_showclassmembers.h"

ShowClassMembers::ShowClassMembers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowClassMembers)
{
    ui->setupUi(this);
    ui->label_lessonCode->setText(LessonCode) ;
    ui->label_lessonName ->setText(LessonName);
    QSqlQuery qry;
    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
            qry.bindValue(":lesscode",LessonCode);
    qry.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry);
    ui->tableView_Student->setModel(model);
    //----------------------------------------------------------------------------------------------
    QSqlQuery qry1;
    qry1.prepare("Select COUNT(Distinct p.FirstName ) \
                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
            qry1.bindValue(":lesscode",LessonCode);
    qry1.exec();
    while(qry1.next()){
        StuNumber=qry1.value(0).toInt();
    }
    //---------------------------------------------------------------------------------------------
//    int j = 60 ;
//    for (int i = 0 ; i<StuNumber ; i++) {
//        QPushButton *btn = new QPushButton(this);
//        btn->setGeometry(j,540,100,33);
//        btn->setText("hi");
//        j = j+200;
//     }

}

ShowClassMembers::~ShowClassMembers()
{
    delete ui;
}

void ShowClassMembers::on_tableView_Student_clicked(const QModelIndex &index)
{
    NumberOfRow_Student = index.row();
    QSqlQuery qry;
    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
            qry.bindValue(":lesscode",LessonCode);
    qry.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry);
    ui->tableView_Student->setModel(model);
    qry.seek(NumberOfRow_Student);
    StuCode = qry.value(1).toString();
    FullName = qry.value(0).toString();
    ui->label_fullName->setText(FullName);
    ui->label_stuCode->setText(StuCode);
    //-------------------------------------------------------------------


}

void ShowClassMembers::on_pushButton_exit_clicked()
{
    this->close();
}
