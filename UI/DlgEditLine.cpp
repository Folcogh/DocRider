#include "DlgEditLine.hpp"
#include "../Index/Country.hpp"
#include "../Index/Customer.hpp"
#include "../Index/DocIndex.hpp"
#include "MainWindow.hpp"
#include "ui_DlgEditLine.h"

DlgEditLine::DlgEditLine(QWidget* parent, QString title, Line* line)
    : QDialog(parent)
    , ui(new Ui::DlgEditLine)
{
    ui->setupUi(this);
    setWindowTitle(title);


    // Connections
    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });

    // Specificities for new/edited lines
    if (line == nullptr) {
        // Line creation: the country combo box is populated with the available countries,
        // then the customer combo box is populated according to the current country

        // Populate the country combo box
        QList<Country*> Countries = DocIndex::instance()->countryList();
        for (int i = 0; i < Countries.size(); i++) {
            ui->ComboCountry->addItem(Countries.at(i)->name(), QVariant::fromValue(Countries.at(i)));
            ui->ComboCountry->setCurrentIndex(0);
        }

        // Populate the customer combo box
        updateComboCustomer();

        // Connections
        connect(ui->ComboCustomer, &QComboBox::currentIndexChanged, this, [this]() { updateButtonOK(); });
        connect(ui->ComboCountry, &QComboBox::currentIndexChanged, this, [this]() { updateComboCustomer(); });
        connect(ui->EditLine, &QLineEdit::textEdited, this, [this]() { updateButtonOK(); });
    }
    else {
        // Line edition: the combo boxes are used only to display the country and the customer.
        // Then the combo box are frozen

        // Set and freeze the customer
        Customer* customer = line->customer();
        ui->ComboCustomer->addItem(customer->name());
        ui->ComboCustomer->setEnabled(false);

        // Set and freeze the country
        Country* country = customer->country();
        ui->ComboCountry->addItem(country->name());
        ui->ComboCountry->setEnabled(false);

        // Update the button OK according to the line name
        connect(ui->EditLine, &QLineEdit::textEdited, this, [this, line]() { updateButtonOK(line); });
    }
}

DlgEditLine::~DlgEditLine()
{
    delete ui;
}

Line* DlgEditLine::newLine(QWidget* parent)
{
    Line*        line = nullptr;
    DlgEditLine* dlg  = new DlgEditLine(parent, tr("New line"));

    if (dlg->exec() == QDialog::Accepted) {
        // new line
    }
    delete dlg;
    return line;
}

void DlgEditLine::updateComboCustomer()
{
    // Clear the customer list and set the one of the current country
    ui->ComboCustomer->clear();
    Country*         country      = ui->ComboCountry->currentData().value<Country*>();
    QList<Customer*> CustomerList = country->customerList();

    // Insert the customer according to the current country
    for (int i = 0; i < CustomerList.size(); i++) {
        ui->ComboCustomer->addItem(CustomerList.at(i)->name(), QVariant::fromValue(CustomerList.at(i)));
    }
    ui->ComboCustomer->setCurrentIndex(0);

    updateButtonOK();
}

void DlgEditLine::updateButtonOK()
{
    Customer* customer = ui->ComboCustomer->currentData(RoleCustomer).value<Customer*>();
    bool      valid    = customer->validateNewLineName(ui->EditLine->text());
    ui->ButtonOK->setEnabled(valid);
}

void DlgEditLine::updateButtonOK(Line* line)
{
    Customer* customer = line->customer();
    bool      valid    = customer->validateEditLineName(line, ui->EditLine->text());
    ui->ButtonOK->setEnabled(valid);
}
