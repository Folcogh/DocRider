#include "MainWindow.hpp"
#include "../Index/DocIndex.hpp"
#include "./ui_MainWindow.h"
#include "DlgEditCountry.hpp"
#include "DlgEditCustomer.hpp"
#include "TreeWidgetCountry.hpp"
#include "TreeWidgetCustomer.hpp"
#include "TreeWidgetLine.hpp"
#include "TreeWidgetMachine.hpp"
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

    // New country
    this->ActionNewCountry = new QAction(tr("New country"), this);
    connect(this->ActionNewCountry, &QAction::triggered, this, [this]() { newCountry(); });

    // New customer
    this->ActionNewCustomer = new QAction(tr("New customer"), this);
    connect(this->ActionNewCustomer, &QAction::triggered, this, [this]() { newCustomer(); });

    // New line
    this->ActionNewLine = new QAction(tr("New line"), this);
    connect(this->ActionNewLine, &QAction::triggered, this, [this]() { newLine(); });

    // New machine
    this->ActionNewMachine = new QAction(tr("New machine"), this);
    connect(this->ActionNewMachine, &QAction::triggered, this, [this]() { newMachine(); });

    //
    // Tree context menu
    //
    QList<QAction*> TreeContextMenu;
    TreeContextMenu << this->ActionNewCountry << this->ActionNewCustomer << this->ActionNewLine << this->ActionNewMachine;

    ui->TreeDoc->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TreeDoc->addActions(TreeContextMenu);

    updateTreeContextMenu();
}

MainWindow::~MainWindow()
{
    // The singletons are deleted here, because depending on the implementation,
    // QApplication::exec() doesn't return in all cases
    DocIndex::release();

    delete ui;
}


void MainWindow::updateTreeContextMenu()
{
    this->ActionNewCustomer->setEnabled(DocIndex::instance()->hasCountry());
    this->ActionNewLine->setEnabled(DocIndex::instance()->hasCustomer());
    this->ActionNewMachine->setEnabled(DocIndex::instance()->hasLine());
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
        item->setData(0, RoleCountry, QVariant::fromValue(country));
        ui->TreeDoc->addTopLevelItem(item);
        updateTreeContextMenu();
    }
}

void MainWindow::newCustomer()
{
    Customer* customer = DlgEditCustomer::newCustomer(this);
    if (customer != nullptr) {
        // DB
        Country* country = customer->country();
        country->addCustomer(customer);

        // UI
        TreeWidgetCustomer* CustomerItem = new TreeWidgetCustomer;
        CustomerItem->setText(0, customer->name());
        CustomerItem->setData(0, RoleCustomer, QVariant::fromValue(customer));

        // Find the country item and give it the customer
        for (int i = 0; i < ui->TreeDoc->topLevelItemCount(); i++) {
            QTreeWidgetItem* CountryItem = ui->TreeDoc->topLevelItem(i);
            if (CountryItem->data(0, RoleCountry).value<Country*>() == country) {
                CountryItem->addChild(CustomerItem);
            }
        }
    }
    updateTreeContextMenu();
}

void MainWindow::newLine()
{
    updateTreeContextMenu();
}

void MainWindow::newMachine()
{
    updateTreeContextMenu();
}
