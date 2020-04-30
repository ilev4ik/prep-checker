#include "tests_window.h"
#include "ui_tests_window.h"

TestsWindow::TestsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TestsWindow)
{
    ui->setupUi(this);
    connect(ui->createTestBtn, &QPushButton::clicked, this, &TestsWindow::onTestCreateClicked);
    connect(ui->removeTestBtn, &QPushButton::clicked, this, &TestsWindow::onTestRemoveClicked);
    connect(ui->editTestBtn, &QPushButton::clicked, this, &TestsWindow::onTestEditClicked);
}

TestsWindow::~TestsWindow()
{
    delete ui;
}

void TestsWindow::onTestCreateClicked()
{
    // sample code
    TestMetaWindow metaWindow(this);
    if (!metaWindow.exec()) {
        return;
    }

    auto meta = metaWindow.meta();

    TestViewerWindow createWindow(this);
    if (!createWindow.exec()) {
        return;
    }

    auto src = createWindow.source();

    createTest(std::move(meta), std::move(src));
}

void TestsWindow::createTest(Meta&& meta, Source&& src)
{
    // add row to table
}

void TestsWindow::onTestRemoveClicked()
{
    // remove test from table
}

void TestsWindow::onTestEditClicked()
{
    Source dummySrc;
    // get selected row Source

    TestViewerWindow testEditor(dummySrc, this);
    if (testEditor.exec()) {
        // valid edition
        return;
    }
}


