#ifndef EDITLESSONDIALOG_H
#define EDITLESSONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showlessondialog.h>

namespace Ui {
class EditLessonDialog;
}

class EditLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLessonDialog(QWidget *parent = nullptr);
    ~EditLessonDialog();

private slots:
    void on_pushButton_showLesson_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_apply_clicked();

private:
    Ui::EditLessonDialog *ui;
    ShowLessonDialog *showLessDialog;
};

#endif // EDITLESSONDIALOG_H
