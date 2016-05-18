#include "graphicsscene.h"

#include <QDebug>

GraphicsScene::GraphicsScene(Data *data, QObject *parent) :
    QGraphicsScene(parent),
    data(data),
    mode(POINT),
    colorOfTriangulation(1, Qt::green)
{
    setSceneRect(-3000, -3000, 6000, 6000);

    paint();
}

void GraphicsScene::addPoint(Point* p, const QColor &color) {
    qDebug() << Q_FUNC_INFO << p << " " << color;

    addItem(new PointItem(p));
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    emit mouseMoved(event->scenePos());
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    switch(event->button()) {
    case Qt::LeftButton:
        switch(this->mode) {
            case POINT:
                emit pointClicked(event->scenePos());
                break;
            case SEGMENT:
                emit segmentClicked(event->scenePos());
                break;
            case SUPPRESSION:

                break;
        }
        break;
    case Qt::RightButton:
        clickOnSelection(event->scenePos());
        break;
    case Qt::MiddleButton:
        //translate
        break;
    }

}

void GraphicsScene::clickOnSelection(const QPointF &pos) {

}

void GraphicsScene::paint() {
    qDebug() << Q_FUNC_INFO;
    QPainter painter();

    for(auto tri : data->getTriangulations()) {
        for(auto p : tri->getPoints()) {
            addItem(new PointItem(p));
            qDebug() << p;
        }
    }

}

void GraphicsScene::setSelectionMode() {
    mode = SELECTION;
}

void GraphicsScene::setColor(int indexTriangulation, const QColor &color) {
    colorOfTriangulation[indexTriangulation] = color;

}
