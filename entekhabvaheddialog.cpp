#include "entekhabvaheddialog.h"
#include "ui_entekhabvaheddialog.h"

EntekhabVahedDialog::EntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntekhabVahedDialog)
{
    ui->setupUi(this);
}

EntekhabVahedDialog::~EntekhabVahedDialog()
{
    delete ui;
}
/*
void EntekhabVahedDialog::on_pushButton_findStu_clicked()
{
    QString arrStr[4];
    QString strStuCode = ui->lineEdit_stuCode->text();

    QSqlQuery qry("Select FirstName, LastName, StudentCode, Field \
                   From Student.dbo.tblStudent, Student.dbo.tblPerson \
                   Where tblStudent.ID = tblPerson.ID AND ( \
                   tblStudent.StudentCode like '" + strStuCode + "%' OR \
                   tblPerson.FirstName like N'" + strStuCode + "%' OR \
                   tblPerson.LastName like N'" + strStuCode + "%' OR \
                   tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + strStuCode + "%')");

    if(qry.numRowsAffected() != 0){
        if(qry.numRowsAffected() == 1){
            while(qry.next()){
                for(int i=0 ; i<4 ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }
            ui->label_stuName->setText(arrStr[0] + " " + arrStr[1]);
            ui->label_stuCode->setText(arrStr[2]);
            ui->label_fieldStu->setText(arrStr[3]);
        }else{
            QMessageBox::warning(this, "warning", "بیشتر از یک مورد وجود دارد.");
        }
    }else{
        if(ui->lineEdit_stuCode->text().isEmpty()){
            QMessageBox::warning(this, "warning", "ابتدا یک شماره دانشجویی وارد کنید.");

        }else{
            QMessageBox::warning(this, "warning", "لطفا یک شماره دانشجویی صحیح وارد کنید.");
        }
    }
}


void EntekhabVahedDialog::on_pushButton_apply_clicked()
{

    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString stuCode;
    QString eraeID;
    int stuID;

    eraeID = ui->label_entekhabID->text();
    stuCode = ui->label_stuCode->text();

    if(ui->label_stuCode->text().isEmpty() || ui->label_entekhabID->text().isEmpty()){

        if(ui->label_stuCode->text().isEmpty()){

            QMessageBox::warning(this, "Warning", "ابتدا یک دانشجو را جستجو کنید.");
        }else{
            QMessageBox::warning(this, "Warning", "ابتدا یک مشخصه درس را جستجو کنید.");
        }
    }else{    
        qry1.prepare("Select ID From Student.dbo.tblStudent \
                      Where tblStudent.StudentCode = :stucode");

                qry1.bindValue(":stucode", stuCode);
                qry1.exec();

                while(qry1.next()){
                    stuID = qry1.value(0).toInt();
                }

        qry3.prepare("Select ID From Student.dbo.tblEntekhabVahed \
                      Where ID_Erae = :iderae AND ID_Student = :idstudent");
                qry3.bindValue(":iderae", eraeID);
                qry3.bindValue(":idstudent", stuID);
                qry3.exec();

            if(qry3.numRowsAffected() > 0 ){
                QMessageBox::warning(this, "هشدار" , "این درس قبلا برای این دانشجو انتخاب شده است.");

            }else{
                qry2.prepare("Insert Into Student.dbo.tblEntekhabVahed \
                              (ID_Erae, ID_Student) \
                              Values(:iderae, :idstu) ");

                             qry2.bindValue(":iderae", eraeID);
                             qry2.bindValue(":idstu", stuID);

                    if(qry2.exec()){
                            QMessageBox::information(this, "OK", "درس با موفقیت انتخاب شد.");
                            ui->label_stuCode->clear();
                            ui->label_stuName->clear();
                            ui->label_entekhabID->clear();
                            ui->label_lessonName->clear();
                            ui->label_roozeHafte->clear();
                            ui->label_time->clear();
                            ui->label_fieldStu->clear();
                            ui->label_fieldLess->clear();
                    }else{
                        QMessageBox::warning(this, "Warning", "انتخاب درس با شکست مواجه شد.");
                    }
            }
    }

}
*/


void EntekhabVahedDialog::on_pushButton_showErae_2_clicked()
{
    showEraeDialog = new ShowEraeListDialog(this);
    showEraeDialog->show();
}

void EntekhabVahedDialog::on_pushButton_showStu_2_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}

