#ifndef EMPLOYEECHANGEPASSWORDDIALOG_H
#define EMPLOYEECHANGEPASSWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class EmployeeChangePasswordDialog;
}

class EmployeeChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:

    static QString strUserEmp ;

    explicit EmployeeChangePasswordDialog(QWidget *parent = nullptr);
    ~EmployeeChangePasswordDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmployeeChangePasswordDialog *ui;
};

#endif // EMPLOYEECHANGEPASSWORDDIALOG_H
