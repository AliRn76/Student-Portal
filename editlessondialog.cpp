#include "editlessondialog.h"
#include "ui_editlessondialog.h"

EditLessonDialog::EditLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLessonDialog)
{
    ui->setupUi(this);
}

EditLessonDialog::~EditLessonDialog()
{
    delete ui;
}

void EditLessonDialog::on_pushButton_showLesson_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}

void EditLessonDialog::on_pushButton_search_clicked()
{
    ui->label_lessonCode->clear();
    ui->lineEdit_lessonName->clear();
    ui->comboBox_type->setCurrentIndex(0);
    ui->comboBox_tedadVahed->setCurrentIndex(2);

    if(ui->lineEdit_lessCode->text().isEmpty()){
        QMessageBox::warning(this, "warning", "لطفا ابتدا یک کد وارد کنید.");

    }else{
        QString lessCode;
        QString title;
        QString type;
        QString tedadVahed;
        QString lessonCode;
        QString field;

        lessCode = ui->lineEdit_lessCode->text();

        QSqlQuery qry("Select Title, Type, TedadVahed, LessonCode, Field \
                       From tblLesson \
                       Where tblLesson.LessonCode like '" + lessCode + "%' OR tblLesson.Title like N'" + lessCode + "%'");

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

            ui->label_lessonCode->setText(lessonCode);
            ui->comboBox_type->setCurrentText(type);
            ui->comboBox_tedadVahed->setCurrentText(tedadVahed);
            ui->lineEdit_lessonName->setText(title);
            ui->comboBox_field->setCurrentText(field);
        }
    }
}

void EditLessonDialog::on_pushButton_apply_clicked()
{
    if(!(ui->label_lessonCode->text().isEmpty())){

        QSqlQuery qry1;
        QString lessCode;
        QString title;
        QString type;
        QString tedadVahed;
        QString field;

        lessCode = ui->label_lessonCode->text();
        title = ui->lineEdit_lessonName->text();
        type = ui->comboBox_type->currentText();
        tedadVahed = ui->comboBox_tedadVahed->currentText();
        field = ui->comboBox_field->currentText();

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
        ui->lineEdit_lessonName->clear();
        ui->comboBox_type->clear();
        ui->comboBox_tedadVahed->clear();
        ui->label_lessonCode->clear();
        ui->comboBox_field->clear();

    }else{
        QMessageBox::warning(this, "خطا" , "ابتدا یک نام یا کد درسی را جستجو کنید.");
    }
}
