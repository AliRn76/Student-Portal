#ifndef TEACHERSECONDMAINDIALOG_H
#define TEACHERSECONDMAINDIALOG_H

#include <QWidget>
#include <QDialog>
#include <teacherchangepassword.h>
#include <sendjozvedialog.h>
#include <showclassmembers.h>

namespace Ui {
class teachersecondmaindialog;
}

class teachersecondmaindialog : public QWidget
{
    Q_OBJECT

public:
    explicit teachersecondmaindialog(QWidget *parent = nullptr);
    ~teachersecondmaindialog();

private:
    Ui::teachersecondmaindialog *ui;
};

#endif // TEACHERSECONDMAINDIALOG_H
