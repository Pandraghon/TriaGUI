#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    wheel(false)
{
    setMouseTracking(true);
    scale(4, -4);
    setSceneRect(-3000, -3000, 6000, 6000);
    setMinimumSize(300, 300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

void GraphicsView::afterZoom()
{
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
    double scaleFactor = 1.15;
    if(wheel) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    } else {
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }
    scale(scaleFactor, scaleFactor);
    //wheel = false;
    afterZoom();
}

void GraphicsView::zoomOut() {
    qDebug() << Q_FUNC_INFO << tr("ZOOM OUT");
    double scaleFactor = 1.15;
    if(wheel) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    } else {
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    //wheel = false;
    afterZoom();
}

void GraphicsView::center() {
    centerOn(0, 0);
}
