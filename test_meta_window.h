#ifndef TEST_META_WINDOW_H
#define TEST_META_WINDOW_H

#include <QDialog>

namespace Ui {
class TestMetaWindow;
}

struct Meta
{
    QString subject;
    QString theme;
    QString author;
    QString email;
};

class TestMetaWindow : public QDialog
{
    Q_OBJECT
public:
    explicit TestMetaWindow(QWidget* parent = nullptr);
    ~TestMetaWindow();

    Meta meta() const;

private:
    bool isValid() const;

private:
    Ui::TestMetaWindow* ui;
};

#endif // TEST_META_WINDOW_H
