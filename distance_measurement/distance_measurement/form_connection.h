#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "measurement.h"

#define SAVE_FILE_DIR "save_files/"

class FormConnection{
public:
	FormConnection();
	~FormConnection();
	int output(Measurement *m, std::string filename);
	int center_output(Measurement *m, std::string filename);
	int platform_output(Measurement *m, std::string filename);
	int input(Measurement *m, std::string filename);
	int center_input(Measurement *m, std::string filename);
	int platform_input(Measurement *m, std::string filename);
	int doSave(Measurement *m);

private:
	int setSave(std::string folder_name, std::string file_name, int frame_num, bool csv_log);
	int control_platform(Measurement *m, std::string direction, double step_deg);
	int control_platform(Measurement *m, std::string direction, double pan, double tilt);

	std::string save_folder_name, save_file_name, save_file_path;
	int save_frame_num;
	bool save_csv_log;

	std::ofstream save;
	std::ofstream log;

	std::string save_state;

	bool db_reset_ack_l;
	bool db_reset_ack_r;
	bool db_reset_ack_c;
	bool db_all_ack_l;
	bool db_all_ack_r;
	bool db_all_ack_c;
	bool save_ack;
	bool plat_home_ack;
	bool plat_move_ack;
	bool plat_stop_ack;
	bool pc_ok;
};

FormConnection::FormConnection(){
	db_reset_ack_l = false;
	db_reset_ack_r = false;
	db_reset_ack_c = false;
	db_all_ack_l = false;
	db_all_ack_r = false;
	db_all_ack_c = false;
	save_ack = false;
	plat_home_ack = false;
	plat_move_ack = false;
	plat_stop_ack = false;
	pc_ok = false;
	save_frame_num = 0;
	std::string str = SAVE_FILE_DIR;
	str += "NULL";
	save.open(str);
	str += "-LOG";
	log.open(str);
	save_state = "";
}

FormConnection::~FormConnection(){}

int FormConnection::input(Measurement *m, std::string filename){
	std::ifstream in(filename);
	if (in.fail())return -1;
	std::string _save_folder_name, _save_file_name;
	int _save_frame_num;
	bool save_csv_flag;

	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1){ std::stringstream ss; ss << str; ss >> m->baselineLength; }
		if (i == 2){ std::stringstream ss; ss << str; ss >> m->focalLength; }
		if (i == 3){ std::stringstream ss; ss << str; ss >> m->pixelSize; }
		if (i == 4){ if (str == "T") m->vcc_L->allSeekFlag = true; else m->vcc_L->allSeekFlag = false; }
		if (i == 5){ std::stringstream ss; ss << str; ss >> m->vcc_L->allSeekThreshold; }
		if (i == 6){ if (str == "T") m->vcc_L->databaseFlag = true; else m->vcc_L->databaseFlag = false; }
		if (i == 7){ std::stringstream ss; ss << str; ss >> m->vcc_L->databaseSearchThreshold; }
		if (i == 8){ if (str == "T") { m->vcc_L->databaseClearFlag = true; db_reset_ack_l = true; } }
		if (i == 9){ if (str == "T") { m->vcc_L->databaseAllSearchFlag = true; false; db_all_ack_l = true; } }
		if (i == 10){ if (str == "T") m->vcc_L->subpixelFlag = true; else m->vcc_L->subpixelFlag = false; }
		if (i == 11){ if (str == "T") m->vcc_L->kalmanFlag = true; else m->vcc_L->kalmanFlag = false; }
		if (i == 12){ if (str == "T") m->vcc_R->allSeekFlag = true; else m->vcc_R->allSeekFlag = false; }
		if (i == 13){ std::stringstream ss; ss << str; ss >> m->vcc_R->allSeekThreshold; }
		if (i == 14){ if (str == "T") m->vcc_R->databaseFlag = true; else m->vcc_R->databaseFlag = false; }
		if (i == 15){ std::stringstream ss; ss << str; ss >> m->vcc_R->databaseSearchThreshold; }
		if (i == 16){ if (str == "T") { m->vcc_R->databaseClearFlag = true; db_reset_ack_r = true; } }
		if (i == 17){ if (str == "T") { m->vcc_R->databaseAllSearchFlag = true; db_all_ack_r = true; } }
		if (i == 18){ if (str == "T") m->vcc_R->subpixelFlag = true; else m->vcc_R->subpixelFlag = false; }
		if (i == 19){ if (str == "T") m->vcc_R->kalmanFlag = true; else m->vcc_R->kalmanFlag = false; }
		if (i == 20){ std::stringstream ss; ss << str; ss >> m->linear_a2; }
		if (i == 21){ std::stringstream ss; ss << str; ss >> m->linear_a1; }
		if (i == 22){ std::stringstream ss; ss << str; ss >> m->linear_a0; }
		if (i == 23){ std::stringstream ss; ss << str; ss >> m->trackingThreshold; }
		if (i == 24){ if (str == "T") { m->trackingHomeFlag = true; this->plat_home_ack = true; } }
		if (i == 25){ if (str == "T") { m->trackingMoveFlag = true; this->plat_move_ack = true; } }
		if (i == 26){ if (str == "T") { m->trackingMoveFlag = false; this->plat_stop_ack = true; } }
		if (i == 27){ _save_file_name = str; }
		if (i == 28){ _save_folder_name = str; }
		if (i == 29){ std::stringstream ss; ss << str; ss >> _save_frame_num; }
		if (i == 30){ if (str == "T") save_csv_flag = true; else save_csv_flag = false; }
		if (i == 31){ if (str == "T") { setSave(_save_folder_name, _save_file_name, _save_frame_num, save_csv_flag); this->save_ack = true; } }
	}

	in.close();
	return 0;
}

