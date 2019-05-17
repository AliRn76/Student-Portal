#ifndef SHOWSTUDENTDIALOG_H
#define SHOWSTUDENTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <windows.h>

namespace Ui {
class ShowStudentDialog;
}

class ShowStudentDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ShowStudentDialog(QWidget *parent = nullptr);
    ~ShowStudentDialog();

private slots:

private:
    Ui::ShowStudentDialog *ui;
    QSqlQueryModel *qry;
};

#endif // SHOWSTUDENTDIALOG_H
