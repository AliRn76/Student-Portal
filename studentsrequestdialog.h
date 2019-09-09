#ifndef STUDENTSREQUESTDIALOG_H
#define STUDENTSREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class StudentsRequestDialog;
}

class StudentsRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsRequestDialog(QWidget *parent = nullptr);
    ~StudentsRequestDialog();

private:
    Ui::StudentsRequestDialog *ui;
};

#endif // STUDENTSREQUESTDIALOG_H
