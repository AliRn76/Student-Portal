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
                      where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by l.Title");
                qry1.bindValue(":teacode" , username);
                qry1.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry1);
        ui->tableView_Lesson->setModel(model);


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
//        SendJozveDialog::lessCode = ui->lineEdit_lesscode->text();
        sendJozve = new SendJozveDialog(this);
        sendJozve->show();
}

void TeacherMainDialog::on_pushButton_exit_clicked()
{
    this->close();
}



void TeacherMainDialog::on_pushButton_refresh_clicked()
{
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by l.Title");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_Lesson->setModel(model);
    //---------------------------------------------------

//    QSqlQuery qry;
//    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
//                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
//                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
//            qry.bindValue(":lesscode",SendJozveDialog::lessCode);
//    qry.exec();
//    this->model = new QSqlQueryModel();
//    model->setQuery(qry);
//    ui->tableView_Student->setModel(model);

}

void TeacherMainDialog::on_tableView_Lesson_clicked(const QModelIndex &index)
{
    NumberOfRow_Lesson = index.row();
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by l.Title");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_Lesson->setModel(model);


    qry1.seek(NumberOfRow_Lesson);
    SendJozveDialog::lessCode = qry1.value(2).toString();
    ShowClassMembers::LessonName =qry1.value(0).toString();
    ShowClassMembers::LessonCode = qry1.value(2).toString();
    LessonCode = qry1.value(1).toString();
    ui->label_name_2->setText(ShowClassMembers::LessonName);
    ui->label_ID->setText(ShowClassMembers::LessonCode);
    ui->label_code->setText(LessonCode);

//--------------------------------------------------------

//    QSqlQuery qry;
//    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
//                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
//                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
//            qry.bindValue(":lesscode",SendJozveDialog::lessCode);
//    qry.exec();
//    this->model = new QSqlQueryModel();
//    model->setQuery(qry);
//    ui->tableView_Student->setModel(model);
}

//void TeacherMainDialog::on_tableView_Student_clicked(const QModelIndex &index)
//{
//    NumberOfRow_Student = index.row();
//    QSqlQuery qry;
//    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
//                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
//                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
//            qry.bindValue(":lesscode",SendJozveDialog::lessCode);
//    qry.exec();
//    this->model = new QSqlQueryModel();
//    model->setQuery(qry);
//    ui->tableView_Student->setModel(model);
//    qry.seek(NumberOfRow_Student);
//    StuCode = qry.value(1).toString();
//}

void TeacherMainDialog::on_pushButton_SetScore_clicked()
{
    showClass = new ShowClassMembers(this);
    showClass->show();
}

//void TeacherMainDialog::on_pushButton_SetScores_clicked()
//{
//    if(ui->lineEdit_Score->text().isEmpty()){
//        QMessageBox::information(this , "Error","دانشجوی موردنظر را انتخاب کرده و نمره را وارد کنید");
//    }
//    else {

//        QString score = ui->lineEdit_Score->text();
//        QSqlQuery qry;
//        QSqlQuery qry1;

//        QString ID_Stu;

//        qry1.prepare("SELECT ID from Student.dbo.tblStudent where StudentCode = :stucode");
//        qry1.bindValue(":stucode", StuCode);
//        qry1.exec();
//        if(qry1.next()){
//            ID_Stu = qry1.value(0).toString();
//        }

//        qry.prepare("UPDATE Student.dbo.tblEntekhabVahed set Score = :score where ID_Erae = :lesscode and ID_Student = :id_stu");
//        qry.bindValue(":score", score);
//        qry.bindValue(":id_stu" , ID_Stu);
//        qry.bindValue(":lesscode" , SendJozveDialog::lessCode);
//        if(qry.exec()){
//            QMessageBox::information(this , "Done" , "نمره به روز رسانی شد");
//            qDebug() << ID_Stu ;
//            qDebug() << SendJozveDialog::lessCode ;
//            qDebug() << score ;
//        }
//        else {
//            QMessageBox::information(this , "ERROR", "به روزرسانی نمره با مشکل روبرو شد !!!");
//        }

//    }
//}
void TeacherMainDialog::on_radioButton_Day_clicked()
{
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.DaysOfWeek");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_Lesson->setModel(model);
}

void TeacherMainDialog::on_radioButton_Title_clicked()
{
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by l.Title");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_Lesson->setModel(model);
}

void TeacherMainDialog::on_radioButton_Day_2_clicked()
{
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.ID");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_Lesson->setModel(model);
}
