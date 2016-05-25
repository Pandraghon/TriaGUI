#include "segmentitem.h"

#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include "segment.h"

SegmentItem::SegmentItem(Segment *segment, QColor *color, bool *visibility, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    segment(segment),
    color(color),
    visibility(visibility),
    selected(false)
{
}

QRectF SegmentItem::boundingRect() const {
    QPointF p1{segment->getP0()->getX(), segment->getP0()->getY()},
            p2{segment->getP1()->getX(), segment->getP1()->getY()};
    return QRectF(p1, p2);
}

void SegmentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(!*visibility) return;
    painter->setBrush(QBrush(*color));
    QPointF p1{segment->getP0()->getX(), segment->getP0()->getY()},
            p2{segment->getP1()->getX(), segment->getP1()->getY()};

    painter->drawLine(p1, p2);
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
