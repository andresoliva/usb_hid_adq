/********************************************************************************
** Form generated from reading UI file 'ui_usb_hid_adq.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_USB_HID_ADQ_H
#define UI_UI_USB_HID_ADQ_H

#include <../QTLIBs/QCustomPlot_5/qcustomplot.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabDemo;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_3;
    QPushButton *btnConnect;
    QScrollArea *scrollArea;
    QWidget *scrollAreaRegister;
    QLCDNumber *lcdcounter;
    QPushButton *btnSave;
    QDoubleSpinBox *distancia;
    QLabel *label_8;
    QRadioButton *rbZoomV;
    QRadioButton *rbZoomH;
    QRadioButton *rbZoomVH;
    QLabel *label_5;
    QPushButton *btnOpen;
    QPushButton *btnProcesar;
    QDoubleSpinBox *procesamiento_inicial;
    QDoubleSpinBox *procesamiento_final;
    QTextBrowser *result_GC;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QTextBrowser *result_Z0;
    QLabel *label_19;
    QLabel *label_20;
    QTextBrowser *result_FreqCardio;
    QLabel *label_21;
    QLabel *label_22;
    QFrame *line_4;
    QHBoxLayout *hlplot_DZ;
    QCustomPlot *plot;
    QHBoxLayout *hlplot_dZ;
    QCustomPlot *plot_dZ;
    QWidget *tab;
    QCheckBox *checkBox_usb_data_test;
    QCheckBox *checkBox_data_test;
    QCheckBox *checkBox_usb_test;
    QSpinBox *ventanaconvolucion;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *ventanagraficado;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QDoubleSpinBox *GZ;
    QDoubleSpinBox *GZ0;
    QDoubleSpinBox *GDZ;
    QDoubleSpinBox *Gderivada;
    QDoubleSpinBox *treshold_escala;
    QDoubleSpinBox *treshold;
    QSpinBox *ventana_peak_first;
    QSpinBox *ventana_peak;
    QLabel *label_11;
    QLabel *label_12;
    QDoubleSpinBox *Z0_offset;
    QLabel *label_13;
    QCheckBox *checkBox_PLOT_SIGNAL_Z;
    QCheckBox *checkBox_PLOT_SIGNAL_DZ;
    QCheckBox *checkBox_PLOT_SIGNAL_DZ_PB;
    QCheckBox *checkBox_PLOT_SIGNAL_DZ_PA;
    QCheckBox *checkBox_PLOT_SIGNAL_dZ;
    QCheckBox *checkBox_PLOT_SIGNAL_dZ_PEAK;
    QCheckBox *checkBox_INVERT_SIGNAL_dZ;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(500, 768));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        MainWindow->setBaseSize(QSize(1024, 768));
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(5);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setAutoFillBackground(true);
        tabWidget->setMovable(false);
        tabDemo = new QWidget();
        tabDemo->setObjectName(QStringLiteral("tabDemo"));
        tabDemo->setEnabled(true);
        verticalLayout_6 = new QVBoxLayout(tabDemo);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(9);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 9);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_3->setHorizontalSpacing(2);
        btnConnect = new QPushButton(tabDemo);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        btnConnect->setFont(font);
        btnConnect->setCursor(QCursor(Qt::OpenHandCursor));

        gridLayout_3->addWidget(btnConnect, 0, 0, 1, 1);

        scrollArea = new QScrollArea(tabDemo);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(500, 100));
        scrollArea->setMaximumSize(QSize(99999, 100));
        scrollArea->setWidgetResizable(true);
        scrollAreaRegister = new QWidget();
        scrollAreaRegister->setObjectName(QStringLiteral("scrollAreaRegister"));
        scrollAreaRegister->setGeometry(QRect(0, 0, 968, 98));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaRegister->sizePolicy().hasHeightForWidth());
        scrollAreaRegister->setSizePolicy(sizePolicy2);
        scrollAreaRegister->setMinimumSize(QSize(300, 90));
        scrollAreaRegister->setBaseSize(QSize(700, 90));
        lcdcounter = new QLCDNumber(scrollAreaRegister);
        lcdcounter->setObjectName(QStringLiteral("lcdcounter"));
        lcdcounter->setEnabled(false);
        lcdcounter->setGeometry(QRect(560, 100, 131, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Fixedsys"));
        font1.setPointSize(12);
        lcdcounter->setFont(font1);
        btnSave = new QPushButton(scrollAreaRegister);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(10, 30, 95, 23));
        btnSave->setCursor(QCursor(Qt::PointingHandCursor));
        distancia = new QDoubleSpinBox(scrollAreaRegister);
        distancia->setObjectName(QStringLiteral("distancia"));
        distancia->setGeometry(QRect(270, 30, 61, 20));
        distancia->setCursor(QCursor(Qt::IBeamCursor));
        distancia->setDecimals(2);
        distancia->setMinimum(1);
        distancia->setMaximum(3000);
        distancia->setSingleStep(1);
        distancia->setValue(173);
        label_8 = new QLabel(scrollAreaRegister);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(270, 0, 51, 21));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_8->setFont(font2);
        rbZoomV = new QRadioButton(scrollAreaRegister);
        rbZoomV->setObjectName(QStringLiteral("rbZoomV"));
        rbZoomV->setEnabled(true);
        rbZoomV->setGeometry(QRect(120, 30, 71, 17));
        rbZoomV->setCursor(QCursor(Qt::ClosedHandCursor));
        rbZoomV->setChecked(false);
        rbZoomH = new QRadioButton(scrollAreaRegister);
        rbZoomH->setObjectName(QStringLiteral("rbZoomH"));
        rbZoomH->setEnabled(true);
        rbZoomH->setGeometry(QRect(120, 50, 71, 17));
        rbZoomH->setCursor(QCursor(Qt::ClosedHandCursor));
        rbZoomH->setChecked(true);
        rbZoomVH = new QRadioButton(scrollAreaRegister);
        rbZoomVH->setObjectName(QStringLiteral("rbZoomVH"));
        rbZoomVH->setEnabled(true);
        rbZoomVH->setGeometry(QRect(120, 70, 56, 17));
        rbZoomVH->setCursor(QCursor(Qt::ClosedHandCursor));
        label_5 = new QLabel(scrollAreaRegister);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(120, 10, 51, 21));
        label_5->setFont(font);
        btnOpen = new QPushButton(scrollAreaRegister);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setGeometry(QRect(10, 60, 95, 23));
        btnOpen->setCursor(QCursor(Qt::PointingHandCursor));
        btnProcesar = new QPushButton(scrollAreaRegister);
        btnProcesar->setObjectName(QStringLiteral("btnProcesar"));
        btnProcesar->setGeometry(QRect(540, 10, 95, 23));
        btnProcesar->setCursor(QCursor(Qt::PointingHandCursor));
        procesamiento_inicial = new QDoubleSpinBox(scrollAreaRegister);
        procesamiento_inicial->setObjectName(QStringLiteral("procesamiento_inicial"));
        procesamiento_inicial->setGeometry(QRect(660, 40, 61, 20));
        procesamiento_inicial->setCursor(QCursor(Qt::IBeamCursor));
        procesamiento_inicial->setDecimals(2);
        procesamiento_inicial->setMinimum(0);
        procesamiento_inicial->setMaximum(30100);
        procesamiento_inicial->setSingleStep(1);
        procesamiento_inicial->setValue(10);
        procesamiento_final = new QDoubleSpinBox(scrollAreaRegister);
        procesamiento_final->setObjectName(QStringLiteral("procesamiento_final"));
        procesamiento_final->setGeometry(QRect(660, 70, 61, 20));
        procesamiento_final->setCursor(QCursor(Qt::IBeamCursor));
        procesamiento_final->setDecimals(2);
        procesamiento_final->setMinimum(0);
        procesamiento_final->setMaximum(3000.99);
        procesamiento_final->setSingleStep(1);
        procesamiento_final->setValue(30);
        result_GC = new QTextBrowser(scrollAreaRegister);
        result_GC->setObjectName(QStringLiteral("result_GC"));
        result_GC->setGeometry(QRect(370, 20, 61, 31));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        result_GC->setFont(font3);
        result_GC->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ForbiddenCursor)));
        result_GC->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        result_GC->setOpenLinks(true);
        label_15 = new QLabel(scrollAreaRegister);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(370, 0, 131, 20));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setUnderline(false);
        font4.setWeight(75);
        font4.setStrikeOut(false);
        label_15->setFont(font4);
        label_16 = new QLabel(scrollAreaRegister);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(260, 50, 121, 16));
        QFont font5;
        font5.setBold(false);
        font5.setWeight(50);
        label_16->setFont(font5);
        label_17 = new QLabel(scrollAreaRegister);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(540, 40, 121, 20));
        label_18 = new QLabel(scrollAreaRegister);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(540, 70, 121, 20));
        result_Z0 = new QTextBrowser(scrollAreaRegister);
        result_Z0->setObjectName(QStringLiteral("result_Z0"));
        result_Z0->setGeometry(QRect(270, 70, 61, 21));
        result_Z0->setFont(font);
        result_Z0->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ForbiddenCursor)));
        result_Z0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_19 = new QLabel(scrollAreaRegister);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(340, 70, 21, 21));
        label_19->setFont(font);
        label_20 = new QLabel(scrollAreaRegister);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(440, 20, 61, 31));
        label_20->setFont(font2);
        label_20->setTextFormat(Qt::RichText);
        result_FreqCardio = new QTextBrowser(scrollAreaRegister);
        result_FreqCardio->setObjectName(QStringLiteral("result_FreqCardio"));
        result_FreqCardio->setGeometry(QRect(370, 70, 61, 21));
        result_FreqCardio->setFont(font2);
        result_FreqCardio->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ForbiddenCursor)));
        result_FreqCardio->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        result_FreqCardio->setOpenLinks(true);
        label_21 = new QLabel(scrollAreaRegister);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(440, 70, 61, 21));
        label_21->setFont(font2);
        label_21->setTextFormat(Qt::RichText);
        label_22 = new QLabel(scrollAreaRegister);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(370, 50, 161, 20));
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(true);
        font6.setItalic(true);
        font6.setUnderline(false);
        font6.setWeight(75);
        font6.setStrikeOut(false);
        label_22->setFont(font6);
        scrollArea->setWidget(scrollAreaRegister);

        gridLayout_3->addWidget(scrollArea, 3, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_3);


        verticalLayout_6->addLayout(horizontalLayout_3);

        line_4 = new QFrame(tabDemo);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(5);
        sizePolicy3.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy3);
        line_4->setMinimumSize(QSize(700, 2));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_4);

        hlplot_DZ = new QHBoxLayout();
        hlplot_DZ->setSpacing(0);
        hlplot_DZ->setObjectName(QStringLiteral("hlplot_DZ"));
        hlplot_DZ->setSizeConstraint(QLayout::SetFixedSize);
        plot = new QCustomPlot(tabDemo);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy4);
        plot->setMinimumSize(QSize(600, 200));
        plot->setMaximumSize(QSize(9999, 9999));
        plot->setBaseSize(QSize(0, 0));
        plot->setMouseTracking(false);
        plot->setFocusPolicy(Qt::StrongFocus);

        hlplot_DZ->addWidget(plot);


        verticalLayout_6->addLayout(hlplot_DZ);

        hlplot_dZ = new QHBoxLayout();
        hlplot_dZ->setSpacing(6);
        hlplot_dZ->setObjectName(QStringLiteral("hlplot_dZ"));
        plot_dZ = new QCustomPlot(tabDemo);
        plot_dZ->setObjectName(QStringLiteral("plot_dZ"));
        plot_dZ->setMinimumSize(QSize(600, 200));

        hlplot_dZ->addWidget(plot_dZ);


        verticalLayout_6->addLayout(hlplot_dZ);

        tabWidget->addTab(tabDemo, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        checkBox_usb_data_test = new QCheckBox(tab);
        checkBox_usb_data_test->setObjectName(QStringLiteral("checkBox_usb_data_test"));
        checkBox_usb_data_test->setGeometry(QRect(10, 10, 121, 20));
        checkBox_data_test = new QCheckBox(tab);
        checkBox_data_test->setObjectName(QStringLiteral("checkBox_data_test"));
        checkBox_data_test->setGeometry(QRect(10, 30, 91, 20));
        checkBox_usb_test = new QCheckBox(tab);
        checkBox_usb_test->setObjectName(QStringLiteral("checkBox_usb_test"));
        checkBox_usb_test->setGeometry(QRect(10, 50, 759, 17));
        ventanaconvolucion = new QSpinBox(tab);
        ventanaconvolucion->setObjectName(QStringLiteral("ventanaconvolucion"));
        ventanaconvolucion->setGeometry(QRect(130, 10, 51, 20));
        ventanaconvolucion->setMinimum(50);
        ventanaconvolucion->setMaximum(10000);
        ventanaconvolucion->setValue(1000);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 10, 101, 20));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(200, 30, 91, 20));
        ventanagraficado = new QSpinBox(tab);
        ventanagraficado->setObjectName(QStringLiteral("ventanagraficado"));
        ventanagraficado->setGeometry(QRect(130, 40, 51, 20));
        ventanagraficado->setMinimum(10);
        ventanagraficado->setMaximum(10000);
        ventanagraficado->setValue(1000);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(380, 10, 101, 20));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(380, 30, 101, 20));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(380, 50, 101, 20));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(470, 10, 101, 20));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(470, 30, 101, 20));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(490, 50, 71, 20));
        GZ = new QDoubleSpinBox(tab);
        GZ->setObjectName(QStringLiteral("GZ"));
        GZ->setGeometry(QRect(310, 10, 61, 21));
        QFont font7;
        font7.setPointSize(8);
        font7.setStyleStrategy(QFont::PreferAntialias);
        GZ->setFont(font7);
        GZ->setAutoFillBackground(false);
        GZ->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        GZ->setWrapping(false);
        GZ->setAccelerated(false);
        GZ->setKeyboardTracking(true);
        GZ->setDecimals(4);
        GZ->setMinimum(0.01);
        GZ->setMaximum(1000);
        GZ->setSingleStep(1);
        GZ->setValue(155.39);
        GZ0 = new QDoubleSpinBox(tab);
        GZ0->setObjectName(QStringLiteral("GZ0"));
        GZ0->setGeometry(QRect(310, 30, 61, 20));
        GZ0->setDecimals(2);
        GZ0->setMinimum(0);
        GZ0->setSingleStep(1);
        GZ0->setValue(0.5);
        GDZ = new QDoubleSpinBox(tab);
        GDZ->setObjectName(QStringLiteral("GDZ"));
        GDZ->setGeometry(QRect(310, 49, 61, 21));
        GDZ->setDecimals(2);
        GDZ->setMinimum(1);
        GDZ->setMaximum(200.99);
        GDZ->setSingleStep(1);
        GDZ->setValue(34);
        Gderivada = new QDoubleSpinBox(tab);
        Gderivada->setObjectName(QStringLiteral("Gderivada"));
        Gderivada->setGeometry(QRect(410, 10, 51, 20));
        Gderivada->setDecimals(2);
        Gderivada->setMinimum(-1000);
        Gderivada->setMaximum(100000);
        Gderivada->setSingleStep(1);
        Gderivada->setValue(1000);
        treshold_escala = new QDoubleSpinBox(tab);
        treshold_escala->setObjectName(QStringLiteral("treshold_escala"));
        treshold_escala->setGeometry(QRect(410, 30, 51, 20));
        treshold_escala->setDecimals(2);
        treshold_escala->setMinimum(0);
        treshold_escala->setSingleStep(0.1);
        treshold_escala->setValue(0.5);
        treshold = new QDoubleSpinBox(tab);
        treshold->setObjectName(QStringLiteral("treshold"));
        treshold->setGeometry(QRect(410, 50, 61, 20));
        treshold->setDecimals(2);
        treshold->setMinimum(0);
        treshold->setMaximum(10000);
        treshold->setSingleStep(1);
        treshold->setValue(0.01);
        ventana_peak_first = new QSpinBox(tab);
        ventana_peak_first->setObjectName(QStringLiteral("ventana_peak_first"));
        ventana_peak_first->setGeometry(QRect(580, 10, 51, 20));
        ventana_peak_first->setMinimum(10);
        ventana_peak_first->setMaximum(10000);
        ventana_peak_first->setValue(2000);
        ventana_peak = new QSpinBox(tab);
        ventana_peak->setObjectName(QStringLiteral("ventana_peak"));
        ventana_peak->setGeometry(QRect(580, 30, 51, 20));
        ventana_peak->setMinimum(10);
        ventana_peak->setMaximum(10000);
        ventana_peak->setValue(300);
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(640, 10, 101, 20));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(640, 30, 101, 20));
        Z0_offset = new QDoubleSpinBox(tab);
        Z0_offset->setObjectName(QStringLiteral("Z0_offset"));
        Z0_offset->setGeometry(QRect(310, 70, 61, 20));
        Z0_offset->setDecimals(3);
        Z0_offset->setMinimum(0);
        Z0_offset->setMaximum(10001);
        Z0_offset->setSingleStep(1);
        Z0_offset->setValue(0);
        label_13 = new QLabel(tab);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(380, 70, 101, 20));
        checkBox_PLOT_SIGNAL_Z = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_Z->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_Z"));
        checkBox_PLOT_SIGNAL_Z->setGeometry(QRect(260, 100, 161, 17));
        checkBox_PLOT_SIGNAL_Z->setChecked(false);
        checkBox_PLOT_SIGNAL_Z->setAutoRepeat(false);
        checkBox_PLOT_SIGNAL_DZ = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_DZ->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_DZ"));
        checkBox_PLOT_SIGNAL_DZ->setGeometry(QRect(260, 120, 161, 17));
        checkBox_PLOT_SIGNAL_DZ->setChecked(true);
        checkBox_PLOT_SIGNAL_DZ->setAutoRepeat(false);
        checkBox_PLOT_SIGNAL_DZ_PB = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_DZ_PB->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_DZ_PB"));
        checkBox_PLOT_SIGNAL_DZ_PB->setGeometry(QRect(260, 140, 161, 17));
        checkBox_PLOT_SIGNAL_DZ_PB->setChecked(true);
        checkBox_PLOT_SIGNAL_DZ_PA = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_DZ_PA->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_DZ_PA"));
        checkBox_PLOT_SIGNAL_DZ_PA->setGeometry(QRect(260, 160, 161, 17));
        checkBox_PLOT_SIGNAL_DZ_PA->setChecked(true);
        checkBox_PLOT_SIGNAL_dZ = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_dZ->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_dZ"));
        checkBox_PLOT_SIGNAL_dZ->setGeometry(QRect(260, 180, 161, 17));
        checkBox_PLOT_SIGNAL_dZ->setChecked(true);
        checkBox_PLOT_SIGNAL_dZ_PEAK = new QCheckBox(tab);
        checkBox_PLOT_SIGNAL_dZ_PEAK->setObjectName(QStringLiteral("checkBox_PLOT_SIGNAL_dZ_PEAK"));
        checkBox_PLOT_SIGNAL_dZ_PEAK->setEnabled(true);
        checkBox_PLOT_SIGNAL_dZ_PEAK->setGeometry(QRect(260, 200, 161, 17));
        checkBox_PLOT_SIGNAL_dZ_PEAK->setChecked(true);
        checkBox_INVERT_SIGNAL_dZ = new QCheckBox(tab);
        checkBox_INVERT_SIGNAL_dZ->setObjectName(QStringLiteral("checkBox_INVERT_SIGNAL_dZ"));
        checkBox_INVERT_SIGNAL_dZ->setGeometry(QRect(410, 180, 191, 17));
        checkBox_INVERT_SIGNAL_dZ->setChecked(true);
        tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnConnect->setText(QApplication::translate("MainWindow", "Iniciar Adquisici\303\263n", 0));
        btnSave->setText(QApplication::translate("MainWindow", "Guardar", 0));
#ifndef QT_NO_TOOLTIP
        distancia->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("MainWindow", "Altura", 0));
        rbZoomV->setText(QApplication::translate("MainWindow", "Vertical", 0));
        rbZoomH->setText(QApplication::translate("MainWindow", "Horizontal", 0));
        rbZoomVH->setText(QApplication::translate("MainWindow", "VerHor", 0));
        label_5->setText(QApplication::translate("MainWindow", "Ampliar", 0));
        btnOpen->setText(QApplication::translate("MainWindow", "Abrir", 0));
        btnProcesar->setText(QApplication::translate("MainWindow", "Procesar", 0));
#ifndef QT_NO_TOOLTIP
        procesamiento_inicial->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        procesamiento_final->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("MainWindow", "Gasto Cardiaco", 0));
        label_16->setText(QApplication::translate("MainWindow", "Impedancia Basal Z0", 0));
        label_17->setText(QApplication::translate("MainWindow", "Inicio de procesamiento", 0));
        label_18->setText(QApplication::translate("MainWindow", "Final de procesamiento", 0));
#ifndef QT_NO_STATUSTIP
        label_19->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_19->setText(QApplication::translate("MainWindow", "[\316\251]", 0));
#ifndef QT_NO_TOOLTIP
        label_20->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_20->setText(QApplication::translate("MainWindow", "[L/min]", 0));
#ifndef QT_NO_TOOLTIP
        label_21->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("MainWindow", "[1/min]", 0));
        label_22->setText(QApplication::translate("MainWindow", "Frecuencia Card\303\255aca", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabDemo), QApplication::translate("MainWindow", "Ventana Principal", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_usb_data_test->setToolTip(QApplication::translate("MainWindow", "Puentea la comunicaic\303\263n USB\n"
"", 0));
#endif // QT_NO_TOOLTIP
        checkBox_usb_data_test->setText(QApplication::translate("MainWindow", "USB DATA TEST ON", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_data_test->setToolTip(QApplication::translate("MainWindow", "Reemplaza los datos adquiridos via USB\n"
"por datos guardados en un archivo", 0));
#endif // QT_NO_TOOLTIP
        checkBox_data_test->setText(QApplication::translate("MainWindow", "DATA TEST ON", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_usb_test->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_usb_test->setText(QApplication::translate("MainWindow", "USB TEST on", 0));
#ifndef QT_NO_TOOLTIP
        ventanaconvolucion->setToolTip(QApplication::translate("MainWindow", "Determina el numero de puntos cada el cual realizo la operaci\303\263n\n"
"de convolucion.\n"
"Esto determina los intervalos a los cuales se realiza\n"
"El procesamiento de los datos\n"
"Y el graficado de los valores, que depende del tama\303\261o\n"
"de ventana elegido\n"
"", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "Convolution points", 0));
        label_2->setText(QApplication::translate("MainWindow", "Window plot", 0));
#ifndef QT_NO_TOOLTIP
        ventanagraficado->setToolTip(QApplication::translate("MainWindow", "Determina la cantidad de puntos mostrados \n"
"cada vez que se realiza un grafico", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "G Z", 0));
        label_4->setText(QApplication::translate("MainWindow", "G Z0", 0));
        label_6->setText(QApplication::translate("MainWindow", "G DZ", 0));
        label_7->setText(QApplication::translate("MainWindow", "G Derivada[+ o -]", 0));
        label_9->setText(QApplication::translate("MainWindow", "%treshold escala pico", 0));
        label_10->setText(QApplication::translate("MainWindow", "treshold min", 0));
#ifndef QT_NO_TOOLTIP
        GZ->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        GZ->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_TOOLTIP
        GZ0->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        GDZ->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        Gderivada->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        treshold_escala->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        treshold->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ventana_peak_first->setToolTip(QApplication::translate("MainWindow", "Determina la cantidad de puntos mostrados \n"
"cada vez que se realiza un grafico", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ventana_peak->setToolTip(QApplication::translate("MainWindow", "Determina la cantidad de puntos mostrados \n"
"cada vez que se realiza un grafico", 0));
#endif // QT_NO_TOOLTIP
        label_11->setText(QApplication::translate("MainWindow", "ventana  peak_first", 0));
        label_12->setText(QApplication::translate("MainWindow", "ventana  peak", 0));
#ifndef QT_NO_TOOLTIP
        Z0_offset->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_13->setText(QApplication::translate("MainWindow", "Z0 offset", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_Z->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_Z->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_Z", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_DZ", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ_PB->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ_PB->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_DZ_LP", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ_PA->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_DZ_PA->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_DZ_PA", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_dZ->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_dZ->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_dZ", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_dZ_PEAK->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_PLOT_SIGNAL_dZ_PEAK->setText(QApplication::translate("MainWindow", "PLOT_SIGNAL_dZ_PEAK", 0));
#ifndef QT_NO_TOOLTIP
        checkBox_INVERT_SIGNAL_dZ->setToolTip(QApplication::translate("MainWindow", "Tildado: Puentea la comunicaci\303\263n USB,\n"
"simula los datos adquiridos con datos gardados", 0));
#endif // QT_NO_TOOLTIP
        checkBox_INVERT_SIGNAL_dZ->setText(QApplication::translate("MainWindow", "PLOT_INVERT_SIGNAL_dZ", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Configuraci\303\263n", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_USB_HID_ADQ_H
