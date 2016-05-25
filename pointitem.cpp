#include "pointitem.h"

#include <QDebug>
#include <QBrush>

PointItem::PointItem(Point* point, QColor *color, bool *visibility, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    point(point),
    color(color),
    visibility(visibility),
    bounds()
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    //setFlags(QGraphicsItem::ItemIgnoresTransformations);
}

QRectF PointItem::boundingRect() const {
    return QRectF(point->getX() - boundSize, point->getY() - boundSize, boundSize * 2, boundSize * 2);
}

void PointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    if(!*visibility) return;
    painter->setBrush(QBrush(*color));
    // @see http://stackoverflow.com/a/24874013
    QTransform t = painter->transform();
    qreal m11 = t.m11(), m22 = t.m22();
    painter->save();
    painter->setTransform(QTransform(1, t.m12(), t.m13(),
                                         t.m21(), 1, t.m23(), t.m31(),
                                         t.m32(), t.m33()));
    //bounds = QRectF(point->getX() * m11 - rad, point->getY() * m22 - rad, rad * 2, rad * 2);
    painter->drawEllipse(point->getX() * m11 - rad, point->getY() * m22 - rad, rad * 2, rad * 2);
    if(isSelected()) {
        painter->setBrush(QBrush(Qt::blue, Qt::NoBrush));
        painter->drawEllipse(point->getX() * m11 - selectionRad, point->getY() * m22 - selectionRad, selectionRad * 2, selectionRad * 2);
    }
    painter->restore();
}

void PointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //emit clicked(this);
    select(!isSelected());
    QGraphicsItem::mouseReleaseEvent(event);
}

void PointItem::select(bool isSelected) {
    setSelected(isSelected);
    update(point->getX() - selectionRad, point->getY() - selectionRad, selectionRad * 2, selectionRad * 2);
}

Point *PointItem::getPoint() const {
    return point;
}
