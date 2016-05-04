#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>

#include "data.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum MODE { POINT, SEGMENT, SELECTION, SUPPRESSION };

    explicit RenderArea(Data* data, QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:

public slots:
    void setMode(MODE mode);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    MODE mode;
    Data* data;
};

#endif // RENDERAREA_H
