#include "triangleitem.h"

#include "graphicsscene.h"

#include <QPainter>
#include <QPainterPath>
#include <QPolygon>

#include <QDebug>

TriangleItem::TriangleItem(Triangle *triangle, int indexOfTriangulation, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    triangle(triangle),
    indexOfTriangulation(indexOfTriangulation)
{}

QRectF TriangleItem::boundingRect() const {
    QPointF p1{std::min(std::min(triangle->getP0()->getX(), triangle->getP1()->getX()), triangle->getP2()->getX()), std::max(std::max(triangle->getP0()->getY(), triangle->getP1()->getY()), triangle->getP2()->getY())},
            p2{std::max(std::max(triangle->getP0()->getX(), triangle->getP1()->getX()), triangle->getP2()->getX()), std::min(std::min(triangle->getP0()->getY(), triangle->getP1()->getY()), triangle->getP2()->getY())};
    return QRectF(p1, p2);
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    if(!GraphicsScene::visibility(indexOfTriangulation)) return;
    QTransform t = painter->transform();
    qreal m11 = t.m11(), m22 = t.m22();
    painter->save();
    painter->setTransform(QTransform(1, t.m12(), t.m13(),
                                     t.m21(), 1, t.m23(),
                                     t.m31(), t.m32(), t.m33()));
    //QColor c = *color;
    //c.setAlphaF(0.6);
    painter->setOpacity(0.4);
    //painter->setPen(QPen(QBrush(*color), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPolygon poly;
    poly << QPoint(triangle->getP0()->getX() * m11, triangle->getP0()->getY() * m22)
         << QPoint(triangle->getP1()->getX() * m11, triangle->getP1()->getY() * m22)
         << QPoint(triangle->getP2()->getX() * m11, triangle->getP2()->getY() * m22);

    QPainterPath path;
    path.addPolygon(poly);

    //painter->drawPolygon(poly);
    QBrush b(GraphicsScene::color(indexOfTriangulation), Qt::SolidPattern);
    if(triangle->calculated()) b.setStyle(Qt::FDiagPattern);
    painter->fillPath(path, b);
    painter->restore();
}
