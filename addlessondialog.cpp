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
                        From Student.dbo.tblLesson \
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
            qry1.prepare("Insert Into Student.dbo.tblLesson \
                         (Title, TedadVahed, Type, Field) \
                         Values(:title, :tedadvahed, :type, :field)");
                    qry1.bindValue(":title", strTitle);
                    qry1.bindValue(":tedadvahed", strTedadVahed);
                    qry1.bindValue(":type", strType);
                    qry1.bindValue(":field", strField);

                        if(qry1.exec()){
                            currentID = qry3.lastInsertId().toString();
                            qry4.prepare("Select LessonCode From Student.dbo.tblLesson \
                                          Where tblLesson.ID = :id");
                               qry4.bindValue(":id", currentID);
                               qry4.exec();

                               if(qry4.next()){
                                   currentCode = qry4.value(0).toString();
                               }

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
    // hasan
    // sheeeeeeeeeeeeeeeeellllllllooooooooooo
    // hasan ok sho
    // sarma nakhor , sarpa bokhor
}

void AddLessonDialog::on_pushButton_showAllCourses_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}
