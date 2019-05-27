#ifndef STUDENTCHANGEPASSWORDDIALOG_H
#define STUDENTCHANGEPASSWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class StudentChangePasswordDialog;
}

class StudentChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:

    static QString strUserStu;

    explicit StudentChangePasswordDialog(QWidget *parent = nullptr);
    ~StudentChangePasswordDialog();

private slots:

    void on_pushButton_change_clicked();

private:
    Ui::StudentChangePasswordDialog *ui;
};

#endif // STUDENTCHANGEPASSWORDDIALOG_H
