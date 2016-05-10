#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void setMousePosText(const QPointF &pos);
    void addPoint(const QPointF &pos);

};

#endif // MAINWINDOW_H
