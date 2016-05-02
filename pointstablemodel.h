#ifndef POINTSTABLEMODEL_H
#define POINTSTABLEMODEL_H

#include <QAbstractTableModel>

#include "triangulation.h"

class PointsTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PointsTableModel(Triangulation* triang, QWidget *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    Triangulation* m_triang;
};

#endif // POINTSTABLEMODEL_H
