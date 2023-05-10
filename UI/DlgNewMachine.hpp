#ifndef DLGNEWMACHINE_HPP
#define DLGNEWMACHINE_HPP

#include <QDialog>

namespace Ui {
class DlgNewMachine;
}

class DlgNewMachine : public QDialog
{
    Q_OBJECT

public:
    explicit DlgNewMachine(QWidget *parent = nullptr);
    ~DlgNewMachine();

private:
    Ui::DlgNewMachine *ui;
};

#endif // DLGNEWMACHINE_HPP
