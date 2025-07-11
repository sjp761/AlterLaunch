#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <QString>
#include <QProcess>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->launchButton, &QPushButton::clicked, this, [this]() {
        launchGameExe(QString::fromStdString(gameExe));
    });
    connect(ui->changeEXEButton, &QPushButton::clicked, this, &MainWindow::changeGameExe);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchGameExe(const QString &exePath)
{
    if (gameExe.empty()) {
        std::cout << "Error: No game executable specified" << std::endl;
        return;
    }
    
    QProcess *process = new QProcess(this);
    
    QStringList arguments;
    arguments << "--verb=waitforexitandrun";
    arguments << "--";
    arguments << QString::fromStdString(protonExe);
    arguments << "waitforexitandrun";
    arguments << QString::fromStdString(gameExe);
    
    if (!gameParams.empty()) {
        QStringList gameArgs = QString::fromStdString(gameParams).split(" ", Qt::SkipEmptyParts);
        arguments << gameArgs;
    }
    
    std::cout << "Launching game with command: " << slrPath << std::endl;
    std::cout << "Arguments: ";
    for (const QString &arg : arguments) {
        std::cout << arg.toStdString() << " ";
    }
    std::cout << std::endl;
    
    process->start(QString::fromStdString(slrPath), arguments);
    
    if (!process->waitForStarted(3000)) {
        std::cout << "Failed to start process: " << process->errorString().toStdString() << std::endl;
        process->deleteLater();
    }
}

void MainWindow::setGameLaunchInfo(char *argv[])
{
    if (argv[1]) {
        gameExe = argv[1];
        std::cout << "Game executable set to: " << gameExe << std::endl;
    }
    if (argv[2]) {
        gameParams = argv[2];
        std::cout << "Game parameters set to: " << gameParams << std::endl;
    }
    refreshGameInfoBox();
}

void MainWindow::refreshGameInfoBox()
{
    QString info = "Steam Linux Runtime Path: " + QString::fromStdString(slrPath) + "\n";
    info += "Proton Path: " + QString::fromStdString(protonExe) + "\n";
    info += "Game EXE: " + QString::fromStdString(gameExe) + "\n";
    if (!gameParams.empty()) {
        info += "Parameters: " + QString::fromStdString(gameParams) + "\n";
    }
    ui->gameInfoBox->setText(info);
}

void MainWindow::changeGameExe()
{
    QString newExe = QFileDialog::getOpenFileName(this, "Select Game Executable", QString(), "Executable Files (*.exe *.sh)");
    if (!newExe.isEmpty()) {
        gameExe = newExe.toStdString();
        std::cout << "Game executable changed to: " << gameExe << std::endl;
        refreshGameInfoBox();
    }
}
