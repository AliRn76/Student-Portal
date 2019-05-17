#ifndef SHOWLESSONDIALOG_H
#define SHOWLESSONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class ShowLessonDialog;
}

class ShowLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowLessonDialog(QWidget *parent = nullptr);
    ~ShowLessonDialog();

private:
    Ui::ShowLessonDialog *ui;
    QSqlQueryModel *qry;
};

#endif // SHOWLESSONDIALOG_H
