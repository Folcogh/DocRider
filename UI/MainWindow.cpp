#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "../Index/DocIndex.hpp"
#include "../UI/DlgEditCountry.hpp"
#include <QMenu>
#include <QTreeWidget>
#include <QTreeWidgetItem>

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
    connect(ActionNewCountry, &QAction::triggered, [this]() { newCountry(); });

    //
    // Tree context menu
    //
    QList<QAction*> TreeContextMenu;
    TreeContextMenu << ActionNewCountry;

    ui->TreeDoc->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->TreeDoc->addActions(TreeContextMenu);
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
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, country->name());
        ui->TreeDoc->addTopLevelItem(item);
    }
}
