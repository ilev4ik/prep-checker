#include "testswindow.h"

TestsWindow::TestsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TestsWindow)
{
    ui->setupUi(this);
}

TestsWindow::~TestsWindow()
{
    delete ui;
}
