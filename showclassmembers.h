#ifndef SHOWCLASSMEMBERS_H
#define SHOWCLASSMEMBERS_H

#include <QDialog>
#include <QtSql>
#include <sendjozvedialog.h>
#include <teacherchangepassword.h>

namespace Ui {
class ShowClassMembers;
}

class ShowClassMembers : public QDialog
{
    Q_OBJECT

public:
    explicit ShowClassMembers(QWidget *parent = nullptr);
    ~ShowClassMembers();

private:
    Ui::ShowClassMembers *ui;
    QSqlQueryModel *model;
};

#endif // SHOWCLASSMEMBERS_H
