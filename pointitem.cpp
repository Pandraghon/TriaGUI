#include "pointitem.h"

#include <QDebug>

PointItem::PointItem(Point* point, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point)
{
    //setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

QRectF PointItem::boundingRect() const {
    return QRectF(point->getX() - rad, point->getY() - rad, rad * 2, rad * 2);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::SolidPattern);
    qDebug() << Q_FUNC_INFO << scale();
    qDebug() << painter->transform().m11() << " " << painter->transform().m22();
    painter->drawEllipse(boundingRect());
}
