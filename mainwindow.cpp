#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QSettings>
#include <taglib.h>
#include <taglib/fileref.h>
#include <jack/jack.h>

#include <iostream>
#include <math.h>

#include "jack/jackclient.h"
#include "jack/jackfadermodule.h"
#include "micbutton.h"
#include "signalbus.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), optionsDialog(new OptionsDialog(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    connect(SignalBus::instance, &SignalBus::jackStateChanged, this, &MainWindow::jackStateChanged);
    connect(ui->actionExit, &QAction::triggered, [](){ QApplication::quit(); });
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::optionsActionTriggered);
}

void
MainWindow::jackStateChanged(bool checked)
{
    if (checked)
    {
        jackClient = new JackClient("PiCasterQt");
        jackClient->process();
    }
    else
    {
        jackClient->close();
        delete jackClient;
    }
}

void
MainWindow::optionsActionTriggered()
{
    if (optionsDialog->exec() == QDialog::Accepted) {
        QSettings settings;
        settings.setValue("input device", optionsDialog->getInputDevice());
        settings.setValue("output device", optionsDialog->getOutputDevice());
    }
}

