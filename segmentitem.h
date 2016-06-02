#ifndef SEGMENTITEM_H
#define SEGMENTITEM_H

#include <QGraphicsItem>

#include "segment.h"

class QPainter;
class QPainterPath;
class QGraphicsSceneMouseEvent;

class SegmentItem : public QGraphicsItem {
public:
    explicit SegmentItem(Segment* segment, int indexOfTriangulation, QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    virtual QPainterPath shape() const Q_DECL_OVERRIDE;
    void select(bool isSelected = true);

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Segment* segment;
    int indexOfTriangulation;
    bool selected;

signals:

public slots:

};

#endif // SEGMENTITEM_H
