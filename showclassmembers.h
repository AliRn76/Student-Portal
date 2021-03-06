#ifndef SHOWCLASSMEMBERS_H
#define SHOWCLASSMEMBERS_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class ShowClassMembers;
}

class ShowClassMembers : public QDialog
{
    Q_OBJECT

public:
    int NumberOfRow_Student;
    int StuNumber;
    float score ;
    QString StuCode ;
    QString firstname;
    QString lastname;
    static QString LessonCode;
    static QString LessonName;

    explicit ShowClassMembers(QWidget *parent = nullptr);
    ~ShowClassMembers();

private slots:
    void on_tableView_Student_clicked(const QModelIndex &index);

    void on_pushButton_exit_clicked();

    void on_pushButton_SetScore_clicked();

private:
    Ui::ShowClassMembers *ui;
    QSqlQueryModel *model;
};

#endif // SHOWCLASSMEMBERS_H
