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
    double scaleFactor;

signals:

public slots:
    void zoom(double factor);
    void zoomIn();
    void zoomOut();
    void center();
    void likeANewBorn();

};

#endif // GRAPHICSVIEW_H
