#include "employeemainwindow.h"
#include "ui_employeemainwindow.h"

EmployeeMainWindow::EmployeeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeMainWindow)
{
    ui->setupUi(this);




    QString name;
    QString lastName;
    QString cpyStrUser = EmployeeChangePasswordDialog::strUserEmp;
    QSqlQuery qry1;
    QSqlQuery qry2;
    int currentID;

    qry1.prepare("Select ID \
                  From tblEmployee \
                  Where tblEmployee.EmployeeCode = :empcode");
            qry1.bindValue(":empcode", cpyStrUser);
            qry1.exec();
    if(qry1.next()){
        currentID = qry1.value(0).toInt();
    }

    qry2.prepare("Select FirstName, LastName \
                  From tblPerson \
                  Where tblPerson.ID = :id");
            qry2.bindValue(":id", currentID);
            qry2.exec();
    if(qry2.next()){
        name = qry2.value(0).toString();
        lastName = qry2.value(1).toString();
    }

    ui->label_name->setText(name + " " + lastName);
    ui->label_employeeCode->setText(cpyStrUser);

}

EmployeeMainWindow::~EmployeeMainWindow()
{
    delete ui;
}

void EmployeeMainWindow::on_pushButton_addStu_clicked()
{
    addStuDialog = new AddStudentDialog(this);
    addStuDialog->show();
}

void EmployeeMainWindow::on_pushButton_removeStu_clicked()
{
    rmvStuDialog = new RemoveStudentDialog(this);
    rmvStuDialog->show();
}

void EmployeeMainWindow::on_pushButton_editStu_clicked()
{
    editStuDialog = new EditStudentDialog(this);
    editStuDialog->show();
}

void EmployeeMainWindow::on_pushButton_entekhabVahed_clicked()
{
    entekhVahedDialog = new EntekhabVahedDialog(this);
    entekhVahedDialog->show();
}

void EmployeeMainWindow::on_pushButton_setting_clicked()
{
    empChangeDialog = new EmployeeChangePasswordDialog(this);
    empChangeDialog->show();
}

void EmployeeMainWindow::on_pushButton_addLesson_clicked()
{
    addLessDialog = new AddLessonDialog(this);
    addLessDialog->show();
}

void EmployeeMainWindow::on_pushButton_removeLesson_clicked()
{
    rmvLessDialog = new RemoveLessonDialog(this);
    rmvLessDialog->show();
}

void EmployeeMainWindow::on_pushButton_editLesson_clicked()
{
    editLessDialog = new EditLessonDialog(this);
    editLessDialog->show();
}

void EmployeeMainWindow::on_pushButton_addTeacher_clicked()
{
    addTeachDialog = new AddTeacherDialog(this);
    addTeachDialog->show();
}

void EmployeeMainWindow::on_pushButton_removeTeacher_clicked()
{
    rmvTeachDialog = new RemoveTeacherDialog(this);
    rmvTeachDialog->show();
}

void EmployeeMainWindow::on_pushButton_editTeacher_clicked()
{
    editTeachDialog = new EditTeacherDialog(this);
    editTeachDialog->show();
}

void EmployeeMainWindow::on_pushButton_eraeDars_clicked()
{
    eraeDialog = new EraeDarsDialog(this);
    eraeDialog->show();
}

void EmployeeMainWindow::on_pushButton_removeErae_clicked()
{
    rmvEraeDialog = new RemoveEraeDarsDialog(this);
    rmvEraeDialog->show();
}

void EmployeeMainWindow::on_pushButton_showStu_clicked()
{
    showStuDialog = new ShowStudentDialog(this);
    showStuDialog->show();
}

void EmployeeMainWindow::on_pushButton_showEntekhab_clicked()
{
    showEntekhabDialog = new ShowEntekhabVahedDialog(this);
    showEntekhabDialog->show();
}

void EmployeeMainWindow::on_pushButton_showLesson_clicked()
{
    showLessDialog = new ShowLessonDialog(this);
    showLessDialog->show();
}

void EmployeeMainWindow::on_pushButton_showTeacher_clicked()
{
    showTeachDialog = new ShowTeacherDialog(this);
    showTeachDialog->show();
}

void EmployeeMainWindow::on_pushButton_showErae_clicked()
{
    showEraeDialog = new ShowEraeListDialog(this);
    showEraeDialog->show();
}
