#ifndef DLGEDITCUSTOMER_HPP
  #define DLGEDITCUSTOMER_HPP

#include "../Index/Customer.hpp"
#include <QDialog>
#include <QString>

namespace Ui {
    class DlgEditCustomer;
}

class DlgEditCustomer : public QDialog
{
    Q_OBJECT

  public:
    static Customer* newCustomer(QWidget* parent);

  private:
    DlgEditCustomer(QWidget* parent, QString title, Customer* customer = nullptr);
    ~DlgEditCustomer();

    // Validators
    void updateUI();
    void updateUI(Customer* customer);

    Ui::DlgEditCustomer* ui;
};

#endif // DLGEDITCUSTOMER_HPP