void EntekhabVahedDialog::on_pushButton_findLesson_2_clicked()
{
    fieldLesson = ui->comboBox_field->currentText();
    entekhabID = ui->lineEdit_entekhabID_2->text();

    if(entekhabID.isEmpty()){
        QMessageBox::warning(this, "warning", "ابتدا یک مشخصه وارد کنید.");

    }else{
        qryModelLesson = new QSqlQueryModel(this);
        qryModelLesson->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت', Field as 'رشته'\
                                 From Student.dbo.tblLesson, Student.dbo.tblErae, Student.dbo.tblTeacher \
                                 Where tblErae.ID_Lesson = tblLesson.ID \
                                 AND tblLesson.Field = N'" + fieldLesson + "' \
                                 AND ( tblErae.ID like '" + entekhabID + "' OR tblLesson.Title like N'" + entekhabID + "%')");

        ui->tableView_lesson->setModel(qryModelLesson);
        ui->tableView_lesson->resizeRowToContents(1);
        ui->tableView_lesson->setColumnWidth(0,75);
        ui->tableView_lesson->setColumnWidth(1,180);
        ui->tableView_lesson->setColumnWidth(2,90);
        ui->tableView_lesson->setColumnWidth(4,260);
        ui->tableView_lesson->setWordWrap(false);

   /*
            qry1.prepare("Select tblErae.ID, Title, DaysOfWeek, TimeOfClass, Field \
                         From Student.dbo.tblLesson, Student.dbo.tblErae \
                         Where tblErae.ID_Lesson = tblLesson.ID \
                         AND tblLesson.Field = :fieldless \
                         AND tblErae.ID = :entekhabID");
                    qry1.bindValue(":fieldless", fieldLess);
                    qry1.bindValue(":entekhabID", entekhabId);
                    qry1.exec();

            if(qry1.numRowsAffected() != 0){
                while(qry1.next()){
                        entekhabID = qry1.value(0).toString();
                        lessonName = qry1.value(1).toString();
                        roozeHafte = qry1.value(2).toString();
                        time = qry1.value(3).toString();
                        field = qry1.value(4).toString();
                }
            }else{
                QMessageBox::warning(this, "خطا", "لطفا یک مشخصه صحیح وارد کنید.");
                qDebug()<<qry1.lastError().text();
            }
            */

    }
}

void EntekhabVahedDialog::on_pushButton_findStu_2_clicked()
{
    stuCode = ui->lineEdit_stuCode_2->text();

    if(stuCode.isEmpty()){
        QMessageBox::warning(this, "warning", "ابتدا نام یا شماره دانشجویی وارد کنید.");
    }else{
        qryModeStu = new QSqlQueryModel(this);
        qryModeStu->setQuery("Select StudentCode as 'شماره دانشجویی', FirstName + ' ' + LastName as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود' , Field as 'رشته' \
                             From Student.dbo.tblStudent, Student.dbo.tblPerson \
                             Where tblStudent.ID = tblPerson.ID AND ( \
                             tblStudent.StudentCode like '" + stuCode + "%' OR \
                             tblPerson.FirstName like N'" + stuCode + "%' OR \
                             tblPerson.LastName like N'" + stuCode + "%' OR \
                             tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + stuCode + "%')");
    }
    ui->tableView_stu->setModel(qryModeStu);
    ui->tableView_stu->setWordWrap(false);
    ui->tableView_stu->setColumnWidth(0,115);
    ui->tableView_stu->setColumnWidth(1,180);
    ui->tableView_stu->setColumnWidth(2,80);
    ui->tableView_stu->setColumnWidth(3,70);
    ui->tableView_stu->setColumnWidth(4,260);

/*
    if(qry.numRowsAffected() != 0){
        if(qry.numRowsAffected() == 1){
            while(qry.next()){
                for(int i=0 ; i<4 ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }
            ui->label_stuName->setText(arrStr[0] + " " + arrStr[1]);
            ui->label_stuCode->setText(arrStr[2]);
            ui->label_fieldStu->setText(arrStr[3]);
        }else{
            QMessageBox::warning(this, "warning", "بیشتر از یک مورد وجود دارد.");
        }
    }else{
        if(ui->lineEdit_stuCode->text().isEmpty()){
            QMessageBox::warning(this, "warning", "ابتدا یک شماره دانشجویی وارد کنید.");

        }else{
            QMessageBox::warning(this, "warning", "لطفا یک شماره دانشجویی صحیح وارد کنید.");
        }
    }
    */
}

void EntekhabVahedDialog::on_pushButton_continue_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlQuery qry1;

    ui->label_field->setText(fieldLesson);
    ui->label_stuCode->setText(stuCode);
    ui->label_name->setText(stuName);
    ui->label_fathersName->setText(fathersName);
    ui->label_saalVoroud->setText(saalVoroud);
    ui->label_entekhabID->setText(entekhabID);
    ui->label_title->setText(lessonName);
    ui->label_teacherName->setText(teacherName);
    ui->label_roozeHafte->setText(roozeHafte);
    ui->label_saat->setText(saat);
    ui->label_classNum->setText("Hanuz Tanzim Nashode");

}

void EntekhabVahedDialog::on_pushButton_backPage2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void EntekhabVahedDialog::on_tableView_lesson_clicked(const QModelIndex &index)
{
    QSqlQuery qry1;
    QSqlQuery qry2;

    qry1.exec("Select Distinct tblErae.ID, Title, DaysOfWeek, TimeOfClass, Field\
              From Student.dbo.tblLesson, Student.dbo.tblErae, Student.dbo.tblTeacher \
              Where tblErae.ID_Lesson = tblLesson.ID \
              AND tblLesson.Field = N'" + fieldLesson + "' \
              AND ( tblErae.ID like '" + entekhabID + "' OR tblLesson.Title like N'" + entekhabID + "%')");

    qry1.seek(index.row());

    entekhabID = qry1.value(0).toString();
    lessonName = qry1.value(1).toString();
    roozeHafte = qry1.value(2).toString();
    saat = qry1.value(3).toString();
    fieldLesson = qry1.value(4).toString();

    qry2.exec("Select FirstName + ' ' + LastName \
               From Student.dbo.tblPerson, Student.dbo.tblTeacher, Student.dbo.tblErae \
               Where tblErae.ID_Teacher = tblTeacher.ID AND \
                     tblTeacher.ID = tblPerson.ID AND \
                     tblErae.ID = " + entekhabID);

    teacherName = qry2.value(0).toString();
}








