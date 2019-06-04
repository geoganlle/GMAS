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
	if (string_input.back() != ' ')
	result.push_back(temp_int);
	return result;
}


void MainWindow::save_to_cacaed_file(QString filepath)
{
	//map.txt mas.txt
	std::ofstream __file;
	__file.open(filepath.toStdString()+"\\map.txt", std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		QString msg = QString::fromStdString("file open failed : ") +filepath+ QString::fromStdString("\\map.txt");
		ui->textBrowser->setText(msg);
		__file.close();
		return;
	}
	for (int i = 0; i < scene->get_row(); i++) {
		for (int j = 0; j < scene->get_col(); j++) {
			if (scene->get_map()[i][j]->is_obstaculo())__file << 0;
			else __file << 1;
		}
		__file << "\n";
	};
	__file.close();

	__file.open(filepath.toStdString() + "\\mas.txt", std::ios::out | std::ios::trunc);
	if (!__file.is_open()) {
		QString msg = QString::fromStdString("file open failed : ") + filepath + QString::fromStdString("\\mas.txt");
		__file.close();
		return;
	}
	/*
	# cached mas n agents
	# init_point(x,y) goal_point(x,y)
	C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\map.txt
	*/
	int tasknumber = std::min(static_cast<int>(scene->init_pos_pool.size()),static_cast<int>( scene->goal_pos_pool.size()));
	__file << "# cached mas \t"<< tasknumber <<" agents\n";
	__file << "# init_point(x, y) goal_point(x, y)\n";
	__file << filepath.toStdString()+"\\map.txt\n";
	for (int i = 0; i < tasknumber; i++) {
		__file << scene->init_pos_pool[i].x << " " << scene->init_pos_pool[i].y << " ";
		__file << scene->goal_pos_pool[i].x << " " << scene->goal_pos_pool[i].y << "\n";
	};
	__file.close();
}

