#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "measurement.h"

#define SAVE_FILE_DIR "../save_files/"

class FormConnection{
public:
	FormConnection();
	~FormConnection();
	int output(Measurement *m, std::string filename);
	int input(Measurement *m, std::string filename);
	int doSave(Measurement *m);

private:
	int setSave(std::string filename, int frame_num, std::string save_param, bool csv_log);

	std::string save_file_name, save_file_param;
	int save_frame_num;
	bool save_csv_log;

	std::ofstream save;
	std::ofstream log;

	std::string save_state;

	bool db_reset_ack_l;
	bool db_reset_ack_r;
	bool db_all_ack_l;
	bool db_all_ack_r;
	bool save_ack;
	bool plat_home_ack;
	bool plat_move_ack;
	bool plat_stop_ack;
};

FormConnection::FormConnection(){
	db_reset_ack_l = false;
	db_reset_ack_r = false;
	db_all_ack_l = false;
	db_all_ack_r = false;
	save_ack = false;
	plat_home_ack = false;
	plat_move_ack = false;
	plat_stop_ack = false;
	save_frame_num = 0;
	std::string str = SAVE_FILE_DIR;
	str += "NULL";
	save.open(str);
	str += "-LOG";
	log.open(str);
	save_state = "保存可能です";
}

FormConnection::~FormConnection(){}

int FormConnection::input(Measurement *m, std::string filename){
	std::ifstream in(filename);
	if (in.fail())return -1;
	std::string save_filename, save_setdata_name;
	int save_frame_num;
	bool save_csv_flag;

	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1){ if (str == "T") m->vcc_L->allSeekFlag = true; else m->vcc_L->allSeekFlag = false; }
		if (i == 2){ std::stringstream ss; ss << str; ss >> m->vcc_L->allSeekThreshold; }
		if (i == 3){ if (str == "T") m->vcc_L->databaseFlag = true; else m->vcc_L->databaseFlag = false; }
		if (i == 4){ std::stringstream ss; ss << str; ss >> m->vcc_L->databaseSearchThreshold; }
		if (i == 5){ if (str == "T") { m->vcc_L->databaseClearFlag = true; db_reset_ack_l = true; } }
		if (i == 6){ if (str == "T") { m->vcc_L->databaseAllSearchFlag = true; false; db_all_ack_l = true; } }
		if (i == 7){ if (str == "T") m->vcc_L->subpixelFlag = true; else m->vcc_L->subpixelFlag = false; }
		if (i == 8){ if (str == "T") m->vcc_L->kalmanFlag = true; else m->vcc_L->kalmanFlag = false; }
		if (i == 9){ if (str == "T") m->vcc_R->allSeekFlag = true; else m->vcc_R->allSeekFlag = false; }
		if (i == 10){ std::stringstream ss; ss << str; ss >> m->vcc_R->allSeekThreshold; }
		if (i == 11){ if (str == "T") m->vcc_R->databaseFlag = true; else m->vcc_R->databaseFlag = false; }
		if (i == 12){ std::stringstream ss; ss << str; ss >> m->vcc_R->databaseSearchThreshold; }
		if (i == 13){ if (str == "T") { m->vcc_R->databaseClearFlag = true; db_reset_ack_r = true; } }
		if (i == 14){ if (str == "T") { m->vcc_R->databaseAllSearchFlag = true; db_all_ack_r = true; } }
		if (i == 15){ if (str == "T") m->vcc_R->subpixelFlag = true; else m->vcc_R->subpixelFlag = false; }
		if (i == 16){ if (str == "T") m->vcc_R->kalmanFlag = true; else m->vcc_R->kalmanFlag = false; }
		if (i == 17){ std::stringstream ss; ss << str; ss >> m->correctParallel; }
		if (i == 18){ std::stringstream ss; ss << str; ss >> m->trackingThreshold; }
		if (i == 19){ if (str == "T") { m->trackingHomeFlag = true; this->plat_home_ack = true; } }
		if (i == 20){ if (str == "T") { m->trackingMoveFlag = true; this->plat_move_ack = true; } }
		if (i == 21){ if (str == "T") { m->trackingMoveFlag = false; this->plat_stop_ack = true; } }
		if (i == 22){ save_filename = str; }
		if (i == 23){ std::stringstream ss; ss << str; ss >> save_frame_num; }
		if (i == 24){ save_setdata_name = str; }
		if (i == 25){ if (str == "T") save_csv_flag = true; else save_csv_flag = false; }
		if (i == 26){ if (str == "T") { setSave(save_filename, save_frame_num, save_setdata_name, save_csv_flag); this->save_ack = true; } }
	}

	in.close();
	return 0;
}

