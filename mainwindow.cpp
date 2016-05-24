#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QDebug>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(),
    currentTriang(0),
    currentMode(POINT),
    pointsTableModel(new PointsTableModel(data.getTriangulation(currentTriang))),
    segmentsTableModel(new SegmentsTableModel(data.getTriangulation(currentTriang))),
    graphicsScene(new GraphicsScene(&data)),
    graphicsView(new GraphicsView()),
    actionGroup(new QActionGroup(this))
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

    actionGroup->addAction(ui->actionSelection);
    actionGroup->addAction(ui->actionPoint);
    actionGroup->addAction(ui->actionSegment);
    actionGroup->addAction(ui->actionSuppression);
    ui->mainToolBar->addActions(actionGroup->actions());

    changeColor(Qt::green);

    QObject::connect(graphicsScene, &GraphicsScene::mouseMoved, this, &MainWindow::setMousePosText);
    QObject::connect(graphicsScene, &GraphicsScene::pointClicked, this, &MainWindow::addPoint);
    QObject::connect(graphicsScene, &GraphicsScene::viewDragged, graphicsView, &GraphicsView::drag);

    QObject::connect(pointsTableModel, &PointsTableModel::valuesChanged, this, &MainWindow::redraw);
    QObject::connect(pointsTableModel, &PointsTableModel::pointAdded, this, &MainWindow::addPoint);

    QObject::connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::chooseColor);
    QObject::connect(ui->isVisible, &QCheckBox::clicked, this, &MainWindow::manageVisibility);

    // Toolbar
    QObject::connect(ui->actionEnregistrer, &QAction::triggered, this, &MainWindow::save);
    QObject::connect(ui->actionOuvrir, &QAction::triggered, this, &MainWindow::readSettings);
    QObject::connect(ui->actionZoom, &QAction::triggered, graphicsView, &GraphicsView::zoomIn);
    QObject::connect(ui->actionZoom_2, &QAction::triggered, graphicsView, &GraphicsView::zoomOut);
    QObject::connect(ui->actionRecentrer, &QAction::triggered, graphicsView, &GraphicsView::center);
    QObject::connect(ui->actionR_initialiser, &QAction::triggered, graphicsView, &GraphicsView::likeANewBorn);
    QObject::connect(actionGroup, &QActionGroup::triggered, this, &MainWindow::manageMode);
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
    graphicsScene->addPoint(p, currentTriang);
}

void MainWindow::redraw(const Point& p1, const Point& p2) {
    QPointF b1(std::min(p1.getX(), p2.getX()) - PointItem::rad, std::min(p1.getY(), p2.getY()) - PointItem::rad),
            b2(std::max(p1.getX(), p2.getX()) + PointItem::rad, std::max(p1.getY(), p2.getY()) + PointItem::rad);
    graphicsScene->update(QRectF(b1, b2));
}

void MainWindow::chooseColor() {
    changeColor(QColorDialog::getColor());
}

void MainWindow::changeColor(const QColor &col) {
    if(!col.isValid()) return;
    QString qss = QString("background-color: %1").arg(col.name());
    ui->colorButton->setStyleSheet(qss);
    graphicsScene->setColor(currentTriang, col);
}

void MainWindow::manageMode() {
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    if(actionGroup->checkedAction() == ui->actionSelection) {
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsScene->setMode(GraphicsScene::SELECTION);
    } else if(actionGroup->checkedAction() == ui->actionPoint) {
        graphicsScene->setMode(GraphicsScene::POINT);
    } else if(actionGroup->checkedAction() == ui->actionSegment) {
        graphicsScene->setMode(GraphicsScene::SEGMENT);
    } else if(actionGroup->checkedAction() == ui->actionSuppression) {
        graphicsScene->setMode(GraphicsScene::SUPPRESSION);
    }
}

void MainWindow::manageVisibility() {
    graphicsScene->setVisibility(currentTriang, ui->isVisible->isChecked());
    // Hack pour faire redessiner la scene
    graphicsView->zoom(2.0);
    graphicsView->zoom(0.5);
}

void MainWindow::save() {
    qDebug() << Q_FUNC_INFO << "Saving ...";
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::readSettings() {
    qDebug() << Q_FUNC_INFO << "Restoring ...";
    QSettings settings("MyCompany", "MyApp");
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    restoreState(settings.value("MainWindow/windowState").toByteArray());
}
