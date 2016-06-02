#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "data.h"
#include "point.h"
#include "pointitem.h"
#include "segment.h"
#include "segmentitem.h"
#include "triangle.h"
#include "triangleitem.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum MODE { POINT, SEGMENT, SELECTION, SUPPRESSION };

    explicit GraphicsScene(Data *data, QObject *parent = 0);
    void addPoint(Point *p, int indexOfTriangulation);
    void addSegment(Segment *s, int indexOfTriangulation);
    void addTriangle(Triangle* t, int indexOfTriangulation);
    void setMode(MODE mode);
    void paintTriangulation(int index);
    void paintTriangulation(Triangulation* tri, int i);

    static const QColor& color(int i);
    static bool visibility(int i);

private:
    Data *data;
    MODE mode;
    static QVector<QColor> colorOfTriangulation;
    static QVector<bool> visibilityOfTriangulation;
    QVector<PointItem*> pointsSelected;
    QPointF lastMousePos;
    //PointItem* ps1; //points of segment
    //PointItem* ps2;

    void clickOnSelection(const QPointF& pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void paint();

signals:
    void mouseMoved(const QPointF& pos);
    void pointClicked(const QPointF& pos);
    void segmentClicked(const QList<QGraphicsItem*>& list);
    void viewDragged(const QPointF& delta);


public slots:
    void setSelectionMode();
    void managePointClick(PointItem* p);

    static void setColor(int indexTriangulation, const QColor& color);
    static void setVisibility(int indexTriangulation, bool visibility);

};

#endif // GRAPHICSSCENE_H