void MainWindow::generate_map_by_file(QString filepath)
{
	std::string	line_string;
	std::ifstream	file(filepath.toStdString());
	std::vector<std::string> gridmap_line_vector;
	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {
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
		while (std::getline(file, line_string) && line_string.size()) {
			if (line_string[0] == '#')continue;
			if (line_string[0] == '.'|| line_string[0] == 'C') {
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
		scene->init_pos_pool.push_back(Point(point_pool[0], point_pool[1]));
		scene->goal_pos_pool.push_back(Point(point_pool[2], point_pool[3]));
		scene->get_map()[point_pool[1]][point_pool[0]]->set_colour(pinkio);
		scene->get_map()[point_pool[3]][point_pool[2]]->set_colour(blueio);
		ui->gv_map->setScene(scene);
	}
}

void MainWindow::generate_path_by_file(QString filepath)
{
	scene->clear_path();
	std::string	line_string;
	std::ifstream	file(filepath.toStdString()+"\\pathpool.txt");
	std::vector<std::string> line_vector;
	if (file.is_open()) {
		while (std::getline(file, line_string) && line_string.size()) {
			if (line_string[0] == '#')continue;
			line_vector.push_back(line_string);
		}
		file.close();
	}
	else {
		std::string msg = "ERROR: Could not open file " + filepath.toStdString();
		std::cout << msg << std::endl;
		ui->textBrowser->setText(QString::fromStdString(msg));
	}
	int linenumber = static_cast<int> (line_vector.size());
	for (int i = 0; i < linenumber; i++) {
		std::vector<int> point_pool = string_spilt_to_int(line_vector.at(i));
		int agent_number = point_pool.front();
		if (point_pool.size() < 4)continue;
		std::vector<int> path(point_pool.begin()+1,point_pool.end());
		pathpool.push_back(path);
		//为出发点和终点设置tip
		int init_row = *(point_pool.begin() + 1) / col_map;
		int init_col = *(point_pool.begin() + 1) % col_map;
		std::string tips = scene->get_map()[init_row][init_col]->toolTip().toStdString()
			+ " [" + std::to_string(agent_number) + "]";
		scene->get_map()[init_row][init_col]->setToolTip(QString::fromStdString(tips));
		int goal_row = *(point_pool.end() - 1) / col_map;
		int goal_col = *(point_pool.end() - 1) % col_map;
		tips.clear();
		tips = scene->get_map()[goal_row][goal_col]->toolTip().toStdString() 
			+ " [" + std::to_string(agent_number) + "]";
		scene->get_map()[goal_row][goal_col]->setToolTip(QString::fromStdString(tips));

		for (auto it = point_pool.begin() + 2; it != point_pool.end()-1; it++) {
			int point_row = (*it / col_map);
			int point_col = (*it % col_map);
			if(scene->get_map()[point_row][point_col]->get_ColourIcon()==whiteio)
			scene->get_map()[point_row][point_col]->set_colour(pregreenio);
			std::stringstream ss;
			ss <<"["<< agent_number << "]("<< (it - point_pool.begin() - 1)<<")";
			std::string tips;
			ss >> tips;
			scene->get_map()[point_row][point_col]->setToolTip(scene->get_map()[point_row][point_col]->toolTip()+" "+QString::fromStdString(tips));
		}
	}
	
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	curTime = -1;
	curAgent = 0;
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
	row_map = ui->spin_row->value();
}

void MainWindow::on_spin_row_valueChanged(int arg1)
{
    row_map=arg1;
	col_map = ui->spin_col->value();
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
	save_to_cacaed_file("C:\\Users\\guzhe\\Desktop\\GMAS\\cached");
	QProcess* process = new QProcess(this);
	QString run_global_exe = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\GMAS1.exe";
	process->execute(run_global_exe);
	generate_path_by_file("C:\\Users\\guzhe\\Desktop\\GMAS\\cached");
}

void MainWindow::on_btn_run_Dynamic_clicked()
{
	save_to_cacaed_file("C:\\Users\\guzhe\\Desktop\\GMAS\\cached");
	QProcess* process = new QProcess(this);
	QString run_global_exe = "C:\\Users\\guzhe\\Desktop\\GMAS\\cached\\GMAS2.exe";
	process->execute(run_global_exe);
	generate_path_by_file("C:\\Users\\guzhe\\Desktop\\GMAS\\cached");
}

void MainWindow::on_btn_run_by_step_clicked()
{
	if (curTime == -1) { 
		scene->clear_path(); 
		curTime = 1;
	}
	if (curTime > pathpool[curAgent].size()-1)
	{
		goto endfun;
	}
	if (curTime==pathpool[curAgent].size()-1 ) {
		for (int i=1;i< pathpool[curAgent].size()-1;i++)
		{
			int cur_point_row = pathpool[curAgent][i] / col_map;
			int cur_point_col = pathpool[curAgent][i] % col_map;
			scene->get_map()[cur_point_row][cur_point_col]->set_colour(greenio);
		}
		goto endfun;
	}
	if (curTime != 0) {
		int cur_point_row = pathpool[curAgent][curTime] / col_map;
		int cur_point_col = pathpool[curAgent][curTime] % col_map;
		std::string pathstring = "curTime:" + std::to_string(curTime) + " curAgent:" + std::to_string(curAgent)+" curPosition"+ std::to_string(pathpool[curAgent][curTime]);
		ui->textBrowser->append(QString::fromStdString(pathstring));
		scene->get_map()[cur_point_row][cur_point_col]->set_colour(greenio);
		int beforetime = curTime - 1;
		if (beforetime > 0) {
			int cur_point_row = pathpool[curAgent][beforetime] / col_map;
			int cur_point_col = pathpool[curAgent][beforetime] % col_map;
			scene->get_map()[cur_point_row][cur_point_col]->set_colour(pregreenio);
		}
	}
	endfun:
	if (curAgent == static_cast<int>(pathpool.size()-1)) {
		curTime++;
		curAgent = 0;
	}
	else curAgent++;
}

void MainWindow::on_btn_run_by_stage_clicked()
{
	for (int i = 0; i < pathpool.size(); i++)
	{
		on_btn_run_by_step_clicked();
	}
}

void MainWindow::on_btn_exit_clicked()
{
	qApp->exit(0);
}

void MainWindow::on_btn_map_bigger_clicked()
{
	ui->gv_map->scale(1.2,1.2);
}

void MainWindow::on_btn_map_smaller_clicked()
{
	ui->gv_map->scale(1/1.2, 1/1.2);
}

void MainWindow::on_btn_reset_mas_clicked()
{
	scene->clear_init_and_pool();
	scene->clear_path();
}

void MainWindow::on_btn_reset_map_clicked()
{
	pathpool.clear();
	delete scene;
	scene = nullptr;
	row_map = ui->spin_row->value();
	col_map = ui->spin_row->value();
	scene = new CScene(row_map, col_map);
	ui->gv_map->setScene(scene);
}

void MainWindow::on_btn_run_reset_clicked()
{
	curTime = -1;
	curAgent = 0;
	scene->clear_path();
}
