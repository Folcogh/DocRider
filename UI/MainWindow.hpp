#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../Machine/Machine.hpp"
#include <QAction>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void addMachineInMainUI(Machine* machine);

  private:
    Ui::MainWindow* ui;
    void newMachine();
    void machineDoubleClicked();
};

// Main table header
#define COLUMN_COUNT 8
enum {
    COLUMN_MACHINE_TYPE,
    COLUMN_SERIAL,
    COLUMN_DEVSTEP,
    COLUMN_LINE,
    COLUMN_CUSTOMER,
    COLUMN_COUNTRY,
    COLUMN_CREATED,
    COLUMN_MODIFIED
};

// Attach Machine* to UI elements
#define DATA_ROLE Qt::UserRole
Q_DECLARE_METATYPE(Machine*)

#endif // MAINWINDOW_HPP
