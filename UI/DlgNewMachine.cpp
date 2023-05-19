#include "DlgNewMachine.hpp"
#include "../Machine/Database.hpp"
#include "ui_DlgNewMachine.h"
#include <QList>
#include <QMessageBox>

DlgNewMachine::DlgNewMachine(QWidget* parent, QString title, Machine* machine)
    : QDialog(parent)
    , ui(new Ui::DlgNewMachine)
{
    ui->setupUi(this);
    setWindowTitle(title);

    // Connections
    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });
    connect(ui->SpinSN1, &QSpinBox::valueChanged, this, [this]() { updateButtonOK(); });
    connect(ui->SpinSN2, &QSpinBox::valueChanged, this, [this]() { updateButtonOK(); });
    connect(ui->ComboCountry, &QComboBox::currentTextChanged, this, [this]() { updateCustomerList(); });
    connect(ui->ComboCustomer, &QComboBox::currentTextChanged, this, [this]() { updateLineList(); });

    // Fill the machine type list, but don't select any type
    ui->ComboType->addItems(Database::instance()->typeList());
    ui->ComboType->setCurrentIndex(-1);

    // Fill the country list, but don't select any country
    ui->ComboCountry->addItems(Database::instance()->countryList());
    ui->ComboCountry->setCurrentIndex(-1);

    // Populate the UI if we edit a machine
    if (machine != nullptr) {
        ui->ComboType->setCurrentText(machine->type());
        ui->SpinSN1->setValue(machine->serialNumber1());
        ui->SpinSN2->setValue(machine->serialNumber2());
        ui->SpinDevStep->setValue(machine->devStep());
        ui->ComboCountry->setCurrentText(machine->country());
        ui->ComboCustomer->setCurrentText(machine->customer());
        ui->ComboLine->setCurrentText(machine->line());

        // Freeze the S/N, because this is THE core property of the machine
        ui->SpinSN1->setReadOnly(true);
        ui->SpinSN2->setReadOnly(true);
    }

    // Set the button OK according to the content
    updateButtonOK();
}

DlgNewMachine::~DlgNewMachine()
{
    delete ui;
}

Machine* DlgNewMachine::newMachine(QWidget* parent)
{
    Machine* machine = nullptr;

    // Create and exec the dialog
    DlgNewMachine* dlg = new DlgNewMachine(parent, tr("New machine"));
    if (dlg->exec() == QDialog::Accepted) {
        // Create the machine if the dialog was validated
        machine = Database::instance()->newMachine(dlg->ui->ComboType->currentText(),
                                                   dlg->ui->SpinSN1->value(),
                                                   dlg->ui->SpinSN2->value(),
                                                   dlg->ui->SpinDevStep->value(),
                                                   dlg->ui->ComboCountry->currentText(),
                                                   dlg->ui->ComboCustomer->currentText(),
                                                   dlg->ui->ComboLine->currentText());

        // Check that the machine was successfully created
        // A failure means that the machine already exists,
        // or we are out memory, but there is no diag for this
        if (machine == nullptr) {
            int SN1 = dlg->ui->SpinSN1->value();
            int SN2 = dlg->ui->SpinSN2->value();

            QMessageBox::critical(parent, tr("Error - New Machine"), tr("The machine %1/%2 already exists").arg(SN1).arg(SN2));
        }
    }

    delete dlg;
    return machine;
}

void DlgNewMachine::updateButtonOK()
{
    bool Enabled = (ui->SpinSN1->value() != 0) && (ui->SpinSN2->value() != 0);
    ui->ButtonOK->setEnabled(Enabled);
}

void DlgNewMachine::updateCustomerList()
{
    QString Country = ui->ComboCountry->currentText(); // Shortcut
    Database::instance()->startMachineIteration();     // Initialize iterator
    QList<QString> Customers;                          // New items

    // Add all the customers of the country
    while (Machine* machine = Database::instance()->nextMachine()) {
        if (machine->country() == Country) {
            Customers << machine->customer();
        }
    }

    // Clean the list and update the combo, but don't select any customer
    Customers.removeDuplicates();
    Customers.sort();
    ui->ComboCustomer->clear();
    ui->ComboCustomer->addItems(Customers);
    ui->ComboCustomer->setCurrentIndex(-1);
}

void DlgNewMachine::updateLineList()
{
    ui->ComboLine->clear();

    // Shortcuts
    QString        Country  = ui->ComboCountry->currentText();
    QString        Customer = ui->ComboCustomer->currentText();
    QList<QString> Lines;

    Database::instance()->startMachineIteration();
    while (Machine* machine = Database::instance()->nextMachine()) {
        if ((machine->customer() == Customer) && (machine->country() == Country)) {
            Lines << machine->line();
        }
    }

    // Clean the list and update the combo, but don't select any line
    Lines.removeDuplicates();
    Lines.sort();
    ui->ComboLine->clear();
    ui->ComboLine->addItems(Lines);
    ui->ComboLine->setCurrentIndex(-1);
}
