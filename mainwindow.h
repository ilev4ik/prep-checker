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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void startNewGame();
    int correct() const;
    int errors() const;
    int answered() const;
    int totalPrepPhotos() const;
    void showCurrentStats();
    ~MainWindow();

private:
    void readPreps();
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
};

#endif // MAINWINDOW_H
