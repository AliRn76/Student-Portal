#ifndef ENTEKHABVAHEDDIALOG_H
#define ENTEKHABVAHEDDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showstudentdialog.h>
#include <showeraelistdialog.h>

namespace Ui {
class EntekhabVahedDialog;
}

class EntekhabVahedDialog : public QDialog
{
    Q_OBJECT

public:
    QString entekhabID;
    QString lessonName;
    QString roozeHafte;
    QString fieldLesson;
    QString stuName;
    QString stuCode;
    QString fathersName;
    QString saat;
    QString teacherName;
    QString saalVoroud;

    explicit EntekhabVahedDialog(QWidget *parent = nullptr);
    ~EntekhabVahedDialog();

private slots:

    void on_pushButton_showErae_2_clicked();

    void on_pushButton_showStu_2_clicked();

    void on_pushButton_findLesson_2_clicked();

    void on_pushButton_findStu_2_clicked();

    void on_pushButton_continue_clicked();

    void on_pushButton_backPage2_clicked();

    void on_tableView_lesson_clicked(const QModelIndex &index);

private:
    Ui::EntekhabVahedDialog *ui;
    ShowStudentDialog *showStuDialog;
    ShowEraeListDialog *showEraeDialog;
    QSqlQueryModel *qryModelLesson;
    QSqlQueryModel *qryModeStu;
};

#endif // ENTEKHABVAHEDDIALOG_H
