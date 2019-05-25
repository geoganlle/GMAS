#include "mainwindow.h"
#include "ui_mainwindow.h"

std::vector<int> string_spilt_to_int(const std::string& string_input)
{
	std::vector<int> result;
	int temp_int = 0;
	for (auto it = string_input.begin(); it != string_input.end(); it++) {
		if (*it == ' ')
		{
			result.push_back(temp_int);
			temp_int = 0;
		}
		else {
			temp_int = temp_int * 10 + ((*it) - '0');
		}
	}
	result.push_back(temp_int);
	return result;
}


void MainWindow::generate_map_by_file(QString filepath)
{
	std::string	line_string;
	std::ifstream	file(filepath.toStdString());
	std::vector<std::string> gridmap_line_vector;
	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//读一行行长度不为0
			gridmap_line_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::string msg = "ERROR: Could not open file " + filepath.toStdString();
		std::cout << msg << std::endl;
		ui->textBrowser->setText(QString::fromStdString(msg));
	}
	row_map = static_cast<int> (gridmap_line_vector.size());
	col_map = static_cast<int> (gridmap_line_vector.at(0).size());

	if (scene != nullptr)delete scene;
	scene = new CScene(row_map, col_map);

	for (int i = 0; i < row_map; i++) {
		for (int j = 0; j < col_map; j++) {
			// true 1 false 0
			if(gridmap_line_vector[i][j] == '0')
			scene->get_map()[i][j]->set_colour(greyio);
		}
	}
	ui->gv_map->setScene(scene);
	int sizey = row_map * 20;
	int sizex = col_map * 20;
	ui->gv_map->fitInView(QRectF(0, 0, sizey, sizex), Qt::KeepAspectRatioByExpanding);
	ui->gv_map->setInteractive(true);
}

void MainWindow::generate_mas_by_file(QString filepath)
{
	std::string	line_string;
	std::ifstream	file(filepath.toStdString());
	std::vector<std::string> point_line_vector;
	std::string map_file_path_name;
	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {//读一行行长度不为0
			if (line_string[0] == '#')continue;
			if (line_string[0] == '.') {
				generate_map_by_file(QString::fromStdString(line_string));
				continue;
			}
			point_line_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::string msg = "ERROR: Could not open file " + filepath.toStdString();
		std::cout << msg << std::endl;
		ui->textBrowser->setText(QString::fromStdString(msg));
	}

	int agent_number = static_cast<int> (point_line_vector.size());
	
	for (int i = 0; i < agent_number; i++) {
		std::vector<int> point_pool = string_spilt_to_int(point_line_vector.at(i));
		if (point_pool.size() != 4)continue;
		init_pos_pool.push_back(Point(point_pool[0], point_pool[1]));
		goal_pos_pool.push_back(Point(point_pool[2], point_pool[3]));
		scene->get_map()[point_pool[1]][point_pool[0]]->set_colour(pinkio);
		scene->get_map()[point_pool[3]][point_pool[2]]->set_colour(blueio);
		ui->gv_map->setScene(scene);
	}
}

void MainWindow::generate_point_by_file(QString filepath)
{

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=nullptr;
	row_map = ui->spin_row->value();
	col_map = ui->spin_row->value();
    ui->gv_map->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (scene){
        delete scene;
        scene = nullptr;
    }
}

void MainWindow::on_btn_openfile_clicked()
{
    QString curPath=QDir::currentPath();
    ui->textBrowser->setText(curPath);
    curPath="C:\\Users\\guzhe\\Desktop\\GMAS\\mas";//TOFIX:
    QString dlgTitle="select a mas file to generate";
    QString filter="text file(*.txt);;picture file(*.jpg *.gif *.png);;all file(*.*)";
    QString filename=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (!filename.isEmpty()){
        ui->lab_filename->setText(filename);
        ui->lab_filename->adjustSize();
        const QSize size = ui->lab_filename->size();
        ui->scrollAreaWidgetContents->setMinimumSize(size);
		generate_mas_by_file(filename);
    }
}

void MainWindow::on_spin_col_valueChanged(int arg1)
{
    col_map=arg1;
}

void MainWindow::on_spin_row_valueChanged(int arg1)
{
    row_map=arg1;
}

void MainWindow::on_btn_generate_map_clicked()
{
	if (scene != nullptr)delete scene;
	scene = new CScene(row_map, col_map);
	ui->gv_map->setScene(scene);
	int sizey = row_map * 20;
	int sizex = col_map * 20;
	ui->gv_map->fitInView(QRectF(0, 0, sizey, sizex), Qt::KeepAspectRatioByExpanding);
	ui->gv_map->setInteractive(true);
}

void MainWindow::on_btn_generate_obstacle_clicked()
{
    scene->set_curcolour(greyio);
}

void MainWindow::on_btn_genarate_taskpoint_clicked()
{
	if (scene->get_curcolour() == pinkio || scene->get_curcolour() == blueio)return;
    scene->set_curcolour(pinkio);
}

void MainWindow::on_btn_run_global_clicked()
{
	QProcess* process = new QProcess(this);
	QString run_global_exe = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\GMAS1.exe";
	process->start(run_global_exe);
}

void MainWindow::on_btn_run_Dynamic_clicked()
{

}

void MainWindow::on_btn_run_by_step_clicked()
{

}

void MainWindow::on_btn_run_by_stage_clicked()
{

}

void MainWindow::on_btn_reset_clicked()
{

}

void MainWindow::on_btn_exit_clicked()
{
	qApp->exit(0);
}
