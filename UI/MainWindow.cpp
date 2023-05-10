#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connections
    connect(ui->ButtonNewMachine, &QPushButton::clicked, this, [this]() { newMachine(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newMachine()
{
    DlgNewMachine *dlg = new DlgNewMachine(this);
    if (dlg->exec() == QDialog::accepted) {
    }
    delete dlg;
    // update machine
}
