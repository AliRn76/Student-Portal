#ifndef SHOWERAELISTDIALOG_H
#define SHOWERAELISTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QtCore>
#include <QtGui>

namespace Ui {
class ShowEraeListDialog;
}

class ShowEraeListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowEraeListDialog(QWidget *parent = nullptr);
    ~ShowEraeListDialog();

private:
    Ui::ShowEraeListDialog *ui;
    QSqlQueryModel *qry;
};

#endif // SHOWERAELISTDIALOG_H
