#include "pointitem.h"

PointItem::PointItem(Point* point, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point)
{
}

QRectF PointItem::boundingRect() const {
    return QRectF(point->getX() - rad, point->getY() - rad, rad * 2, rad * 2);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::SolidPattern);
    painter->drawEllipse(boundingRect());
}
