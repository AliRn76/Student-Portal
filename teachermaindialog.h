#ifndef TEACHERMAINDIALOG_H
#define TEACHERMAINDIALOG_H

#include <QDialog>

namespace Ui {
class TeacherMainDialog;
}

class TeacherMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherMainDialog(QWidget *parent = nullptr);
    ~TeacherMainDialog();

private:
    Ui::TeacherMainDialog *ui;
};

#endif // TEACHERMAINDIALOG_H
