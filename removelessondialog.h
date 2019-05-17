#ifndef REMOVELESSONDIALOG_H
#define REMOVELESSONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showlessondialog.h>
#include <QDebug>

namespace Ui {
class RemoveLessonDialog;
}

class RemoveLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveLessonDialog(QWidget *parent = nullptr);
    ~RemoveLessonDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_showAllStu_clicked();

private:
    Ui::RemoveLessonDialog *ui;
    ShowLessonDialog *showLessDialog;
};

#endif // REMOVELESSONDIALOG_H
