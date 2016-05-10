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
    void addPoint(Point *p, const QColor& color);

private:
    Data *data;
    MODE mode;

    void clickOnSelection(const QPointF& pos);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void paint();

signals:
    void mouseMoved(const QPointF& pos);
    void pointClicked(const QPointF& pos);
    void segmentClicked(const QPointF& pos);

public slots:

};

#endif // GRAPHICSSCENE_H
