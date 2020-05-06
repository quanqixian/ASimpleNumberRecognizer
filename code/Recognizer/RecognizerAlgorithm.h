#ifndef RECOGNIZERALGORITHM_H
#define RECOGNIZERALGORITHM_H

#include "IRecognizer.h"

struct Characteristic
{
    int array[9];
};

class RecognizerAlgorithm :public IRecognizer
{
public:
    RecognizerAlgorithm();
    ~RecognizerAlgorithm();
    bool set(const int number, const QList<QPoint>& pointsList);
    void get(int &number, const QList<QPoint>& pointsList);
protected:
    void featureExtraction(int (&array)[9], QList<QPoint>& pointsList);
    QList<Characteristic > m_dataDase[10];
};

#endif // RECOGNIZERALGORITHM_H
