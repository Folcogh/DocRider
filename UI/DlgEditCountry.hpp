#ifndef DLGEDITCOUNTRY_HPP
#define DLGEDITCOUNTRY_HPP

#include "../Index/Country.hpp"
#include <QDialog>
#include <QString>

namespace Ui {
    class DlgEditCountry;
}

class DlgEditCountry : public QDialog
{
    Q_OBJECT

  public:
    static Country* newCountry(QWidget* parent);
    //    static bool editCountry(QWidget* parent, Country* country);

  private:
    DlgEditCountry(QWidget* parent, QString title, QString country = nullptr);
    ~DlgEditCountry();
    Ui::DlgEditCountry* ui;
    void requestValidation();
};

#endif // DLGEDITCOUNTRY_HPP
