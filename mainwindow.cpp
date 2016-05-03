#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_data(),
    m_currentMode(POINT),
    m_pointsTableModel(new PointsTableModel(m_data.getTriangulation(0)))
{
    ui->setupUi(this);
    ui->tabPoints->setModel(m_pointsTableModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
