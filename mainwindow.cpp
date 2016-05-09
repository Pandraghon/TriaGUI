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
    graphicsScene(new GraphicsScene(&data))
{
    ui->setupUi(this);

    ui->tabPoints->setModel(pointsTableModel);
    ui->tabPoints->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabPoints->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tabSegments->setModel(segmentsTableModel);
    ui->tabSegments->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabSegments->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->areaDrawing->setScene(graphicsScene);
    ui->areaDrawing->setMouseTracking(true);
    ui->areaDrawing->scale(1, -1);

    QObject::connect(graphicsScene, &GraphicsScene::mouseMoved, this, &MainWindow::setMousePos);
    QObject::connect(graphicsScene, &GraphicsScene::pointClicked, this, &MainWindow::addPoint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMousePos(const QPointF& pos) {
    ui->textMousePosition->setText(tr("(") + QString::number(pos.x()) + tr(";") + QString::number(pos.y()) + tr(")"));
}


void MainWindow::addPoint(const QPointF &pos) {
    qDebug() << pos;
    this->data.getTriangulation(this->currentTriang)->addPoint(new Point(pos.x(), pos.y()));
    ui->areaDrawing->repaint();
}
