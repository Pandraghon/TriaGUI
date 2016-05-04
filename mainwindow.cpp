#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(),
    currentMode(POINT),
    pointsTableModel(new PointsTableModel(data.getTriangulation(0))),
    segmentsTableModel(new SegmentsTableModel(data.getTriangulation(0))),
    renderArea(new RenderArea(&data))
{
    ui->setupUi(this);
    ui->tabPoints->setModel(pointsTableModel);
    ui->tabPoints->horizontalHeader()->setAutoFillBackground(true);
    ui->tabPoints->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabPoints->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tabSegments->setModel(segmentsTableModel);
    ui->tabSegments->horizontalHeader()->setAutoFillBackground(true);
    ui->tabSegments->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabSegments->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->drawingLayout->addWidget(renderArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
