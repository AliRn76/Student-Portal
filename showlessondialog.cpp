#include "showlessondialog.h"
#include "ui_showlessondialog.h"

ShowLessonDialog::ShowLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowLessonDialog)
{
    ui->setupUi(this);

    qry = new QSqlQueryModel(this);

    qry->setQuery("Select LessonCode as 'کد درس', Title as 'عنوان درس', TedadVahed as 'تعداد واحد', Type as 'نوع درس' \
                   From Student.dbo.tblLesson");

    ui->treeView->setModel(qry);
}

ShowLessonDialog::~ShowLessonDialog()
{
    delete ui;
}
