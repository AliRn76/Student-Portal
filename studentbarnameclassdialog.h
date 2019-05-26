#ifndef STUDENTBARNAMECLASSDIALOG_H
#define STUDENTBARNAMECLASSDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class StudentBarnameClassDialog;
}

class StudentBarnameClassDialog : public QDialog
{
    Q_OBJECT

public:

    static QString stuCodeBarname;

    explicit StudentBarnameClassDialog(QWidget *parent = nullptr);
    ~StudentBarnameClassDialog();

private:
    Ui::StudentBarnameClassDialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // STUDENTBARNAMECLASSDIALOG_H
