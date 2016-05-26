#include "segmentstablemodel.h"

SegmentsTableModel::SegmentsTableModel(Triangulation* triang, QObject *parent) :
    QAbstractTableModel(parent),
    m_triang(triang),
    m_headers({tr("P1"), tr("P2"), tr("actions")})
{
}

int SegmentsTableModel::rowCount(const QModelIndex & /*parent*/) const {
    return m_triang->getSegments().size() + 1;
}

int SegmentsTableModel::columnCount(const QModelIndex & /*parent*/) const {
    return 3;
}

QVariant SegmentsTableModel::data(const QModelIndex &index, int role) const {
    int row{index.row()};
    int col{index.column()};

    switch(role) {
        case Qt::DisplayRole:
            if(row < m_triang->getSegments().size()) {
                switch(col) {
                    case 0:
                        return QString::fromStdString(m_triang->getSegment(row)->getP0()->getNom());
                    case 1:
                        return QString::fromStdString(m_triang->getSegment(row)->getP1()->getNom());
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

QVariant SegmentsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            return m_headers[section];
        } else {
            return QString("S%1").arg(section + 1);
        }
    }

    return QVariant();
}

bool SegmentsTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    int row{index.row()};
    int col{index.column()};
    if(role == Qt::EditRole) {
        if(value.toString() == "") return false;
        float v = value.toFloat();
        if(row < m_triang->getPoints().size()) {
            switch(col) {
            case 0:
                //m_triang->getPoint(row)->setX(v);
                break;
            case 1:
                //m_triang->getPoint(row)->setY(v);
                break;
            }
        }
        emit editCompleted(value.toString());
    }
    return true;
}

Qt::ItemFlags SegmentsTableModel::flags(const QModelIndex &index) const {
    if(index.column() == 2) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void SegmentsTableModel::setTriangulation(Triangulation* triang) {
    m_triang = triang;
}
