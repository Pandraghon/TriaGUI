/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouveau;
    QAction *actionEnregistrer;
    QAction *actionEnregistrer_sous;
    QAction *actionOuvrir;
    QAction *actionExporter;
    QAction *actionImporter;
    QAction *actionSelection;
    QAction *actionPoint;
    QAction *actionSegment;
    QAction *actionSuppression;
    QAction *actionTout_effacer;
    QAction *actionZoom;
    QAction *actionZoom_2;
    QAction *actionRecentrer;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label;
    QTableView *tabPoints;
    QLabel *label_2;
    QTableView *tabSegments;
    QVBoxLayout *drawingLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *textMousePosition;
    QSpacerItem *horizontalSpacer_2;
    QLabel *textSelectedPointName;
    QLabel *textSelectedPointPosition;
    QFrame *frame_2;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuDessin;
    QMenu *menuMode;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1058, 669);
        MainWindow->setBaseSize(QSize(530, 420));
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_sheet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNouveau->setIcon(icon);
        actionEnregistrer = new QAction(MainWindow);
        actionEnregistrer->setObjectName(QStringLiteral("actionEnregistrer"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_floppydisk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEnregistrer->setIcon(icon1);
        actionEnregistrer_sous = new QAction(MainWindow);
        actionEnregistrer_sous->setObjectName(QStringLiteral("actionEnregistrer_sous"));
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOuvrir->setIcon(icon2);
        actionExporter = new QAction(MainWindow);
        actionExporter->setObjectName(QStringLiteral("actionExporter"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExporter->setIcon(icon3);
        actionImporter = new QAction(MainWindow);
        actionImporter->setObjectName(QStringLiteral("actionImporter"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImporter->setIcon(icon4);
        actionSelection = new QAction(MainWindow);
        actionSelection->setObjectName(QStringLiteral("actionSelection"));
        actionSelection->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_mouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelection->setIcon(icon5);
        actionPoint = new QAction(MainWindow);
        actionPoint->setObjectName(QStringLiteral("actionPoint"));
        actionPoint->setCheckable(true);
        actionPoint->setChecked(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/software_pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPoint->setIcon(icon6);
        actionSegment = new QAction(MainWindow);
        actionSegment->setObjectName(QStringLiteral("actionSegment"));
        actionSegment->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_pencil_ruler.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSegment->setIcon(icon7);
        actionSuppression = new QAction(MainWindow);
        actionSuppression->setObjectName(QStringLiteral("actionSuppression"));
        actionSuppression->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/software_slice.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSuppression->setIcon(icon8);
        actionTout_effacer = new QAction(MainWindow);
        actionTout_effacer->setObjectName(QStringLiteral("actionTout_effacer"));
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_magnifier_plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon9);
        actionZoom_2 = new QAction(MainWindow);
        actionZoom_2->setObjectName(QStringLiteral("actionZoom_2"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_magnifier_minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_2->setIcon(icon10);
        actionRecentrer = new QAction(MainWindow);
        actionRecentrer->setObjectName(QStringLiteral("actionRecentrer"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/Desktop/_PNG 64_/basic_gunsight.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRecentrer->setIcon(icon11);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(300, 0));
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setBaseSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(comboBox);


        verticalLayout_3->addLayout(horizontalLayout_3);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(label);

        tabPoints = new QTableView(frame);
        tabPoints->setObjectName(QStringLiteral("tabPoints"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabPoints->sizePolicy().hasHeightForWidth());
        tabPoints->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(tabPoints);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(label_2);

        tabSegments = new QTableView(frame);
        tabSegments->setObjectName(QStringLiteral("tabSegments"));
        sizePolicy3.setHeightForWidth(tabSegments->sizePolicy().hasHeightForWidth());
        tabSegments->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(tabSegments);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout->addWidget(frame);

        drawingLayout = new QVBoxLayout();
        drawingLayout->setSpacing(6);
        drawingLayout->setObjectName(QStringLiteral("drawingLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textMousePosition = new QLabel(centralWidget);
        textMousePosition->setObjectName(QStringLiteral("textMousePosition"));

        horizontalLayout_2->addWidget(textMousePosition);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        textSelectedPointName = new QLabel(centralWidget);
        textSelectedPointName->setObjectName(QStringLiteral("textSelectedPointName"));

        horizontalLayout_2->addWidget(textSelectedPointName);

        textSelectedPointPosition = new QLabel(centralWidget);
        textSelectedPointPosition->setObjectName(QStringLiteral("textSelectedPointPosition"));

        horizontalLayout_2->addWidget(textSelectedPointPosition);


        drawingLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(drawingLayout);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(300, 0));
        frame_2->setMaximumSize(QSize(300, 16777215));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_2);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 26));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuDessin = new QMenu(menuBar);
        menuDessin->setObjectName(QStringLiteral("menuDessin"));
        menuMode = new QMenu(menuDessin);
        menuMode->setObjectName(QStringLiteral("menuMode"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuDessin->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addSeparator();
        menuFichier->addAction(actionEnregistrer);
        menuFichier->addAction(actionEnregistrer_sous);
        menuFichier->addSeparator();
        menuFichier->addAction(actionExporter);
        menuFichier->addAction(actionImporter);
        menuDessin->addAction(actionTout_effacer);
        menuDessin->addAction(menuMode->menuAction());
        menuDessin->addSeparator();
        menuDessin->addAction(actionZoom);
        menuDessin->addAction(actionZoom_2);
        menuDessin->addAction(actionRecentrer);
        menuMode->addAction(actionSelection);
        menuMode->addAction(actionPoint);
        menuMode->addAction(actionSegment);
        menuMode->addAction(actionSuppression);
        mainToolBar->addAction(actionNouveau);
        mainToolBar->addAction(actionOuvrir);
        mainToolBar->addAction(actionEnregistrer);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExporter);
        mainToolBar->addAction(actionImporter);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoom);
        mainToolBar->addAction(actionZoom_2);
        mainToolBar->addAction(actionRecentrer);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSelection);
        mainToolBar->addAction(actionPoint);
        mainToolBar->addAction(actionSegment);
        mainToolBar->addAction(actionSuppression);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNouveau->setText(QApplication::translate("MainWindow", "Nouveau", 0));
        actionEnregistrer->setText(QApplication::translate("MainWindow", "Enregistrer", 0));
        actionEnregistrer_sous->setText(QApplication::translate("MainWindow", "Enregistrer sous ...", 0));
        actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        actionExporter->setText(QApplication::translate("MainWindow", "Exporter", 0));
        actionImporter->setText(QApplication::translate("MainWindow", "Importer", 0));
        actionSelection->setText(QApplication::translate("MainWindow", "Selection", 0));
        actionPoint->setText(QApplication::translate("MainWindow", "Point", 0));
        actionPoint->setShortcut(QApplication::translate("MainWindow", "P", 0));
        actionSegment->setText(QApplication::translate("MainWindow", "Segment", 0));
        actionSegment->setShortcut(QApplication::translate("MainWindow", "S", 0));
        actionSuppression->setText(QApplication::translate("MainWindow", "Suppression", 0));
        actionSuppression->setShortcut(QApplication::translate("MainWindow", "D", 0));
        actionTout_effacer->setText(QApplication::translate("MainWindow", "Tout effacer", 0));
        actionZoom->setText(QApplication::translate("MainWindow", "Zoom +", 0));
        actionZoom_2->setText(QApplication::translate("MainWindow", "Zoom -", 0));
        actionRecentrer->setText(QApplication::translate("MainWindow", "Recentrer", 0));
        label_3->setText(QApplication::translate("MainWindow", "Triangulation : ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Degr\303\251 1", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Liste des points :", 0));
        label_2->setText(QApplication::translate("MainWindow", "Liste des segments :", 0));
        textMousePosition->setText(QApplication::translate("MainWindow", "(x;y)", 0));
        textSelectedPointName->setText(QApplication::translate("MainWindow", "P1", 0));
        textSelectedPointPosition->setText(QApplication::translate("MainWindow", "(x;y)", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menuDessin->setTitle(QApplication::translate("MainWindow", "Dessin", 0));
        menuMode->setTitle(QApplication::translate("MainWindow", "Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
