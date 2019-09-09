#include "teacherrequest.h"
#include "ui_teacherrequest.h"

teacherRequest::teacherRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacherRequest)
{
    ui->setupUi(this);

    if(whichpage==0){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (whichpage==1) {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (whichpage==2) {
        ui->stackedWidget->setCurrentIndex(2);
    }
    ui->comboBox_Day->addItem("شنبه");
    ui->comboBox_Day->addItem("یکشنبه");
    ui->comboBox_Day->addItem("دوشنبه");
    ui->comboBox_Day->addItem("سه شنبه");
    ui->comboBox_Day->addItem("چهارشنبه");
    ui->comboBox_Day->addItem("پنج شنبه");
}

teacherRequest::~teacherRequest()
{
    delete ui;
}
