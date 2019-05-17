#ifndef EDITTEACHERDIALOG_H
#define EDITTEACHERDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <showteacherdialog.h>

namespace Ui {
class EditTeacherDialog;
}

class EditTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTeacherDialog(QWidget *parent = nullptr);
    ~EditTeacherDialog();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_showAllStudent_clicked();

    void on_pushButton_apply_clicked();

private:
    Ui::EditTeacherDialog *ui;
    ShowTeacherDialog *showTeachDialog;
};

#endif // EDITTEACHERDIALOG_H
