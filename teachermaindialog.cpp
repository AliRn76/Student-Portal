#include "teachermaindialog.h"
#include "ui_teachermaindialog.h"

TeacherMainDialog::TeacherMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherMainDialog)
{
    ui->setupUi(this);
//----------------------------------------------------------------
    QString username = TeacherChangePassword::strUserTeacher;
    ui->label_TeacherCode->setText(username);

    QString fullname ;
    QSqlQuery qry;
    qry.prepare("Select FirstName + ' ' +LastName from Student.dbo.tblPerson p , Student.dbo.tblTeacher t where p.ID=t.ID and t.TeacherCode = :teacode");
    qry.bindValue(":teacode" , username);
    qry.exec();
    while(qry.next()){
        fullname = qry.value(0).toString();
    }
    ui->label_name->setText(fullname);
//----------------------------------------------------------------

    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID ");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView->setModel(model);

//----------------------------------------------------------------

}

TeacherMainDialog::~TeacherMainDialog()
{
    delete ui;
}

void TeacherMainDialog::on_pushButton_setting_clicked()
{
    teacherChangePassword = new TeacherChangePassword(this);
    teacherChangePassword->show();
}

void TeacherMainDialog::on_pushButton_3_clicked()
{
    SendJozveDialog::lessCode = ui->lineEdit_lesscode->text();
    sendJozve = new SendJozveDialog(this);
    sendJozve->show();
}

void TeacherMainDialog::on_pushButton_exit_clicked()
{
    this->close();
}
