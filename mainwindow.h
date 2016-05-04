#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "data.h"
#include "pointstablemodel.h"
#include "segmentstablemodel.h"
#include "renderarea.h"

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
    MODE currentMode;
    PointsTableModel* pointsTableModel;
    SegmentsTableModel* segmentsTableModel;
    RenderArea* renderArea;
};

#endif // MAINWINDOW_H
