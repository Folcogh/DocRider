#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "../Index/DocIndex.hpp"
#include "../UI/DlgEditCountry.hpp"
#include "../UI/TreeWidgetCountry.hpp"
#include <QMenu>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //======================================================================================================================================//
    //                                                                                                                                      //
    //                                                              Actions                                                                 //
    //                                                                                                                                      //
    //======================================================================================================================================//

    // New Country
    QAction* ActionNewCountry = new QAction("New country", this);
    connect(ActionNewCountry, &QAction::triggered, this, [this]() { newCountry(); });

    // New Customer
    QAction* ActionNewCustomer = new QAction("New customer", this);
    connect(ActionNewCustomer, &QAction::triggered, this, [this]() { newCustomer(); });

    // New line
    QAction* ActionNewLine = new QAction("New line", this);
    connect(ActionNewLine, &QAction::triggered, this, [this]() { newLine(); });

    // New machine
    QAction* ActionNewMachine = new QAction("New country", this);
    connect(ActionNewMachine, &QAction::triggered, this, [this]() { newMachine(); });

    //
    // Tree context menu
    //
    QList<QAction*> TreeContextMenu;
    TreeContextMenu << ActionNewCountry << ActionNewCustomer << ActionNewLine << ActionNewMachine;

    ui->TreeDoc->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TreeDoc->addActions(TreeContextMenu);

    // Update the available actions when the selection changes in the Tree
    // - the root level allows to create a country
    // - the country level allows to create a customer or a country
    // - the customer level allows to create a line, a customer or a country
    // - etc
    connect(ui->TreeDoc, &QTreeWidget::itemSelectionChanged, this, [this]() { updateTreeContextMenu(); });
}

MainWindow::~MainWindow()
{
    DocIndex::release();
    delete ui;
}

void MainWindow::newCountry()
{
    Country* country = DlgEditCountry::newCountry(this);
    if (country != nullptr) {
        // DB
        DocIndex::instance()->newCountry(country);

        // UI
        TreeWidgetCountry* item = new TreeWidgetCountry;
        item->setText(0, country->name());
        ui->TreeDoc->addTopLevelItem(item);
    }
}

void MainWindow::newCustomer()
{}

void MainWindow::newLine()
{}

void MainWindow::newMachine()
{}

void MainWindow::updateTreeContextMenu()
{}
