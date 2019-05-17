#ifndef REMOVEERAEDARS2DIALOG_H
#define REMOVEERAEDARS2DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class RemoveEraeDars2Dialog;
}

class RemoveEraeDars2Dialog : public QDialog
{
    Q_OBJECT

public:

    static QString name;
    static QString teacherCode;
    static QString teachID;

    explicit RemoveEraeDars2Dialog(QWidget *parent = nullptr);
    ~RemoveEraeDars2Dialog();

private slots:
    void on_pushButton_choose_clicked();

    void on_pushButton_remove_clicked();

private:
    Ui::RemoveEraeDars2Dialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // REMOVEERAEDARS2DIALOG_H
