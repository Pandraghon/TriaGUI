#include "pointitem.h"

#include <QDebug>

PointItem::PointItem(Point* point, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point)
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    //setFlags(QGraphicsItem::ItemIgnoresTransformations);
}

QRectF PointItem::boundingRect() const {
    return QRectF(point->getX() - rad, point->getY() - rad, rad * 2, rad * 2);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::SolidPattern);
    // @see http://stackoverflow.com/a/24874013
    QTransform t = painter->transform();
    qreal m11 = t.m11(), m22 = t.m22();
    qDebug() << Q_FUNC_INFO << scale();
    qDebug() << m11 << " " << m22;
    painter->save();
    painter->setTransform(QTransform(1, t.m12(), t.m13(),
                                         t.m21(), 1, t.m23(), t.m31(),
                                         t.m32(), t.m33()));
    painter->drawEllipse(point->getX() * m11 - rad, point->getY() * m22 - rad, rad * 2, rad * 2);
    painter->restore();
}
