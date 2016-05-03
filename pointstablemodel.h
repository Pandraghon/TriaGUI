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
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setTriangulation(Triangulation* triang);

private:
    Triangulation* m_triang;
    QString m_headers[3];

signals:
    void editCompleted(const QString &);
};

#endif // POINTSTABLEMODEL_H
