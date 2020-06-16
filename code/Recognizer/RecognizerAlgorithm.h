#ifndef RECOGNIZERALGORITHM_H
#define RECOGNIZERALGORITHM_H

#include "IRecognizer.h"
#include "SqliteHandler/SqliteHandler.h"

class RecognizerAlgorithm :public IRecognizer
{
public:
    RecognizerAlgorithm();
    ~RecognizerAlgorithm();
    bool set(const int number, const QList<QPoint>& pointsList);
    void get(int &number, const QList<QPoint>& pointsList);
protected:
    bool getAverageChara(int number, Characteristic &averageChara);
    double getDistance(Characteristic x, Characteristic y);/* 获取两个特征值间的距离 */
    void featureExtraction(int (&array)[9], QList<QPoint>& pointsList);
    Characteristic m_averageChara[10]{};
};

#endif // RECOGNIZERALGORITHM_H
