#ifndef ERAEDARSDIALOG_H
#define ERAEDARSDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <showteacherdialog.h>
#include <showlessondialog.h>
#include <QSqlRecord>
#include <QDebug>
#include <showeraelistdialog.h>
#include <QtCore>

namespace Ui {
class EraeDarsDialog;
}

class EraeDarsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EraeDarsDialog(QWidget *parent = nullptr);
    ~EraeDarsDialog();

private slots:
    void on_pushButton_showTeach_clicked();

    void on_pushButton_findTeach_clicked();

    void on_pushButton_showLesson_clicked();

    void on_pushButton_findLesson_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_clicked();

private:
    Ui::EraeDarsDialog *ui;
    ShowTeacherDialog *showTeachDialog;
    ShowLessonDialog *showLessDialog;
    ShowEraeListDialog *showEraeDialog;

};

#endif // ERAEDARSDIALOG_H
