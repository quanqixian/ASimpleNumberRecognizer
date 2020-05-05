#ifndef RECOGNIZERALGORITHM_H
#define RECOGNIZERALGORITHM_H

#include "IRecognizer.h"

class RecognizerAlgorithm :public IRecognizer
{
public:
    RecognizerAlgorithm();
    ~RecognizerAlgorithm();
    bool set(const int number, const QList<QPoint>& pointsList);
    void get(int &number, const QList<QPoint>& pointsList);
};

#endif // RECOGNIZERALGORITHM_H