int FormConnection::center_input(Measurement *m, std::string filename){
	std::ifstream in(filename);
	if (in.fail())return -1;

	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1){ std::stringstream ss; ss << str; ss >> m->centerCameraFocalLength; }
		if (i == 2){ if (str == "T") m->vcc_C->allSeekFlag = true; else m->vcc_C->allSeekFlag = false; }
		if (i == 3){ std::stringstream ss; ss << str; ss >> m->vcc_C->allSeekThreshold; }
		if (i == 4){ if (str == "T") m->vcc_C->databaseFlag = true; else m->vcc_C->databaseFlag = false; }
		if (i == 5){ std::stringstream ss; ss << str; ss >> m->vcc_C->databaseSearchThreshold; }
		if (i == 6){ if (str == "T") { m->vcc_C->databaseClearFlag = true; db_reset_ack_c = true; } }
		if (i == 7){ if (str == "T") { m->vcc_C->databaseAllSearchFlag = true; false; db_all_ack_c = true; } }
		if (i == 8){ if (str == "T") m->vcc_C->subpixelFlag = true; else m->vcc_C->subpixelFlag = false; }
		if (i == 9){ if (str == "T") m->vcc_C->kalmanFlag = true; else m->vcc_C->kalmanFlag = false; }
	}
	in.close();
	return 0;
}

int FormConnection::control_platform(Measurement *m, std::string direction, double step_deg){
	if (direction == "UP"){
		m->outControlFlag = true;
		Measurement::PanTilt pt;
		pt.pan = 0;
		pt.tilt = DEG2RAD(-step_deg);
		m->outControlPT = pt;
	}
	else if (direction == "DOWN"){
		m->outControlFlag = true;
		Measurement::PanTilt pt;
		pt.pan = 0;
		pt.tilt = DEG2RAD(step_deg);
		m->outControlPT = pt;
	}
	else if (direction == "LEFT"){
		m->outControlFlag = true;
		Measurement::PanTilt pt;
		pt.pan = DEG2RAD(-step_deg);
		pt.tilt = 0;
		m->outControlPT = pt;
	}
	else if (direction == "RIGHT"){
		m->outControlFlag = true;
		Measurement::PanTilt pt;
		pt.pan = DEG2RAD(step_deg);
		pt.tilt = 0;
		m->outControlPT = pt;
	}
	else{
		return 0;
	}
	this->pc_ok = true;
	return 0;
}

