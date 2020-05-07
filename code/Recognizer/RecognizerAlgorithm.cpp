#include "RecognizerAlgorithm.h"
#include <QtMath>
#include <QDebug>
RecognizerAlgorithm::RecognizerAlgorithm()
{

}

RecognizerAlgorithm::~RecognizerAlgorithm()
{

}

bool RecognizerAlgorithm::set(const int number, const QList<QPoint>& pointsList)
{
    bool ret = true;
    Characteristic chara;

    /* 参数检查，如果没有画，直接返回0 */
    if(pointsList.size()==0)
    {
        return false;
    }

    featureExtraction(chara.array, const_cast<QList<QPoint>& >(pointsList));
    for(int i=0;i<9;i++)
    {
         qDebug()<<chara.array[i];
    }
    m_dataDase[number].append(chara);
    return ret;
}

void RecognizerAlgorithm::get(int &number, const QList<QPoint>& pointsList)
{
    double d = 0;
    Characteristic chara;
    double   temp    = 5000;
    /* 参数检查，如果没有画，直接返回0 */
    if(pointsList.size()==0)
    {
        number = 0;
        return ;
    }
    featureExtraction(chara.array, const_cast<QList<QPoint>& >(pointsList));

    for(int i=0; i<10; i++)
    {
        for(int j = 0; j<m_dataDase[i].size(); j++)
        {
            d = 0;
            for(int index=0;index<9;index++)
            {
                d+=(m_dataDase[i][j].array[index] - chara.array[index]) *(m_dataDase[i][j].array[index] - chara.array[index]);
            }
            d = qSqrt(d);
            if(d<temp)
            {
                temp =d;
                number = i;
            }
        }
    }
}

/**
 * @brief RecognizerAlgorithm::featureExtraction
 * 特征提取
 */
void RecognizerAlgorithm::featureExtraction(int (&array)[9],QList<QPoint>& pointsList)
{
    int maxX = 0, maxY = 0, minX = 0, minY = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, dx = 0, dy = 0;

    QPoint pos;
    /* 寻找最大最小x，y坐标值 */
    maxX = pointsList.first().x();
    minX = pointsList.first().x();
    maxY = pointsList.first().y();
    minY = pointsList.first().y();

    for(int i=0; i<pointsList.size(); i++)
    {
        pos = pointsList[i];
        if(maxX <pos.x())
        {
            maxX =pos.x();
        }

        if(maxY < pos.y())
        {
            maxY = pos.y();
        }

        if(minX >pos.x())
        {
            minX =pos.x();
        }

        if(minY > pos.y())
        {
            minY = pos.y();
        }
    }

    dx = (maxX - minX)/3;
    dy = (maxY - minY)/3;
    x1 = minX  + dx;
    y1 = minY  + dy;
    x2 = x1    + dx;
    y2 = y1    + dy;

    for(int i=0; i<9; i++)
    {
        array[i] = 0;
    }

    /* 计算点落在每个区域的百分比 */
    for(int i=0; i<pointsList.size(); i++)
    {
        pos = pointsList[i];
        if(pos.x() >= minX &&pos.x()<x1 && pos.y()>=minY && pos.y()<y1)
        {
            array[0]++;
        }
        if(pos.x() >= x1 &&pos.x()<x2 && pos.y()>=minY && pos.y()<y1)
        {
            array[1]++;
        }
        if(pos.x() >= x2 &&pos.x()<=maxX && pos.y()>=minY && pos.y()<y1)
        {
            array[2]++;
        }
        if(pos.x() >= minX &&pos.x()<x1 && pos.y()>=y1 && pos.y()<y2)
        {
            array[3]++;
        }
        if(pos.x() >= x1 &&pos.x()<x2 && pos.y()>=y1 && pos.y()<y2)
        {
            array[4]++;
        }
        if(pos.x() >= x2 &&pos.x()<maxX && pos.y()>=y1 && pos.y()<y2)
        {
            array[5]++;
        }
        if(pos.x() >= minX &&pos.x()<x1 && pos.y()>=y2 && pos.y()<=maxY)
        {
            array[6]++;
        }
        if(pos.x() >= x1 &&pos.x()<x2 && pos.y()>=y2 && pos.y()<=maxY)
        {
            array[7]++;
        }
        if(pos.x()>= x2 &&pos.x()<=maxX && pos.y()>=y2 && pos.y()<=maxY)
        {
            array[8]++;
        }
    }

    for(int i=0; i<9; i++)
    {
        array[i] *= 100;
        array[i] /= pointsList.size();
    }
}
