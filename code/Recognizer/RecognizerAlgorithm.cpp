#include "RecognizerAlgorithm.h"
#include <QtMath>
#include <QDebug>
#define ROW_NUMBER 100
#include <iostream>
using namespace  std;

RecognizerAlgorithm::RecognizerAlgorithm()
{
    /* 从数据库中初始化平均特征值 */
    for(int i=0;i<10;i++)
    {
        getAverageChara(i, m_averageChara[i]);
    }
}

RecognizerAlgorithm::~RecognizerAlgorithm()
{

}

/**
 * @brief
 * @param number
 * @param x
 * @return
 */
bool RecognizerAlgorithm::getAverageChara(int number, Characteristic &averageChara)
{
    QList<Characteristic > list;
    int startRow = 0;
    int countSum = 0;
    long long characterSumBuf[9] = {0};
    while(true)
    {
        list.clear();
        SqliteHandler::getInstance()->getItems(number, startRow, ROW_NUMBER, list);
        for(int j = 0; j<list.size(); j++)
        {
            for(int i=0;i<9;i++)
            {
                characterSumBuf[i] += list[j].array[i];
            }
        }
        countSum += list.size();
        startRow += list.size();/*更新表读取起始位置*/

        /* 读到最后一页，不足ROW_NUMBER个，读完退出 */
        if(ROW_NUMBER != list.size())
        {
            break;
        }
    }
    if(0 != countSum)
    {
        for(int i=0;i<9;i++)
        {
            averageChara.array[i] = characterSumBuf[i]/countSum;
        }
    }
    return true;
}


bool RecognizerAlgorithm::set(const int number, const QList<QPoint>& pointsList)
{
    bool ret = true;
    Characteristic chara;
    int lastCount = 0;

    /* 参数检查，如果没有画，直接返回0 */
    if(pointsList.size()==0)
    {
        return false;
    }

    featureExtraction(chara.array, const_cast<QList<QPoint>& >(pointsList));

    SqliteHandler::getInstance()->getItemsCount(number, lastCount);
    SqliteHandler::getInstance()->addItem(number, chara.array);

    for(int j=0; j<9; j++)
    {
        m_averageChara[number].array[j] =  (m_averageChara[number].array[j] * lastCount + chara.array[j])/(lastCount+1);
    }
#if 0
    /* 打印每个数字的平均特征值的变化 */
    for(int x= 0;x<10;x++)
    {
        for(int y=0;y<9;y++)
        {
            cout<<m_averageChara[x].array[y]<<"  ";
        }
        cout<<endl;
    }
#endif
    return ret;
}

void RecognizerAlgorithm::get(int &number, const QList<QPoint>& pointsList)
{
    double distance = 0;
    Characteristic chara;
    double temp = INT_MAX;

    /* 参数检查，如果没有画，直接返回0 */
    if(pointsList.size()==0)
    {
        number = 0;
        return ;
    }
    featureExtraction(chara.array, const_cast<QList<QPoint>& >(pointsList));

    for(int i=0; i<10; i++)
    {
        distance = getDistance(chara, m_averageChara[i]);
        if(distance<temp)
        {
            temp = distance;
            number = i;
        }
    }
}

double RecognizerAlgorithm::getDistance(Characteristic x, Characteristic y)
{
    double distance = 0;
    for(int index=0;index<9;index++)
    {
        distance+=(x.array[index] - y.array[index]) *(x.array[index] - y.array[index]);
    }
    distance = qSqrt(distance);
    return  distance;
}

/**
 * @brief RecognizerAlgorithm::featureExtraction
 * 特征提取
 */
void RecognizerAlgorithm::featureExtraction(int (&array)[9],QList<QPoint>& pointsList)
{
    int maxX = 0, maxY = 0, minX = 0, minY = 0;/* 用于记录最大最小x，y坐标值 */
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, dx = 0, dy = 0;

    QPoint pos;
    /* 寻找 */
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

    /* 计算点落在每个区域的点数 */
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
    /* 将落在每个区域的点数换算成百分比 */
    for(int i=0; i<9; i++)
    {
        array[i] *= 100;
        array[i] /= pointsList.size();
    }
}
