#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("mydsn32");
    db.setHostName("localhost");
    if(!db.open()){
        qDebug() << db.lastError().text();
    }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

QString EmployeeChangePasswordDialog::strUserEmp;
QString StudentChangePasswordDialog::strUserStu;

void MainWindow::on_pushButton_manager_clicked()
{
    QString strUsername = ui->lineEdit_username->text();
    QString strPassword = ui->lineEdit_password->text();

    EmployeeChangePasswordDialog::strUserEmp = strUsername;

    QSqlQuery qry;

    qry.prepare("Select Password From Student.dbo.tblEmployee \
                 Where tblEmployee.EmployeeCode = :username");
                qry.bindValue(":username", strUsername);
                qry.exec();
    if(qry.next()){
        if(strPassword == qry.value(0).toString()){
            emploMainDialog = new EmployeeMainDialog(this);
            emploMainDialog->show();
        }else if(strPassword == "شیئهد"){
            QMessageBox::warning(this, "هشدار", "زبان سیستم خود را به انگلیسی تغییر دهید.");
        }else{
            QMessageBox::warning(this, "warning", "رمز عبور یا نام کاربری وارد شده صحیح نمیباشد.");
        }
    }else{
        QMessageBox::warning(this, "warning", "رمز عبور یا نام کاربری وارد شده صحیح نمیباشد.");
    }
}

void MainWindow::on_pushButton_teacher_clicked()
{
    QString strUsername = ui->lineEdit_username->text();
    QString strPassword = ui->lineEdit_password->text();

    QSqlQuery qry;

    qry.prepare("Select Password From Student.dbo.tblTeacher \
                 Where tblTeacher.TeacherCode = :teachercode");
                qry.bindValue(":teachercode", strUsername);
                qry.exec();
    if(qry.next()){
        qDebug() << "Teacher is OK too";
    }else{
        qDebug() <<"Teacher has problem :(";
    }
}

void MainWindow::on_pushButton_stu_clicked()
{
    QString strUsername = ui->lineEdit_username->text();
    QString strPassword = ui->lineEdit_password->text();

    StudentChangePasswordDialog::strUserStu = strUsername;

    QSqlQuery qry;

    qry.prepare("Select Password From Student.dbo.tblStudent \
                 Where tblStudent.StudentCode = :stucode");
                qry.bindValue(":stucode", strUsername);
                qry.exec();
    if(qry.next()){
        if(strPassword == qry.value(0).toString()){
            stuMainDialog = new StudentMainDialog(this);
            stuMainDialog->show();
        }else{
            QMessageBox::warning(this, "warning", "رمز عبور یا نام کاربری وارد شده صحیح نمیباشد.");
        }
    }else{
        QMessageBox::warning(this, "warning", "رمز عبور یا نام کاربری وارد شده صحیح نمیباشد.");
    }
}
