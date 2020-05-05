#ifndef IRECOGNIZER_H
#define IRECOGNIZER_H

#include <QList>
#include <QPoint>
class IRecognizer
{
public:
    virtual bool set(const int number, const QList<QPoint>& pointsList) = 0;
    virtual void get(int &number, const QList<QPoint>& pointsList) = 0;
};
#endif // IRECOGNIZER_H
