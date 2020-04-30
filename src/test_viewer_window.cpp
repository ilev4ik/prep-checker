#include "test_viewer_window.h"
#include "ui_test_viewer_window.h"

#include "object_entry_window.h"

TestViewerWindow::TestViewerWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TestViewerWindow)
{
    ui->setupUi(this);
    connect(ui->addObjectBtn, &QPushButton::clicked, this, &TestViewerWindow::onAddObjectClicked);
}

TestViewerWindow::TestViewerWindow(const Source& src, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TestViewerWindow)
{
    ui->setupUi(this);
}

TestViewerWindow::~TestViewerWindow()
{
    delete ui;
}

Source TestViewerWindow::source() const
{
    // obtain source from table model
    return {};
}

void TestViewerWindow::onAddObjectClicked()
{
    ObjectEntryWindow objectEntry;
    objectEntry.exec();
}
