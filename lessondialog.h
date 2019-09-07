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

    void on_pushButton_searchTab2_clicked();

    void on_pushButton_apply_Tab2_clicked();

    void on_pushButton_showLessonsTab2_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_removeTab3_clicked();

    void on_pushButton_showLessonsTab3_clicked();

private:
    Ui::AddLessonDialog *ui;
    ShowLessonDialog *showLessDialog;
};

#endif // ADDLESSONDIALOG_H
