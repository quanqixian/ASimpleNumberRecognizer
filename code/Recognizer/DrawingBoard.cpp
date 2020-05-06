#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget *parent, int width, int height) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(width, height);
    m_image = QImage(width, height, QImage::Format_RGB32);//画板大小700,500,用32位色(就是平时用的都有)
    m_backColor = qRgb(220,220,220);
    m_image.fill(m_backColor);//RGB（255，255，255）为白色，m_image画布被填充为白色
}

void DrawingBoard::paintEvent(QPaintEvent *)
{
    if(m_mouseDown)
    {
        QPen pen;
        pen.setWidth(3);//画笔线条宽度
        QPainter painter(&m_image); //image(image是painterDevice类型参数，由于是引用，其实就是画在m_image上)
        painter.setPen(pen);
        painter.drawLine(lastPoint,endPoint);
        lastPoint = endPoint;

    }
    QPainter p(this);
    p.drawImage(0,0,m_image);

}

void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
	{
        lastPoint = event->pos();
        m_list.append(lastPoint);
    }
    m_mouseDown = true;
}

void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{ 
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint = event->pos();
        m_list.append(endPoint);
        update();
	}
}
void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        m_list.append(endPoint);
        update();
    }
    m_mouseDown = false;
}
void DrawingBoard::clear()
{
    m_list.clear();
    m_image.fill(m_backColor);//RGB（255，255，255）为白色，m_image画布被填充为白色
    update();
}
 QList<QPoint>& DrawingBoard::getPointsList(void)
 {
     return m_list;
 }
