#include "teacherthirdmaindialog.h"
#include "ui_teacherthirdmaindialog.h"

teacherthirdmaindialog::teacherthirdmaindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacherthirdmaindialog)
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
                      where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by l.Title");
                qry1.bindValue(":teacode" , username);
                qry1.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry1);
        ui->tableView_2->setModel(model);

        //-----------------------------------------------------------------

        QSqlQuery qry2;
        qry2.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                      from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                      where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.DaysOfWeek");
                qry2.bindValue(":teacode" , username);
                qry2.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry2);
        ui->tableView_3->setModel(model);

        //------------------------------------------------------------------

        QSqlQuery qry3;
        qry3.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                      from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                      where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.ID");
                qry3.bindValue(":teacode" , username);
                qry3.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry3);
        ui->tableView->setModel(model);
}

teacherthirdmaindialog::~teacherthirdmaindialog()
{
    delete ui;
}

void teacherthirdmaindialog::on_pushButton_setting_clicked()
{
    teacherChangePassword = new TeacherChangePassword(this);
    teacherChangePassword->show();
}

void teacherthirdmaindialog::on_pushButton_exit_clicked()
{
    this->close();
}
