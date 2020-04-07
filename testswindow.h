#ifndef TESTSWINDOW_H
#define TESTSWINDOW_H

#include "ui_testswindow.h"

class TestsWindow : public QDialog
{
public:
    TestsWindow(QWidget* parent = nullptr);
    ~TestsWindow();
private:
    Ui::TestsWindow* ui;
};

#endif // TESTSWINDOW_H
