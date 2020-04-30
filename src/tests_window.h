#ifndef TESTSWINDOW_H
#define TESTSWINDOW_H

#include <QDialog>

#include "test_meta_window.h"
#include "test_viewer_window.h"

namespace Ui {
class TestsWindow;
}

class TestsWindow : public QDialog
{
    Q_OBJECT
public:
    TestsWindow(QWidget* parent = nullptr);
    ~TestsWindow();

private:
    void onTestCreateClicked();
    void onTestRemoveClicked();
    void onTestEditClicked();

    void createTest(Meta&& meta, Source&& src);

private:
    Ui::TestsWindow* ui;
};

#endif // TESTSWINDOW_H
