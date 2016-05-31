#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QMessageBox>
#include <QVariant> // serialization

#include "data.h"
#include "pointstablemodel.h"
#include "segmentstablemodel.h"
#include "graphicsview.h"
#include "graphicsscene.h"

enum MODE { POINT, SEGMENT, SELECTION, SUPPRESSION };
const QString TITLE("TriaGUI");

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
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    QMessageBox::StandardButton saveQuestion() const;
    void setModified(bool isModified = true);
    void setTitle();

    Ui::MainWindow *ui;
    Data data;
    int currentTriang;
    MODE currentMode;
    PointsTableModel* pointsTableModel;
    SegmentsTableModel* segmentsTableModel;
    GraphicsScene* graphicsScene;
    GraphicsView* graphicsView;
    QActionGroup* actionGroup;
    QString currentSaveFile;
    bool modified;

//    friend QDataStream& operator<<(QDataStream&, const MainWindow&);
//    friend QDataStream& operator>>(QDataStream&, MainWindow&);

private slots:
    void setMousePosText(const QPointF &pos);
    void addPoint(const QPointF &pos);
    void addSegment(const QList<QGraphicsItem *> &list);
    void redraw(const Point &p1, const Point &p2);
    void chooseColor();
    void changeColor(const QColor& col);
    void manageMode();
    void manageVisibility();
    void save(bool forced = false);
    void saveAs();
    void load();
};

//Q_DECLARE_METATYPE(MainWindow)
//QDataStream& operator<<(QDataStream& out, const MainWindow& v);
//QDataStream& operator>>(QDataStream& in, MainWindow& v);

#endif // MAINWINDOW_H
