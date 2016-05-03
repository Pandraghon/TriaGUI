#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_data(),
    m_currentMode(POINT),
    m_pointsTableModel(new PointsTableModel(m_data.getTriangulation(0))),
    m_segmentsTableModel(new SegmentsTableModel(m_data.getTriangulation(0)))
{
    ui->setupUi(this);
    ui->tabPoints->setModel(m_pointsTableModel);
    ui->tabPoints->horizontalHeader()->setAutoFillBackground(true);
    ui->tabPoints->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabPoints->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tabSegments->setModel(m_segmentsTableModel);
    ui->tabSegments->horizontalHeader()->setAutoFillBackground(true);
    ui->tabSegments->horizontalHeader()->setDefaultSectionSize(75);
    ui->tabSegments->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}
