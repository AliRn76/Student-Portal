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
    static QString stuID;

    explicit StudentEntekhabVahedDialog(QWidget *parent = nullptr);
    ~StudentEntekhabVahedDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_remove_clicked();

    void on_treeView_acceptedLesson_clicked(const QModelIndex &index);

private:
    Ui::StudentEntekhabVahedDialog *ui;
    QSqlQueryModel *qryModel;
    QSqlQueryModel *qryModel2;
    QSqlQueryModel *qryModel3;
    QSqlQueryModel *qryModel4;
    QSqlQueryModel *qryModel5;
};

#endif // STUDENTENTEKHABVAHEDDIALOG_H
