#include "pointstablemodel.h"

#include <QDebug>

PointsTableModel::PointsTableModel(Triangulation *triang, QObject *parent) :
    QAbstractTableModel(parent),
    m_triang(triang),
    m_headers({tr("x"), tr("y"), tr("actions")})
{
}

int PointsTableModel::rowCount(const QModelIndex & /*parent*/) const {
    return m_triang->getPoints().size() + 1;
}

int PointsTableModel::columnCount(const QModelIndex & /*parent*/) const {
    return 3;
}

QVariant PointsTableModel::data(const QModelIndex &index, int role) const {
    int row{index.row()};
    int col{index.column()};

    switch(role) {
        case Qt::DisplayRole:
            if(row < m_triang->getPoints().size()) {
                switch(col) {
                    case 0:
                        return m_triang->getPoint(row)->getX();
                    case 1:
                        return m_triang->getPoint(row)->getY();
                }
            }
            break;
        case Qt::FontRole:
            break;
        case Qt::BackgroundRole:
            break;
        case Qt::TextAlignmentRole:
            break;
    }

    return QVariant();
}

QVariant PointsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            return m_headers[section];
        } else {
            return QString("P%1").arg(section + 1);
        }
    }

    return QVariant();
}

bool PointsTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    int row{index.row()};
    int col{index.column()};
    if(role == Qt::EditRole) {
        if(value.toString() == "") return false;
        float v = value.toFloat();
        if(row < m_triang->getPoints().size()) {
            switch(col) {
            case 0:
                m_triang->getPoint(row)->setX(v);
                break;
            case 1:
                m_triang->getPoint(row)->setY(v);
                break;
            }
        }
        emit editCompleted(value.toString());
    }
    return true;
}

Qt::ItemFlags PointsTableModel::flags(const QModelIndex &index) const {
    if(index.column() == 2) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void PointsTableModel::setTriangulation(Triangulation* triang) {
    m_triang = triang;
}
