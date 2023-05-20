#include "MainWindow.hpp"
#include "../Machine/Database.hpp"
#include "../Machine/Machine.hpp"
#include "./ui_MainWindow.h"
#include "DlgNewMachine.hpp"
#include <QList>
#include <QString>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    // Machine table settings
    //
    ui->TableMachines->setColumnCount(COLUMN_COUNT);
    ui->TableMachines->setShowGrid(true);
    ui->TableMachines->setSortingEnabled(false);
    ui->TableMachines->setAlternatingRowColors(true);
    ui->TableMachines->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableMachines->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableMachines->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableMachines->horizontalHeader()->setStretchLastSection(true);
    ui->TableMachines->verticalHeader()->setVisible(false);

    // Headers
    QList<QString> Labels;
    Labels << tr("Type") << tr("Serial") << tr("Dev. Step") << tr("Line") << tr("Customer") << tr("Country") << tr("Created") << tr("Modified");
    ui->TableMachines->setHorizontalHeaderLabels(Labels);

    // Connections
    connect(ui->ButtonNewMachine, &QPushButton::clicked, this, [this]() { newMachine(); });
    connect(ui->TableMachines, &QTableWidget::itemDoubleClicked, this, [this]() { machineDoubleClicked(); });
}

MainWindow::~MainWindow()
{
    // Delete the singleton here and not in main(), because in some implementation, QCoreApplication does not return
    Database::release();
    delete ui;
}

void MainWindow::newMachine()
{
    Machine* machine = DlgNewMachine::newMachine(this);
    if (machine != nullptr) {
        addMachineInMainUI(machine);
    }
}

void MainWindow::addMachineInMainUI(Machine* machine)
{
    QTableWidgetItem* ItemType     = new QTableWidgetItem(machine->type());
    QTableWidgetItem* ItemSN       = new QTableWidgetItem(QString("%1/%2").arg(machine->serialNumber1()).arg(machine->serialNumber2()));
    QTableWidgetItem* ItemDevStep  = new QTableWidgetItem(QString("%1").arg(machine->devStep()));
    QTableWidgetItem* ItemLine     = new QTableWidgetItem(machine->line());
    QTableWidgetItem* ItemCustomer = new QTableWidgetItem(machine->customer());
    QTableWidgetItem* ItemCountry  = new QTableWidgetItem(machine->country());
    QTableWidgetItem* ItemCreated  = new QTableWidgetItem(machine->created().toString());
    QTableWidgetItem* ItemModified = new QTableWidgetItem(machine->lastModified().toString());

    ui->TableMachines->blockSignals(true); // Prevent sorting while the table is updated

    int Row = ui->TableMachines->rowCount();
    ui->TableMachines->setRowCount(Row + 1);
    ui->TableMachines->setItem(Row, COLUMN_MACHINE_TYPE, ItemType);
    ui->TableMachines->setItem(Row, COLUMN_SERIAL, ItemSN);
    ui->TableMachines->setItem(Row, COLUMN_DEVSTEP, ItemDevStep);
    ui->TableMachines->setItem(Row, COLUMN_LINE, ItemLine);
    ui->TableMachines->setItem(Row, COLUMN_CUSTOMER, ItemCustomer);
    ui->TableMachines->setItem(Row, COLUMN_COUNTRY, ItemCountry);
    ui->TableMachines->setItem(Row, COLUMN_CREATED, ItemCreated);
    ui->TableMachines->setItem(Row, COLUMN_MODIFIED, ItemModified);

    // Set the Machine ptr to the dedicated item
    ui->TableMachines->item(Row, COLUMN_DATA)
        ->setData(DATA_ROLE, QVariant::fromValue<Machine*>(machine));

    ui->TableMachines->blockSignals(false); // Enable again the signals
}

void MainWindow::machineDoubleClicked()
{
    Machine* machine;
    QList<QTableWidgetItem*> Selection = ui->TableMachines->selectedItems();
    int Row = Selection.at(0)->row();
    for (int i = 0; i < Selection.size(); i++) {
        QTableWidgetItem* item = Selection.at(i);
        if (item->column() == COLUMN_DATA) {
            machine = item->data(DATA_ROLE).value<Machine*>();
            if (DlgNewMachine::editMachine(this, machine)) {
                ui->TableMachines->item(Row, COLUMN_MACHINE_TYPE)->setText(machine->type());
                ui->TableMachines->item(Row, COLUMN_DEVSTEP)
                    ->setText(QString("%1").arg(machine->devStep()));
                ui->TableMachines->item(Row, COLUMN_COUNTRY)->setText(machine->country());
                ui->TableMachines->item(Row, COLUMN_CUSTOMER)->setText(machine->customer());
                ui->TableMachines->item(Row, COLUMN_LINE)->setText(machine->line());
                ui->TableMachines->item(Row, COLUMN_MODIFIED)
                    ->setText(machine->lastModified().toString());
            }
            break;
        }
    }
}
