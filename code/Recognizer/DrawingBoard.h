#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include <QPoint>
class DrawingBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingBoard(QWidget *parent = 0, int width = 200, int height = 200);
protected:
    void paintEvent(QPaintEvent *);       /* 重绘事件(重点:由update()函数触发) */
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
protected slots:
   void clear();
private:
    QImage m_image;
    QRgb m_backColor;
    QList<QPoint> m_list;
    QPoint lastPoint{0,0};/* 前一个点，因为线是由无数点组成的 */
    QPoint endPoint{0,0}; /* 后一个点(结束点) */
    bool m_mouseDown = false;
};

#endif
