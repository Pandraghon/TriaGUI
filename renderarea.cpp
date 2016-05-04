#include "renderarea.h"

#include <QDebug>

RenderArea::RenderArea(Data *data, QWidget *parent) :
    QWidget(parent),
    mode(POINT),
    data(data)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

void RenderArea::setMode(MODE mode) {
    this->mode = mode;
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(auto tri : data->getTriangulations()) {
        for(auto p : tri->getPoints()) {
            painter.drawPoint(p->getX(), p->getY());
            qDebug() << tr("pouet");
        }
    }
}
