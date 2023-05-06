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
    // Use a delegate constructor for editing a Country name
    // Use also another validator

  private:
    DlgEditCountry(QWidget* parent, QString title, Country* country = nullptr); // country is null when editing the name of a new country
                                                                                // country points to the country to be modified when changing the name
    ~DlgEditCountry();
    void updateUI();
    void updateUI(Country* country);

    Ui::DlgEditCountry* ui;
};

#endif // DLGEDITCOUNTRY_HPP
