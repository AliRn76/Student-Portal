#ifndef SHOWSTUDENTERAELISTDIALOG_H
#define SHOWSTUDENTERAELISTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QtCore>
#include <QMessageBox>

namespace Ui {
class ShowStudentEraeListDialog;
}

class ShowStudentEraeListDialog : public QDialog
{
    Q_OBJECT

public:

    static QString stuField;

    explicit ShowStudentEraeListDialog(QWidget *parent = nullptr);
    ~ShowStudentEraeListDialog();

private:
    Ui::ShowStudentEraeListDialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // SHOWSTUDENTERAELISTDIALOG_H
