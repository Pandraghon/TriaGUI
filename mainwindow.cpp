#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(),
    currentTriang(0),
    currentMode(POINT),
    pointsTableModel(new PointsTableModel(data.getTriangulation(currentTriang))),
    segmentsTableModel(new SegmentsTableModel(data.getTriangulation(currentTriang))),
    graphicsScene(new GraphicsScene(&data)),
    graphicsView(new GraphicsView())
{
    ui->setupUi(this);

    ui->tabPoints->setModel(pointsTableModel);
    ui->tabPoints->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabPoints->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tabSegments->setModel(segmentsTableModel);
    ui->tabSegments->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabSegments->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    graphicsView->setScene(graphicsScene);
    ui->drawingLayout->insertWidget(0, graphicsView);

    QObject::connect(graphicsScene, &GraphicsScene::mouseMoved, this, &MainWindow::setMousePosText);
    QObject::connect(graphicsScene, &GraphicsScene::pointClicked, this, &MainWindow::addPoint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMousePosText(const QPointF& pos) {
    ui->textMousePosition->setText(tr("(") + QString::number(pos.x()) + tr(";") + QString::number(pos.y()) + tr(")"));
}


void MainWindow::addPoint(const QPointF &pos) {
    Point* p = new Point(pos.x(), pos.y());
    this->data.getTriangulation(this->currentTriang)->addPoint(p);
    ui->tabPoints->model()->layoutChanged();
    graphicsScene->addPoint(p, Qt::blue);
    //ui->areaDrawing->repaint();
}
