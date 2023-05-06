#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAction>
#include <QMainWindow>
#include <QTreeWidget>

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

  private:
    Ui::MainWindow* ui;

    //
    //          Actions
    //

    // Context menu handling
    void updateTreeContextMenu();

    // Actions handlers
    void newCountry();
    void newCustomer();
    void newLine();
    void newMachine();

    // The actions themselves. They are members,maybe we need them somewhere else than in the constructor
    QAction* ActionNewCountry;
    QAction* ActionNewCustomer;
    QAction* ActionNewLine;
    QAction* ActionNewMachine;
};

// Define the type of the QTreeWidgetItems added in the Tree
enum {
    TYPE_COUNTRY = QTreeWidgetItem::UserType,
    TYPE_CUSTOMER,
    TYPE_LINE,
    TYPE_MACHINE
};

// Define the role of the QTreeWidgetItems added in the Tree
enum {
    RoleCountry = Qt::UserRole,
    RoleCustomer,
    RoleLine,
    RoleMachine
};

#endif // MAINWINDOW_HPP
