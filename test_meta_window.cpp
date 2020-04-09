#include "test_meta_window.h"
#include "ui_test_meta_window.h"

TestMetaWindow::TestMetaWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TestMetaWindow)
{
    ui->setupUi(this);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
}

Meta TestMetaWindow::meta() const
{
    Meta meta;
    meta.subject = ui->subjectEdit->text().trimmed();
    meta.theme = ui->themeEdit->text().trimmed();
    meta.author = ui->authorEdit->text().trimmed();
    meta.email = ui->emailEdit->text().trimmed();

    return meta;
}

bool TestMetaWindow::isValid() const
{
    // todo: implement validation
    return true;
}

TestMetaWindow::~TestMetaWindow()
{
    delete ui;
}
