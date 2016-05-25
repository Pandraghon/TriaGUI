#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

#include "data.h"
#include "pointstablemodel.h"
#include "segmentstablemodel.h"
#include "graphicsview.h"
#include "graphicsscene.h"

enum MODE { POINT, SEGMENT, SELECTION, SUPPRESSION };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Data data;
    int currentTriang;
    MODE currentMode;
    PointsTableModel* pointsTableModel;
    SegmentsTableModel* segmentsTableModel;
    GraphicsScene* graphicsScene;
    GraphicsView* graphicsView;
    QActionGroup* actionGroup;

private slots:
    void setMousePosText(const QPointF &pos);
    void addPoint(const QPointF &pos);
    void addSegment(const QList<QGraphicsItem *> &list);
    void redraw(const Point &p1, const Point &p2);
    void chooseColor();
    void changeColor(const QColor& col);
    void manageMode();
    void manageVisibility();
    void save();
    void readSettings();
};

#endif // MAINWINDOW_H
