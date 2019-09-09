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
    qry.prepare("Select Distinct FirstName as 'نام' , LastName as ' نام خانوادگی ', StudentCode as 'شماره دانشجویی', Field as 'رشته'  \
                From tblPerson , tblErae , tblTeacher , tblEntekhabVahed , tblStudent \
                where tblPerson.ID = tblStudent.ID AND tblErae.ID = :lesscode AND tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                tblEntekhabVahed.ID_Erae = tblErae.ID order by LastName");
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
//    qry.prepare("Select Distinct p.FirstName +' ' + p.LastName as 'نام و نام خانوادگی ' ,s.StudentCode as 'شماره دانشجویی' ,s.Field as 'رشته' \
//                 from Student.dbo.tblPerson p , Student.dbo.tblStudent s , Student.dbo.tblErae e , Student.dbo.tblEntekhabVahed en , Student.dbo.tblTeacher t \
//                 where p.ID = s.ID and e.ID = :lesscode and en.ID_Student = s.ID and en.ID_Erae = e.ID ");
    qry.prepare("Select Distinct FirstName as 'نام' , LastName as ' نام خانوادگی ', StudentCode as 'شماره دانشجویی', Field as 'رشته'  \
                From tblPerson , tblErae , tblTeacher , tblEntekhabVahed , tblStudent \
                where tblPerson.ID = tblStudent.ID AND tblErae.ID = :lesscode AND tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                tblEntekhabVahed.ID_Erae = tblErae.ID order by LastName");
            qry.bindValue(":lesscode",LessonCode);
    qry.exec();
    this->model = new QSqlQueryModel();
    model->setQuery(qry);
    ui->tableView_Student->setModel(model);
    qry.seek(NumberOfRow_Student);
    StuCode = qry.value(2).toString();
    firstname = qry.value(0).toString();
    lastname = qry.value(1).toString();
    ui->label_firstName->setText(firstname);
    ui->label_lastName->setText(lastname);
    ui->label_stuCode->setText(StuCode);
    //-------------------------------------------------------------------


}

void ShowClassMembers::on_pushButton_exit_clicked()
{
    this->close();
}


void ShowClassMembers::on_pushButton_SetScore_clicked()
{
    if(ui->lineEdit_score->text().isEmpty()){
        QMessageBox::information(this , "Error" , "لطفا فیلد نمره را پر کنید.");
    }
    else if (ui->lineEdit_score->text().toFloat()<0 || ui->lineEdit_score->text().toFloat()>20) {
        QMessageBox::information(this , "Error" , "لطفا نمره را در بازه 0 تا 20 وارد نمایید");
    }
    else {


        score = ui->lineEdit_score->text().toFloat();

        QSqlQuery qry1;
        qry1.prepare("select ID  \
                      from  tblStudent \
                      where StudentCode = :Scode");
                qry1.bindValue(":Scode" , StuCode );

        qry1.exec();
        int id = qry1.value(0).toInt();


        QSqlQuery qry;
        qry.prepare("Update tblEntekhabVahed SET Score = :sc where ID_Student = :id");
        qry.bindValue(":sc" , score);
        qry.bindValue(":id" , id);
        if(qry.exec()){
            QMessageBox::information(this , "Done" , ".نمره با موفقیت ثبت شد");
            ui->label_lastName->clear();
            ui->label_firstName->clear();
            ui->label_stuCode->clear();
            ui->lineEdit_score->setText("");
        }

    }
}
