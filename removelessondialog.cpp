#include "removelessondialog.h"
#include "ui_removelessondialog.h"

RemoveLessonDialog::RemoveLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveLessonDialog)
{
    ui->setupUi(this);
}

RemoveLessonDialog::~RemoveLessonDialog()
{
    delete ui;
}

void RemoveLessonDialog::on_pushButton_search_clicked()
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

    lessCode = ui->lineEdit_lessCode->text();

    ui->label_name->clear();
    ui->label_type->clear();
    ui->label_lessonCode->clear();
    ui->label_field->clear();
    ui->label_tedadVahed->clear();

    if(lessCode.isEmpty()){
        QMessageBox::warning(this, "خطا","ابتدا یک کد یا نام وارد کنید.");

    }else {
        QSqlQuery qry1("Select Title, Type, LessonCode, Field, TedadVahed \
                        From Student.dbo.tblLesson \
                        Where Student.dbo.tblLesson.LessonCode like '" + lessCode + "' \
                        OR Student.dbo.tblLesson.Title like N'" + lessCode +"'");

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

           ui->label_name->setText(title);
           ui->label_type->setText(type);
           ui->label_lessonCode->setText(lessonCode);
           ui->label_field->setText(field);
           ui->label_tedadVahed->setText(tedadVahed);
        }

    }
}

void RemoveLessonDialog::on_pushButton_remove_clicked()
{
    QSqlQuery qry1;
    QString lessonCode;

    if(!(ui->label_name->text().isEmpty())){
        lessonCode = ui->label_lessonCode->text();

        qry1.prepare("Delete From Student.dbo.tblLesson \
                      Where Student.dbo.tblLesson.LessonCode = :lessoncode");
        qry1.bindValue(":lessoncode", lessonCode);

        if(qry1.exec()){
            QMessageBox::information(this, "OK", "درس مورد نظر حذف شد.");
            ui->label_name->clear();
            ui->label_type->clear();
            ui->label_lessonCode->clear();
            ui->label_field->clear();

        }else{
            QMessageBox::warning(this,"Error", "به دلیل اینکه این درس ارائه داده شده است ، شما قادر به حذف ان نیستید.");

        }
    }else{
        QMessageBox::warning(this, "Warning", "لطفا اول یک مشخصه درس را جستجو کنید.");

    }
}

void RemoveLessonDialog::on_pushButton_showAllStu_clicked()
{
    showLessDialog = new ShowLessonDialog();
    showLessDialog->show();
}
