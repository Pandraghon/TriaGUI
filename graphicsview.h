#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    void refresh();
    //static constexpr double scaleFactor = 1.15;

protected:
    virtual void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

    bool wheel;
    double scaleFactor;
    QPointF lastMousePos;

signals:

public slots:
    void zoom(double factor);
    void zoomIn();
    void zoomOut();
    void center();
    void likeANewBorn();
    void drag(const QPointF& delta);

};

#endif // GRAPHICSVIEW_H
