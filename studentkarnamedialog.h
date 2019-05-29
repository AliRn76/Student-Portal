#ifndef STUDENTKARNAMEDIALOG_H
#define STUDENTKARNAMEDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class StudentKarnameDialog;
}

class StudentKarnameDialog : public QDialog
{
    Q_OBJECT

public:
    static QString stuIDKarname;

    explicit StudentKarnameDialog(QWidget *parent = nullptr);
    ~StudentKarnameDialog();

private:
    Ui::StudentKarnameDialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // STUDENTKARNAMEDIALOG_H
