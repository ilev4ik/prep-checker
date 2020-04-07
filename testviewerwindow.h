#ifndef TESTVIEWERWINDOW_H
#define TESTVIEWERWINDOW_H

#include <QDialog>

namespace Ui {
class testviewerwindow;
}

class testviewerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit testviewerwindow(QWidget *parent = 0);
    ~testviewerwindow();

private:
    Ui::testviewerwindow *ui;
};

#endif // TESTVIEWERWINDOW_H
