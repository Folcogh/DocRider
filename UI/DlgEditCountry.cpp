#include "DlgEditCountry.hpp"
#include "../Index/DocIndex.hpp"
#include "ui_DlgEditCountry.h"

DlgEditCountry::DlgEditCountry(QWidget* parent, QString title, QString country)
    : QDialog(parent)
    , ui(new Ui::DlgEditCountry)
{
    ui->setupUi(this);
    setWindowTitle(title);
    connect(ui->EditName, &QLineEdit::textChanged, this, [this]() { requestValidation(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });
    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
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

void DlgEditCountry::requestValidation()
{
    bool Valid = DocIndex::instance()->validateNewCountryName(ui->EditName->text());
    ui->ButtonOK->setEnabled(Valid);
}
