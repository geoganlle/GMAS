#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdir.h>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_openfile_clicked()
{
    //QString curPath=QDir::currentPath();//获取系统当前目录
    //获取应用程序的路径
    QString curPath="";
    QString dlgTitle="选择一个文件"; //对话框标题
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (!aFileName.isEmpty()){
        ui->lab_filename->setText(aFileName);
        ui->lab_filename->adjustSize();
        const QSize size = ui->lab_filename->size();
        ui->scrollAreaWidgetContents->setMinimumSize(size);
    }
}
