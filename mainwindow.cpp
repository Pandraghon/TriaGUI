#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QColorDialog>
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

    QActionGroup* ag = new QActionGroup(this);
    ag->addAction(ui->actionSelection);
    ag->addAction(ui->actionPoint);
    ag->addAction(ui->actionSegment);
    ag->addAction(ui->actionSuppression);
    ui->mainToolBar->addActions(ag->actions());

    QObject::connect(graphicsScene, &GraphicsScene::mouseMoved, this, &MainWindow::setMousePosText);
    QObject::connect(graphicsScene, &GraphicsScene::pointClicked, this, &MainWindow::addPoint);

    QObject::connect(pointsTableModel, &PointsTableModel::valuesChanged, this, &MainWindow::redraw);
    QObject::connect(pointsTableModel, &PointsTableModel::pointAdded, this, &MainWindow::addPoint);

    QObject::connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::changeColor);

    // Toolbar
    QObject::connect(ui->actionZoom, &QAction::triggered, graphicsView, &GraphicsView::zoomIn);
    QObject::connect(ui->actionZoom_2, &QAction::triggered, graphicsView, &GraphicsView::zoomOut);
    QObject::connect(ui->actionRecentrer, &QAction::triggered, graphicsView, &GraphicsView::center);
    QObject::connect(ui->actionR_initialiser, &QAction::triggered, graphicsView, &GraphicsView::likeANewBorn);
    QObject::connect(ui->actionSelection, &QAction::triggered, graphicsScene, &GraphicsScene::setSelectionMode);
            // @see http://stackoverflow.com/questions/27188538/how-to-delete-qgraphicsitem-properly
}

MainWindow::~MainWindow() {
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
}

void MainWindow::redraw(const Point& p1, const Point& p2) {
    QPointF b1(std::min(p1.getX(), p2.getX()) - PointItem::rad, std::min(p1.getY(), p2.getY()) - PointItem::rad),
            b2(std::max(p1.getX(), p2.getX()) + PointItem::rad, std::max(p1.getY(), p2.getY()) + PointItem::rad);
    graphicsScene->update(QRectF(b1, b2));
    //graphicsView->zoom(2.0);
    //graphicsView->zoom(0.5);
}

void MainWindow::changeColor() {
    qDebug() << Q_FUNC_INFO << "Graaaaaah";
    QColor color = QColorDialog::getColor();
    if(!color.isValid()) return;
//    QPalette p = ui->colorButton->palette();
//    p.setColor(QPalette::Button, color);
//    ui->colorButton->setAutoFillBackground(true);
//    ui->colorButton->setPalette(p);
//    ui->colorButton->update();
    QString qss = QString("background-color: %1").arg(color.name());
    ui->colorButton->setStyleSheet(qss);
}
