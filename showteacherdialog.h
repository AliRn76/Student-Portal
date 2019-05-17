#ifndef SHOWTEACHERDIALOG_H
#define SHOWTEACHERDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ShowTeacherDialog;
}

class ShowTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTeacherDialog(QWidget *parent = nullptr);
    ~ShowTeacherDialog();

private:
    Ui::ShowTeacherDialog *ui;
    QSqlQueryModel *qry;
};

#endif // SHOWTEACHERDIALOG_H
