#include "graphicsscene.h"

#include <QDebug>
#include "triangulation.h"

GraphicsScene::GraphicsScene(Data *data, QObject *parent) :
    QGraphicsScene(parent),
    data(data),
    mode(POINT),
    colorOfTriangulation(1, Qt::green),
    visibilityOfTriangulation(1, true),
    pointsSelected(0),
    lastMousePos()/*,
    ps1(nullptr),
    ps2(nullptr)*/
{
    setSceneRect(-3000, -3000, 6000, 6000);

    paint();
}

void GraphicsScene::addPoint(Point* p, int indexOfTriangulation) {
    PointItem* pi{new PointItem(p, &(colorOfTriangulation[indexOfTriangulation]), &(visibilityOfTriangulation[indexOfTriangulation]))};
    addItem(pi);
    for(auto i : selectedItems()) ((PointItem*)i)->select(false);
    //for(auto i : pointsSelected) i->select(false);
    //pointsSelected.clear();
    pi->select();
    //pointsSelected.push_back(pi);
}

void GraphicsScene::addSegment(Segment *s, int indexOfTriangulation) {
    SegmentItem* si{new SegmentItem(s, &(colorOfTriangulation[indexOfTriangulation]), &(visibilityOfTriangulation[indexOfTriangulation]))};
    addItem(si);
}

void GraphicsScene::addTriangle(Triangle *t, int indexOfTriangulation) {
    TriangleItem* ti{new TriangleItem(t, &(colorOfTriangulation[indexOfTriangulation]), &(visibilityOfTriangulation[indexOfTriangulation]))};
    addItem(ti);
}

void GraphicsScene::setMode(GraphicsScene::MODE mode) {
    this->mode = mode;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    emit mouseMoved(event->scenePos());
    //QGraphicsScene::mouseMoveEvent(event);
}

/*void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    switch(event->button()) {
    case Qt::RightButton:
        clickOnSelection(event->scenePos());
        break;
    case Qt::MiddleButton:
        //translate
        break;
    default:
    }
}*/

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    switch(event->button()) {
    case Qt::LeftButton:
        switch(this->mode) {
            case POINT:
                //http://forum.qtfr.org/discussion/13407/selection-multiple-avancee-dans-une-qgraphicsscene
                emit pointClicked(event->scenePos());
                break;
            case SEGMENT: {
                QGraphicsScene::mouseReleaseEvent(event);
                QList<QGraphicsItem*> l = selectedItems();
                //if(itemAt(event->scenePos(), QTransform()) == NULL) break;
                //TODO
                if(l.size() >= 2) {
                    emit segmentClicked(l);
                    for(auto i : l)
                        ((PointItem*)i)->select(false);
                    ((PointItem*)itemAt(event->scenePos(), QTransform()))->select(true);
                }
                } break;
            case SUPPRESSION:

                break;
        }
        break;
    case Qt::RightButton:
        clickOnSelection(event->scenePos());
        QGraphicsScene::mouseReleaseEvent(event);
        break;
    case Qt::MiddleButton:
        //translate
        break;
    default:
        break;
    }
}

void GraphicsScene::clickOnSelection(const QPointF &pos) {
    qDebug() << selectedItems();
}

void GraphicsScene::paint() {
    Triangulation* tri;
    for(unsigned int i{} ; i < data->getTriangulations().size() && (tri = data->getTriangulation(i)) ; ++i) {
        for(auto p : tri->getPoints()) {
            addPoint(p, i);
        }
    }

}

void GraphicsScene::setSelectionMode() {
    mode = SELECTION;
}

void GraphicsScene::managePointClick(PointItem *p) {

}

void GraphicsScene::setColor(int indexTriangulation, const QColor &color) {
    colorOfTriangulation[indexTriangulation] = color;
}

void GraphicsScene::setVisibility(int indexTriangulation, bool visibility) {
    visibilityOfTriangulation[indexTriangulation] = visibility;
}
