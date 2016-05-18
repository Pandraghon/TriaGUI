#include "pointitem.h"

#include <QDebug>
#include <QBrush>

PointItem::PointItem(Point* point, const QColor &color, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point),
    color(color)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    //setFlags(QGraphicsItem::ItemIgnoresTransformations);
}

QRectF PointItem::boundingRect() const {
    return QRectF(point->getX() - rad, point->getY() - rad, rad * 2, rad * 2);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(QBrush(color));
    // @see http://stackoverflow.com/a/24874013
    QTransform t = painter->transform();
    qreal m11 = t.m11(), m22 = t.m22();
    painter->save();
    painter->setTransform(QTransform(1, t.m12(), t.m13(),
                                         t.m21(), 1, t.m23(), t.m31(),
                                         t.m32(), t.m33()));
    painter->drawEllipse(point->getX() * m11 - rad, point->getY() * m22 - rad, rad * 2, rad * 2);
    painter->restore();
}
