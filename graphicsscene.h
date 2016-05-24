#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "data.h"
#include "pointitem.h"
#include "point.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum MODE { POINT, SEGMENT, SELECTION, SUPPRESSION };

    explicit GraphicsScene(Data *data, QObject *parent = 0);
    void addPoint(Point *p, int indexOfTriangulation);
    void setMode(MODE mode);

private:
    Data *data;
    MODE mode;
    QVector<QColor> colorOfTriangulation;
    QVector<bool> visibilityOfTriangulation;
    QPointF lastMousePos;

    void clickOnSelection(const QPointF& pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void paint();

signals:
    void mouseMoved(const QPointF& pos);
    void pointClicked(const QPointF& pos);
    void segmentClicked(const QPointF& pos);
    void viewDragged(const QPointF& delta);


public slots:
    void setSelectionMode();

    void setColor(int indexTriangulation, const QColor& color);
    void setVisibility(int indexTriangulation, bool visibility);

};

#endif // GRAPHICSSCENE_H
