#ifndef SENDJOZVEDIALOG_H
#define SENDJOZVEDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class SendJozveDialog;
}

class SendJozveDialog : public QDialog
{
    Q_OBJECT

public:
    static QString lessCode ;

    explicit SendJozveDialog(QWidget *parent = nullptr);
    ~SendJozveDialog();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_Send_clicked();

private:
    Ui::SendJozveDialog *ui;
};

#endif // SENDJOZVEDIALOG_H
