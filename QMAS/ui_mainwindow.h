/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSpinBox *spin_col;
    QPushButton *btn_run_by_step;
    QPushButton *btn_exit;
    QPushButton *btn_generate_obstacle;
    QPushButton *btn_genarate_taskpoint;
    QLabel *lab_title_input;
    QPushButton *btn_run_by_stage;
    QLabel *lab_title_input_2;
    QTextBrowser *textBrowser;
    QFrame *line_1;
    QPushButton *btn_reset_mas;
    QLabel *label_name_row;
    QFrame *line_3;
    QPushButton *btn_run_global;
    QPushButton *btn_run_Dynamic;
    QGraphicsView *gv_map;
    QLabel *label_name_col;
    QLabel *lab_title_output;
    QPushButton *btn_generate_map;
    QFrame *line_2;
    QLabel *lab_title_input_1;
    QSpinBox *spin_row;
    QPushButton *btn_openfile;
    QLabel *label_mapsize;
    QFrame *line_0;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *lab_filename;
    QLabel *label_readme;
    QFrame *line_4;
    QPushButton *btn_map_bigger;
    QPushButton *btn_map_smaller;
    QFrame *line_5;
    QLabel *lab_title_output_2;
    QPushButton *btn_reset_map;
    QPushButton *btn_run_reset;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(740, 520);
        MainWindow->setMinimumSize(QSize(740, 520));
        MainWindow->setMaximumSize(QSize(740, 520));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../resources/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(40, 40));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        spin_col = new QSpinBox(centralWidget);
        spin_col->setObjectName(QString::fromUtf8("spin_col"));
        spin_col->setGeometry(QRect(669, 130, 42, 22));
        spin_col->setMinimum(2);
        spin_col->setValue(10);
        btn_run_by_step = new QPushButton(centralWidget);
        btn_run_by_step->setObjectName(QString::fromUtf8("btn_run_by_step"));
        btn_run_by_step->setGeometry(QRect(560, 340, 80, 30));
        btn_run_by_step->setCheckable(false);
        btn_exit = new QPushButton(centralWidget);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(670, 475, 60, 40));
        btn_generate_obstacle = new QPushButton(centralWidget);
        btn_generate_obstacle->setObjectName(QString::fromUtf8("btn_generate_obstacle"));
        btn_generate_obstacle->setGeometry(QRect(600, 190, 60, 30));
        btn_genarate_taskpoint = new QPushButton(centralWidget);
        btn_genarate_taskpoint->setObjectName(QString::fromUtf8("btn_genarate_taskpoint"));
        btn_genarate_taskpoint->setGeometry(QRect(670, 190, 60, 30));
        lab_title_input = new QLabel(centralWidget);
        lab_title_input->setObjectName(QString::fromUtf8("lab_title_input"));
        lab_title_input->setGeometry(QRect(519, 13, 54, 12));
        btn_run_by_stage = new QPushButton(centralWidget);
        btn_run_by_stage->setObjectName(QString::fromUtf8("btn_run_by_stage"));
        btn_run_by_stage->setGeometry(QRect(650, 340, 80, 30));
        lab_title_input_2 = new QLabel(centralWidget);
        lab_title_input_2->setObjectName(QString::fromUtf8("lab_title_input_2"));
        lab_title_input_2->setGeometry(QRect(520, 110, 60, 20));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(520, 380, 210, 90));
        line_1 = new QFrame(centralWidget);
        line_1->setObjectName(QString::fromUtf8("line_1"));
        line_1->setGeometry(QRect(520, 100, 210, 15));
        line_1->setFrameShape(QFrame::HLine);
        line_1->setFrameShadow(QFrame::Sunken);
        btn_reset_mas = new QPushButton(centralWidget);
        btn_reset_mas->setObjectName(QString::fromUtf8("btn_reset_mas"));
        btn_reset_mas->setGeometry(QRect(530, 475, 60, 40));
        label_name_row = new QLabel(centralWidget);
        label_name_row->setObjectName(QString::fromUtf8("label_name_row"));
        label_name_row->setGeometry(QRect(644, 130, 20, 20));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(520, 370, 210, 10));
        line_3->setLineWidth(2);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        btn_run_global = new QPushButton(centralWidget);
        btn_run_global->setObjectName(QString::fromUtf8("btn_run_global"));
        btn_run_global->setGeometry(QRect(560, 275, 80, 60));
        btn_run_Dynamic = new QPushButton(centralWidget);
        btn_run_Dynamic->setObjectName(QString::fromUtf8("btn_run_Dynamic"));
        btn_run_Dynamic->setGeometry(QRect(650, 275, 80, 60));
        gv_map = new QGraphicsView(centralWidget);
        gv_map->setObjectName(QString::fromUtf8("gv_map"));
        gv_map->setGeometry(QRect(10, 10, 500, 500));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gv_map->sizePolicy().hasHeightForWidth());
        gv_map->setSizePolicy(sizePolicy);
        gv_map->setMinimumSize(QSize(500, 500));
        gv_map->setInteractive(false);
        gv_map->setSceneRect(QRectF(0, 0, 0, 0));
        gv_map->setDragMode(QGraphicsView::NoDrag);
        label_name_col = new QLabel(centralWidget);
        label_name_col->setObjectName(QString::fromUtf8("label_name_col"));
        label_name_col->setGeometry(QRect(715, 130, 20, 20));
        lab_title_output = new QLabel(centralWidget);
        lab_title_output->setObjectName(QString::fromUtf8("lab_title_output"));
        lab_title_output->setGeometry(QRect(520, 278, 40, 20));
        lab_title_output->setTextFormat(Qt::AutoText);
        btn_generate_map = new QPushButton(centralWidget);
        btn_generate_map->setObjectName(QString::fromUtf8("btn_generate_map"));
        btn_generate_map->setGeometry(QRect(550, 155, 180, 30));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(520, 220, 210, 15));
        line_2->setFrameShadow(QFrame::Sunken);
        line_2->setLineWidth(3);
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::HLine);
        lab_title_input_1 = new QLabel(centralWidget);
        lab_title_input_1->setObjectName(QString::fromUtf8("lab_title_input_1"));
        lab_title_input_1->setGeometry(QRect(521, 30, 71, 16));
        spin_row = new QSpinBox(centralWidget);
        spin_row->setObjectName(QString::fromUtf8("spin_row"));
        spin_row->setGeometry(QRect(599, 130, 42, 22));
        spin_row->setMinimum(2);
        spin_row->setValue(10);
        btn_openfile = new QPushButton(centralWidget);
        btn_openfile->setObjectName(QString::fromUtf8("btn_openfile"));
        btn_openfile->setGeometry(QRect(630, 30, 100, 23));
        label_mapsize = new QLabel(centralWidget);
        label_mapsize->setObjectName(QString::fromUtf8("label_mapsize"));
        label_mapsize->setGeometry(QRect(565, 130, 30, 20));
        label_mapsize->setAcceptDrops(false);
        line_0 = new QFrame(centralWidget);
        line_0->setObjectName(QString::fromUtf8("line_0"));
        line_0->setGeometry(QRect(520, 20, 211, 16));
        line_0->setFrameShape(QFrame::HLine);
        line_0->setFrameShadow(QFrame::Sunken);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(520, 60, 210, 40));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 208, 38));
        scrollAreaWidgetContents->setContextMenuPolicy(Qt::DefaultContextMenu);
        scrollAreaWidgetContents->setAcceptDrops(false);
        lab_filename = new QLabel(scrollAreaWidgetContents);
        lab_filename->setObjectName(QString::fromUtf8("lab_filename"));
        lab_filename->setGeometry(QRect(0, 0, 91, 21));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_readme = new QLabel(centralWidget);
        label_readme->setObjectName(QString::fromUtf8("label_readme"));
        label_readme->setGeometry(QRect(550, 190, 50, 20));
        label_readme->setAcceptDrops(false);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(520, 260, 210, 15));
        line_4->setLineWidth(3);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        btn_map_bigger = new QPushButton(centralWidget);
        btn_map_bigger->setObjectName(QString::fromUtf8("btn_map_bigger"));
        btn_map_bigger->setGeometry(QRect(560, 230, 80, 30));
        btn_map_smaller = new QPushButton(centralWidget);
        btn_map_smaller->setObjectName(QString::fromUtf8("btn_map_smaller"));
        btn_map_smaller->setGeometry(QRect(650, 230, 80, 30));
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(520, 4, 210, 15));
        line_5->setFrameShadow(QFrame::Sunken);
        line_5->setLineWidth(3);
        line_5->setMidLineWidth(0);
        line_5->setFrameShape(QFrame::HLine);
        lab_title_output_2 = new QLabel(centralWidget);
        lab_title_output_2->setObjectName(QString::fromUtf8("lab_title_output_2"));
        lab_title_output_2->setGeometry(QRect(520, 230, 40, 20));
        btn_reset_map = new QPushButton(centralWidget);
        btn_reset_map->setObjectName(QString::fromUtf8("btn_reset_map"));
        btn_reset_map->setGeometry(QRect(600, 475, 60, 40));
        btn_run_reset = new QPushButton(centralWidget);
        btn_run_reset->setObjectName(QString::fromUtf8("btn_run_reset"));
        btn_run_reset->setGeometry(QRect(520, 340, 30, 30));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QMAS", nullptr));
        btn_run_by_step->setText(QApplication::translate("MainWindow", "\345\215\225\346\255\245\350\277\220\350\241\214", nullptr));
        btn_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        btn_generate_obstacle->setText(QApplication::translate("MainWindow", "\351\232\234\347\242\215\347\211\251", nullptr));
        btn_genarate_taskpoint->setText(QApplication::translate("MainWindow", "\350\265\267\347\202\271/\347\273\210\347\202\271", nullptr));
        lab_title_input->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245", nullptr));
        btn_run_by_stage->setText(QApplication::translate("MainWindow", "\345\215\225\351\230\266\346\256\265\350\277\220\350\241\214", nullptr));
        lab_title_input_2->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250\350\276\223\345\205\245\357\274\232", nullptr));
        btn_reset_mas->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256\344\273\273\345\212\241", nullptr));
        label_name_row->setText(QApplication::translate("MainWindow", "\350\241\214", nullptr));
        btn_run_global->setText(QApplication::translate("MainWindow", "\351\235\231\346\200\201\350\247\204\345\210\222", nullptr));
        btn_run_Dynamic->setText(QApplication::translate("MainWindow", "\345\212\250\346\200\201\350\247\204\345\210\222", nullptr));
        label_name_col->setText(QApplication::translate("MainWindow", "\345\210\227", nullptr));
        lab_title_output->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
        btn_generate_map->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\345\234\260\345\233\276", nullptr));
        lab_title_input_1->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\276\223\345\205\245\357\274\232", nullptr));
        btn_openfile->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label_mapsize->setText(QApplication::translate("MainWindow", "\345\260\272\345\257\270\357\274\232", nullptr));
        lab_filename->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\267\257\345\276\204+\346\226\207\344\273\266\345\220\215", nullptr));
        label_readme->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\347\202\271\357\274\232", nullptr));
        btn_map_bigger->setText(QApplication::translate("MainWindow", "\346\211\251\345\244\247", nullptr));
        btn_map_smaller->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
        lab_title_output_2->setText(QApplication::translate("MainWindow", "\350\260\203\346\225\264\357\274\232", nullptr));
        btn_reset_map->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256\345\234\260\345\233\276", nullptr));
        btn_run_reset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
