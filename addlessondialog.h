#ifndef ADDLESSONDIALOG_H
#define ADDLESSONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showlessondialog.h>

namespace Ui {
class AddLessonDialog;
}

class AddLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLessonDialog(QWidget *parent = nullptr);
    ~AddLessonDialog();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_showAllCourses_clicked();

private:
    Ui::AddLessonDialog *ui;
    ShowLessonDialog *showLessDialog;
};

#endif // ADDLESSONDIALOG_H
