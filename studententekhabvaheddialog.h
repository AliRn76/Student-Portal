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

    static QString stuCode;
    static QString stuFieldEntekhab;

    explicit StudentEntekhabVahedDialog(QWidget *parent = nullptr);
    ~StudentEntekhabVahedDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_apply_clicked();

private:
    Ui::StudentEntekhabVahedDialog *ui;
    QSqlQueryModel *qryModel;
    QSqlQueryModel *qryModel2;
};

#endif // STUDENTENTEKHABVAHEDDIALOG_H
