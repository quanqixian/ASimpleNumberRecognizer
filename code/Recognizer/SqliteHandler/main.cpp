#include <QCoreApplication>
#include <QDebug>
#include "SqliteHandler.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int array[9] = {11,22,33,44,55,66,77,88,99};
    QList<Characteristic > list;
    SqliteHandler*p = SqliteHandler::getInstance();

    for(int i=0;i<=9;i++)
    {
        array[0] = i;
        for(int j=0;j<=3;j++)
        {
            array[0] = j;
            p->addItem(i,array);
        }
    }

    p->clearTable(5);
    p->getItems(3, 2, 5, list);
    for(auto it:list)
    {
        for(int i=0;i<9;i++)
        {
            qDebug()<< it.array[i] <<" ";
        }
        qDebug()<<endl;
    }
    int count = 0;
    p->getItemsCount(3,count);
    qDebug()<<"count is :"<<count;
    delete p;
    return a.exec();
}
