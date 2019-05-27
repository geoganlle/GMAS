#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CScene.h"
#include <QDir>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <vector>
#include <QProcess>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    CScene* scene;

    int row_map;
    int col_map;

	void save_to_cacaed_file(QString filepath);
    void generate_map_by_file(QString filepath);
	void generate_mas_by_file(QString filepath);
	void generate_path_by_file(QString filepath);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_openfile_clicked();
    void on_spin_col_valueChanged(int arg1);
    void on_spin_row_valueChanged(int arg1);
    void on_btn_generate_map_clicked();
    void on_btn_generate_obstacle_clicked();
    void on_btn_genarate_taskpoint_clicked();
    void on_btn_run_global_clicked();
    void on_btn_run_Dynamic_clicked();
    void on_btn_run_by_step_clicked();
    void on_btn_run_by_stage_clicked();
    void on_btn_reset_clicked();
    void on_btn_exit_clicked();
    void on_btn_map_bigger_clicked();
    void on_btn_map_smaller_clicked();
};

#endif // MAINWINDOW_H
