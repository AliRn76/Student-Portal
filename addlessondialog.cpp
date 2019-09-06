#include "addlessondialog.h"
#include "ui_addlessondialog.h"

AddLessonDialog::AddLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLessonDialog)
{
    ui->setupUi(this);
}

AddLessonDialog::~AddLessonDialog()
{
    delete ui;
}

///---------------Tab1-------------------------------------------------------------------------------->


void AddLessonDialog::on_pushButton_add_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QSqlQuery qry4;
    QString strTitle;
    QString strType;
    QString strTedadVahed;
    QString strField;
    QString checkTitle;
    QString checkType;
    QString checkField;
    QString checkTedad;
    QString currentID;
    QString currentCode;

    strTitle = ui->lineEdit_title->text();
    strTedadVahed = ui->comboBox_tedadVahed->currentText();
    strType = ui->comboBox_type->currentText();
    strField = ui->comboBox_field_2->currentText();

    if(strTitle.isEmpty()){
        QMessageBox::warning(this, "خطا" , "لطفا یک نام برای درس وارد کنید.");

    }else{
        QSqlQuery qry2("Select Title, Type, TedadVahed, Field \
                        From tblLesson \
                        Where tblLesson.Title like N'" + strTitle + "' \
                        AND tblLesson.Type like N'" + strType + "' \
                        AND tblLesson.TedadVahed like '" + strTedadVahed + "' \
                        And tblLesson.Field like '" + strField + "'");

        if(qry2.numRowsAffected() > 0){
            QMessageBox::warning(this, "خطا" , "درس مورد نظر قبلا اضافه شده است.");
            ui->lineEdit_title->clear();
            ui->comboBox_type->setCurrentIndex(0);
            ui->comboBox_tedadVahed->setCurrentIndex(2);
            ui->comboBox_field_2->setCurrentIndex(0);

        }else{
            qry1.prepare("Insert Into tblLesson \
                         (Title, TedadVahed, Type, Field) \
                         Values(:title, :tedadvahed, :type, :field)");
                    qry1.bindValue(":title", strTitle);
                    qry1.bindValue(":tedadvahed", strTedadVahed);
                    qry1.bindValue(":type", strType);
                    qry1.bindValue(":field", strField);

                        if(qry1.exec()){
                            currentID = qry1.lastInsertId().toString();
                            qry4.prepare("Select LessonCode From tblLesson \
                                          Where tblLesson.ID = :id");
                               qry4.bindValue(":id", currentID);
                               qry4.exec();

                               if(qry4.next()){
                                   currentCode = qry4.value(0).toString();
                               }
                            qDebug() << currentID ;

                            QMessageBox::information(this, "Ok", "درس اضافه شد، کد درس : " + currentCode);
                            ui->lineEdit_title->clear();
                            ui->comboBox_type->setCurrentIndex(0);
                            ui->comboBox_tedadVahed->setCurrentIndex(2);
                        }else{
                            QMessageBox::warning(this, "Warning", "اضافه کردن درس با مشکل مواجه شد.");
                            qDebug() << qry1.lastError().text();
                        }
        }
    }
}

void AddLessonDialog::on_pushButton_showAllCourses_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}


///---------------Tab2-------------------------------------------------------------------------------->



void AddLessonDialog::on_pushButton_searchTab2_clicked()
{
    ui->label_lessonCodeTab2->clear();
    ui->lineEdit_lessonNameTab2->clear();
    ui->comboBox_type->setCurrentIndex(0);
    ui->comboBox_tedadVahed->setCurrentIndex(2);

    if(ui->lineEdit_lessCodeTab2->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");

    }else{
        QString lessCode;
        QString title;
        QString type;
        QString tedadVahed;
        QString lessonCode;
        QString field;

        lessCode = ui->lineEdit_lessCodeTab2->text();

        QSqlQuery qry("Select Title, Type, TedadVahed, LessonCode, Field \
                       From tblLesson \
                       Where tblLesson.LessonCode like '" + lessCode + "%' OR \
                             tblLesson.Title like N'" + lessCode + "%'");

        if(qry.numRowsAffected() == 0){
            QMessageBox::warning(this, "خطا", "لطفا یک کد یا نام صحیح وارد کنید");

        }else{
            if(qry.numRowsAffected() > 1){
                QMessageBox::warning(this, "هشدار", "بیشتر از یک درس وجود دارد.");
            }
            if(qry.next()){
                title = qry.value(0).toString();
                type = qry.value(1).toString();
                tedadVahed = qry.value(2).toString();
                lessonCode = qry.value(3).toString();
                field = qry.value(4).toString();
            }

            ui->label_lessonCodeTab2->setText(lessonCode);
            ui->comboBox_typeTab2->setCurrentText(type);
            ui->comboBox_tedadVahedTab2->setCurrentText(tedadVahed);
            ui->lineEdit_lessonNameTab2->setText(title);
            ui->comboBox_fieldTab2->setCurrentText(field);
        }
    }
}

