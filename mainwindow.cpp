#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

#include <fstream>

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
    actionGroup(new QActionGroup(this)),
    currentSaveFile(""),
    modified()
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

    setTitle();
    changeColor(Qt::green);
    setModified(false);

    QObject::connect(graphicsScene, &GraphicsScene::mouseMoved, this, &MainWindow::setMousePosText);
    QObject::connect(graphicsScene, &GraphicsScene::pointClicked, this, &MainWindow::addPoint);
    QObject::connect(graphicsScene, &GraphicsScene::segmentClicked, this, &MainWindow::addSegment);
    QObject::connect(graphicsScene, &GraphicsScene::viewDragged, graphicsView, &GraphicsView::drag);

    QObject::connect(pointsTableModel, &PointsTableModel::valuesChanged, this, &MainWindow::redraw);
    QObject::connect(pointsTableModel, &PointsTableModel::pointAdded, this, &MainWindow::addPoint);

    QObject::connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::chooseColor);
    QObject::connect(ui->isVisible, &QCheckBox::clicked, this, &MainWindow::manageVisibility);
    QObject::connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generate);
    QObject::connect(ui->nextOrderButton, &QPushButton::clicked, this, &MainWindow::nextOrder);
    QObject::connect(ui->triBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::changeDegree);

    // Toolbar
    QObject::connect(ui->actionEnregistrer, &QAction::triggered, this, &MainWindow::save);
    QObject::connect(ui->actionNouveau, &QAction::triggered, this, &MainWindow::newFile);
    QObject::connect(ui->actionEnregistrer_sous, &QAction::triggered, this, &MainWindow::saveAs);
    QObject::connect(ui->actionExporter, &QAction::triggered, this, &MainWindow::exportToSVG);
    QObject::connect(ui->actionOuvrir, &QAction::triggered, this, &MainWindow::load);
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

void MainWindow::closeEvent(QCloseEvent *event) {
    if(!modified) {
        return QMainWindow::closeEvent(event);
    }
    int ret{saveQuestion()};

    switch(ret) {
    case QMessageBox::Save:
        save();
    case QMessageBox::Discard:
        event->accept();
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    }
}

QMessageBox::StandardButton MainWindow::saveQuestion() const {
    QMessageBox b;
    b.setIcon(QMessageBox::Warning);
    b.setText(tr("Les données ont été modifiées."));
    b.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
    b.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    b.setButtonText(QMessageBox::Save, tr("Sauvegarder"));
    b.setButtonText(QMessageBox::Discard, tr("Ne pas sauvegarder"));
    b.setButtonText(QMessageBox::Cancel, tr("Annuler"));
    b.setDefaultButton(QMessageBox::Save);
    return static_cast<QMessageBox::StandardButton>(b.exec());
}

void MainWindow::setModified(bool isModified) {
    modified = isModified;
    ui->actionEnregistrer->setEnabled(isModified);
    setTitle();
}

void MainWindow::setTitle() {
    QString t = QString("%1 - %2")
                .arg(TITLE).arg(currentSaveFile.isEmpty() ? "new" : currentSaveFile);
    if(modified) t.append("*");
    QMainWindow::setWindowTitle(t);
}

void MainWindow::setMousePosText(const QPointF& pos) {
    ui->textMousePosition->setText(QString("(%1;%2)").arg(QString::number(pos.x())).arg(QString::number(pos.y())));
}

void MainWindow::addPoint(const QPointF &pos) {
    Point* p = new Point(pos.x(), pos.y());
    this->data.getTriangulation(this->currentTriang)->addPoint(p);
    ui->tabPoints->model()->layoutChanged();
    graphicsScene->addPoint(p, currentTriang);
    setModified();
}

void MainWindow::addSegment(const QList<QGraphicsItem *> &list) {
    Segment* s = new Segment(((PointItem*)list.at(0))->getPoint(), ((PointItem*)list.at(1))->getPoint());
    this->data.getTriangulation(this->currentTriang)->addSegment(s);
    ui->tabSegments->model()->layoutChanged();
    graphicsScene->addSegment(s, currentTriang);
    setModified();
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
    setModified();
}

void MainWindow::changeDegree(int degree) {
    qDebug() << Q_FUNC_INFO << degree;
    ui->isVisible->setChecked(GraphicsScene::visibility(degree));
    QString qss = QString("background-color: %1").arg(GraphicsScene::color(degree).name());
    ui->colorButton->setStyleSheet(qss);
    currentTriang = degree;
    Triangulation* t(data.getTriangulation(degree));
    pointsTableModel->setTriangulation(data.getTriangulation(degree));
    ui->tabPoints->model()->layoutChanged();
    segmentsTableModel->setTriangulation(data.getTriangulation(degree));
    ui->tabSegments->model()->layoutChanged();
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
    setModified();
}

void MainWindow::generate() {
    Triangulation* t = data.getTriangulation(currentTriang);
    t->scanTriangles();
    for(auto r : t->getTriangles()) {
        graphicsScene->addTriangle(r, currentTriang);
    }
    setModified();
}

void MainWindow::nextOrder() {
    Triangulation* t = new Triangulation(&data);

    currentTriang = data.nbTriangulation() - 1;
    GraphicsScene::setVisibility(currentTriang, true);
    GraphicsScene::setColor(currentTriang, Qt::red);
    graphicsScene->paintTriangulation(t, currentTriang);
    ui->triBox->addItem(QString("Degré %1").arg(currentTriang + 1));
    ui->triBox->setCurrentIndex(currentTriang);
    //changeDegree(currentTriang);
    setModified();
}

void MainWindow::save(bool forced) {
    if(!modified && !forced) return;

    QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder"), "files/", tr("Save Files (*.save)"));
    if(filename.isNull()) return;

    qDebug() << "Saving in " << filename;
    std::ofstream fout{filename.toStdString()};
    fout << data;

    currentSaveFile = filename;
    setModified(false);
}

void MainWindow::saveAs() {
    save(true);
}

void MainWindow::exportToSVG() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter"), "files/", tr("SVG Files (*.svg)"));
    if(filename.isNull()) return;

    qDebug() << "Exporting in " << filename;
    data.exportToEPS(filename.toStdString());
}

void MainWindow::load() {
    if(modified) {
        int ret{saveQuestion()};
        switch(ret) {
        case QMessageBox::Save:
            save();
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
        }
    }

    QString filename = QFileDialog::getSaveFileName(this, tr("Ouvrir"), "files/", tr("Save Files (*.save)"));
    if(filename.isNull()) return;

    clear();
    qDebug() << "Restoring from " << filename;
    std::ifstream fin{filename.toStdString()};
    fin >> data;

    currentSaveFile = filename;

    currentTriang == 0 ? changeDegree(0) : ui->triBox->setCurrentIndex(data.nbTriangulation());
    setModified(false);
}

void MainWindow::clear() {
    //currentTriang = 0;
    int nb = data.nbTriangulation();
    data.clear();
    currentTriang == 0 ? changeDegree(0) : ui->triBox->setCurrentIndex(0);
    for(unsigned int i{1} ; i < nb ; ++i) ui->triBox->removeItem(1);
    graphicsView->likeANewBorn();
    graphicsScene->clear();
}

void MainWindow::newFile() {
    qDebug() << Q_FUNC_INFO;
    clear();
    currentSaveFile.clear();
    setModified(false);
}
