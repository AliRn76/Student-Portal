#include "eraedarsdialog.h"
#include "ui_eraedarsdialog.h"

EraeDarsDialog::EraeDarsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EraeDarsDialog)
{
    ui->setupUi(this);
}

EraeDarsDialog::~EraeDarsDialog()
{
    delete ui;
}

void EraeDarsDialog::on_pushButton_showTeach_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}

void EraeDarsDialog::on_pushButton_findTeach_clicked()
{
    QString strTeacherCode = ui->lineEdit_teachCode->text();
    QString name;
    QString arrStr[4];
    QSqlRecord rec;
    int col;

    ui->label_teachCode->clear();
    ui->label_teachName->clear();
    ui->label_eduDegree->clear();

    if(strTeacherCode.isEmpty()){
        QMessageBox::warning(this, "Warning", "ابتدا یک نام یا کد کارمندی وارد کنید.");
    }else{
        QSqlQuery qry("Select TeacherCode, FirstName, LastName, EducationDegree \
                       From tblPerson , tblTeacher \
                       Where ( tblPerson.ID = tblTeacher.ID ) AND ( tblTeacher.TeacherCode like '" + strTeacherCode + "%' OR \
                               tblPerson.Firstname like N'" + strTeacherCode + "%' OR \
                               tblPerson.Lastname like N'" + strTeacherCode + "%' OR \
                               tblPerson.FirstName + ' ' + tblPerson.LastName like N'" + strTeacherCode + "')");

        if(qry.numRowsAffected() > 1){
          QMessageBox::information(this, "Warning", "بیش از یک مورد " + strTeacherCode + " وجود دارد.");
        }

        if(qry.numRowsAffected() != 0){
            rec = qry.record();
            col = rec.count();

            while(qry.next()){
                for (int i=0 ; i<col ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }

            name = arrStr[1] + " " + arrStr[2];

            ui->label_teachCode->setText(arrStr[0]);
            ui->label_teachName->setText(name);
            ui->label_eduDegree->setText(arrStr[3]);
        }else {
            QMessageBox::warning(this, "Warning", "لطفا یک نام یا کد کارمندی صحیح وارد کنید.");
        }
    }
}

void EraeDarsDialog::on_pushButton_showLesson_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}

void EraeDarsDialog::on_pushButton_findLesson_clicked()
{
    QString strLesson = ui->lineEdit_lessonCode->text();
    QString arrStr[4];
    QSqlRecord rec;
    int col;

    ui->label_lessonCode->clear();
    ui->label_lessonName->clear();
    ui->label_tedadVahed->clear();
    ui->label_type->clear();

    if(strLesson.isEmpty()){
        QMessageBox::warning(this, "Warning", "ابتدا یک نام یا کد درس وارد کنید.");
    }else{
        QSqlQuery qry("Select LessonCode, Title, Type, TedadVahed \
                       From tblLesson \
                       Where ( tblLesson.LessonCode like '" + strLesson+ "%') OR \
                             ( tblLesson.Title like N'" + strLesson + "%')" );

        if(qry.numRowsAffected() > 1){
          QMessageBox::information(this, "Warning", "بیش از یک مورد " + strLesson + " وجود دارد.");
        }

        if(qry.numRowsAffected() != 0){
            rec = qry.record();
            col = rec.count();

            while(qry.next()){
                for (int i=0 ; i<col ; i++){
                    arrStr[i] = qry.value(i).toString();
                }
            }
            ui->label_lessonCode->setText(arrStr[0]);
            ui->label_lessonName->setText(arrStr[1]);
            ui->label_type->setText(arrStr[2]);
            ui->label_tedadVahed->setText(arrStr[3]);
        }else{
            QMessageBox::warning(this, "warning", "لطفا یک نام یا کد درس صحیح وارد کنید.");
        }
    }
}

void EraeDarsDialog::on_pushButton_apply_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QSqlQuery qry4;
    QString roozHafte;
    QString classTime;
    QString checkRooz;
    QString checkTime;
    int teacherID;
    int lessonID;

    roozHafte = ui->comboBox->currentText();
    classTime = ui->timeEdit->time().toString();

    if(ui->label_lessonCode->text().isEmpty() || ui->label_teachCode->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا موارد بالا را پر کنید.");
    }else{
        qry1.prepare("Select ID \
                      From tblTeacher \
                      Where tblTeacher.teacherCode = :teachcode");

                    qry1.bindValue(":teachcode", ui->label_teachCode->text());
                    qry1.exec();

        while(qry1.next()){
            teacherID = qry1.value(0).toInt();
        }

        qry2.prepare("Select ID \
                      From tblLesson \
                      Where tblLesson.LessonCode = :lessoncode");

                    qry2.bindValue(":lessoncode", ui->label_lessonCode->text());
                    qry2.exec();

        while(qry2.next()){
            lessonID = qry2.value(0).toInt();
        }

        qry4.prepare("Select DaysOfWeek, TimeOfClass From tblErae \
                      Where tblErae.ID_Teacher = :idteacher AND tblErae.ID_Lesson = :idlesson");
                qry4.bindValue(":idteacher", teacherID);
                qry4.bindValue(":idlesson", lessonID);
                qry4.exec();

                while(qry4.next()){
                    checkRooz = qry4.value(0).toString();
                    checkTime = qry4.value(1).toString();
                }

            if(checkRooz == roozHafte && checkTime == classTime){
                QMessageBox::warning(this, "خطا", "این درس قبلا با این استاد در این زمان ارائه داده شده است.");
                ui->label_teachCode->clear();
                ui->label_teachName->clear();
                ui->label_eduDegree->clear();
                ui->label_lessonCode->clear();
                ui->label_lessonName->clear();
                ui->label_tedadVahed->clear();
                ui->label_type->clear();
                ui->comboBox->setCurrentIndex(0);
                ui->timeEdit->clear();

            }else{
                qry3.prepare("Insert Into tblErae \
                              (ID_Teacher, ID_Lesson, DaysOfWeek, TimeOfClass) \
                              Values(:idteacher, :idlesson, :days, :time)");

                             qry3.bindValue(":idteacher", teacherID);
                             qry3.bindValue(":idlesson", lessonID);
                             qry3.bindValue(":days", roozHafte);
                             qry3.bindValue(":time", classTime);

                             if(qry3.exec()){
                                 QMessageBox::information(this, "OK", "درس ارائه داده شد.");
                                 ui->label_teachCode->clear();
                                 ui->label_teachName->clear();
                                 ui->label_eduDegree->clear();
                                 ui->label_lessonCode->clear();
                                 ui->label_lessonName->clear();
                                 ui->label_tedadVahed->clear();
                                 ui->label_type->clear();
                                 ui->comboBox->setCurrentIndex(0);
                                 ui->timeEdit->clear();
                             }else{
                                 QMessageBox::warning(this, "OK", "ارائه درس با مشکل مواجه شد.");
                             }
            }
    }
}

void EraeDarsDialog::on_pushButton_clicked()
{
    showEraeDialog = new ShowEraeListDialog(this);
    showEraeDialog->show();
}
