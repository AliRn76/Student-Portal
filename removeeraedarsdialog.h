#ifndef REMOVEERAEDARSDIALOG_H
#define REMOVEERAEDARSDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <removeeraedars2dialog.h>

namespace Ui {
class RemoveEraeDarsDialog;
}

class RemoveEraeDarsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveEraeDarsDialog(QWidget *parent = nullptr);
    ~RemoveEraeDarsDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_choose_clicked();

    void on_pushButton_nextPage_clicked();

private:
    Ui::RemoveEraeDarsDialog *ui;
    QSqlQueryModel *qryModel;
    RemoveEraeDars2Dialog *rmvErae2Dialog;
};

#endif // REMOVEERAEDARSDIALOG_H
