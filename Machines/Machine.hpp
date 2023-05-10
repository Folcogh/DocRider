#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <QDateTime>
#include <QString>

class Machine
{
public:
    Machine();
    ~Machine();

private:
    QString Type;
    int SerialNumber1;
    int SerialNumber2;
    int DevStep;
    QString Country;
    QString Customer;
    QString Line;
    QDateTime Created;
    QDateTime LastModified;
};

#endif // MACHINE_HPP
