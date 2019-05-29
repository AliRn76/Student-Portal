#ifndef STUDENTMAINDIALOG_H
#define STUDENTMAINDIALOG_H

#include <QDialog>
#include <QtSql>
#include <studentchangepassworddialog.h>
#include <showstudenteraelistdialog.h>
#include <studententekhabvaheddialog.h>
#include <studententekhabvaheddialog.h>
#include <studentbarnameclassdialog.h>
#include <studentkarnamedialog.h>

namespace Ui {
class StudentMainDialog;
}

class StudentMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentMainDialog(QWidget *parent = nullptr);
    ~StudentMainDialog();

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_listErae_clicked();

    void on_pushButton_entekhabVahed_clicked();

    void on_pushButton_barnameClass_clicked();

    void on_pushButton_karname_clicked();

private:
    Ui::StudentMainDialog *ui;
    StudentChangePasswordDialog *stuChangeDialog;
    ShowStudentEraeListDialog *showStuEraListDialog;
    StudentEntekhabVahedDialog *stuEntekhabDialog;
    StudentBarnameClassDialog *stuBarnameDialog;
    StudentKarnameDialog *stuKarnameDialog;
};

#endif // STUDENTMAINDIALOG_H
