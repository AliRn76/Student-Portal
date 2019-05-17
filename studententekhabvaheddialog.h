#ifndef STUDENTENTEKHABVAHEDDIALOG_H
#define STUDENTENTEKHABVAHEDDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class StudentEntekhabVahedDialog;
}

class StudentEntekhabVahedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentEntekhabVahedDialog(QWidget *parent = nullptr);
    ~StudentEntekhabVahedDialog();

private:
    Ui::StudentEntekhabVahedDialog *ui;

};

#endif // STUDENTENTEKHABVAHEDDIALOG_H
