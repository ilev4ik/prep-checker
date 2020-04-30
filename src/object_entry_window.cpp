#include "object_entry_window.h"
#include "ui_object_entry_window.h"

ObjectEntryWindow::ObjectEntryWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ObjectEntryWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}
