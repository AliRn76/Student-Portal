#include "teachershowlesson.h"
#include "ui_teachershowlesson.h"

teachershowlesson::teachershowlesson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teachershowlesson)
{
    ui->setupUi(this);
}

teachershowlesson::~teachershowlesson()
{
    delete ui;
}
