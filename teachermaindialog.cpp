#include "teachermaindialog.h"
#include "ui_teachermaindialog.h"

TeacherMainDialog::TeacherMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherMainDialog)
{
    ui->setupUi(this);

// -----------------------------------------------
    QString username = TeacherChangePassword::strUserTeach;
    this->model=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه درس' , e.DaysOfWeek as 'روزهای برگزاری' , e.TimeOfClass as 'ساعت کلاس' , e.jozve as 'جزوه' \
                from Student.dbo.tblTeacher t , Student.dbo.tblLesson l , Student.dbo.tblErae e \
                where t.TeacherCode = :user and e.ID_Teacher = t.ID and e.ID_Lesson = l.ID ");

            qry.bindValue(":user" , username);
            qry.exec();
    model->setQuery(qry);
    ui->tableView->setModel(model);
// -------------------------------------------------

    ui->label_teacherCode->setText(username);
    QString fullname ;
    QSqlQuery qry1 ;
    qry1.prepare("Select FirstName + ' ' + LastName from Student.dbo.tblTeacher t , Student.dbo.tblPerson p  where t.ID = p.ID and t.TeacherCode = :user");
    qry1.bindValue(":user" , username);
    qry1.exec();
    while (qry1.next()) {
        fullname = qry1.value(0).toString();
    }
    ui->label_name->setText(fullname);

//-------------------------------------------------

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

void TeacherMainDialog::on_pushButton_exit_clicked()
{
    this->close();
}

void TeacherMainDialog::on_pushButton_3_clicked()
{
    SendJozveDialog::lessCode = ui->lineEdit_lesscode->text();
    sendJozve = new SendJozveDialog(this);
    sendJozve->show();
}
