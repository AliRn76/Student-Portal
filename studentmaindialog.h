#ifndef STUDENTMAINDIALOG_H
#define STUDENTMAINDIALOG_H

#include <QDialog>
#include <QtSql>
#include <studentchangepassworddialog.h>
#include <showstudenteraelistdialog.h>

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

private:
    Ui::StudentMainDialog *ui;
    StudentChangePasswordDialog *stuChangeDialog;
    ShowStudentEraeListDialog *showStuEraListDialog;
};

#endif // STUDENTMAINDIALOG_H
