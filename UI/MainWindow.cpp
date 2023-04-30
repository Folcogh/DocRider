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
        // DB
        DocIndex::instance()->newCountry(country);

        // UI
        TreeWidgetCountry* item = new TreeWidgetCountry;
        item->setText(0, country->name());
        ui->TreeDoc->addTopLevelItem(item);
    }
}
