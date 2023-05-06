#include "DlgEditCountry.hpp"
#include "../Index/DocIndex.hpp"
#include "ui_DlgEditCountry.h"

DlgEditCountry::DlgEditCountry(QWidget* parent, QString title, Country* country)
    : QDialog(parent)
    , ui(new Ui::DlgEditCountry)
{
    ui->setupUi(this);
    setWindowTitle(title);

    // Connections
    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });

    // Specificities for new/edited country name
    if (country == nullptr) {
        connect(ui->EditName, &QLineEdit::textEdited, this, [this]() { updateUI(); }); // This validator forbids name duplication
        ui->ButtonOK->setEnabled(false);                                               // The input field is empty, so prevent to validate the name initially
                                                                                       // (later on, the validator of DocIndex will do it)
    }
    else {
        connect(ui->EditName, &QLineEdit::textEdited, this, [this, country]() { updateUI(country); }); // This validator allows that the current name remains the same
        ui->EditName->setText(country->name());                                                        // Fill the input field with the name to be modified
    }
}

DlgEditCountry::~DlgEditCountry()
{
    delete ui;
}

Country* DlgEditCountry::newCountry(QWidget* parent)
{
    Country* country = nullptr;
    DlgEditCountry* dlg = new DlgEditCountry(parent, tr("New country"));

    if (dlg->exec() == QDialog::Accepted) {
        country = new Country(dlg->ui->EditName->text());
    }
    delete dlg;
    return country;
}

void DlgEditCountry::updateUI()
{
    // Enable the button OK according to the validity of the name
    bool Valid = DocIndex::instance()->validateNewCountryName(ui->EditName->text());
    ui->ButtonOK->setEnabled(Valid);
}

void DlgEditCountry::updateUI(Country* country)
{
    // Enable the button OK according to the validity of the name
    bool Valid = DocIndex::instance()->validateExistingCountryName(country, ui->EditName->text());
    ui->ButtonOK->setEnabled(Valid);
}
