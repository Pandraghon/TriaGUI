#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    wheel(false),
    scaleFactor(4.0),
    lastMousePos()
{
    setMouseTracking(true);
    scale(scaleFactor, - scaleFactor);
    setSceneRect(-3000, -3000, 6000, 6000);
    setMinimumSize(300, 300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(DragMode::NoDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    wheel = true;
    if(event->delta() > 0) {
        // Zoom
        zoomIn();
    } else {
        // Dezoom
        zoomOut();
    }
}

void GraphicsView::zoom(double factor)
{
    scaleFactor *= factor;
    if(wheel) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    } else {
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }
    scale(factor, factor);
    wheel = false;
    QRectF rect = scene()->itemsBoundingRect();
    qDebug() << Q_FUNC_INFO << rect;
    if(rect.isNull()) {
        scene()->setSceneRect(QRectF(0, 0, 1, 1));
    } else {
        qDebug() << Q_FUNC_INFO << rect;
        scene()->setSceneRect(rect);
    }
}

void GraphicsView::zoomIn() {
    qDebug() << Q_FUNC_INFO << tr("ZOOM IN");
    zoom(1.15);
}

void GraphicsView::zoomOut() {
    qDebug() << Q_FUNC_INFO << tr("ZOOM OUT");
    zoom(1.0 / 1.15);
}

void GraphicsView::center() {
    centerOn(0, 0);
}

void GraphicsView::likeANewBorn() {
    center();
    zoom(4 / scaleFactor);
}

void GraphicsView::drag(const QPointF &delta) {
    qDebug() << Q_FUNC_INFO << tr("TRANSLATE");
    translate(delta.x(), delta.y());
}
