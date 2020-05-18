#include <QCoreApplication>
#include "SqliteHandler.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int array[9] = {11,22,33,44,55,66,77,88,99};
    SqliteHandler*p = SqliteHandler::getInstance();
    for(int i=0;i<=9;i++)
    {
        array[0] = i;
        for(int j=0;j<=20;j++)
        {
            array[0] = j;
            p->additem(i,array);
        }
    }
    p->clearTable(5);
    delete p;
    return a.exec();
}
