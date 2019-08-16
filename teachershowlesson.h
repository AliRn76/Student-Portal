#ifndef TEACHERSHOWLESSON_H
#define TEACHERSHOWLESSON_H

#include <QDialog>

namespace Ui {
class teachershowlesson;
}

class teachershowlesson : public QDialog
{
    Q_OBJECT

public:
    explicit teachershowlesson(QWidget *parent = nullptr);
    ~teachershowlesson();

private:
    Ui::teachershowlesson *ui;
};

#endif // TEACHERSHOWLESSON_H
