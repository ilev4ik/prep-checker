#include "testviewerwindow.h"
#include "ui_testviewerwindow.h"

testviewerwindow::testviewerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testviewerwindow)
{
    ui->setupUi(this);
}

testviewerwindow::~testviewerwindow()
{
    delete ui;
}
