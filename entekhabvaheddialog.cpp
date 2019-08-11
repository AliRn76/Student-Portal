#include "entekhabvaheddialog.h"
#include "ui_entekhabvaheddialog.h"

EntekhabVahedDialog::EntekhabVahedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntekhabVahedDialog)
{
    ui->setupUi(this);

    preQryModelLesson = new QSqlQueryModel(this);
    preQryModelStu = new QSqlQueryModel(this);
    preQryModelStuTab2 = new QSqlQueryModel(this);
    preQryModelLessonTab2 = new QSqlQueryModel(this);

    preQryModelLesson->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', Concat(FirstName, ' ', LastName) as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت', Field as 'رشته'\
                                From tblLesson, tblErae, tblTeacher, tblPerson \
                                Where tblErae.ID_Lesson = tblLesson.ID \
                                AND tblTeacher.ID = tblPerson.ID \
                                AND tblLesson.Field = N' '");

    preQryModelStu->setQuery("Select StudentCode as 'شماره دانشجویی', Concat(FirstName , ' ' , LastName) as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود' , Field as 'رشته' \
                     From tblStudent, tblPerson \
                     Where tblStudent.ID = tblPerson.ID AND \
                           tblStudent.StudentCode like ' '");

    ui->tableView_lesson->setModel(preQryModelLesson);
        ui->tableView_lesson->setColumnWidth(0,60);
        ui->tableView_lesson->setColumnWidth(1,160);
        ui->tableView_lesson->setColumnWidth(3,80);
        ui->tableView_lesson->setColumnWidth(4,80);
        ui->tableView_lesson->setColumnWidth(5,260);
        ui->tableView_lesson->setWordWrap(false);

    ui->tableView_stu->setModel(preQryModelStu);
        ui->tableView_stu->setColumnWidth(0,115);
        ui->tableView_stu->setColumnWidth(1,180);
        ui->tableView_stu->setColumnWidth(2,80);
        ui->tableView_stu->setColumnWidth(3,70);
        ui->tableView_stu->setColumnWidth(4,260);
        ui->tableView_stu->setWordWrap(false);

    /// Tab 2 ---------------->


    preQryModelStuTab2->setQuery("Select Distinct StudentCode as 'شماره دانشجویی', Concat(FirstName , ' ' , LastName) as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود', Field as 'رشته' \
                                  From tblPerson , tblStudent \
                                  Where tblPerson.ID = tblStudent.ID AND \
                                        tblStudent.Field like N' '");

    preQryModelLessonTab2->setQuery("Select tblErae.ID as 'مشخصه', Title as 'عنوان درس', Concat(FirstName, ' ', LastName) as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                                    From tblPerson,        \
                                         tblTeacher,       \
                                         tblStudent,       \
                                         tblEntekhabVahed, \
                                         tblErae,          \
                                         tblLesson         \
                                    Where tblPerson.ID = tblTeacher.ID AND                \
                                          tblTeacher.ID = tblErae.ID_Teacher AND          \
                                          tblErae.ID_Lesson = tblLesson.ID AND            \
                                          tblEntekhabVahed.ID_Erae = tblErae.ID AND       \
                                          tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                                          tblStudent.StudentCode = ' '");

    ui->tableView_stuTab2->setModel(preQryModelStuTab2);
        ui->tableView_stuTab2->setWordWrap(false);
        ui->tableView_stuTab2->setColumnWidth(0,115);
        ui->tableView_stuTab2->setColumnWidth(1,180);
        ui->tableView_stuTab2->setColumnWidth(2,80);
        ui->tableView_stuTab2->setColumnWidth(3,70);
        ui->tableView_stuTab2->setColumnWidth(4,260);

    ui->tableView_LessTab2->setModel(preQryModelLessonTab2);
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
    eraeID = ui->lineEdit_entekhabID_2->text();
    finallField = fieldLesson;

    if(fieldStudent.isEmpty() || fieldLesson == fieldStudent){
        qDebug() << fieldLesson ;
        qDebug() << eraeID ;

        if(eraeID.isEmpty()){
            QMessageBox::warning(this, "warning", "ابتدا یک مشخصه وارد کنید.");

        }else{
            qryModelLesson = new QSqlQueryModel(this);
            qryModelLesson->setQuery("Select Distinct tblErae.ID as 'مشخصه', Title as 'عنوان درس', Concat(FirstName, ' ', LastName) as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت', Field as 'رشته'\
                                     From tblLesson, tblErae, tblTeacher, tblPerson \
                                     Where tblErae.ID_Lesson = tblLesson.ID \
                                     AND tblTeacher.ID = tblPerson.ID \
                                     AND tblLesson.Field = N'" + fieldLesson + "' \
                                     AND ( tblErae.ID like '" + eraeID + "' OR tblLesson.Title like N'" + eraeID + "%')");

            ui->tableView_lesson->setModel(qryModelLesson);
            ui->tableView_lesson->setColumnWidth(0,60);
            ui->tableView_lesson->setColumnWidth(1,160);
            ui->tableView_lesson->setColumnWidth(3,80);
            ui->tableView_lesson->setColumnWidth(4,80);
            ui->tableView_lesson->setColumnWidth(5,260);
            ui->tableView_lesson->setWordWrap(false);


            qDebug() << "lastError qryModelLesson: " << qryModelLesson->lastError().text();
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
    }else{
        QMessageBox::warning(this, "خطا", "لطفا رشته را با رشته دانشجویی که انتخاب کرده اید یکی کنید.");
    }
}

void EntekhabVahedDialog::on_pushButton_findStu_2_clicked()
{
    stuCode = ui->lineEdit_stuCode_2->text();
    fieldStudent = ui->comboBox_field->currentText();

    qDebug() << fieldLesson;
    if(fieldLesson.isEmpty() || fieldLesson == fieldStudent){

        finallField = fieldStudent;
        qDebug () << stuCode;

        if(stuCode.isEmpty()){
            QMessageBox::warning(this, "warning", "ابتدا نام یا شماره دانشجویی وارد کنید.");
        }else{
            qryModelStu = new QSqlQueryModel(this);
            qryModelStu->setQuery("Select StudentCode as 'شماره دانشجویی', Concat(FirstName , ' ' , LastName) as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود' , Field as 'رشته' \
                                   From tblStudent, tblPerson \
                                   Where tblStudent.ID = tblPerson.ID AND \
                                         tblStudent.Field = N'" + fieldStudent + "' AND ( \
                                         tblStudent.StudentCode like '" + stuCode + "%' OR \
                                         tblPerson.FirstName like N'" + stuCode + "%' OR \
                                         tblPerson.LastName like N'" + stuCode + "%' OR \
                                         tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + stuCode + "%')");
        }
        ui->tableView_stu->setModel(qryModelStu);
        ui->tableView_stu->setWordWrap(false);
        ui->tableView_stu->setColumnWidth(0,115);
        ui->tableView_stu->setColumnWidth(1,180);
        ui->tableView_stu->setColumnWidth(2,80);
        ui->tableView_stu->setColumnWidth(3,70);
        ui->tableView_stu->setColumnWidth(4,260);

        qDebug() << qryModelStu->lastError().text();
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
    }else{
        QMessageBox::warning(this, "خطا", "لطفا رشته را با رشته درسی که انتخاب کرده اید یکی کنید.");
    }
}

void EntekhabVahedDialog::on_pushButton_continue_clicked()
{
    if(!ui->label_stuCode->text().isEmpty() && !ui->label_title->text().isEmpty()){
        qDebug() << "joftesh click shode";

        ui->stackedWidget->setCurrentIndex(1);

        ui->label_field->setText(finallField);
     //   ui->label_stuCode->setText(stuCode);
     //   ui->label_name->setText(stuName);
     //   ui->label_fathersName->setText(fathersName);
     //   ui->label_saalVoroud->setText(saalVoroud);
     //   ui->label_entekhabID->setText(entekhabID);
     //   ui->label_title->setText(lessonName);
     //   ui->label_teacherName->setText(teacherName);
     //   ui->label_roozeHafte->setText(roozeHafte);
     //   ui->label_saat->setText(saat);
        ui->label_classNum->setText("Hanuz Tanzim Nashode");

        qDebug() << teacherName;
        qDebug() << stuName;
        qDebug() << fathersName;
        qDebug() << saalVoroud;
    }else if(ui->label_title->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "لطفا ابتدا یک درس را از جدول انتخاب کنید.");
    }else if(ui->label_stuCode->text().isEmpty()){
        QMessageBox::warning(this, "خطا", "لطفا ابتدا یک دانشجو را از جدول انتخاب کنید.");
    }else{
        QMessageBox::warning(this, "خطا", "نمیدونم چرا ، ولی یه جای کار میلنگه.");
    }
}

void EntekhabVahedDialog::on_pushButton_backPage2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void EntekhabVahedDialog::on_tableView_lesson_clicked(const QModelIndex &index)
{
    QSqlQuery qry1;
    qDebug() << "index tableView_lesson_clicked: " << index ;

    qry1.exec("Select Distinct tblErae.ID, Title, Concat(FirstName, ' ', LastName), DaysOfWeek, TimeOfClass, Field\
               From tblLesson, tblErae, tblTeacher, tblPerson \
               Where tblErae.ID_Lesson = tblLesson.ID \
               AND tblTeacher.ID = tblPerson.ID \
               AND tblLesson.Field = N'" + fieldLesson + "' \
               AND ( tblErae.ID like '" + eraeID + "' OR tblLesson.Title like N'" + eraeID + "%')");

    qry1.seek(index.row());

    eraeID = qry1.value(0).toString();
    lessonName = qry1.value(1).toString();
    teacherName = qry1.value(2).toString();
    roozeHafte = qry1.value(3).toString();
    saat = qry1.value(4).toString();
    fieldLesson = qry1.value(5).toString();

    ui->label_entekhabID->setText(qry1.value(0).toString());
    ui->label_title->setText(qry1.value(1).toString());
    ui->label_teacherName->setText(qry1.value(2).toString());
    ui->label_roozeHafte->setText(qry1.value(3).toString());
    ui->label_saat->setText(qry1.value(4).toString());

    // Class Num inja bayad biad .......................................................................................
}

void EntekhabVahedDialog::on_tableView_stu_clicked(const QModelIndex &index)
{
    QSqlQuery qry;
    qDebug() << "index tableView_stu_clicked: " << index ;

    qry.exec("Select StudentCode, Concat(FirstName , ' ' , LastName), FathersName, SaalVoroud, Field \
             From tblStudent, tblPerson \
             Where tblStudent.ID = tblPerson.ID AND ( \
                   tblStudent.StudentCode like '" + stuCode + "%' OR \
                   tblPerson.FirstName like N'" + stuCode + "%' OR \
                   tblPerson.LastName like N'" + stuCode + "%' OR \
                   tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + stuCode + "%')");
    qry.seek(index.row());

    finallStuCode = qry.value(0).toString();
    stuName = qry.value(1).toString();
    fathersName = qry.value(2).toString();
    saalVoroud = qry.value(3).toString();

    ui->label_stuCode->setText(qry.value(0).toString());
    ui->label_name->setText(qry.value(1).toString());
    ui->label_fathersName->setText(qry.value(2).toString());
    ui->label_saalVoroud->setText(qry.value(3).toString());
}

void EntekhabVahedDialog::on_pushButton_apply_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;

    QString tempID;
    QString stuID;

    qry1.prepare("Select ID From tblStudent \
                  Where tblStudent.StudentCode = :stucode");

            qry1.bindValue(":stucode", finallStuCode);
            qry1.exec();

            if(qry1.next()){
                stuID = qry1.value(0).toString();
            }

            qDebug() << "finallStuCode: " << finallStuCode;
            qDebug() << "qry1.value(0).toString(): " << qry1.value(0).toString();
            qDebug() << "stuID: " << stuID;

    qry2.prepare("Select ID From tblEntekhabVahed \
                 Where ID_Erae = :iderae AND ID_Student = :idstudent");

            qry2.bindValue(":iderae", eraeID);
            qry2.bindValue(":idstudent", stuID);
            qry2.exec();

            while(qry2.next()){
                tempID = qry2.value(0).toString();
            }

            qDebug() << tempID;

            if(!tempID.isEmpty()) {
                QMessageBox::warning(this, "هشدار" , "این درس قبلا برای این دانشجو انتخاب شده است.");

            }else{
                qry3.prepare("Insert Into tblEntekhabVahed \
                              (ID_Erae, ID_Student) \
                              Values(:iderae, :idstu) ");

                             qry3.bindValue(":iderae", eraeID);
                             qry3.bindValue(":idstu", stuID);

                            qDebug() << "iderae: " << eraeID;
                            qDebug() << "idstu: " << stuID;

                if(qry3.exec()){
                    QMessageBox::information(this, "OK", "درس با موفقیت انتخاب شد.");

                    ui->label_field->clear();
                    ui->label_stuCode->clear();
                    ui->label_name->clear();
                    ui->label_fathersName->clear();
                    ui->label_saalVoroud->clear();
                    ui->label_entekhabID->clear();
                    ui->label_title->clear();
                    ui->label_teacherName->clear();
                    ui->label_roozeHafte->clear();
                    ui->label_saat->clear();
                    ui->label_classNum->clear();

                    ui->stackedWidget->setCurrentIndex(0);

                }else{
                    QMessageBox::warning(this, "Warning", "انتخاب این درس با شکست مواجه شد.");
                    qDebug() << qry3.lastError().text();
                }
            }
}



//////// TAB 2 ---------->



void EntekhabVahedDialog::on_pushButton_findStuTab2_clicked()
{
    fieldTab2 = ui->comboBox_fieldTab2->currentText();

    if(ui->lineEdit_stuCodeTab2->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");

    }else{

        stuCodeTab2 = ui->lineEdit_stuCodeTab2->text();
        qryModelStuTab2 = new QSqlQueryModel(this);

        QString strQry = ("Select Distinct StudentCode as 'شماره دانشجویی', Concat(FirstName , ' ' , LastName) as 'نام', FathersName as 'نام پدر', SaalVoroud as 'سال ورود', Field as 'رشته' \
                          From tblPerson , tblStudent \
                          Where tblPerson.ID = tblStudent.ID AND \
                                tblStudent.Field like N'" + fieldTab2 + "' AND \
                                ( tblStudent.StudentCode like '" + stuCodeTab2 + "%' OR \
                                  tblPerson.Firstname like N'" + stuCodeTab2 + "%' OR \
                                  tblPerson.Lastname like N'" + stuCodeTab2 + "%' OR \
                                  tblPerson.Firstname + ' ' + tblPerson.LastName like N'" + stuCodeTab2 + "%')");

        qryModelStuTab2->setQuery(strQry);

        ui->tableView_stuTab2->setModel(qryModelStuTab2);
        ui->tableView_stuTab2->setWordWrap(false);
        ui->tableView_stuTab2->setColumnWidth(0,115);
        ui->tableView_stuTab2->setColumnWidth(1,180);
        ui->tableView_stuTab2->setColumnWidth(2,80);
        ui->tableView_stuTab2->setColumnWidth(3,70);
        ui->tableView_stuTab2->setColumnWidth(4,260);


        qDebug() << fieldTab2 ;
        qDebug() << stuCodeTab2;
        qDebug() << qryModelStuTab2->lastError().text();
    }
}

void EntekhabVahedDialog::on_tableView_stuTab2_clicked(const QModelIndex &index)
{
    QSqlQuery qry1;
    qryModelStuLessonsTab2 = new QSqlQueryModel(this);

    qry1.exec("Select Distinct StudentCode, Concat(FirstName , ' ' , LastName), FathersName, SaalVoroud, Field \
               From tblPerson , tblStudent \
               Where tblPerson.ID = tblStudent.ID AND \
                    tblStudent.Field like N'" + fieldTab2 + "' AND \
                    ( tblStudent.StudentCode like '" + stuCodeTab2 + "%' OR \
                      tblPerson.Firstname like N'" + stuCodeTab2 + "%' OR \
                      tblPerson.Lastname like N'" + stuCodeTab2 + "%' OR \
                      tblPerson.Firstname + ' ' + tblPerson.LastName like N'" + stuCodeTab2 + "%')");

    qry1.seek(index.row());

    finallStuCodeTab2 = qry1.value(0).toString();

    ui->label_StuCodTab2->setText(finallStuCodeTab2);
    ui->label_stuNameTab2->setText(qry1.value(1).toString());

    qryModelStuLessonsTab2->setQuery("Select tblErae.ID as 'مشخصه', Title as 'عنوان درس', Concat(FirstName, ' ', LastName) as 'نام استاد', DaysOfWeek as 'روز هفته', TimeOfClass as 'ساعت' \
                                      From tblPerson,        \
                                           tblTeacher,       \
                                           tblStudent,       \
                                           tblEntekhabVahed, \
                                           tblErae,          \
                                           tblLesson         \
                                      Where tblPerson.ID = tblTeacher.ID AND                \
                                            tblTeacher.ID = tblErae.ID_Teacher AND          \
                                            tblErae.ID_Lesson = tblLesson.ID AND            \
                                            tblEntekhabVahed.ID_Erae = tblErae.ID AND       \
                                            tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                                            tblStudent.StudentCode = " + finallStuCodeTab2);

            ui->tableView_LessTab2->setModel(qryModelStuLessonsTab2);
}

void EntekhabVahedDialog::on_tableView_LessTab2_clicked(const QModelIndex &index)
{
    QSqlQuery qry;

    qry.exec("Select Title, DaysOfWeek, TimeOfClass, tblErae.ID, FirstName, LastName \
             From tblPerson,         \
                  tblTeacher,        \
                  tblStudent,        \
                  tblEntekhabVahed,  \
                  tblErae, tblLesson \
             Where tblPerson.ID = tblTeacher.ID AND                \
                   tblTeacher.ID = tblErae.ID_Teacher AND          \
                   tblErae.ID_Lesson = tblLesson.ID AND            \
                   tblEntekhabVahed.ID_Erae = tblErae.ID AND       \
                   tblEntekhabVahed.ID_Student = tblStudent.ID AND \
                   tblStudent.StudentCode = " + finallStuCodeTab2);

    qry.seek(index.row());

    ui->label_eraeIDTab2->setText(qry.value(0).toString());
    ui->label_lessonNameTab2->setText(qry.value(1).toString());
    ui->label_teacherNameTab2->setText(qry.value(2).toString());
    ui->label_rouzTab2->setText(qry.value(3).toString());
    ui->label_saatTab2->setText(qry.value(4).toString());
}

void EntekhabVahedDialog::on_pushButton_removeTab2_clicked()
{
    // #1 delete neshon mide ke delet karde vali kar nmikone
    // #2 vaghti daneshjoo ro avaz mikone bayad etelaat oon payin marboot be dars clear beshe
    // #3 size table dars bayad fix bshe

    if(!ui->label_eraeIDTab2->text().isEmpty()){
        QSqlQuery qry1;
        QSqlQuery qry2;
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "هشدار", "آیا از حذف اطمینان دارید؟", QMessageBox::No|QMessageBox::Yes);

        if (reply == QMessageBox::Yes) {
            qry1.prepare("Select ID \
                          From tblStudent \
                          Where tblStudent.StudentCode = :stucode");

                    qry1.bindValue(":stucode", finallStuCodeTab2);
                    qry1.exec();

            if(qry1.next()){
                stuIDTab2 = qry1.value(0).toString();
            }

            qry2.prepare("Delete From tblEntekhabVahed \
                          Where ID_Erae = :iderae AND   \
                                ID_Student = :idstu");


                    qry2.bindValue(":iderae", ui->label_eraeIDTab2->text());
                    qry2.bindValue(":idstu", stuIDTab2);

            if(qry2.exec()){
               QMessageBox::information(this, "OK", "درس مورد نظر از دروس انتخاب شده برای این دانشجو حذف شد.");

            }else{
                qDebug() << "qry2.lastError(): " << qry2.lastError().text();
            }

        }else {
        qDebug() << "No Ro Click Kard!";
        // do nothing

        }
    }else if(ui->label_StuCodTab2->text().isEmpty()){
        QMessageBox::warning(this,"خطا", "لطفا ابتدا یک دانشجو را انتخاب کنید.");

    }else if(ui->label_eraeIDTab2->text().isEmpty()){
        QMessageBox::warning(this,"خطا", "لطفا ابتدا یک درس را انتخاب کنید.");

    }else{
        QMessageBox::warning(this,"خطا", "یه مشکل جدی پیش اومده ، برنامه رو نشون علی بده.");
    }
}
