#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

#include "triangle.h"

class TriangleItem : public QGraphicsItem {
public:
    explicit TriangleItem(Triangle* triangle, QColor* color, bool* visibility, QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

private:
    Triangle* triangle;
    QColor* color;
    bool* visibility;

signals:

public slots:

};

#endif // TRIANGLEITEM_H
