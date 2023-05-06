#ifndef DLGEDITLINE_HPP
#define DLGEDITLINE_HPP

#include "../Index/Line.hpp"
#include <QDialog>
#include <QString>

namespace Ui {
    class DlgEditLine;
}

class DlgEditLine : public QDialog
{
    Q_OBJECT

  public:
    static Line* newLine(QWidget* parent);
    ~DlgEditLine();

  private:
    DlgEditLine(QWidget* parent, QString title, Line* line = nullptr);
    void updateComboCustomer();
    void updateButtonOK();
    void updateButtonOK(Line* line);

    Ui::DlgEditLine *ui;
};

#endif // DLGEDITLINE_HPP
