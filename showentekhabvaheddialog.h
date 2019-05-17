#ifndef SHOWENTEKHABVAHEDDIALOG_H
#define SHOWENTEKHABVAHEDDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ShowEntekhabVahedDialog;
}

class ShowEntekhabVahedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowEntekhabVahedDialog(QWidget *parent = nullptr);
    ~ShowEntekhabVahedDialog();

private:
    Ui::ShowEntekhabVahedDialog *ui;
    QSqlQueryModel *qryModel;
};

#endif // SHOWENTEKHABVAHEDDIALOG_H
