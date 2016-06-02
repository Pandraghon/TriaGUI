#include "segmentitem.h"

#include "graphicsscene.h"

#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>

SegmentItem::SegmentItem(Segment *segment, int indexOfTriangulation, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    segment(segment),
    indexOfTriangulation(indexOfTriangulation),
    selected(false)
{}

QRectF SegmentItem::boundingRect() const {
    QPointF p1{segment->getP0()->getX(), segment->getP0()->getY()},
            p2{segment->getP1()->getX(), segment->getP1()->getY()};
    return QRectF(p1, p2);
}

void SegmentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(!GraphicsScene::visibility(indexOfTriangulation)) return;
    //painter->setBrush(QBrush(*color));
    QTransform t = painter->transform();
    qreal m11 = t.m11(), m22 = t.m22();
    painter->save();
    painter->setTransform(QTransform(1, t.m12(), t.m13(),
                                         t.m21(), 1, t.m23(), t.m31(),
                                         t.m32(), t.m33()));
    painter->setPen(QPen(QBrush(GraphicsScene::color(indexOfTriangulation)), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPointF p1{segment->getP0()->getX() * m11, segment->getP0()->getY() * m22},
            p2{segment->getP1()->getX() * m11, segment->getP1()->getY() * m22};

    painter->drawLine(p1, p2);
    painter->restore();
}

QPainterPath SegmentItem::shape() const {
    QPointF p1{segment->getP0()->getX(), segment->getP0()->getY()},
            p2{segment->getP1()->getX(), segment->getP1()->getY()};
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    return path;
}

void SegmentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}

void SegmentItem::select(bool isSelected) {
    selected = isSelected;
    //update(point->getX() - selectionRad, point->getY() - selectionRad, selectionRad * 2, selectionRad * 2);
}
