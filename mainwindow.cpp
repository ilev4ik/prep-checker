#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xml_parser_handler.h"
#include "xml_schema_validator.h"

#include <algorithm>

#include <QListWidgetItem>
#include <QDateTime>
#include <QListWidget>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QLabel>
#include <QStandardPaths>

// xml stuff
#include <QXmlSimpleReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , imgLabel(new QLabel)
    , rd()
    , gen(rd())
    , xmlHandler(new XmlParserHandler(etalonPreps))
{
    ui->setupUi(this);
    setWindowTitle(tr("Проверка препаратов"));
    ui->centralWidget->setLayout(ui->verticalLayout);
    ui->horizontalLayout->setStretch(0, 4);
    ui->horizontalLayout->setStretch(1, 2);
    resetStats();

    connect(ui->a_newGame, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(ui->a_onlyErrors, &QAction::triggered, this, &MainWindow::reinitWithErrors);
    connect(ui->a_currentStats, &QAction::triggered, this, &MainWindow::showCurrentStats);
    connect(ui->a_loadTest, &QAction::triggered, this, &MainWindow::propmtTestLocation);
    connect(ui->skipBtn, &QPushButton::clicked, this, &MainWindow::skipPrep);
    connect(ui->ansList, &QListWidget::itemDoubleClicked, this, &onItemSelected);

    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgLabel->setScaledContents(true);

    ui->scrollArea->setWidget(imgLabel);

    ui->progress->setFormat("%v/%m");

    gen.seed(QDateTime::currentMSecsSinceEpoch() % 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete xmlHandler;
}

void MainWindow::startNewGame()
{
    if (tryReadPreps(QDir::fromNativeSeparators(propmtTestLocation())))
    {
        ui->ansList->clear();
        resetStats();
        initList();
        initEtalon();
        getNextPrep();
    }
}

void MainWindow::reinitWithErrors()
{
    if (errors() == 0) {
        QMessageBox::information(this, tr("Запуск только ошибок"),
                                 tr("Ошибок не было найдено"), QMessageBox::Ok);
        return;
    }

    auto errorVecTemp = errorsVec;
    resetStats();

    gamePreps = errorVecTemp;
    ui->progress->setMaximum(gamePreps.size());
    getNextPrep();
}

void MainWindow::initEtalon()
{
    for (const auto& subject : etalonPreps) {
        const auto& subjectVec = subject.second;
        std::copy(subjectVec.begin(), subjectVec.end(), std::back_inserter(gamePreps));
    }
}

void MainWindow::onItemSelected(QListWidgetItem* selected)
{
    int subjectId = selected->data(Qt::UserRole + 1).toInt();
    if (subjectId == current_pick_it->subjectId) {
        markCorrect();
    } else {
        markError(*current_pick_it);
    }

    ui->remainCount->setText(QString::number(totalPrepPhotos() - answered()));
    std::iter_swap(current_pick_it, preLastAnswered());
    getNextPrep();
}

void MainWindow::showCurrentStats()
{
    QMessageBox::information(this, tr("Статистика"),
                          tr("Верных ответов: %1\nОшибок: %2\nВ меню можно перезапустить тест только для ошибок!")
                          .arg(correct()).arg(errors())
                             );
}

QString MainWindow::propmtTestLocation()
{
    auto standardPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    auto path = QFileDialog::getOpenFileName(this, tr("Выбор файла теста"),
                                              standardPaths.isEmpty() ? "" : standardPaths[0],
                                              tr("XML files (*.xml)"));
    return path;
}

void MainWindow::skipPrep()
{
    getNextPrep();
}

void MainWindow::setPrepPic(const QString& picPath)
{
    imgLabel->setPixmap(QPixmap(picPath));
    imgLabel->resize(imgLabel->pixmap()->size());
    imgLabel->update();
}

void MainWindow::getNextPrep()
{
    if (answered() == totalPrepPhotos()) {
        showCurrentStats();
        return;
    }

    current_pick_it = pickRandomPrep();
    if (current_pick_it != gamePreps.end()) {
        setPrepPic(current_pick_it->picPath);
    }
}

int MainWindow::totalPrepPhotos() const
{
    return ui->progress->maximum();
}

std::vector<Prep>::iterator MainWindow::pickRandomPrep()
{
    if (answered() < totalPrepPhotos()) {
        int a = answered();
        int to = gamePreps.size() - 1 - a;
        std::uniform_int_distribution<> dis(0, to);
        return gamePreps.begin() + dis(gen);
    }

    return gamePreps.end();
}


void MainWindow::markError(Prep prep)
{
    ui->errorCount->setText(QString::number(errors() + 1));
    errorsVec.push_back(prep);
    QMessageBox::warning(this, tr("Неверный ответ"),
                         tr("Верный ответ: %1").arg(prep.name), QMessageBox::Ok);
}

void MainWindow::markCorrect()
{
    ui->progress->setValue(correct() + 1);
}

std::vector<Prep>::iterator MainWindow::preLastAnswered()
{
    return gamePreps.end() - answered();
}

int MainWindow::correct() const
{
    return ui->progress->value();
}

int MainWindow::errors() const
{
    return ui->errorCount->text().toInt();
}

int MainWindow::answered() const
{
    return correct() + errors();
}

void MainWindow::resetStats()
{
    errorsVec.clear();
    gamePreps.clear();
    ui->progress->setValue(0);
    ui->errorCount->setText(QString::number(0));
    ui->remainCount->setText(QString::number(0));
    current_pick_it = gamePreps.end();
}

void MainWindow::initList()
{
    for (const auto& prep : etalonPreps) {
        const auto& preps = prep.second;
        auto* item = new QListWidgetItem(preps[0].name);
        item->setData(Qt::UserRole + 1, preps[0].subjectId);
        ui->ansList->addItem(item);
    }

    //ui->ansList->sortItems();
}

bool MainWindow::tryReadPreps(QString xmlPath)
{
    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Не удалось открыть xml-файл %1").arg(xmlPath),
                              QMessageBox::Ok);
        return false;
    }

    QString errorMsg;
    if (!XmlSchemaValidator::validate(xmlFile, errorMsg))
    {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("xml-файл имеет неправильную структуру %1:\n%2").arg(xmlPath).arg(errorMsg),
                              QMessageBox::Ok);
        return false;
    }

    xmlFile.seek(0);

    // etalonPreps here to be read
    etalonPreps.clear();
    QXmlSimpleReader xmlReader;
    xmlHandler->setFileInfo(xmlPath);
    QXmlInputSource source(&xmlFile);
    xmlReader.setContentHandler(xmlHandler);
    xmlReader.parse(&source);

    ui->progress->setRange(0, xmlHandler->loadedSubjects());
    return true;
}
