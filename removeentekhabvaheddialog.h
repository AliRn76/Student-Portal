#ifndef REMOVEENTEKHABVAHEDDIALOG_H
#define REMOVEENTEKHABVAHEDDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <removeentekhabvahed2dialog.h>

namespace Ui {
class RemoveEntekhabVahedDialog;
}

class RemoveEntekhabVahedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveEntekhabVahedDialog(QWidget *parent = nullptr);
    ~RemoveEntekhabVahedDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_choose_clicked();

    void on_pushButton_nextPage_clicked();

private:
    Ui::RemoveEntekhabVahedDialog *ui;
    QSqlQueryModel *qryModel;
    RemoveEntekhabVahed2Dialog *rmvEntekhab2Dialog;
};

#endif // REMOVEENTEKHABVAHEDDIALOG_H