void AddLessonDialog::on_pushButton_apply_Tab2_clicked()
{
    if(!(ui->label_lessonCodeTab2->text().isEmpty())){

        QSqlQuery qry1;
        QString lessCode;
        QString title;
        QString type;
        QString tedadVahed;
        QString field;

        lessCode = ui->label_lessonCodeTab2->text();
        title = ui->lineEdit_lessonNameTab2->text();
        type = ui->comboBox_typeTab2->currentText();
        tedadVahed = ui->comboBox_tedadVahedTab2->currentText();
        field = ui->comboBox_fieldTab2->currentText();

        qry1.prepare("Update tblLesson \
                      Set Title = :title, Type = :type, TedadVahed = :tedadvahed, Field = :field \
                      Where tblLesson.LessonCode = :lessoncode");
                qry1.bindValue(":title", title);
                qry1.bindValue(":type", type);
                qry1.bindValue(":tedadvahed", tedadVahed);
                qry1.bindValue(":lessoncode", lessCode);
                qry1.bindValue(":field", field);
                qry1.exec();

        QMessageBox::information(this, "OK", "اطلاعات درس به روز شد.");
        ui->lineEdit_lessonNameTab2->clear();
        ui->comboBox_typeTab2->setCurrentIndex(0);
        ui->comboBox_tedadVahedTab2->setCurrentIndex(2);
        ui->label_lessonCodeTab2->clear();
        ui->comboBox_fieldTab2->setCurrentIndex(0);

    }else{
        QMessageBox::warning(this, "خطا" , "ابتدا یک نام یا کد درسی را جستجو کنید.");
    }
}

void AddLessonDialog::on_pushButton_showLessonsTab2_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}


///---------------Tab3-------------------------------------------------------------------------------->



void AddLessonDialog::on_pushButton_search_clicked()
{
    QSqlQuery qry1;
    QSqlQuery qry2;
    QSqlQuery qry3;
    QString lessCode;
    QString title;
    QString type;
    QString lessonCode;
    QString field;
    QString tedadVahed;

    lessCode = ui->lineEdit_lessCodeTab3->text();

    ui->label_lessonNameTab3->clear();
    ui->label_typeTab3->clear();
    ui->label_lessonCodeTab3->clear();
    ui->label_fieldTab3->clear();
    ui->label_tedadVahedTab3->clear();

    if(lessCode.isEmpty()){
        QMessageBox::warning(this, "خطا","ابتدا یک کد یا نام وارد کنید.");

    }else {
        QSqlQuery qry1("Select Title, Type, LessonCode, Field, TedadVahed \
                        From tblLesson \
                        Where tblLesson.LessonCode like '" + lessCode + "%' \
                        OR tblLesson.Title like N'" + lessCode +"%'");

        if(qry1.numRowsAffected() == 0 ){
           QMessageBox::warning(this, "خطا","هیچ درسی یافت نشد.");

        }else {
            if(qry1.numRowsAffected() > 1){
              QMessageBox::warning(this, "هشدار" , "بیشتر از یک درس با این نام وجود دارد.");
            }

           while(qry1.next()){
               title = qry1.value(0).toString();
               type = qry1.value(1).toString();
               lessonCode = qry1.value(2).toString();
               field = qry1.value(3).toString();
               tedadVahed = qry1.value(4).toString();
           }

           ui->label_lessonNameTab3->setText(title);
           ui->label_typeTab3->setText(type);
           ui->label_lessonCodeTab3->setText(lessonCode);
           ui->label_fieldTab3->setText(field);
           ui->label_tedadVahedTab3->setText(tedadVahed);
        }

    }
}

void AddLessonDialog::on_pushButton_removeTab3_clicked()
{
    QSqlQuery qry1;
    QString lessonCode;

    if(!(ui->label_lessonNameTab3->text().isEmpty())){
        lessonCode = ui->label_lessonCodeTab3->text();

        qry1.prepare("Delete From tblLesson \
                      Where tblLesson.LessonCode = :lessoncode");
        qry1.bindValue(":lessoncode", lessonCode);

        if(qry1.exec()){
            QMessageBox::information(this, "OK", "درس مورد نظر حذف شد.");
            ui->label_lessonNameTab3->clear();
            ui->label_typeTab3->clear();
            ui->label_lessonCodeTab3->clear();
            ui->label_fieldTab3->clear();

        }else{
            QMessageBox::warning(this,"Error", "به دلیل اینکه این درس ارائه داده شده است ، شما قادر به حذف ان نیستید.");

        }
    }else{
        QMessageBox::warning(this, "Warning", "لطفا اول یک مشخصه درس را جستجو کنید.");

    }
}

void AddLessonDialog::on_pushButton_showLessonsTab3_clicked()
{
    showLessDialog = new ShowLessonDialog();
    showLessDialog->show();
}
