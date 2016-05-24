#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "point.h"

class PointItem : public QGraphicsItem {
public:
    static const int boundSize = 20;
    static const int rad = 2;

    explicit PointItem(Point* point, QColor* color, bool* visibility, QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    Point* point;
    QColor* color;
    bool* visibility;

signals:

public slots:

};

#endif // POINTITEM_H
