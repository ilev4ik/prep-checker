#ifndef OBJECT_ENTRY_WINDOW_H
#define OBJECT_ENTRY_WINDOW_H

#include <QDialog>

namespace Ui {
class ObjectEntryWindow;
}

class ObjectEntryWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ObjectEntryWindow(QWidget* parent = nullptr);

private:
    Ui::ObjectEntryWindow* ui;
};

#endif // OBJECT_ENTRY_WINDOW_H
