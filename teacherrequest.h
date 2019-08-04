#ifndef TEACHERREQUEST_H
#define TEACHERREQUEST_H

#include <QDialog>

namespace Ui {
class teacherRequest;
}

class teacherRequest : public QDialog
{
    Q_OBJECT

public:
    static int whichpage ;
    explicit teacherRequest(QWidget *parent = nullptr);
    ~teacherRequest();

private:
    Ui::teacherRequest *ui;
};

#endif // TEACHERREQUEST_H
