#include "pointstablemodel.h"
#include "ui_pointstablemodel.h"

PointsTableModel::PointsTableModel(Triangulation *triang, QWidget *parent) :
    QAbstractTableModel(parent),
    m_triang(triang)
{
}

int PointsTableModel::rowCount(const QModelIndex & /*parent*/) const {
    return m_triang->getPoints().size();
}

int PointsTableModel::columnCount(const QModelIndex & /*parent*/) const {
    return 4;
}

QVariant PointsTableModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return QString("P%1").arg(index.row() + 1);
        case 1:
            return m_triang->getPoints()[index.row()]->getX();
        case 2:
            return m_triang->getPoints()[index.row()]->getY();
        }
    }
    return QVariant();
}
