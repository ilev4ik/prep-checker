#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <random>

#include <QMainWindow>
#include "prep.h"


namespace Ui {
    class MainWindow;
}

class QLabel;
class QListWidgetItem;
class XmlParserHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void startNewGame();
    void loadTest();
    int correct() const;
    int errors() const;
    int answered() const;
    int totalPrepPhotos() const;
    void showCurrentStats();
    QString propmtTestLocation();
    ~MainWindow();

private:
    bool tryReadPreps(const QString& xmlPath);
    void initList();
    void initEtalon();
    void resetStats();
    void skipPrep();
    void getNextPrep();

    void markError(Prep prep);
    void markCorrect();

    void onItemSelected(QListWidgetItem* selected);
    std::vector<Prep>::iterator pickRandomPrep();
    std::vector<Prep>::iterator preLastAnswered();

    void reinitWithErrors();
    void setPrepPic(const QString& picPath);

private:
    Ui::MainWindow *ui;
    QLabel* imgLabel;
    std::random_device rd;
    std::mt19937 gen;
    std::vector<Prep> gamePreps;
    std::vector<Prep>::iterator current_pick_it;

    std::vector<Prep> errorsVec;

    //subject id -> pics
    std::map<int, std::vector<Prep>> etalonPreps;
    XmlParserHandler* xmlHandler;
};

#endif // MAINWINDOW_H