int FormConnection::output(Measurement *m, std::string filename){

	/* -- *///書き込み処理
	/* -- */std::ofstream out(filename);
	/* -- */if (out.fail()) return -1;
	/* 01 */out << m->distance.original << std::endl;
	/* 02 */out << m->distance.mid << std::endl;
	/* 03 */out << m->distance.kf << std::endl;
	/* 04 */out << m->vcc_L->matchingParameters[2] << std::endl;
	/* 05 */out << m->vcc_L->matchingParameters[3] << std::endl;
	/* 06 */out << m->vcc_L->targetDB_x << std::endl;
	/* 07 */out << m->vcc_L->targetDB_y << std::endl;
	/* 08 */out << m->vcc_L->matchingParameters[8] << std::endl;
	/* 19 */out << m->vcc_R->matchingParameters[2] << std::endl;
	/* 10 */out << m->vcc_R->matchingParameters[3] << std::endl;
	/* 11 */out << m->vcc_R->targetDB_x << std::endl;
	/* 12 */out << m->vcc_R->targetDB_y << std::endl;
	/* 13 */out << m->vcc_R->matchingParameters[8] << std::endl;
	/* -- *///ack
	/* 14 */if (db_reset_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
	/* 15 */if (db_all_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
	/* 16 */if (db_reset_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
	/* 17 */if (db_all_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */db_reset_ack_l = false;
	/* -- */db_reset_ack_r = false;
	/* -- */db_all_ack_l = false;
	/* -- */db_all_ack_r = false;
	/* -- *///電動雲台
	/* 18 */out << m->trackingState << std::endl;
	/* 19 */out << m->trackingAngle.pan << std::endl;
	/* 20 */out << m->trackingAngle.tilt << std::endl;
	/* 21 */out << m->platformState.pan << std::endl;
	/* 22 */out << m->platformState.tilt << std::endl;
	/* 23 */if (plat_home_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* 24 */if (plat_move_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* 25 */if (plat_stop_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */plat_home_ack = false;
	/* -- */plat_move_ack = false;
	/* -- */plat_stop_ack = false;
	/* -- *///セーブ関係
	/* 26 */out << this->save_state << std::endl;
	/* 27 */if (save_ack) out << "T" << std::endl; else out << "F" << std::endl;
	/* -- */save_ack = false;
	/* -- */
	/* -- */out.close();
	/* -- */return 0;
}

int FormConnection::setSave(std::string filename, int frame_num, std::string save_param, bool csv_log){
	this->save_file_name = SAVE_FILE_DIR + filename;
	this->save_frame_num = frame_num;
	this->save_file_param = save_param;
	this->save_csv_log = csv_log;

	save.close();
	std::string str = this->save_file_name + ".txt";
	save.open(str);
	if (this->save_csv_log){
		log.close();
		str = this->save_file_name + ".csv";
		log.open(str);
	}
	return 0;
}

int FormConnection::doSave(Measurement *m){
	if (save_frame_num <= 0){
		this->save_state = "保存完了";
		return 0;
	}
	save_frame_num--;
	this->save_state = "保存中";
	if (this->save_file_param == "KF適用後"){
		save << m->distance.kf << std::endl;
	}
	else if (this->save_file_param == "中心からの距離"){
		save << m->distance.mid << std::endl;
	}
	else if (this->save_file_param == "計測値"){
		save << m->distance.original << std::endl;
	}

	if (this->save_csv_log){	
	/* 01 */log << m->distance.original << ",";
	/* 02 */log << m->distance.mid << ",";
	/* 03 */log << m->distance.kf << ",";
	/* 04 */log << m->distance.theta << ",";
	/* 05 */log << m->vcc_L->matchingParameters[2] << ",";
	/* 06 */log << m->vcc_L->matchingParameters[3] << ",";
	/* 07 */log << m->vcc_L->targetDB_x << ",";
	/* 08 */log << m->vcc_L->targetDB_y << ",";
	/* 09 */log << m->vcc_L->matchingParameters[8] << ",";
	/* 10 */log << m->vcc_R->matchingParameters[2] << ",";
	/* 11 */log << m->vcc_R->matchingParameters[3] << ",";
	/* 12 */log << m->vcc_R->targetDB_x << ",";
	/* 13 */log << m->vcc_R->targetDB_y << ",";
	/* 14 */log << m->vcc_R->matchingParameters[8] << ",";
	/* 15 */if (db_reset_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 16 */if (db_all_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 17 */if (db_reset_ack_r) log << "T" << ","; else log << "F" << ",";
	/* 18 */if (db_all_ack_l) log << "T" << ","; else log << "F" << ",";
	/* 19 */log << m->trackingState << ",";
	/* 20 */log << m->platformState.pan << ",";
	/* 21 */log << m->platformState.tilt << ",";
	/* 22 */if (plat_home_ack) log << "T" << ","; else log << "F" << ",";
	/* 23 */if (plat_move_ack) log << "T" << ","; else log << "F" << ",";
	/* 24 */if (plat_stop_ack) log << "T" << ","; else log << "F" << ",";
	/* 25 */log << this->save_state << ",";
	/* 26 */if (save_ack) log << "T" << std::endl; else log << "F" << std::endl;
	}
}