#include "DlgEditCustomer.hpp"
#include "../Index/DocIndex.hpp"
#include "ui_DlgEditCustomer.h"
#include <QList>
#include <QVariant>

DlgEditCustomer::DlgEditCustomer(QWidget* parent, QString title, Customer* customer)
    : QDialog(parent)
    , ui(new Ui::DlgEditCustomer)
{
    ui->setupUi(this);
    setWindowTitle(title);

    // Populate the country combo box
    QList<Country*> Countries = DocIndex::instance()->countryList();
    for (int i = 0; i < Countries.size(); i++) {
        ui->ComboCountry->addItem(Countries.at(i)->name(), QVariant::fromValue(Countries.at(i)));
    }

    // Connections
    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });

    // Specificities for new/edited customer name
    if (customer == nullptr) {
        connect(ui->EditCustomer, &QLineEdit::textEdited, this, [this]() { updateUI(); });
        connect(ui->ComboCountry, &QComboBox::currentIndexChanged, this, [this]() { updateUI(); });
    }
    else {
        ui->ComboCountry->setEnabled(false);
        connect(ui->EditCustomer, &QLineEdit::textEdited, this, [this, customer]() { updateUI(customer); });
        connect(ui->ComboCountry, &QComboBox::currentIndexChanged, this, [this, customer]() { updateUI(customer); });
    }
}

DlgEditCustomer::~DlgEditCustomer()
{
    delete ui;
}

Customer* DlgEditCustomer::newCustomer(QWidget* parent)
{
    Customer*        customer = nullptr;
    DlgEditCustomer* dlg      = new DlgEditCustomer(parent, "New customer");

    if (dlg->exec() == QDialog::Accepted) {
        Country* country = dlg->ui->ComboCountry->currentData().value<Country*>();
        QString  name    = dlg->ui->EditCustomer->text();
        customer         = new Customer(country, name);
    }
    delete dlg;
    return customer;
}

void DlgEditCustomer::updateUI()
{
    Country* country = ui->ComboCountry->currentData().value<Country*>();
    QString  name    = ui->EditCustomer->text();
    bool     valid   = country->validateNewCustomerName(name);
    ui->ButtonOK->setEnabled(valid);
}

void DlgEditCustomer::updateUI(Customer* customer)
{
    Country* country = ui->ComboCountry->currentData().value<Country*>();
    QString  name    = ui->EditCustomer->text();
    bool     valid   = country->validateEditedCustomerName(customer, name);
    ui->ButtonOK->setEnabled(valid);
}