int FormConnection::control_platform(Measurement *m, std::string direction, double pan, double tilt){
		if (direction == "ABSOLUTE"){
			m->outControlFlag = true;
			m->outControlAbs = true;
			Measurement::PanTilt pt;
			pt.pan = DEG2RAD(pan);
			pt.tilt = DEG2RAD(tilt);
			m->outControlPT = pt;
		}
		else if (direction == "RELATIVE"){
			m->outControlFlag = true;
			Measurement::PanTilt pt;
			pt.pan = DEG2RAD(pan);
			pt.tilt = DEG2RAD(tilt);
			m->outControlPT = pt;
		}
		else {
			return 0;
		}
		this->pc_ok = true;
		return 0;
}

int FormConnection::platform_input(Measurement *m, std::string filename){
	std::ifstream in(filename);
	if (in.fail())return -1;
	double platform_deg;
	double platform_pan,platform_tilt;

	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1){ std::stringstream ss; ss << str; ss >> platform_deg; }
		if (i == 2){ this->control_platform(m, str, platform_deg); }
		if (i == 3){ std::stringstream ss; ss << str; ss >> platform_pan; }
		if (i == 4){ std::stringstream ss; ss << str; ss >> platform_tilt; }
		if (i == 5){ this->control_platform(m, str, platform_pan, platform_tilt); }
	}
	in.close();
	return 0;
}

int FormConnection::platform_output(Measurement *m, std::string filename){

	/* -- *///èëÇ´çûÇ›èàóù
	/* -- */std::ofstream out(filename);
	/* -- */if (out.fail()) return -1;
	/* 01 */if (pc_ok) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */pc_ok = false;
	/* -- */out.close();
	/* -- */return 0;
}

