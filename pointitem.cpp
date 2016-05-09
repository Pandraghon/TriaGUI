#include "pointitem.h"

PointItem::PointItem(Point* point, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point)
{
}

QRectF PointItem::boundingRect() const
{
    return QRectF(0, 0, boundSize, boundSize);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->drawPoint(point->getX(), point->getY());
}
