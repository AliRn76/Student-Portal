#include "sendjozvedialog.h"
#include "ui_sendjozvedialog.h"

SendJozveDialog::SendJozveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendJozveDialog)
{
    ui->setupUi(this);
}

SendJozveDialog::~SendJozveDialog()
{
    delete ui;
}

void SendJozveDialog::on_pushButton_exit_clicked()
{
    this->close();
}

void SendJozveDialog::on_pushButton_Send_clicked()
{
    QString link = ui->lineEdit_link->text();

    if(ui->lineEdit_link->text().isEmpty()){
        QMessageBox::warning(this , "Error" , "لطفا فیلد را پر کنید .");
    }
    else {
        QSqlQuery qry;
        qry.prepare("Update tblErae set jozve = :link where tblErae.ID = :id");
        qry.bindValue(":link" , link);
        qry.bindValue(":id" , lessCode);
        if(qry.exec()){
            QMessageBox::information(this , "Done" , "لینک جزوه در دیتابیس به روز رسانی شد .");
        }
        else {
            QMessageBox::warning(this , "Error", "به روز رسانی دیتابیس با مشکل روبرو شد .");
        }
    }
    ui->lineEdit_link->clear();
}
