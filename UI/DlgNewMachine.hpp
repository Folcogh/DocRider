#ifndef DLGNEWMACHINE_HPP
#define DLGNEWMACHINE_HPP

#include "../Machine/Machine.hpp"
#include <QDialog>
#include <QString>

namespace Ui {
class DlgNewMachine;
}

class DlgNewMachine : public QDialog
{
    Q_OBJECT

  public:
      static Machine* newMachine(QWidget* parent);
      static bool editMachine(QWidget* parent, Machine* machine);
      ~DlgNewMachine();

  private:
    Ui::DlgNewMachine* ui;
    DlgNewMachine(QWidget* parent, QString title, Machine* machine = nullptr);
    void updateButtonOK();
    void updateCustomerList();
    void updateLineList();
};

#endif // DLGNEWMACHINE_HPP
