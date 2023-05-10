#include "DlgNewMachine.hpp"
#include "ui_DlgNewMachine.h"

DlgNewMachine::DlgNewMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgNewMachine)
{
    ui->setupUi(this);
}

DlgNewMachine::~DlgNewMachine()
{
    delete ui;
}
