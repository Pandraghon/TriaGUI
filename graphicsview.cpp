#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    scale(1, -1);
    setSceneRect(-300, -300, 600, 600);
    setMinimumSize(300, 300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom
        qDebug() << Q_FUNC_INFO << tr("ZOOM IN");
        scale(scaleFactor, scaleFactor);
    } else {
        // Dezoom
        qDebug() << Q_FUNC_INFO << tr("ZOOM OUT");
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
