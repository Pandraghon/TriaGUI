#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "data.h"
#include "pointstablemodel.h"

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
    Data m_data;
    MODE m_currentMode;
    PointsTableModel* m_pointsTableModel;
};

#endif // MAINWINDOW_H
