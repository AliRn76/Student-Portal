#ifndef REMOVEENTEKHABVAHED2DIALOG_H
#define REMOVEENTEKHABVAHED2DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class RemoveEntekhabVahed2Dialog;
}

class RemoveEntekhabVahed2Dialog : public QDialog
{
    Q_OBJECT

public:
    static QString name;
    static QString studentCode;
    static QString stuID;

    explicit RemoveEntekhabVahed2Dialog(QWidget *parent = nullptr);
    ~RemoveEntekhabVahed2Dialog();

private slots:

    void on_pushButton_choose_clicked();

    void on_pushButton_remove_clicked();

private:
    Ui::RemoveEntekhabVahed2Dialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // REMOVEENTEKHABVAHED2DIALOG_H
