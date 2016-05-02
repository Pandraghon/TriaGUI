/********************************************************************************
** Form generated from reading UI file 'pointstablemodel.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTSTABLEMODEL_H
#define UI_POINTSTABLEMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PointsTableModel
{
public:

    void setupUi(QWidget *PointsTableModel)
    {
        if (PointsTableModel->objectName().isEmpty())
            PointsTableModel->setObjectName(QStringLiteral("PointsTableModel"));
        PointsTableModel->resize(400, 300);

        retranslateUi(PointsTableModel);

        QMetaObject::connectSlotsByName(PointsTableModel);
    } // setupUi

    void retranslateUi(QWidget *PointsTableModel)
    {
        PointsTableModel->setWindowTitle(QApplication::translate("PointsTableModel", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class PointsTableModel: public Ui_PointsTableModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTSTABLEMODEL_H