int FormConnection::output(Measurement *m, std::string filename){

	/* -- *///èëÇ´çûÇ›èàóù
	/* -- */std::ofstream out(filename);
	/* -- */if (out.fail()) return -1;
	/* 01 */out << m->non_offset.original << std::endl;
	/* 02 */out << m->non_offset.mid << std::endl;
	/* 03 */out << m->non_offset.kf << std::endl;
	/* 04 */out << m->distance.original << std::endl;
	/* 05 */out << m->distance.mid << std::endl;
	/* 06 */out << m->distance.kf << std::endl;
	/* 07 */out << m->vcc_L->matchingParameters[2] << std::endl;
	/* 08 */out << m->vcc_L->matchingParameters[3] << std::endl;
	/* 19 */out << m->vcc_L->targetDB_x << std::endl;
	/* 10 */out << m->vcc_L->targetDB_y << std::endl;
	/* 11 */out << m->vcc_L->matchingParameters[8] << std::endl;
	/* 12 */out << m->vcc_R->matchingParameters[2] << std::endl;
	/* 13 */out << m->vcc_R->matchingParameters[3] << std::endl;
	/* 14 */out << m->vcc_R->targetDB_x << std::endl;
	/* 15 */out << m->vcc_R->targetDB_y << std::endl;
	/* 16 */out << m->vcc_R->matchingParameters[8] << std::endl;
	/* -- *///ack
	/* 17 */if (db_reset_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
	/* 18 */if (db_all_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
	/* 19 */if (db_reset_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
	/* 20 */if (db_all_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */db_reset_ack_l = false;
	/* -- */db_reset_ack_r = false;
	/* -- */db_all_ack_l = false;
	/* -- */db_all_ack_r = false;
	/* -- *///ìdìÆâ_ë‰
	/* 21 */out << m->trackingState << std::endl;
	/* 22 */if (m->centerCameraFlag){
	/* -- */	m->mtx.lock(); out << m->angle_C.pan << std::endl; m->mtx.unlock();
	/* -- */}
	/* -- */else out << m->trackingAngle.pan << std::endl;
	/* 23 */if (m->centerCameraFlag){
	/* -- */	m->mtx.lock(); out << m->angle_C.tilt << std::endl; m->mtx.unlock();
	/* -- */}
	/* -- */else out << m->trackingAngle.tilt << std::endl;
	/* 24 */out << m->platformState.pan << std::endl;
	/* 25 */out << m->platformState.tilt << std::endl;
	/* 26 */if (plat_home_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* 27 */if (plat_move_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* 28 */if (plat_stop_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */plat_home_ack = false;
	/* -- */plat_move_ack = false;
	/* -- */plat_stop_ack = false;
	/* -- *///ÉZÅ[Éuä÷åW
	/* 29 */out << this->save_state << std::endl;
	/* 30 */if (save_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */save_ack = false;
	/* -- */
	/* -- */out.close();
	/* -- */return 0;
}

int FormConnection::center_output(Measurement *m, std::string filename){

	/* -- *///èëÇ´çûÇ›èàóù
	/* -- */std::ofstream out(filename);
	/* -- */if (out.fail()) return -1;
	/* 01 */out << m->vcc_C->matchingParameters[2] << std::endl;
	/* 02 */out << m->vcc_C->matchingParameters[3] << std::endl;
	/* 03 */out << m->vcc_C->targetDB_x << std::endl;
	/* 04 */out << m->vcc_C->targetDB_y << std::endl;
	/* 05 */out << m->vcc_C->matchingParameters[8] << std::endl;
	/* -- *///ack
	/* 06 */if (db_reset_ack_c) out << "T" << std::endl; else out << "F" << std::endl;
	/* 07 */if (db_all_ack_c) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */db_reset_ack_c = false;
	/* -- */db_all_ack_c = false;
	/* -- */
	/* -- */out.close();
	/* -- */return 0;
}

int FormConnection::setSave(std::string folder_name, std::string file_name, int frame_num, bool csv_log){
	using namespace std::tr2::sys;

	std::string folder_path = SAVE_FILE_DIR;
	folder_path += folder_name;
	create_directory(path(folder_path));
	this->save_folder_name = folder_name;
	this->save_file_name = file_name;
	
	this->save_file_path = SAVE_FILE_DIR;
	this->save_file_path += folder_path;
	this->save_file_path += "\\";
	this->save_file_path += file_name;
	this->save_frame_num = frame_num;
	this->save_csv_log = csv_log;

	save.close();
	std::string str = this->save_file_path + ".txt";
	save.open(str);
	if (this->save_csv_log){
		log.close();
		str = this->save_file_path + ".csv";
		log.open(str);
	}
	return 0;
}

int FormConnection::doSave(Measurement *m){
	if (save_frame_num <= 0){
		this->save_state = "ï€ë∂äÆóπ";
		return 0;
	}
	save_frame_num--;
	this->save_state = "ï€ë∂íÜ";
	save << m->distance.kf << std::endl;

	if (this->save_csv_log){
	/* 01 */log << m->non_offset.original << ",";
	/* 02 */log << m->non_offset.mid << ",";
	/* 03 */log << m->non_offset.kf << ",";
	/* 04 */log << m->distance.original << ",";
	/* 05 */log << m->distance.mid << ",";
	/* 06 */log << m->distance.kf << ",";
	/* 07 */log << m->vcc_L->matchingParameters[2] << ",";
	/* 08 */log << m->vcc_L->matchingParameters[3] << ",";
	/* 09 */log << m->vcc_L->targetDB_x << ",";
	/* 10 */log << m->vcc_L->targetDB_y << ",";
	/* 11 */log << m->vcc_L->matchingParameters[8] << ",";
	/* 12 */log << m->vcc_R->matchingParameters[2] << ",";
	/* 13 */log << m->vcc_R->matchingParameters[3] << ",";
	/* 14 */log << m->vcc_R->targetDB_x << ",";
	/* 15 */log << m->vcc_R->targetDB_y << ",";
	/* 16 */log << m->vcc_R->matchingParameters[8] << ",";
	/* 17 */if (db_reset_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 18 */if (db_all_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 19 */if (db_reset_ack_r) log << "T" << ","; else log << "F" << ",";
	/* 20 */if (db_all_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 21 */log << m->trackingState << ",";
	/* 22 */log << m->trackingAngle.pan << ",";
	/* 23 */log << m->trackingAngle.tilt << ",";
	/* 24 */log << m->platformState.pan << ",";
	/* 25 */log << m->platformState.tilt << ",";
	/* 26 */if (plat_home_ack) log << "T" << ","; else log << "F" << ",";
	/* 27 */if (plat_move_ack) log << "T" << ","; else log << "F" << ",";
	/* 28 */if (plat_stop_ack) log << "T" << ","; else log << "F" << ",";
	/* 29 */log << this->save_state << ",";
	/* 30 */if (save_ack) log << "T" << std::endl; else log << "F" << std::endl;
	}
}