#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    //static constexpr double scaleFactor = 1.15;

protected:
    virtual void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

    bool wheel;

signals:

public slots:
    void zoomIn();
    void zoomOut();
    void center();

};

#endif // GRAPHICSVIEW_H
