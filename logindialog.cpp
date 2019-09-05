//#include "logindialog.h"
//#include "ui_logindialog.h"

//LoginDialog::LoginDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::LoginDialog)
//{
//    ui->setupUi(this);

//    //    db = QSqlDatabase::addDatabase("QODBC");
//    //    db.setDatabaseName("mydsn32");
//    //    db.setHostName("localhost");

//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("se7enf98.ddns.net");
//    db.setUserName("team");
//    db.setPassword("portal98");
//    db.setDatabaseName("Portal");

//    if(!db.open()){
//        qDebug() << db.lastError().text();
//        QMessageBox::warning(this,"warning", db.lastError().text());
//    }
//}

//LoginDialog::~LoginDialog()
//{
//    delete ui;
//}

//QString EmployeeChangePasswordDialog::strUserEmp;
//QString StudentChangePasswordDialog::strUserStu;
//QString TeacherChangePassword::strUserTeacher;
//QString SendJozveDialog::lessCode;


//void LoginDialog::on_pushButton_login_clicked()
//{
//    QString strUsername = ui->lineEdit_username->text();
//    QString strPassword = ui->lineEdit_password->text();

//    QSqlQuery qry;
//    QSqlQuery qry2;
//    QSqlQuery qry3;

//    qry.prepare("Select Password From tblStudent \
//                 Where tblStudent.StudentCode = :stucode");
//                qry.bindValue(":stucode", strUsername);
//                qry.exec();

//    if(qry.next()){
//        if(strPassword == qry.value(0).toString()){
//            StudentChangePasswordDialog::strUserStu = strUsername;
//            stuMainDialog = new StudentMainDialog(this);
//            stuMainDialog->show();
//        }else{
//            QMessageBox::warning(this, "خطا", "نام کاربری یا کلمه عبور وارد شده صحیح نمیباشد #1.");
//        }

//    }else{
//        qry2.prepare("Select Password \
//                      From tblTeacher \
//                      Where tblTeacher.TeacherCode = :teachercode");
//                    qry2.bindValue(":teachercode", strUsername);
//                    qry2.exec();

//        if(qry2.next()){
//            if(strPassword == qry2.value(0).toString()){
//                TeacherChangePassword::strUserTeacher = strUsername;
//                teamaindialog = new TeacherMainDialog(this);
//                teamaindialog->show();
//            }else{
//                QMessageBox::warning(this, "خطا", "نام کاربری یا کلمه عبور وارد شده صحیح نمیباشد #2.");
//            }

//        }else{
//            qry3.prepare("Select Password \
//                          From tblEmployee \
//                          Where tblEmployee.EmployeeCode = :username");
//                        qry3.bindValue(":username", strUsername);
//                        qry3.exec();

//            if(qry3.next()){
//                if(strPassword == qry3.value(0).toString()){
//                    EmployeeChangePasswordDialog::strUserEmp = strUsername;
//                    emploMainWindow = new EmployeeMainWindow(this);
//                    emploMainWindow->show();
//                    hide();
//                }else if(strPassword == "شیئهد"){
//                    QMessageBox::warning(this, "هشدار", "زبان سیستم خود را به انگلیسی تغییر دهید.");
//                }else{
//                    QMessageBox::warning(this, " #3خطا", "نام کاربری یا کلمه عبور وارد شده صحیح نمیباشد.");
//                }
//            }else{
//                QMessageBox::warning(this, "خطا", "نام کاربری وارد شده معتبر نمیباشد.");
//            }
//        }
//    }
//}
