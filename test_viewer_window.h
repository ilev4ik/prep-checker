#ifndef TESTVIEWERWINDOW_H
#define TESTVIEWERWINDOW_H

#include "prep.h"
#include <QDialog>

namespace Ui {
class TestViewerWindow;
}

using Source = std::vector<Prep>;

class TestViewerWindow : public QDialog
{
    Q_OBJECT
public:
    explicit TestViewerWindow(QWidget* parent = 0);
    explicit TestViewerWindow(const Source& src, QWidget* parent = nullptr);
    ~TestViewerWindow();

    Source source() const;

private:
    void onAddObjectClicked();

private:
    Ui::TestViewerWindow* ui;
};

#endif // TESTVIEWERWINDOW_H
