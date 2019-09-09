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
        qry.prepare("Select concat(FirstName , ' ' , LastName) as fullname from tblPerson , tblTeacher where tblPerson.ID=tblTeacher.ID and tblTeacher.TeacherCode = :teacode");
        qry.bindValue(":teacode" , username);
        qry.exec();
        while(qry.next()){
            fullname = qry.value(0).toString();
        }
        ui->label_name->setText(fullname);

        //----------------------------------------------------------------

        QSqlQuery qry1;
        qry1.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس'  \
                     From tblLesson , tblErae , tblTeacher \
                   Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblLesson.Title");
                qry1.bindValue(":teacode" , username);
                qry1.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry1);
        ui->tableView_2->setModel(model);

        //-----------------------------------------------------------------

        QSqlQuery qry2;
//        qry2.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' \
//                      from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
//                      where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.DaysOfWeek");
                qry2.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس',TimeOfClass as 'رمان کلاس' \
                             From tblLesson , tblErae , tblTeacher \
                           Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.DaysOfWeek");
                qry2.bindValue(":teacode" , username);
                qry2.exec();
        this->model = new QSqlQueryModel();
        model->setQuery(qry2);
        ui->tableView_3->setModel(model);

        //------------------------------------------------------------------

        QSqlQuery qry3;
        qry3.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                      From tblLesson , tblErae , tblTeacher \
                    Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.ID");
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


void teacherthirdmaindialog::on_tableView_clicked(const QModelIndex &index)
{
    NumberOfRow_Lesson = index.row();
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
//    qry1.prepare("Select l.Title as 'نام درس' , l.LessonCode as 'کد درس' , e.ID as 'مشخصه' , e.TimeOfClass as 'زمان کلاس' , e.DaysOfWeek as 'روز کلاس' , e.ClassNum as 'شماره کلاس' , e.jozve as 'جزوه'\
//                  from Student.dbo.tblLesson l , Student.dbo.tblErae e , Student.dbo.tblTeacher t \
//                  where t.TeacherCode = :teacode and l.ID = e.ID_Lesson and e.ID_Teacher = t.ID order by e.ID");
    qry1.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.ID");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    qry1.seek(NumberOfRow_Lesson);
    SendJozveDialog::lessCode = qry1.value(2).toString();
    ShowClassMembers::LessonName =qry1.value(0).toString();
    ShowClassMembers::LessonCode = qry1.value(2).toString();
    LessonCode = qry1.value(1).toString();
    ui->label_name_2->setText(ShowClassMembers::LessonName);
    ui->label_ID->setText(ShowClassMembers::LessonCode);
    ui->label_code->setText(LessonCode);
}

void teacherthirdmaindialog::on_tableView_2_clicked(const QModelIndex &index)
{
    NumberOfRow_Lesson = index.row();
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblLesson.Title");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    qry1.seek(NumberOfRow_Lesson);
    SendJozveDialog::lessCode = qry1.value(2).toString();
    ShowClassMembers::LessonName =qry1.value(0).toString();
    ShowClassMembers::LessonCode = qry1.value(2).toString();
    LessonCode = qry1.value(1).toString();
    ui->label_name_2->setText(ShowClassMembers::LessonName);
    ui->label_ID->setText(ShowClassMembers::LessonCode);
    ui->label_code->setText(LessonCode);
}

void teacherthirdmaindialog::on_tableView_3_clicked(const QModelIndex &index)
{
    NumberOfRow_Lesson = index.row();
    QString username = TeacherChangePassword::strUserTeacher;
    QSqlQuery qry1;
    qry1.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.DaysOfWeek ");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    qry1.seek(NumberOfRow_Lesson);
    SendJozveDialog::lessCode = qry1.value(2).toString();
    ShowClassMembers::LessonName =qry1.value(0).toString();
    ShowClassMembers::LessonCode = qry1.value(2).toString();
    LessonCode = qry1.value(1).toString();
    ui->label_name_2->setText(ShowClassMembers::LessonName);
    ui->label_ID->setText(ShowClassMembers::LessonCode);
    ui->label_code->setText(LessonCode);
}

void teacherthirdmaindialog::on_pushButton_3_clicked()
{
    sendJozve = new SendJozveDialog(this);
    sendJozve->show();
}

void teacherthirdmaindialog::on_pushButton_refresh_clicked()
{
    QString username = TeacherChangePassword::strUserTeacher;

    QSqlQuery qry1;
    qry1.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblLesson.Title");
            qry1.bindValue(":teacode" , username);
            qry1.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry1);
    ui->tableView_2->setModel(model);

    //-----------------------------------------------------------------

    QSqlQuery qry2;
    qry2.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس',TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.DaysOfWeek");
            qry2.bindValue(":teacode" , username);
            qry2.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry2);
    ui->tableView_3->setModel(model);

    //------------------------------------------------------------------

    QSqlQuery qry3;
    qry3.prepare("Select Title as 'نام درس', LessonCode as 'کد درس', tblErae.ID as 'مشخصه', DaysOfWeek as 'روز کلاس', ClassNum as 'شماره کلاس' , TimeOfClass as 'رمان کلاس' \
                 From tblLesson , tblErae , tblTeacher \
               Where tblTeacher.TeacherCode=:teacode AND tblLesson.ID=tblErae.ID_Lesson AND tblErae.ID_Teacher=tblTeacher.ID order by tblErae.ID");
            qry3.bindValue(":teacode" , username);
            qry3.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry3);
    ui->tableView->setModel(model);
}

void teacherthirdmaindialog::on_pushButton_SetScore_clicked()
{
    showClass = new ShowClassMembers(this);
    showClass->show();
}

void teacherthirdmaindialog::on_pushButton_req_dars_clicked()
{
    teacherRequest::whichpage = 0 ;
    teareq = new teacherRequest(this);
    teareq->show();
}

void teacherthirdmaindialog::on_pushButton_req_parking_clicked()
{
    teacherRequest::whichpage = 1 ;
    teareq = new teacherRequest(this);
    teareq->show();
}

void teacherthirdmaindialog::on_pushButton_req_vam_clicked()
{
    teacherRequest::whichpage = 2 ;
    teareq = new teacherRequest(this);
    teareq->show();
}
