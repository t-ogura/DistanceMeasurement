#pragma once
#include <fstream>
#include <string>

#include "ParallelOffsetTool.h"
#define INFILE "../param_files/send.param"
#define OUTFILE "../param_files/receive.param"
#define CENTER_INPUT_FILENAME "../param_files/center_send.param"
#define CENTER_OUTPUT_FILENAME "../param_files/center_receive.param"
#define PLATFORMCONTROLLER_INPUT_FILENAME "../param_files/pc_send.param"
#define PLATFORMCONTROLLER_OUTPUT_FILENAME "../param_files/pc_receive.param"
#define QUIT_FILENAME "../param_files/quit.param"
#define INIT_FILE_DIRECTRY "initialize.cfg"

#define DEG2RAD(X) (X/180.*M_PI)
#define RAD2DEG(X) (X*180/M_PI)

namespace Parameters {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// ParamShow の概要
	/// </summary>
	public ref class ParamShow : public System::Windows::Forms::Form
	{
	public:
		ParamShow(void)
		{
			InitializeComponent();
			this->readConfigFile("main.cfg\\Defalt.cfg");
			this->readInitFile(INIT_FILE_DIRECTRY);
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

		/// std::string -> System::String への変換
		String^ ToSystemString(	const std::string& i_src){
			return  gcnew System::String(i_src.data(), 0, i_src.size());
		}
		/// System::String^ -> std::string の変換
		std::string ToStdString(String^ i_src){
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(i_src)).ToPointer();
			std::string os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			return os;
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~ParamShow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  theta;

	private: System::Windows::Forms::Label^  pan_label;





	private: System::Windows::Forms::Label^  mid;


	private: System::Windows::Forms::GroupBox^  leftcamera;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  xl;
	private: System::Windows::Forms::Label^  yl;
	private: System::Windows::Forms::Label^  coodinatel;
	private: System::Windows::Forms::Label^  databasel;
	private: System::Windows::Forms::Label^  coor_xl;
	private: System::Windows::Forms::Label^  coor_yl;
	private: System::Windows::Forms::Label^  db_xl;
	private: System::Windows::Forms::Label^  db_yl;
	private: System::Windows::Forms::GroupBox^  rightcamera;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Label^  xr;
	private: System::Windows::Forms::Label^  yr;
	private: System::Windows::Forms::Label^  coodinater;
	private: System::Windows::Forms::Label^  databaser;
	private: System::Windows::Forms::Label^  coor_xr;
	private: System::Windows::Forms::Label^  coor_yr;
	private: System::Windows::Forms::Label^  db_xr;
	private: System::Windows::Forms::Label^  db_yr;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::Label^  corr_l;
	private: System::Windows::Forms::Label^  correlatel;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::Label^  corr_r;
	private: System::Windows::Forms::Label^  correlater;
	private: System::Windows::Forms::CheckBox^  db_flag_l;
	private: System::Windows::Forms::Button^  db_all_l;
	private: System::Windows::Forms::Button^  db_reset_l;
	private: System::Windows::Forms::Label^  thl;
	private: System::Windows::Forms::TextBox^  th_box_l;
	private: System::Windows::Forms::CheckBox^  all_flag_l;
	private: System::Windows::Forms::CheckBox^  kalman_flag_l;
	private: System::Windows::Forms::CheckBox^  sub_flag_l;
	private: System::Windows::Forms::Label^  roll_label_l;
	private: System::Windows::Forms::TextBox^  roll_box_l;
	private: System::Windows::Forms::CheckBox^  roll_flag_l;
	private: System::Windows::Forms::Label^  roll_label_r;
	private: System::Windows::Forms::TextBox^  roll_box_r;
	private: System::Windows::Forms::CheckBox^  roll_flag_r;
	private: System::Windows::Forms::Label^  thr;
	private: System::Windows::Forms::CheckBox^  kalman_flag_r;
	private: System::Windows::Forms::CheckBox^  db_flag_r;
	private: System::Windows::Forms::CheckBox^  sub_flag_r;
	private: System::Windows::Forms::CheckBox^  all_flag_r;
	private: System::Windows::Forms::Button^  db_all_r;
	private: System::Windows::Forms::TextBox^  th_box_r;
	private: System::Windows::Forms::Button^  db_reset_r;
	private: System::Windows::Forms::GroupBox^  offset_group;

	private: System::Windows::Forms::GroupBox^  pan_tilt_unit_group;
	private: System::Windows::Forms::GroupBox^  pan_tilt_status;
	private: System::Windows::Forms::Label^  platform_state;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
private: System::Windows::Forms::Label^  pla_move_label;


private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
private: System::Windows::Forms::Label^  filename_label;

private: System::Windows::Forms::Label^  platform_tilt;
private: System::Windows::Forms::Label^  platform_pan;
private: System::Windows::Forms::Label^  tilt_label;
private: System::Windows::Forms::Label^  pla_pos_label;
public: System::Windows::Forms::TextBox^  linear_a2;
private:

public: System::Windows::Forms::CheckBox^  offset_check;
private: System::Windows::Forms::Label^  move_tilt;
private: System::Windows::Forms::GroupBox^  save_box;





private: System::Windows::Forms::Button^  save_button;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
private: System::Windows::Forms::Label^  save_state;

private: System::Windows::Forms::Label^  flame;
private: System::Windows::Forms::NumericUpDown^  flame_num;

private: System::Windows::Forms::TextBox^  filename_box;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
private: System::Windows::Forms::CheckBox^  csv_check;
private: System::Windows::Forms::Button^  plat_stop_button;
private: System::Windows::Forms::Label^  plat_th_label;
private: System::Windows::Forms::TextBox^  plat_th_box;

private: System::Windows::Forms::Button^  plat_home_button;
private: System::Windows::Forms::Button^  plat_move_button;
private: System::Windows::Forms::Label^  db_th_label_l;
private: System::Windows::Forms::TextBox^  db_th_box_l;
private: System::Windows::Forms::Label^  db_th_label_r;
private: System::Windows::Forms::TextBox^  db_th_box_r;
private: System::Windows::Forms::Button^  tool_button;

private: System::Windows::Forms::GroupBox^  groupBox2;


private: System::Windows::Forms::Button^  reset_button;

private: System::Windows::Forms::Button^  output_button;

private: System::Windows::Forms::Button^  read_button;

private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::TextBox^  pixel_box;

private: System::Windows::Forms::Label^  pixel_label;

private: System::Windows::Forms::TextBox^  focal_box;
private: System::Windows::Forms::Label^  focal_label;
public: System::Windows::Forms::TextBox^  base_box;
private: System::Windows::Forms::Label^  base_label;
public: System::Windows::Forms::TextBox^  linear_a0;
private:

private: System::Windows::Forms::Label^  label4;
public: System::Windows::Forms::TextBox^  linear_a1;
private:


private: System::Windows::Forms::Label^  kalman;
public: System::Windows::Forms::Label^  label3;
private:
private: System::Windows::Forms::GroupBox^  groupBox4;
public:






private: System::Windows::Forms::Label^  origin_measure_before;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TabPage^  tabPage1;
private: System::Windows::Forms::TabPage^  tabPage2;
private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::CheckBox^  calib_check;

private: System::Windows::Forms::TextBox^  true_value;

private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::TabPage^  tabPage4;
private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  server_dir_label;
private: System::Windows::Forms::Button^  server_dir_button;
private: System::Windows::Forms::TextBox^  server_dir_box;
private: System::Windows::Forms::RadioButton^  b_radio;
private: System::Windows::Forms::RadioButton^  a_radio;
private: System::Windows::Forms::CheckBox^  server_check;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TabPage^  tabPage5;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  db_th_box_c;

private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::TextBox^  roll_box_c;
private: System::Windows::Forms::CheckBox^  roll_flag_c;
private: System::Windows::Forms::CheckBox^  kalman_flag_c;

private: System::Windows::Forms::CheckBox^  sub_flag_c;

private: System::Windows::Forms::Button^  db_all_c;

private: System::Windows::Forms::Button^  db_reset_c;

private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  th_box_c;
private: System::Windows::Forms::CheckBox^  all_flag_c;
private: System::Windows::Forms::CheckBox^  db_flag_c;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
private: System::Windows::Forms::Label^  corr_c;

private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel10;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  coor_xc;
private: System::Windows::Forms::Label^  coor_yc;
private: System::Windows::Forms::Label^  db_xc;
private: System::Windows::Forms::Label^  db_yc;




private: System::Windows::Forms::TextBox^  centercamera_focallength;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::GroupBox^  groupBox7;

private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::NumericUpDown^  movestep;
private: System::Windows::Forms::Button^  pc_absolute;


private: System::Windows::Forms::TextBox^  pc_tilt;

private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::TextBox^  pc_pan;

private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Button^  pc_down;

private: System::Windows::Forms::Button^  pc_right;
private: System::Windows::Forms::Button^  pc_left;


private: System::Windows::Forms::Button^  pc_up;
private: System::Windows::Forms::Button^  pc_relative;
private: System::Windows::Forms::Button^  Quit;






private:









	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ParamShow::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->theta = (gcnew System::Windows::Forms::Label());
			this->pan_label = (gcnew System::Windows::Forms::Label());
			this->mid = (gcnew System::Windows::Forms::Label());
			this->leftcamera = (gcnew System::Windows::Forms::GroupBox());
			this->db_th_label_l = (gcnew System::Windows::Forms::Label());
			this->db_th_box_l = (gcnew System::Windows::Forms::TextBox());
			this->roll_label_l = (gcnew System::Windows::Forms::Label());
			this->roll_box_l = (gcnew System::Windows::Forms::TextBox());
			this->roll_flag_l = (gcnew System::Windows::Forms::CheckBox());
			this->kalman_flag_l = (gcnew System::Windows::Forms::CheckBox());
			this->sub_flag_l = (gcnew System::Windows::Forms::CheckBox());
			this->db_all_l = (gcnew System::Windows::Forms::Button());
			this->db_reset_l = (gcnew System::Windows::Forms::Button());
			this->thl = (gcnew System::Windows::Forms::Label());
			this->th_box_l = (gcnew System::Windows::Forms::TextBox());
			this->all_flag_l = (gcnew System::Windows::Forms::CheckBox());
			this->db_flag_l = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->corr_l = (gcnew System::Windows::Forms::Label());
			this->correlatel = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->xl = (gcnew System::Windows::Forms::Label());
			this->yl = (gcnew System::Windows::Forms::Label());
			this->coodinatel = (gcnew System::Windows::Forms::Label());
			this->databasel = (gcnew System::Windows::Forms::Label());
			this->coor_xl = (gcnew System::Windows::Forms::Label());
			this->coor_yl = (gcnew System::Windows::Forms::Label());
			this->db_xl = (gcnew System::Windows::Forms::Label());
			this->db_yl = (gcnew System::Windows::Forms::Label());
			this->rightcamera = (gcnew System::Windows::Forms::GroupBox());
			this->db_th_label_r = (gcnew System::Windows::Forms::Label());
			this->db_th_box_r = (gcnew System::Windows::Forms::TextBox());
			this->roll_label_r = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->corr_r = (gcnew System::Windows::Forms::Label());
			this->correlater = (gcnew System::Windows::Forms::Label());
			this->roll_box_r = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->xr = (gcnew System::Windows::Forms::Label());
			this->yr = (gcnew System::Windows::Forms::Label());
			this->coodinater = (gcnew System::Windows::Forms::Label());
			this->databaser = (gcnew System::Windows::Forms::Label());
			this->coor_xr = (gcnew System::Windows::Forms::Label());
			this->coor_yr = (gcnew System::Windows::Forms::Label());
			this->db_xr = (gcnew System::Windows::Forms::Label());
			this->db_yr = (gcnew System::Windows::Forms::Label());
			this->roll_flag_r = (gcnew System::Windows::Forms::CheckBox());
			this->thr = (gcnew System::Windows::Forms::Label());
			this->kalman_flag_r = (gcnew System::Windows::Forms::CheckBox());
			this->db_flag_r = (gcnew System::Windows::Forms::CheckBox());
			this->sub_flag_r = (gcnew System::Windows::Forms::CheckBox());
			this->all_flag_r = (gcnew System::Windows::Forms::CheckBox());
			this->db_all_r = (gcnew System::Windows::Forms::Button());
			this->th_box_r = (gcnew System::Windows::Forms::TextBox());
			this->db_reset_r = (gcnew System::Windows::Forms::Button());
			this->offset_group = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->linear_a0 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->linear_a1 = (gcnew System::Windows::Forms::TextBox());
			this->tool_button = (gcnew System::Windows::Forms::Button());
			this->linear_a2 = (gcnew System::Windows::Forms::TextBox());
			this->offset_check = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->origin_measure_before = (gcnew System::Windows::Forms::Label());
			this->kalman = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->filename_label = (gcnew System::Windows::Forms::Label());
			this->pan_tilt_unit_group = (gcnew System::Windows::Forms::GroupBox());
			this->plat_th_label = (gcnew System::Windows::Forms::Label());
			this->plat_th_box = (gcnew System::Windows::Forms::TextBox());
			this->plat_home_button = (gcnew System::Windows::Forms::Button());
			this->plat_move_button = (gcnew System::Windows::Forms::Button());
			this->plat_stop_button = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tilt_label = (gcnew System::Windows::Forms::Label());
			this->platform_tilt = (gcnew System::Windows::Forms::Label());
			this->platform_pan = (gcnew System::Windows::Forms::Label());
			this->pla_move_label = (gcnew System::Windows::Forms::Label());
			this->pla_pos_label = (gcnew System::Windows::Forms::Label());
			this->move_tilt = (gcnew System::Windows::Forms::Label());
			this->pan_tilt_status = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->platform_state = (gcnew System::Windows::Forms::Label());
			this->save_box = (gcnew System::Windows::Forms::GroupBox());
			this->calib_check = (gcnew System::Windows::Forms::CheckBox());
			this->true_value = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->csv_check = (gcnew System::Windows::Forms::CheckBox());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->save_state = (gcnew System::Windows::Forms::Label());
			this->flame = (gcnew System::Windows::Forms::Label());
			this->flame_num = (gcnew System::Windows::Forms::NumericUpDown());
			this->filename_box = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->reset_button = (gcnew System::Windows::Forms::Button());
			this->output_button = (gcnew System::Windows::Forms::Button());
			this->read_button = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->base_box = (gcnew System::Windows::Forms::TextBox());
			this->base_label = (gcnew System::Windows::Forms::Label());
			this->pixel_box = (gcnew System::Windows::Forms::TextBox());
			this->pixel_label = (gcnew System::Windows::Forms::Label());
			this->focal_box = (gcnew System::Windows::Forms::TextBox());
			this->focal_label = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->pc_relative = (gcnew System::Windows::Forms::Button());
			this->pc_absolute = (gcnew System::Windows::Forms::Button());
			this->pc_tilt = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->pc_pan = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->pc_down = (gcnew System::Windows::Forms::Button());
			this->pc_right = (gcnew System::Windows::Forms::Button());
			this->pc_left = (gcnew System::Windows::Forms::Button());
			this->pc_up = (gcnew System::Windows::Forms::Button());
			this->movestep = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->server_dir_label = (gcnew System::Windows::Forms::Label());
			this->server_dir_button = (gcnew System::Windows::Forms::Button());
			this->server_dir_box = (gcnew System::Windows::Forms::TextBox());
			this->b_radio = (gcnew System::Windows::Forms::RadioButton());
			this->a_radio = (gcnew System::Windows::Forms::RadioButton());
			this->server_check = (gcnew System::Windows::Forms::CheckBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->centercamera_focallength = (gcnew System::Windows::Forms::TextBox());
			this->db_th_box_c = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->coor_xc = (gcnew System::Windows::Forms::Label());
			this->coor_yc = (gcnew System::Windows::Forms::Label());
			this->db_xc = (gcnew System::Windows::Forms::Label());
			this->db_yc = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->corr_c = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->roll_box_c = (gcnew System::Windows::Forms::TextBox());
			this->db_flag_c = (gcnew System::Windows::Forms::CheckBox());
			this->roll_flag_c = (gcnew System::Windows::Forms::CheckBox());
			this->all_flag_c = (gcnew System::Windows::Forms::CheckBox());
			this->kalman_flag_c = (gcnew System::Windows::Forms::CheckBox());
			this->th_box_c = (gcnew System::Windows::Forms::TextBox());
			this->sub_flag_c = (gcnew System::Windows::Forms::CheckBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->db_all_c = (gcnew System::Windows::Forms::Button());
			this->db_reset_c = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->Quit = (gcnew System::Windows::Forms::Button());
			this->leftcamera->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->rightcamera->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->offset_group->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->pan_tilt_unit_group->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->pan_tilt_status->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->save_box->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->flame_num))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->movestep))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->tableLayoutPanel10->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &ParamShow::timer1_Tick);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(225, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(43, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"0000.00";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->Click += gcnew System::EventHandler(this, &ParamShow::label2_Click);
			// 
			// theta
			// 
			this->theta->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->theta->AutoSize = true;
			this->theta->Location = System::Drawing::Point(77, 14);
			this->theta->Name = L"theta";
			this->theta->Size = System::Drawing::Size(37, 12);
			this->theta->TabIndex = 3;
			this->theta->Text = L"0.0000";
			this->theta->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->theta->Click += gcnew System::EventHandler(this, &ParamShow::label4_Click);
			// 
			// pan_label
			// 
			this->pan_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pan_label->AutoSize = true;
			this->pan_label->Location = System::Drawing::Point(7, 14);
			this->pan_label->Name = L"pan_label";
			this->pan_label->Size = System::Drawing::Size(24, 12);
			this->pan_label->TabIndex = 7;
			this->pan_label->Text = L"Pan";
			this->pan_label->Click += gcnew System::EventHandler(this, &ParamShow::label5_Click);
			// 
			// mid
			// 
			this->mid->AutoSize = true;
			this->mid->Location = System::Drawing::Point(3, 19);
			this->mid->Name = L"mid";
			this->mid->Size = System::Drawing::Size(91, 12);
			this->mid->TabIndex = 5;
			this->mid->Text = L"Correction Value";
			this->mid->Click += gcnew System::EventHandler(this, &ParamShow::label7_Click);
			// 
			// leftcamera
			// 
			this->leftcamera->Controls->Add(this->db_th_label_l);
			this->leftcamera->Controls->Add(this->db_th_box_l);
			this->leftcamera->Controls->Add(this->roll_label_l);
			this->leftcamera->Controls->Add(this->roll_box_l);
			this->leftcamera->Controls->Add(this->roll_flag_l);
			this->leftcamera->Controls->Add(this->kalman_flag_l);
			this->leftcamera->Controls->Add(this->sub_flag_l);
			this->leftcamera->Controls->Add(this->db_all_l);
			this->leftcamera->Controls->Add(this->db_reset_l);
			this->leftcamera->Controls->Add(this->thl);
			this->leftcamera->Controls->Add(this->th_box_l);
			this->leftcamera->Controls->Add(this->all_flag_l);
			this->leftcamera->Controls->Add(this->db_flag_l);
			this->leftcamera->Controls->Add(this->tableLayoutPanel3);
			this->leftcamera->Controls->Add(this->tableLayoutPanel1);
			this->leftcamera->Location = System::Drawing::Point(3, 6);
			this->leftcamera->Name = L"leftcamera";
			this->leftcamera->Size = System::Drawing::Size(143, 286);
			this->leftcamera->TabIndex = 8;
			this->leftcamera->TabStop = false;
			this->leftcamera->Text = L"Left Camera";
			// 
			// db_th_label_l
			// 
			this->db_th_label_l->AutoSize = true;
			this->db_th_label_l->Location = System::Drawing::Point(31, 116);
			this->db_th_label_l->Name = L"db_th_label_l";
			this->db_th_label_l->Size = System::Drawing::Size(55, 12);
			this->db_th_label_l->TabIndex = 23;
			this->db_th_label_l->Text = L"Threshold";
			// 
			// db_th_box_l
			// 
			this->db_th_box_l->Location = System::Drawing::Point(92, 113);
			this->db_th_box_l->Name = L"db_th_box_l";
			this->db_th_box_l->Size = System::Drawing::Size(42, 19);
			this->db_th_box_l->TabIndex = 22;
			this->db_th_box_l->Text = L"160";
			this->db_th_box_l->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// roll_label_l
			// 
			this->roll_label_l->AutoSize = true;
			this->roll_label_l->Enabled = false;
			this->roll_label_l->Location = System::Drawing::Point(31, 37);
			this->roll_label_l->Name = L"roll_label_l";
			this->roll_label_l->Size = System::Drawing::Size(34, 12);
			this->roll_label_l->TabIndex = 21;
			this->roll_label_l->Text = L"Value";
			// 
			// roll_box_l
			// 
			this->roll_box_l->Enabled = false;
			this->roll_box_l->Location = System::Drawing::Point(69, 34);
			this->roll_box_l->Name = L"roll_box_l";
			this->roll_box_l->Size = System::Drawing::Size(65, 19);
			this->roll_box_l->TabIndex = 20;
			this->roll_box_l->Text = L"0";
			this->roll_box_l->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// roll_flag_l
			// 
			this->roll_flag_l->AutoSize = true;
			this->roll_flag_l->Enabled = false;
			this->roll_flag_l->Location = System::Drawing::Point(10, 18);
			this->roll_flag_l->Name = L"roll_flag_l";
			this->roll_flag_l->Size = System::Drawing::Size(101, 16);
			this->roll_flag_l->TabIndex = 19;
			this->roll_flag_l->Text = L"Roll Correction";
			this->roll_flag_l->UseVisualStyleBackColor = true;
			// 
			// kalman_flag_l
			// 
			this->kalman_flag_l->AutoSize = true;
			this->kalman_flag_l->Location = System::Drawing::Point(10, 181);
			this->kalman_flag_l->Name = L"kalman_flag_l";
			this->kalman_flag_l->Size = System::Drawing::Size(92, 16);
			this->kalman_flag_l->TabIndex = 18;
			this->kalman_flag_l->Text = L"Kalman Filter";
			this->kalman_flag_l->UseVisualStyleBackColor = true;
			// 
			// sub_flag_l
			// 
			this->sub_flag_l->AutoSize = true;
			this->sub_flag_l->Checked = true;
			this->sub_flag_l->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sub_flag_l->Location = System::Drawing::Point(10, 164);
			this->sub_flag_l->Name = L"sub_flag_l";
			this->sub_flag_l->Size = System::Drawing::Size(114, 16);
			this->sub_flag_l->TabIndex = 17;
			this->sub_flag_l->Text = L"Sub-pixel Method";
			this->sub_flag_l->UseVisualStyleBackColor = true;
			// 
			// db_all_l
			// 
			this->db_all_l->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_all_l->Location = System::Drawing::Point(84, 135);
			this->db_all_l->Name = L"db_all_l";
			this->db_all_l->Size = System::Drawing::Size(50, 23);
			this->db_all_l->TabIndex = 16;
			this->db_all_l->Text = L"Search";
			this->db_all_l->UseVisualStyleBackColor = true;
			this->db_all_l->Click += gcnew System::EventHandler(this, &ParamShow::db_all_l_Click);
			// 
			// db_reset_l
			// 
			this->db_reset_l->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_reset_l->Location = System::Drawing::Point(30, 135);
			this->db_reset_l->Name = L"db_reset_l";
			this->db_reset_l->Size = System::Drawing::Size(50, 23);
			this->db_reset_l->TabIndex = 15;
			this->db_reset_l->Text = L"Reset";
			this->db_reset_l->UseVisualStyleBackColor = true;
			this->db_reset_l->Click += gcnew System::EventHandler(this, &ParamShow::db_reset_l_Click);
			// 
			// thl
			// 
			this->thl->AutoSize = true;
			this->thl->Location = System::Drawing::Point(31, 77);
			this->thl->Name = L"thl";
			this->thl->Size = System::Drawing::Size(55, 12);
			this->thl->TabIndex = 14;
			this->thl->Text = L"Threshold";
			// 
			// th_box_l
			// 
			this->th_box_l->Location = System::Drawing::Point(92, 74);
			this->th_box_l->Name = L"th_box_l";
			this->th_box_l->Size = System::Drawing::Size(42, 19);
			this->th_box_l->TabIndex = 13;
			this->th_box_l->Text = L"200";
			this->th_box_l->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// all_flag_l
			// 
			this->all_flag_l->AutoSize = true;
			this->all_flag_l->Checked = true;
			this->all_flag_l->CheckState = System::Windows::Forms::CheckState::Checked;
			this->all_flag_l->Location = System::Drawing::Point(10, 56);
			this->all_flag_l->Name = L"all_flag_l";
			this->all_flag_l->Size = System::Drawing::Size(95, 16);
			this->all_flag_l->TabIndex = 12;
			this->all_flag_l->Text = L"Seek All Area";
			this->all_flag_l->UseVisualStyleBackColor = true;
			this->all_flag_l->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::all_flag_l_CheckedChanged);
			// 
			// db_flag_l
			// 
			this->db_flag_l->AutoSize = true;
			this->db_flag_l->Checked = true;
			this->db_flag_l->CheckState = System::Windows::Forms::CheckState::Checked;
			this->db_flag_l->Location = System::Drawing::Point(10, 96);
			this->db_flag_l->Name = L"db_flag_l";
			this->db_flag_l->Size = System::Drawing::Size(109, 16);
			this->db_flag_l->TabIndex = 11;
			this->db_flag_l->Text = L"Target Database";
			this->db_flag_l->UseVisualStyleBackColor = true;
			this->db_flag_l->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::db_flag_l_CheckedChanged);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				60)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel3->Controls->Add(this->corr_l, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->correlatel, 0, 0);
			this->tableLayoutPanel3->Location = System::Drawing::Point(6, 259);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 19)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(113, 19);
			this->tableLayoutPanel3->TabIndex = 10;
			// 
			// corr_l
			// 
			this->corr_l->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->corr_l->AutoSize = true;
			this->corr_l->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->corr_l->Location = System::Drawing::Point(70, 0);
			this->corr_l->Name = L"corr_l";
			this->corr_l->Size = System::Drawing::Size(40, 12);
			this->corr_l->TabIndex = 5;
			this->corr_l->Text = L"000";
			this->corr_l->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// correlatel
			// 
			this->correlatel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->correlatel->AutoSize = true;
			this->correlatel->Location = System::Drawing::Point(3, 0);
			this->correlatel->Name = L"correlatel";
			this->correlatel->Size = System::Drawing::Size(61, 12);
			this->correlatel->TabIndex = 3;
			this->correlatel->Text = L"Correlation";
			this->correlatel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				68.68687F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				31.31313F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				44)));
			this->tableLayoutPanel1->Controls->Add(this->xl, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->yl, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->coodinatel, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->databasel, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->coor_xl, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->coor_yl, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->db_xl, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->db_yl, 2, 2);
			this->tableLayoutPanel1->Location = System::Drawing::Point(6, 199);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(131, 59);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// xl
			// 
			this->xl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->xl->AutoSize = true;
			this->xl->Location = System::Drawing::Point(62, 0);
			this->xl->Name = L"xl";
			this->xl->Size = System::Drawing::Size(21, 12);
			this->xl->TabIndex = 0;
			this->xl->Text = L"x";
			this->xl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// yl
			// 
			this->yl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->yl->AutoSize = true;
			this->yl->Location = System::Drawing::Point(89, 0);
			this->yl->Name = L"yl";
			this->yl->Size = System::Drawing::Size(39, 12);
			this->yl->TabIndex = 1;
			this->yl->Text = L"y";
			this->yl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coodinatel
			// 
			this->coodinatel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coodinatel->AutoSize = true;
			this->coodinatel->Location = System::Drawing::Point(3, 19);
			this->coodinatel->Name = L"coodinatel";
			this->coodinatel->Size = System::Drawing::Size(53, 19);
			this->coodinatel->TabIndex = 2;
			this->coodinatel->Text = L"Coordinate ";
			this->coodinatel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// databasel
			// 
			this->databasel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->databasel->AutoSize = true;
			this->databasel->Location = System::Drawing::Point(3, 38);
			this->databasel->Name = L"databasel";
			this->databasel->Size = System::Drawing::Size(53, 12);
			this->databasel->TabIndex = 3;
			this->databasel->Text = L"Database";
			this->databasel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_xl
			// 
			this->coor_xl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_xl->AutoSize = true;
			this->coor_xl->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_xl->Location = System::Drawing::Point(62, 19);
			this->coor_xl->Name = L"coor_xl";
			this->coor_xl->Size = System::Drawing::Size(21, 19);
			this->coor_xl->TabIndex = 4;
			this->coor_xl->Text = L"000";
			this->coor_xl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_yl
			// 
			this->coor_yl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_yl->AutoSize = true;
			this->coor_yl->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_yl->Location = System::Drawing::Point(89, 19);
			this->coor_yl->Name = L"coor_yl";
			this->coor_yl->Size = System::Drawing::Size(39, 12);
			this->coor_yl->TabIndex = 5;
			this->coor_yl->Text = L"000";
			this->coor_yl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_xl
			// 
			this->db_xl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_xl->AutoSize = true;
			this->db_xl->Location = System::Drawing::Point(62, 38);
			this->db_xl->Name = L"db_xl";
			this->db_xl->Size = System::Drawing::Size(21, 12);
			this->db_xl->TabIndex = 6;
			this->db_xl->Text = L"4";
			this->db_xl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_yl
			// 
			this->db_yl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_yl->AutoSize = true;
			this->db_yl->Location = System::Drawing::Point(89, 38);
			this->db_yl->Name = L"db_yl";
			this->db_yl->Size = System::Drawing::Size(39, 12);
			this->db_yl->TabIndex = 7;
			this->db_yl->Text = L"4";
			this->db_yl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// rightcamera
			// 
			this->rightcamera->Controls->Add(this->db_th_label_r);
			this->rightcamera->Controls->Add(this->db_th_box_r);
			this->rightcamera->Controls->Add(this->roll_label_r);
			this->rightcamera->Controls->Add(this->tableLayoutPanel4);
			this->rightcamera->Controls->Add(this->roll_box_r);
			this->rightcamera->Controls->Add(this->tableLayoutPanel2);
			this->rightcamera->Controls->Add(this->roll_flag_r);
			this->rightcamera->Controls->Add(this->thr);
			this->rightcamera->Controls->Add(this->kalman_flag_r);
			this->rightcamera->Controls->Add(this->db_flag_r);
			this->rightcamera->Controls->Add(this->sub_flag_r);
			this->rightcamera->Controls->Add(this->all_flag_r);
			this->rightcamera->Controls->Add(this->db_all_r);
			this->rightcamera->Controls->Add(this->th_box_r);
			this->rightcamera->Controls->Add(this->db_reset_r);
			this->rightcamera->Location = System::Drawing::Point(152, 6);
			this->rightcamera->Name = L"rightcamera";
			this->rightcamera->Size = System::Drawing::Size(143, 286);
			this->rightcamera->TabIndex = 9;
			this->rightcamera->TabStop = false;
			this->rightcamera->Text = L"Right Camera";
			// 
			// db_th_label_r
			// 
			this->db_th_label_r->AutoSize = true;
			this->db_th_label_r->Location = System::Drawing::Point(30, 116);
			this->db_th_label_r->Name = L"db_th_label_r";
			this->db_th_label_r->Size = System::Drawing::Size(55, 12);
			this->db_th_label_r->TabIndex = 34;
			this->db_th_label_r->Text = L"Threshold";
			// 
			// db_th_box_r
			// 
			this->db_th_box_r->Location = System::Drawing::Point(91, 113);
			this->db_th_box_r->Name = L"db_th_box_r";
			this->db_th_box_r->Size = System::Drawing::Size(42, 19);
			this->db_th_box_r->TabIndex = 33;
			this->db_th_box_r->Text = L"160";
			this->db_th_box_r->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// roll_label_r
			// 
			this->roll_label_r->AutoSize = true;
			this->roll_label_r->Enabled = false;
			this->roll_label_r->Location = System::Drawing::Point(28, 37);
			this->roll_label_r->Name = L"roll_label_r";
			this->roll_label_r->Size = System::Drawing::Size(34, 12);
			this->roll_label_r->TabIndex = 32;
			this->roll_label_r->Text = L"Value";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				60.34483F)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				39.65517F)));
			this->tableLayoutPanel4->Controls->Add(this->corr_r, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->correlater, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(5, 259);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(116, 19);
			this->tableLayoutPanel4->TabIndex = 11;
			// 
			// corr_r
			// 
			this->corr_r->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->corr_r->AutoSize = true;
			this->corr_r->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->corr_r->Location = System::Drawing::Point(73, 0);
			this->corr_r->Name = L"corr_r";
			this->corr_r->Size = System::Drawing::Size(40, 12);
			this->corr_r->TabIndex = 5;
			this->corr_r->Text = L"000";
			this->corr_r->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// correlater
			// 
			this->correlater->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->correlater->AutoSize = true;
			this->correlater->Location = System::Drawing::Point(3, 0);
			this->correlater->Name = L"correlater";
			this->correlater->Size = System::Drawing::Size(64, 12);
			this->correlater->TabIndex = 3;
			this->correlater->Text = L"Correlation";
			this->correlater->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// roll_box_r
			// 
			this->roll_box_r->Enabled = false;
			this->roll_box_r->Location = System::Drawing::Point(68, 34);
			this->roll_box_r->Name = L"roll_box_r";
			this->roll_box_r->Size = System::Drawing::Size(65, 19);
			this->roll_box_r->TabIndex = 31;
			this->roll_box_r->Text = L"0";
			this->roll_box_r->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				70)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				31)));
			this->tableLayoutPanel2->Controls->Add(this->xr, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->yr, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->coodinater, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->databaser, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->coor_xr, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->coor_yr, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->db_xr, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->db_yr, 2, 2);
			this->tableLayoutPanel2->Location = System::Drawing::Point(5, 199);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 3;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(131, 59);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// xr
			// 
			this->xr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->xr->AutoSize = true;
			this->xr->Location = System::Drawing::Point(73, 0);
			this->xr->Name = L"xr";
			this->xr->Size = System::Drawing::Size(24, 12);
			this->xr->TabIndex = 0;
			this->xr->Text = L"x";
			this->xr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// yr
			// 
			this->yr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->yr->AutoSize = true;
			this->yr->Location = System::Drawing::Point(103, 0);
			this->yr->Name = L"yr";
			this->yr->Size = System::Drawing::Size(25, 12);
			this->yr->TabIndex = 1;
			this->yr->Text = L"y";
			this->yr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coodinater
			// 
			this->coodinater->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coodinater->AutoSize = true;
			this->coodinater->Location = System::Drawing::Point(3, 19);
			this->coodinater->Name = L"coodinater";
			this->coodinater->Size = System::Drawing::Size(64, 12);
			this->coodinater->TabIndex = 2;
			this->coodinater->Text = L"Coordinate";
			this->coodinater->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// databaser
			// 
			this->databaser->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->databaser->AutoSize = true;
			this->databaser->Location = System::Drawing::Point(3, 38);
			this->databaser->Name = L"databaser";
			this->databaser->Size = System::Drawing::Size(64, 12);
			this->databaser->TabIndex = 3;
			this->databaser->Text = L"Database";
			this->databaser->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_xr
			// 
			this->coor_xr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_xr->AutoSize = true;
			this->coor_xr->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_xr->Location = System::Drawing::Point(73, 19);
			this->coor_xr->Name = L"coor_xr";
			this->coor_xr->Size = System::Drawing::Size(24, 12);
			this->coor_xr->TabIndex = 4;
			this->coor_xr->Text = L"000";
			this->coor_xr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_yr
			// 
			this->coor_yr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_yr->AutoSize = true;
			this->coor_yr->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_yr->Location = System::Drawing::Point(103, 19);
			this->coor_yr->Name = L"coor_yr";
			this->coor_yr->Size = System::Drawing::Size(25, 12);
			this->coor_yr->TabIndex = 5;
			this->coor_yr->Text = L"000";
			this->coor_yr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_xr
			// 
			this->db_xr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_xr->AutoSize = true;
			this->db_xr->Location = System::Drawing::Point(73, 38);
			this->db_xr->Name = L"db_xr";
			this->db_xr->Size = System::Drawing::Size(24, 12);
			this->db_xr->TabIndex = 6;
			this->db_xr->Text = L"4";
			this->db_xr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_yr
			// 
			this->db_yr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_yr->AutoSize = true;
			this->db_yr->Location = System::Drawing::Point(103, 38);
			this->db_yr->Name = L"db_yr";
			this->db_yr->Size = System::Drawing::Size(25, 12);
			this->db_yr->TabIndex = 7;
			this->db_yr->Text = L"4";
			this->db_yr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// roll_flag_r
			// 
			this->roll_flag_r->AutoSize = true;
			this->roll_flag_r->Enabled = false;
			this->roll_flag_r->Location = System::Drawing::Point(9, 18);
			this->roll_flag_r->Name = L"roll_flag_r";
			this->roll_flag_r->Size = System::Drawing::Size(101, 16);
			this->roll_flag_r->TabIndex = 30;
			this->roll_flag_r->Text = L"Roll Correction";
			this->roll_flag_r->UseVisualStyleBackColor = true;
			// 
			// thr
			// 
			this->thr->AutoSize = true;
			this->thr->Location = System::Drawing::Point(30, 77);
			this->thr->Name = L"thr";
			this->thr->Size = System::Drawing::Size(55, 12);
			this->thr->TabIndex = 25;
			this->thr->Text = L"Threshold";
			// 
			// kalman_flag_r
			// 
			this->kalman_flag_r->AutoSize = true;
			this->kalman_flag_r->Location = System::Drawing::Point(8, 181);
			this->kalman_flag_r->Name = L"kalman_flag_r";
			this->kalman_flag_r->Size = System::Drawing::Size(92, 16);
			this->kalman_flag_r->TabIndex = 29;
			this->kalman_flag_r->Text = L"Kalman Filter";
			this->kalman_flag_r->UseVisualStyleBackColor = true;
			// 
			// db_flag_r
			// 
			this->db_flag_r->AutoSize = true;
			this->db_flag_r->Location = System::Drawing::Point(9, 96);
			this->db_flag_r->Name = L"db_flag_r";
			this->db_flag_r->Size = System::Drawing::Size(109, 16);
			this->db_flag_r->TabIndex = 22;
			this->db_flag_r->Text = L"Target Database";
			this->db_flag_r->UseVisualStyleBackColor = true;
			this->db_flag_r->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::db_flag_r_CheckedChanged);
			// 
			// sub_flag_r
			// 
			this->sub_flag_r->AutoSize = true;
			this->sub_flag_r->Checked = true;
			this->sub_flag_r->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sub_flag_r->Location = System::Drawing::Point(8, 164);
			this->sub_flag_r->Name = L"sub_flag_r";
			this->sub_flag_r->Size = System::Drawing::Size(117, 16);
			this->sub_flag_r->TabIndex = 28;
			this->sub_flag_r->Text = L"Sub-pexel Method";
			this->sub_flag_r->UseVisualStyleBackColor = true;
			// 
			// all_flag_r
			// 
			this->all_flag_r->AutoSize = true;
			this->all_flag_r->Checked = true;
			this->all_flag_r->CheckState = System::Windows::Forms::CheckState::Checked;
			this->all_flag_r->Location = System::Drawing::Point(9, 56);
			this->all_flag_r->Name = L"all_flag_r";
			this->all_flag_r->Size = System::Drawing::Size(95, 16);
			this->all_flag_r->TabIndex = 23;
			this->all_flag_r->Text = L"Seek All Area";
			this->all_flag_r->UseVisualStyleBackColor = true;
			this->all_flag_r->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::all_flag_r_CheckedChanged);
			// 
			// db_all_r
			// 
			this->db_all_r->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_all_r->Location = System::Drawing::Point(82, 135);
			this->db_all_r->Name = L"db_all_r";
			this->db_all_r->Size = System::Drawing::Size(50, 23);
			this->db_all_r->TabIndex = 27;
			this->db_all_r->Text = L"Search";
			this->db_all_r->UseVisualStyleBackColor = true;
			this->db_all_r->Click += gcnew System::EventHandler(this, &ParamShow::db_all_r_Click);
			// 
			// th_box_r
			// 
			this->th_box_r->Location = System::Drawing::Point(91, 74);
			this->th_box_r->Name = L"th_box_r";
			this->th_box_r->Size = System::Drawing::Size(42, 19);
			this->th_box_r->TabIndex = 24;
			this->th_box_r->Text = L"200";
			this->th_box_r->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// db_reset_r
			// 
			this->db_reset_r->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_reset_r->Location = System::Drawing::Point(28, 135);
			this->db_reset_r->Name = L"db_reset_r";
			this->db_reset_r->Size = System::Drawing::Size(50, 23);
			this->db_reset_r->TabIndex = 26;
			this->db_reset_r->Text = L"Reset";
			this->db_reset_r->UseVisualStyleBackColor = true;
			this->db_reset_r->Click += gcnew System::EventHandler(this, &ParamShow::db_reset_r_Click);
			// 
			// offset_group
			// 
			this->offset_group->Controls->Add(this->label8);
			this->offset_group->Controls->Add(this->label9);
			this->offset_group->Controls->Add(this->linear_a0);
			this->offset_group->Controls->Add(this->label4);
			this->offset_group->Controls->Add(this->linear_a1);
			this->offset_group->Controls->Add(this->tool_button);
			this->offset_group->Controls->Add(this->linear_a2);
			this->offset_group->Controls->Add(this->offset_check);
			this->offset_group->Location = System::Drawing::Point(3, 95);
			this->offset_group->Name = L"offset_group";
			this->offset_group->Size = System::Drawing::Size(216, 94);
			this->offset_group->TabIndex = 10;
			this->offset_group->TabStop = false;
			this->offset_group->Text = L"Correction";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label8->Location = System::Drawing::Point(201, 15);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(11, 11);
			this->label8->TabIndex = 29;
			this->label8->Text = L"2";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(194, 19);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(11, 12);
			this->label9->TabIndex = 28;
			this->label9->Text = L"x";
			// 
			// linear_a0
			// 
			this->linear_a0->Enabled = false;
			this->linear_a0->Location = System::Drawing::Point(109, 66);
			this->linear_a0->Name = L"linear_a0";
			this->linear_a0->Size = System::Drawing::Size(79, 19);
			this->linear_a0->TabIndex = 25;
			this->linear_a0->Text = L"0.0";
			this->linear_a0->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Enabled = false;
			this->label4->Location = System::Drawing::Point(194, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(11, 12);
			this->label4->TabIndex = 24;
			this->label4->Text = L"x";
			// 
			// linear_a1
			// 
			this->linear_a1->Enabled = false;
			this->linear_a1->Location = System::Drawing::Point(87, 41);
			this->linear_a1->Name = L"linear_a1";
			this->linear_a1->Size = System::Drawing::Size(101, 19);
			this->linear_a1->TabIndex = 12;
			this->linear_a1->Text = L"0.0";
			this->linear_a1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tool_button
			// 
			this->tool_button->Location = System::Drawing::Point(6, 62);
			this->tool_button->Name = L"tool_button";
			this->tool_button->Size = System::Drawing::Size(55, 20);
			this->tool_button->TabIndex = 10;
			this->tool_button->Text = L"Tool";
			this->tool_button->UseVisualStyleBackColor = true;
			this->tool_button->Click += gcnew System::EventHandler(this, &ParamShow::tool_button_Click);
			// 
			// linear_a2
			// 
			this->linear_a2->Enabled = false;
			this->linear_a2->Location = System::Drawing::Point(62, 16);
			this->linear_a2->Name = L"linear_a2";
			this->linear_a2->Size = System::Drawing::Size(126, 19);
			this->linear_a2->TabIndex = 9;
			this->linear_a2->Text = L"0.0";
			this->linear_a2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// offset_check
			// 
			this->offset_check->AutoSize = true;
			this->offset_check->Location = System::Drawing::Point(6, 18);
			this->offset_check->Name = L"offset_check";
			this->offset_check->Size = System::Drawing::Size(53, 16);
			this->offset_check->TabIndex = 8;
			this->offset_check->Text = L"Apply";
			this->offset_check->UseVisualStyleBackColor = true;
			this->offset_check->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::offset_check_CheckedChanged);
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				53.37423F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				46.62577F)));
			this->tableLayoutPanel6->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->origin_measure_before, 1, 0);
			this->tableLayoutPanel6->Controls->Add(this->mid, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->label2, 1, 1);
			this->tableLayoutPanel6->Controls->Add(this->kalman, 0, 2);
			this->tableLayoutPanel6->Controls->Add(this->label3, 1, 2);
			this->tableLayoutPanel6->Location = System::Drawing::Point(9, 19);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 3;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(271, 57);
			this->tableLayoutPanel6->TabIndex = 0;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(77, 12);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Original Value";
			// 
			// origin_measure_before
			// 
			this->origin_measure_before->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->origin_measure_before->AutoSize = true;
			this->origin_measure_before->Location = System::Drawing::Point(225, 0);
			this->origin_measure_before->Name = L"origin_measure_before";
			this->origin_measure_before->Size = System::Drawing::Size(43, 12);
			this->origin_measure_before->TabIndex = 0;
			this->origin_measure_before->Text = L"0000.00";
			this->origin_measure_before->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// kalman
			// 
			this->kalman->AutoSize = true;
			this->kalman->Location = System::Drawing::Point(3, 38);
			this->kalman->Name = L"kalman";
			this->kalman->Size = System::Drawing::Size(73, 12);
			this->kalman->TabIndex = 6;
			this->kalman->Text = L"Kalman Filter";
			this->kalman->Click += gcnew System::EventHandler(this, &ParamShow::label6_Click);
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(225, 38);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 12);
			this->label3->TabIndex = 2;
			this->label3->Text = L"0000.00";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label3->Click += gcnew System::EventHandler(this, &ParamShow::label3_Click);
			// 
			// filename_label
			// 
			this->filename_label->AutoSize = true;
			this->filename_label->Location = System::Drawing::Point(9, 18);
			this->filename_label->Name = L"filename_label";
			this->filename_label->Size = System::Drawing::Size(70, 12);
			this->filename_label->TabIndex = 7;
			this->filename_label->Text = L"Folder Name";
			// 
			// pan_tilt_unit_group
			// 
			this->pan_tilt_unit_group->Controls->Add(this->plat_th_label);
			this->pan_tilt_unit_group->Controls->Add(this->plat_th_box);
			this->pan_tilt_unit_group->Controls->Add(this->plat_home_button);
			this->pan_tilt_unit_group->Controls->Add(this->plat_move_button);
			this->pan_tilt_unit_group->Controls->Add(this->plat_stop_button);
			this->pan_tilt_unit_group->Controls->Add(this->tableLayoutPanel5);
			this->pan_tilt_unit_group->Controls->Add(this->pan_tilt_status);
			this->pan_tilt_unit_group->Location = System::Drawing::Point(3, 6);
			this->pan_tilt_unit_group->Name = L"pan_tilt_unit_group";
			this->pan_tilt_unit_group->Size = System::Drawing::Size(292, 88);
			this->pan_tilt_unit_group->TabIndex = 11;
			this->pan_tilt_unit_group->TabStop = false;
			this->pan_tilt_unit_group->Text = L"Camera Platform";
			// 
			// plat_th_label
			// 
			this->plat_th_label->AutoSize = true;
			this->plat_th_label->Location = System::Drawing::Point(6, 66);
			this->plat_th_label->Name = L"plat_th_label";
			this->plat_th_label->Size = System::Drawing::Size(95, 12);
			this->plat_th_label->TabIndex = 23;
			this->plat_th_label->Text = L"Moving Threshold";
			// 
			// plat_th_box
			// 
			this->plat_th_box->Location = System::Drawing::Point(103, 63);
			this->plat_th_box->Name = L"plat_th_box";
			this->plat_th_box->Size = System::Drawing::Size(42, 19);
			this->plat_th_box->TabIndex = 22;
			this->plat_th_box->Text = L"220";
			this->plat_th_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// plat_home_button
			// 
			this->plat_home_button->Location = System::Drawing::Point(151, 61);
			this->plat_home_button->Name = L"plat_home_button";
			this->plat_home_button->Size = System::Drawing::Size(43, 23);
			this->plat_home_button->TabIndex = 4;
			this->plat_home_button->Text = L"Home";
			this->plat_home_button->UseVisualStyleBackColor = true;
			this->plat_home_button->Click += gcnew System::EventHandler(this, &ParamShow::plat_home_button_Click);
			// 
			// plat_move_button
			// 
			this->plat_move_button->Location = System::Drawing::Point(197, 61);
			this->plat_move_button->Name = L"plat_move_button";
			this->plat_move_button->Size = System::Drawing::Size(43, 23);
			this->plat_move_button->TabIndex = 3;
			this->plat_move_button->Text = L"Auto";
			this->plat_move_button->UseVisualStyleBackColor = true;
			this->plat_move_button->Click += gcnew System::EventHandler(this, &ParamShow::plat_move_button_Click);
			// 
			// plat_stop_button
			// 
			this->plat_stop_button->Location = System::Drawing::Point(243, 61);
			this->plat_stop_button->Name = L"plat_stop_button";
			this->plat_stop_button->Size = System::Drawing::Size(43, 23);
			this->plat_stop_button->TabIndex = 2;
			this->plat_stop_button->Text = L"Stop";
			this->plat_stop_button->UseVisualStyleBackColor = true;
			this->plat_stop_button->Click += gcnew System::EventHandler(this, &ParamShow::plat_stop_button_Click);
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 3;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				38)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				79)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				80)));
			this->tableLayoutPanel5->Controls->Add(this->tilt_label, 0, 2);
			this->tableLayoutPanel5->Controls->Add(this->pan_label, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->platform_tilt, 2, 2);
			this->tableLayoutPanel5->Controls->Add(this->platform_pan, 2, 1);
			this->tableLayoutPanel5->Controls->Add(this->pla_move_label, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->pla_pos_label, 2, 0);
			this->tableLayoutPanel5->Controls->Add(this->theta, 1, 1);
			this->tableLayoutPanel5->Controls->Add(this->move_tilt, 1, 2);
			this->tableLayoutPanel5->Location = System::Drawing::Point(89, 12);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 3;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(197, 43);
			this->tableLayoutPanel5->TabIndex = 1;
			// 
			// tilt_label
			// 
			this->tilt_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->tilt_label->AutoSize = true;
			this->tilt_label->Location = System::Drawing::Point(8, 28);
			this->tilt_label->Name = L"tilt_label";
			this->tilt_label->Size = System::Drawing::Size(22, 12);
			this->tilt_label->TabIndex = 11;
			this->tilt_label->Text = L"Tilt";
			// 
			// platform_tilt
			// 
			this->platform_tilt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->platform_tilt->AutoSize = true;
			this->platform_tilt->Location = System::Drawing::Point(157, 28);
			this->platform_tilt->Name = L"platform_tilt";
			this->platform_tilt->Size = System::Drawing::Size(37, 12);
			this->platform_tilt->TabIndex = 10;
			this->platform_tilt->Text = L"0.0000";
			this->platform_tilt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// platform_pan
			// 
			this->platform_pan->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->platform_pan->AutoSize = true;
			this->platform_pan->Location = System::Drawing::Point(157, 14);
			this->platform_pan->Name = L"platform_pan";
			this->platform_pan->Size = System::Drawing::Size(37, 12);
			this->platform_pan->TabIndex = 9;
			this->platform_pan->Text = L"0.0000";
			this->platform_pan->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pla_move_label
			// 
			this->pla_move_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pla_move_label->AutoSize = true;
			this->pla_move_label->Location = System::Drawing::Point(69, 0);
			this->pla_move_label->Name = L"pla_move_label";
			this->pla_move_label->Size = System::Drawing::Size(45, 12);
			this->pla_move_label->TabIndex = 8;
			this->pla_move_label->Text = L"Controll";
			this->pla_move_label->Click += gcnew System::EventHandler(this, &ParamShow::label4_Click_1);
			// 
			// pla_pos_label
			// 
			this->pla_pos_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pla_pos_label->AutoSize = true;
			this->pla_pos_label->Location = System::Drawing::Point(143, 0);
			this->pla_pos_label->Name = L"pla_pos_label";
			this->pla_pos_label->Size = System::Drawing::Size(51, 12);
			this->pla_pos_label->TabIndex = 12;
			this->pla_pos_label->Text = L"Direction";
			// 
			// move_tilt
			// 
			this->move_tilt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->move_tilt->AutoSize = true;
			this->move_tilt->Location = System::Drawing::Point(77, 28);
			this->move_tilt->Name = L"move_tilt";
			this->move_tilt->Size = System::Drawing::Size(37, 12);
			this->move_tilt->TabIndex = 13;
			this->move_tilt->Text = L"0.0000";
			this->move_tilt->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pan_tilt_status
			// 
			this->pan_tilt_status->Controls->Add(this->tableLayoutPanel8);
			this->pan_tilt_status->Location = System::Drawing::Point(6, 19);
			this->pan_tilt_status->Name = L"pan_tilt_status";
			this->pan_tilt_status->Size = System::Drawing::Size(81, 42);
			this->pan_tilt_status->TabIndex = 0;
			this->pan_tilt_status->TabStop = false;
			this->pan_tilt_status->Text = L"Status";
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel8->ColumnCount = 1;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel8->Controls->Add(this->platform_state, 0, 0);
			this->tableLayoutPanel8->Location = System::Drawing::Point(6, 18);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(71, 15);
			this->tableLayoutPanel8->TabIndex = 12;
			// 
			// platform_state
			// 
			this->platform_state->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->platform_state->AutoSize = true;
			this->platform_state->BackColor = System::Drawing::SystemColors::Control;
			this->platform_state->Location = System::Drawing::Point(5, 0);
			this->platform_state->Name = L"platform_state";
			this->platform_state->Size = System::Drawing::Size(63, 12);
			this->platform_state->TabIndex = 0;
			this->platform_state->Text = L"No connect";
			this->platform_state->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->platform_state->Click += gcnew System::EventHandler(this, &ParamShow::platform_state_Click);
			// 
			// save_box
			// 
			this->save_box->Controls->Add(this->calib_check);
			this->save_box->Controls->Add(this->true_value);
			this->save_box->Controls->Add(this->label6);
			this->save_box->Controls->Add(this->csv_check);
			this->save_box->Controls->Add(this->save_button);
			this->save_box->Controls->Add(this->groupBox1);
			this->save_box->Controls->Add(this->flame);
			this->save_box->Controls->Add(this->flame_num);
			this->save_box->Controls->Add(this->filename_box);
			this->save_box->Controls->Add(this->filename_label);
			this->save_box->Location = System::Drawing::Point(3, 241);
			this->save_box->Name = L"save_box";
			this->save_box->Size = System::Drawing::Size(292, 112);
			this->save_box->TabIndex = 12;
			this->save_box->TabStop = false;
			this->save_box->Text = L"Data Output";
			// 
			// calib_check
			// 
			this->calib_check->AutoSize = true;
			this->calib_check->Location = System::Drawing::Point(167, 41);
			this->calib_check->Name = L"calib_check";
			this->calib_check->Size = System::Drawing::Size(79, 16);
			this->calib_check->TabIndex = 14;
			this->calib_check->Text = L"Calibration";
			this->calib_check->UseVisualStyleBackColor = true;
			this->calib_check->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::calib_check_CheckedChanged);
			// 
			// true_value
			// 
			this->true_value->Location = System::Drawing::Point(230, 15);
			this->true_value->Name = L"true_value";
			this->true_value->Size = System::Drawing::Size(53, 19);
			this->true_value->TabIndex = 13;
			this->true_value->Text = L"0";
			this->true_value->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(165, 18);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(66, 12);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Correct dist";
			// 
			// csv_check
			// 
			this->csv_check->AutoSize = true;
			this->csv_check->Location = System::Drawing::Point(167, 59);
			this->csv_check->Name = L"csv_check";
			this->csv_check->Size = System::Drawing::Size(100, 16);
			this->csv_check->TabIndex = 10;
			this->csv_check->Text = L"Save log (.csv)";
			this->csv_check->UseVisualStyleBackColor = true;
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(167, 77);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(119, 23);
			this->save_button->TabIndex = 11;
			this->save_button->Text = L"Save Start";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &ParamShow::save_button_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tableLayoutPanel7);
			this->groupBox1->Location = System::Drawing::Point(6, 59);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(150, 44);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Status";
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 1;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel7->Controls->Add(this->save_state, 0, 1);
			this->tableLayoutPanel7->Location = System::Drawing::Point(6, 18);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 2;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(138, 18);
			this->tableLayoutPanel7->TabIndex = 11;
			// 
			// save_state
			// 
			this->save_state->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->save_state->AutoSize = true;
			this->save_state->Location = System::Drawing::Point(70, -2);
			this->save_state->Name = L"save_state";
			this->save_state->Size = System::Drawing::Size(65, 12);
			this->save_state->TabIndex = 0;
			this->save_state->Text = L"Preservable";
			this->save_state->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// flame
			// 
			this->flame->AutoSize = true;
			this->flame->Location = System::Drawing::Point(66, 42);
			this->flame->Name = L"flame";
			this->flame->Size = System::Drawing::Size(37, 12);
			this->flame->TabIndex = 10;
			this->flame->Text = L"Frame";
			// 
			// flame_num
			// 
			this->flame_num->Location = System::Drawing::Point(109, 38);
			this->flame_num->Name = L"flame_num";
			this->flame_num->Size = System::Drawing::Size(43, 19);
			this->flame_num->TabIndex = 9;
			this->flame_num->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->flame_num->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// filename_box
			// 
			this->filename_box->Location = System::Drawing::Point(85, 15);
			this->filename_box->Name = L"filename_box";
			this->filename_box->Size = System::Drawing::Size(67, 19);
			this->filename_box->TabIndex = 8;
			this->filename_box->Text = L"distance";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->reset_button);
			this->groupBox2->Controls->Add(this->output_button);
			this->groupBox2->Controls->Add(this->read_button);
			this->groupBox2->Location = System::Drawing::Point(226, 95);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(69, 94);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Config";
			// 
			// reset_button
			// 
			this->reset_button->Location = System::Drawing::Point(7, 63);
			this->reset_button->Name = L"reset_button";
			this->reset_button->Size = System::Drawing::Size(53, 20);
			this->reset_button->TabIndex = 2;
			this->reset_button->Text = L"Init";
			this->reset_button->UseVisualStyleBackColor = true;
			this->reset_button->Click += gcnew System::EventHandler(this, &ParamShow::reset_button_Click);
			// 
			// output_button
			// 
			this->output_button->Location = System::Drawing::Point(7, 40);
			this->output_button->Name = L"output_button";
			this->output_button->Size = System::Drawing::Size(53, 20);
			this->output_button->TabIndex = 1;
			this->output_button->Text = L"Export";
			this->output_button->UseVisualStyleBackColor = true;
			this->output_button->Click += gcnew System::EventHandler(this, &ParamShow::output_button_Click);
			// 
			// read_button
			// 
			this->read_button->Location = System::Drawing::Point(7, 17);
			this->read_button->Name = L"read_button";
			this->read_button->Size = System::Drawing::Size(53, 20);
			this->read_button->TabIndex = 0;
			this->read_button->Text = L"Import";
			this->read_button->UseVisualStyleBackColor = true;
			this->read_button->Click += gcnew System::EventHandler(this, &ParamShow::read_button_Click);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &ParamShow::saveFileDialog1_FileOk);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->base_box);
			this->groupBox3->Controls->Add(this->base_label);
			this->groupBox3->Controls->Add(this->pixel_box);
			this->groupBox3->Controls->Add(this->pixel_label);
			this->groupBox3->Controls->Add(this->focal_box);
			this->groupBox3->Controls->Add(this->focal_label);
			this->groupBox3->Location = System::Drawing::Point(3, 195);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(292, 40);
			this->groupBox3->TabIndex = 14;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Stereo Camera Setup";
			// 
			// base_box
			// 
			this->base_box->Location = System::Drawing::Point(73, 15);
			this->base_box->Name = L"base_box";
			this->base_box->Size = System::Drawing::Size(30, 19);
			this->base_box->TabIndex = 19;
			this->base_box->Text = L"300";
			this->base_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// base_label
			// 
			this->base_label->AutoSize = true;
			this->base_label->Location = System::Drawing::Point(4, 18);
			this->base_label->Name = L"base_label";
			this->base_label->Size = System::Drawing::Size(69, 12);
			this->base_label->TabIndex = 18;
			this->base_label->Text = L"Base Length";
			// 
			// pixel_box
			// 
			this->pixel_box->Location = System::Drawing::Point(240, 15);
			this->pixel_box->Name = L"pixel_box";
			this->pixel_box->Size = System::Drawing::Size(41, 19);
			this->pixel_box->TabIndex = 17;
			this->pixel_box->Text = L"0.0075";
			this->pixel_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// pixel_label
			// 
			this->pixel_label->AutoSize = true;
			this->pixel_label->Location = System::Drawing::Point(180, 18);
			this->pixel_label->Name = L"pixel_label";
			this->pixel_label->Size = System::Drawing::Size(55, 12);
			this->pixel_label->TabIndex = 16;
			this->pixel_label->Text = L"Pixel Size";
			// 
			// focal_box
			// 
			this->focal_box->Location = System::Drawing::Point(148, 15);
			this->focal_box->Name = L"focal_box";
			this->focal_box->Size = System::Drawing::Size(26, 19);
			this->focal_box->TabIndex = 15;
			this->focal_box->Text = L"16";
			this->focal_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// focal_label
			// 
			this->focal_label->AutoSize = true;
			this->focal_label->Location = System::Drawing::Point(109, 18);
			this->focal_label->Name = L"focal_label";
			this->focal_label->Size = System::Drawing::Size(33, 12);
			this->focal_label->TabIndex = 8;
			this->focal_label->Text = L"Focal";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tableLayoutPanel6);
			this->groupBox4->Location = System::Drawing::Point(3, 6);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(292, 83);
			this->groupBox4->TabIndex = 15;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Distance Measurement";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Location = System::Drawing::Point(-1, 1);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(311, 385);
			this->tabControl1->TabIndex = 16;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox4);
			this->tabPage1->Controls->Add(this->save_box);
			this->tabPage1->Controls->Add(this->groupBox3);
			this->tabPage1->Controls->Add(this->offset_group);
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(303, 359);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"General";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &ParamShow::tabPage1_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->leftcamera);
			this->tabPage2->Controls->Add(this->rightcamera);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(303, 374);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"VCC";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox7);
			this->tabPage3->Controls->Add(this->pan_tilt_unit_group);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(303, 374);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Platform";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->pc_relative);
			this->groupBox7->Controls->Add(this->pc_absolute);
			this->groupBox7->Controls->Add(this->pc_tilt);
			this->groupBox7->Controls->Add(this->label20);
			this->groupBox7->Controls->Add(this->pc_pan);
			this->groupBox7->Controls->Add(this->label14);
			this->groupBox7->Controls->Add(this->pc_down);
			this->groupBox7->Controls->Add(this->pc_right);
			this->groupBox7->Controls->Add(this->pc_left);
			this->groupBox7->Controls->Add(this->pc_up);
			this->groupBox7->Controls->Add(this->movestep);
			this->groupBox7->Controls->Add(this->label1);
			this->groupBox7->Location = System::Drawing::Point(3, 101);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(292, 112);
			this->groupBox7->TabIndex = 12;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Platform Controller";
			// 
			// pc_relative
			// 
			this->pc_relative->Location = System::Drawing::Point(229, 77);
			this->pc_relative->Name = L"pc_relative";
			this->pc_relative->Size = System::Drawing::Size(56, 23);
			this->pc_relative->TabIndex = 11;
			this->pc_relative->Text = L"Relative";
			this->pc_relative->UseVisualStyleBackColor = true;
			this->pc_relative->Click += gcnew System::EventHandler(this, &ParamShow::pc_relative_Click);
			// 
			// pc_absolute
			// 
			this->pc_absolute->Location = System::Drawing::Point(161, 77);
			this->pc_absolute->Name = L"pc_absolute";
			this->pc_absolute->Size = System::Drawing::Size(62, 23);
			this->pc_absolute->TabIndex = 10;
			this->pc_absolute->Text = L"Absolute";
			this->pc_absolute->UseVisualStyleBackColor = true;
			this->pc_absolute->Click += gcnew System::EventHandler(this, &ParamShow::pc_absolute_Click);
			// 
			// pc_tilt
			// 
			this->pc_tilt->Location = System::Drawing::Point(116, 79);
			this->pc_tilt->Name = L"pc_tilt";
			this->pc_tilt->Size = System::Drawing::Size(39, 19);
			this->pc_tilt->TabIndex = 9;
			this->pc_tilt->Text = L"0";
			this->pc_tilt->TextChanged += gcnew System::EventHandler(this, &ParamShow::textBox2_TextChanged);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(82, 82);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(28, 12);
			this->label20->TabIndex = 8;
			this->label20->Text = L"TILT";
			// 
			// pc_pan
			// 
			this->pc_pan->Location = System::Drawing::Point(37, 79);
			this->pc_pan->Name = L"pc_pan";
			this->pc_pan->Size = System::Drawing::Size(39, 19);
			this->pc_pan->TabIndex = 7;
			this->pc_pan->Text = L"0";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(3, 82);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(28, 12);
			this->label14->TabIndex = 6;
			this->label14->Text = L"PAN";
			// 
			// pc_down
			// 
			this->pc_down->Location = System::Drawing::Point(168, 42);
			this->pc_down->Name = L"pc_down";
			this->pc_down->Size = System::Drawing::Size(51, 23);
			this->pc_down->TabIndex = 5;
			this->pc_down->Text = L"DOWN";
			this->pc_down->UseVisualStyleBackColor = true;
			this->pc_down->Click += gcnew System::EventHandler(this, &ParamShow::pc_down_Click);
			// 
			// pc_right
			// 
			this->pc_right->Location = System::Drawing::Point(225, 26);
			this->pc_right->Name = L"pc_right";
			this->pc_right->Size = System::Drawing::Size(51, 23);
			this->pc_right->TabIndex = 4;
			this->pc_right->Text = L"RIGHT";
			this->pc_right->UseVisualStyleBackColor = true;
			this->pc_right->Click += gcnew System::EventHandler(this, &ParamShow::pc_right_Click);
			// 
			// pc_left
			// 
			this->pc_left->Location = System::Drawing::Point(111, 26);
			this->pc_left->Name = L"pc_left";
			this->pc_left->Size = System::Drawing::Size(51, 23);
			this->pc_left->TabIndex = 3;
			this->pc_left->Text = L"LEFT";
			this->pc_left->UseVisualStyleBackColor = true;
			this->pc_left->Click += gcnew System::EventHandler(this, &ParamShow::pc_left_Click);
			// 
			// pc_up
			// 
			this->pc_up->Location = System::Drawing::Point(168, 13);
			this->pc_up->Name = L"pc_up";
			this->pc_up->Size = System::Drawing::Size(51, 23);
			this->pc_up->TabIndex = 2;
			this->pc_up->Text = L"UP";
			this->pc_up->UseVisualStyleBackColor = true;
			this->pc_up->Click += gcnew System::EventHandler(this, &ParamShow::pc_up_Click_1);
			// 
			// movestep
			// 
			this->movestep->DecimalPlaces = 1;
			this->movestep->Location = System::Drawing::Point(9, 39);
			this->movestep->Name = L"movestep";
			this->movestep->Size = System::Drawing::Size(89, 19);
			this->movestep->TabIndex = 1;
			this->movestep->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->movestep->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Move Step [deg.]";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->groupBox5);
			this->tabPage4->Controls->Add(this->server_check);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(303, 374);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Transmit";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label7);
			this->groupBox5->Controls->Add(this->server_dir_label);
			this->groupBox5->Controls->Add(this->server_dir_button);
			this->groupBox5->Controls->Add(this->server_dir_box);
			this->groupBox5->Controls->Add(this->b_radio);
			this->groupBox5->Controls->Add(this->a_radio);
			this->groupBox5->Location = System::Drawing::Point(10, 29);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(278, 93);
			this->groupBox5->TabIndex = 2;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Configuration";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(58, 20);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(130, 12);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Measurement System ID";
			this->label7->Click += gcnew System::EventHandler(this, &ParamShow::label7_Click_1);
			// 
			// server_dir_label
			// 
			this->server_dir_label->AutoSize = true;
			this->server_dir_label->Location = System::Drawing::Point(10, 45);
			this->server_dir_label->Name = L"server_dir_label";
			this->server_dir_label->Size = System::Drawing::Size(81, 12);
			this->server_dir_label->TabIndex = 5;
			this->server_dir_label->Text = L"Server directry";
			// 
			// server_dir_button
			// 
			this->server_dir_button->Location = System::Drawing::Point(247, 63);
			this->server_dir_button->Name = L"server_dir_button";
			this->server_dir_button->Size = System::Drawing::Size(22, 19);
			this->server_dir_button->TabIndex = 4;
			this->server_dir_button->Text = L"...";
			this->server_dir_button->UseVisualStyleBackColor = true;
			this->server_dir_button->Click += gcnew System::EventHandler(this, &ParamShow::server_dir_button_Click);
			// 
			// server_dir_box
			// 
			this->server_dir_box->Location = System::Drawing::Point(10, 63);
			this->server_dir_box->Name = L"server_dir_box";
			this->server_dir_box->Size = System::Drawing::Size(231, 19);
			this->server_dir_box->TabIndex = 3;
			// 
			// b_radio
			// 
			this->b_radio->AutoSize = true;
			this->b_radio->Location = System::Drawing::Point(231, 18);
			this->b_radio->Name = L"b_radio";
			this->b_radio->Size = System::Drawing::Size(31, 16);
			this->b_radio->TabIndex = 2;
			this->b_radio->Text = L"R";
			this->b_radio->UseVisualStyleBackColor = true;
			this->b_radio->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::b_radio_CheckedChanged);
			// 
			// a_radio
			// 
			this->a_radio->AutoSize = true;
			this->a_radio->Checked = true;
			this->a_radio->Location = System::Drawing::Point(194, 18);
			this->a_radio->Name = L"a_radio";
			this->a_radio->Size = System::Drawing::Size(29, 16);
			this->a_radio->TabIndex = 1;
			this->a_radio->TabStop = true;
			this->a_radio->Text = L"L";
			this->a_radio->UseVisualStyleBackColor = true;
			// 
			// server_check
			// 
			this->server_check->AutoSize = true;
			this->server_check->Location = System::Drawing::Point(10, 7);
			this->server_check->Name = L"server_check";
			this->server_check->Size = System::Drawing::Size(229, 16);
			this->server_check->TabIndex = 1;
			this->server_check->Text = L"Transmitting data to the server program";
			this->server_check->UseVisualStyleBackColor = true;
			this->server_check->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::server_check_CheckedChanged);
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->groupBox6);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(303, 374);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"CenterCam";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->label10);
			this->groupBox6->Controls->Add(this->label11);
			this->groupBox6->Controls->Add(this->centercamera_focallength);
			this->groupBox6->Controls->Add(this->db_th_box_c);
			this->groupBox6->Controls->Add(this->tableLayoutPanel10);
			this->groupBox6->Controls->Add(this->label12);
			this->groupBox6->Controls->Add(this->tableLayoutPanel9);
			this->groupBox6->Controls->Add(this->roll_box_c);
			this->groupBox6->Controls->Add(this->db_flag_c);
			this->groupBox6->Controls->Add(this->roll_flag_c);
			this->groupBox6->Controls->Add(this->all_flag_c);
			this->groupBox6->Controls->Add(this->kalman_flag_c);
			this->groupBox6->Controls->Add(this->th_box_c);
			this->groupBox6->Controls->Add(this->sub_flag_c);
			this->groupBox6->Controls->Add(this->label13);
			this->groupBox6->Controls->Add(this->db_all_c);
			this->groupBox6->Controls->Add(this->db_reset_c);
			this->groupBox6->Location = System::Drawing::Point(6, 6);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(289, 217);
			this->groupBox6->TabIndex = 39;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Center Camera";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(148, 24);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(68, 12);
			this->label10->TabIndex = 0;
			this->label10->Text = L"Focal length";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(23, 151);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(55, 12);
			this->label11->TabIndex = 38;
			this->label11->Text = L"Threshold";
			// 
			// centercamera_focallength
			// 
			this->centercamera_focallength->Location = System::Drawing::Point(222, 21);
			this->centercamera_focallength->Name = L"centercamera_focallength";
			this->centercamera_focallength->Size = System::Drawing::Size(54, 19);
			this->centercamera_focallength->TabIndex = 1;
			this->centercamera_focallength->Text = L"8";
			this->centercamera_focallength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// db_th_box_c
			// 
			this->db_th_box_c->Location = System::Drawing::Point(84, 149);
			this->db_th_box_c->Name = L"db_th_box_c";
			this->db_th_box_c->Size = System::Drawing::Size(42, 19);
			this->db_th_box_c->TabIndex = 37;
			this->db_th_box_c->Text = L"160";
			this->db_th_box_c->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tableLayoutPanel10
			// 
			this->tableLayoutPanel10->ColumnCount = 3;
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				71.28713F)));
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				28.71287F)));
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				42)));
			this->tableLayoutPanel10->Controls->Add(this->label16, 1, 0);
			this->tableLayoutPanel10->Controls->Add(this->label17, 2, 0);
			this->tableLayoutPanel10->Controls->Add(this->label18, 0, 1);
			this->tableLayoutPanel10->Controls->Add(this->label19, 0, 2);
			this->tableLayoutPanel10->Controls->Add(this->coor_xc, 1, 1);
			this->tableLayoutPanel10->Controls->Add(this->coor_yc, 2, 1);
			this->tableLayoutPanel10->Controls->Add(this->db_xc, 1, 2);
			this->tableLayoutPanel10->Controls->Add(this->db_yc, 2, 2);
			this->tableLayoutPanel10->Location = System::Drawing::Point(150, 113);
			this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
			this->tableLayoutPanel10->RowCount = 3;
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel10->Size = System::Drawing::Size(133, 59);
			this->tableLayoutPanel10->TabIndex = 24;
			// 
			// label16
			// 
			this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(67, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(20, 12);
			this->label16->TabIndex = 0;
			this->label16->Text = L"x";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label17
			// 
			this->label17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(93, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(37, 12);
			this->label17->TabIndex = 1;
			this->label17->Text = L"y";
			this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label18
			// 
			this->label18->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(3, 19);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(58, 19);
			this->label18->TabIndex = 2;
			this->label18->Text = L"Coordinate";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label19
			// 
			this->label19->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(3, 38);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(58, 12);
			this->label19->TabIndex = 3;
			this->label19->Text = L"Database";
			this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_xc
			// 
			this->coor_xc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_xc->AutoSize = true;
			this->coor_xc->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_xc->Location = System::Drawing::Point(67, 19);
			this->coor_xc->Name = L"coor_xc";
			this->coor_xc->Size = System::Drawing::Size(20, 19);
			this->coor_xc->TabIndex = 4;
			this->coor_xc->Text = L"000";
			this->coor_xc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// coor_yc
			// 
			this->coor_yc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->coor_yc->AutoSize = true;
			this->coor_yc->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->coor_yc->Location = System::Drawing::Point(93, 19);
			this->coor_yc->Name = L"coor_yc";
			this->coor_yc->Size = System::Drawing::Size(37, 12);
			this->coor_yc->TabIndex = 5;
			this->coor_yc->Text = L"000";
			this->coor_yc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_xc
			// 
			this->db_xc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_xc->AutoSize = true;
			this->db_xc->Location = System::Drawing::Point(67, 38);
			this->db_xc->Name = L"db_xc";
			this->db_xc->Size = System::Drawing::Size(20, 12);
			this->db_xc->TabIndex = 6;
			this->db_xc->Text = L"4";
			this->db_xc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_yc
			// 
			this->db_yc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_yc->AutoSize = true;
			this->db_yc->Location = System::Drawing::Point(93, 38);
			this->db_yc->Name = L"db_yc";
			this->db_yc->Size = System::Drawing::Size(37, 12);
			this->db_yc->TabIndex = 7;
			this->db_yc->Text = L"4";
			this->db_yc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Enabled = false;
			this->label12->Location = System::Drawing::Point(21, 73);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(34, 12);
			this->label12->TabIndex = 36;
			this->label12->Text = L"Value";
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				63.71682F)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				36.28318F)));
			this->tableLayoutPanel9->Controls->Add(this->corr_c, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->label15, 0, 0);
			this->tableLayoutPanel9->Location = System::Drawing::Point(150, 173);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 1;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 19)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(114, 19);
			this->tableLayoutPanel9->TabIndex = 25;
			// 
			// corr_c
			// 
			this->corr_c->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->corr_c->AutoSize = true;
			this->corr_c->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->corr_c->Location = System::Drawing::Point(75, 0);
			this->corr_c->Name = L"corr_c";
			this->corr_c->Size = System::Drawing::Size(36, 12);
			this->corr_c->TabIndex = 5;
			this->corr_c->Text = L"000";
			this->corr_c->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label15
			// 
			this->label15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(3, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(66, 12);
			this->label15->TabIndex = 3;
			this->label15->Text = L"Correlation";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// roll_box_c
			// 
			this->roll_box_c->Enabled = false;
			this->roll_box_c->Location = System::Drawing::Point(61, 70);
			this->roll_box_c->Name = L"roll_box_c";
			this->roll_box_c->Size = System::Drawing::Size(65, 19);
			this->roll_box_c->TabIndex = 35;
			this->roll_box_c->Text = L"0";
			this->roll_box_c->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// db_flag_c
			// 
			this->db_flag_c->AutoSize = true;
			this->db_flag_c->Location = System::Drawing::Point(2, 132);
			this->db_flag_c->Name = L"db_flag_c";
			this->db_flag_c->Size = System::Drawing::Size(72, 16);
			this->db_flag_c->TabIndex = 26;
			this->db_flag_c->Text = L"Database";
			this->db_flag_c->UseVisualStyleBackColor = true;
			// 
			// roll_flag_c
			// 
			this->roll_flag_c->AutoSize = true;
			this->roll_flag_c->Enabled = false;
			this->roll_flag_c->Location = System::Drawing::Point(2, 54);
			this->roll_flag_c->Name = L"roll_flag_c";
			this->roll_flag_c->Size = System::Drawing::Size(101, 16);
			this->roll_flag_c->TabIndex = 34;
			this->roll_flag_c->Text = L"Roll Correction";
			this->roll_flag_c->UseVisualStyleBackColor = true;
			// 
			// all_flag_c
			// 
			this->all_flag_c->AutoSize = true;
			this->all_flag_c->Checked = true;
			this->all_flag_c->CheckState = System::Windows::Forms::CheckState::Checked;
			this->all_flag_c->Location = System::Drawing::Point(2, 92);
			this->all_flag_c->Name = L"all_flag_c";
			this->all_flag_c->Size = System::Drawing::Size(67, 16);
			this->all_flag_c->TabIndex = 27;
			this->all_flag_c->Text = L"Seek All";
			this->all_flag_c->UseVisualStyleBackColor = true;
			// 
			// kalman_flag_c
			// 
			this->kalman_flag_c->AutoSize = true;
			this->kalman_flag_c->Location = System::Drawing::Point(150, 76);
			this->kalman_flag_c->Name = L"kalman_flag_c";
			this->kalman_flag_c->Size = System::Drawing::Size(92, 16);
			this->kalman_flag_c->TabIndex = 33;
			this->kalman_flag_c->Text = L"Kalman Filter";
			this->kalman_flag_c->UseVisualStyleBackColor = true;
			// 
			// th_box_c
			// 
			this->th_box_c->Location = System::Drawing::Point(84, 110);
			this->th_box_c->Name = L"th_box_c";
			this->th_box_c->Size = System::Drawing::Size(42, 19);
			this->th_box_c->TabIndex = 28;
			this->th_box_c->Text = L"200";
			this->th_box_c->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// sub_flag_c
			// 
			this->sub_flag_c->AutoSize = true;
			this->sub_flag_c->Checked = true;
			this->sub_flag_c->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sub_flag_c->Location = System::Drawing::Point(150, 54);
			this->sub_flag_c->Name = L"sub_flag_c";
			this->sub_flag_c->Size = System::Drawing::Size(114, 16);
			this->sub_flag_c->TabIndex = 32;
			this->sub_flag_c->Text = L"Sub-pixel Method";
			this->sub_flag_c->UseVisualStyleBackColor = true;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(23, 113);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(55, 12);
			this->label13->TabIndex = 29;
			this->label13->Text = L"Threshold";
			// 
			// db_all_c
			// 
			this->db_all_c->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_all_c->Location = System::Drawing::Point(76, 171);
			this->db_all_c->Name = L"db_all_c";
			this->db_all_c->Size = System::Drawing::Size(50, 23);
			this->db_all_c->TabIndex = 31;
			this->db_all_c->Text = L"Search";
			this->db_all_c->UseVisualStyleBackColor = true;
			// 
			// db_reset_c
			// 
			this->db_reset_c->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->db_reset_c->Location = System::Drawing::Point(22, 171);
			this->db_reset_c->Name = L"db_reset_c";
			this->db_reset_c->Size = System::Drawing::Size(50, 23);
			this->db_reset_c->TabIndex = 30;
			this->db_reset_c->Text = L"Reset";
			this->db_reset_c->UseVisualStyleBackColor = true;
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &ParamShow::folderBrowserDialog1_HelpRequest);
			// 
			// Quit
			// 
			this->Quit->Location = System::Drawing::Point(229, 388);
			this->Quit->Name = L"Quit";
			this->Quit->Size = System::Drawing::Size(69, 20);
			this->Quit->TabIndex = 17;
			this->Quit->Text = L"Quit";
			this->Quit->UseVisualStyleBackColor = true;
			this->Quit->Click += gcnew System::EventHandler(this, &ParamShow::Quit_Click);
			// 
			// ParamShow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(303, 411);
			this->Controls->Add(this->Quit);
			this->Controls->Add(this->tabControl1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"ParamShow";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"ParamShow";
			this->Load += gcnew System::EventHandler(this, &ParamShow::ParamShow_Load);
			this->leftcamera->ResumeLayout(false);
			this->leftcamera->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->rightcamera->ResumeLayout(false);
			this->rightcamera->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->offset_group->ResumeLayout(false);
			this->offset_group->PerformLayout();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			this->pan_tilt_unit_group->ResumeLayout(false);
			this->pan_tilt_unit_group->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->pan_tilt_status->ResumeLayout(false);
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			this->save_box->ResumeLayout(false);
			this->save_box->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->flame_num))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->movestep))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->tableLayoutPanel10->ResumeLayout(false);
			this->tableLayoutPanel10->PerformLayout();
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: double MyToDouble(std::string str){
			 std::stringstream ss;
			 ss << str;
			 double d;
			 ss >> d;
			 return d;
}

private: System::Void center_input(){
			 std::ifstream in(CENTER_INPUT_FILENAME);
			 std::string str;
			 int i = 0;
			 while (in && std::getline(in, str)){
				 i++;
				 if (i == 1) this->coor_xc->Text = ToSystemString(str);
				 if (i == 2) this->coor_yc->Text = ToSystemString(str);
				 if (i == 3) this->db_xc->Text = ToSystemString(str);
				 if (i == 4) this->db_yc->Text = ToSystemString(str);
				 if (i == 5) this->corr_c->Text = ToSystemString(str);
				 if (i == 6) if ("T" == ToSystemString(str)) this->reset_ack_c = false;
				 if (i == 7) if ("T" == ToSystemString(str)) this->all_ack_c = false;
			 }
			 in.close();
}

private: System::Void input(){
	std::ifstream in(INFILE);
	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1) this->origin_measure_before->Text = String::Format("{0:#0.00}", MyToDouble(str));
		if (i == 5) this->label2->Text = String::Format("{0:#0.00}", MyToDouble(str));
		if (i == 6) this->label3->Text = String::Format("{0:#0.00}", MyToDouble(str));
		if (i == 7) this->coor_xl->Text = ToSystemString(str);
		if (i == 8) this->coor_yl->Text = ToSystemString(str);
		if (i == 9) this->db_xl->Text = ToSystemString(str);
		if (i == 10) this->db_yl->Text = ToSystemString(str);
		if (i == 11) this->corr_l->Text = ToSystemString(str);
		if (i == 12) this->coor_xr->Text = ToSystemString(str);
		if (i == 13) this->coor_yr->Text = ToSystemString(str);
		if (i == 14) this->db_xr->Text = ToSystemString(str);
		if (i == 15) this->db_yr->Text = ToSystemString(str);
		if (i == 16) this->corr_r->Text = ToSystemString(str);
		if (i == 17) if ("T" == ToSystemString(str)) this->reset_ack_l = false;
		if (i == 18) if ("T" == ToSystemString(str)) this->all_ack_l = false;
		if (i == 19) if ("T" == ToSystemString(str)) this->reset_ack_r = false;
		if (i == 20) if ("T" == ToSystemString(str)) this->all_ack_r = false;
		if (i == 21) this->platform_state->Text = ToSystemString(str);
		if (i == 22) this->theta->Text = String::Format("{0:#0.00000}", RAD2DEG(MyToDouble(str)));
		if (i == 23) this->move_tilt->Text = String::Format("{0:#0.00000}", RAD2DEG(MyToDouble(str)));
		if (i == 24) this->platform_pan->Text = String::Format("{0:#0.00000}", RAD2DEG(MyToDouble(str)));
		if (i == 25) this->platform_tilt->Text = String::Format("{0:#0.00000}", RAD2DEG(MyToDouble(str)));
		if (i == 26) if ("T" == ToSystemString(str)) this->plat_home_ack = false;
		if (i == 27) if ("T" == ToSystemString(str)) this->plat_move_ack = false;
		if (i == 28) if ("T" == ToSystemString(str)) this->plat_stop_ack = false;
		if (i == 29) this->save_state->Text = ToSystemString(str);
		if (i == 30) if ("T" == ToSystemString(str)) this->save_ack = false;
	}
	in.close();
}

private: bool reset_ack_l;
private: bool reset_ack_r;
private: bool reset_ack_c;
private: bool all_ack_l;
private: bool all_ack_r;
private: bool all_ack_c;
private: bool save_ack;

private: bool plat_home_ack;
private: bool plat_move_ack;
private: bool plat_stop_ack;

private: System::Void center_output(){

			 std::ofstream out(CENTER_OUTPUT_FILENAME);

			 /* 01 */out << this->ToStdString(this->centercamera_focallength->Text) << std::endl;
			 /* 02 */if (this->all_flag_c->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 03 */out << this->ToStdString(this->th_box_c->Text) << std::endl;
			 /* 04 */if (this->db_flag_c->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 05 */out << this->ToStdString(this->db_th_box_c->Text) << std::endl;
			 /* 06 */if (this->reset_ack_c) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 07 */if (this->all_ack_c) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 08 */if (this->sub_flag_c->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 09 */if (this->kalman_flag_c->Checked) out << "T" << std::endl; else out << "F" << std::endl;

			 out.close();
}

private: System::Void output(){
			 std::ofstream out(OUTFILE);

			 /* 01 */out << this->ToStdString(this->base_box->Text) << std::endl;
			 /* 02 */out << this->ToStdString(this->focal_box->Text) << std::endl;
			 /* 03 */out << this->ToStdString(this->pixel_box->Text) << std::endl;
			 /* 04 */if (this->all_flag_l->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 05 */out << this->ToStdString(this->th_box_l->Text) << std::endl;
			 /* 06 */if (this->db_flag_l->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 07 */out << this->ToStdString(this->db_th_box_l->Text) << std::endl;
			 /* 08 */if (this->reset_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 09 */if (this->all_ack_l) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 10 */if (this->sub_flag_l->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 11 */if (this->kalman_flag_l->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 12 */if (this->all_flag_r->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 13 */out << this->ToStdString(this->th_box_r->Text) << std::endl;
			 /* 14 */if (this->db_flag_r->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 15 */out << this->ToStdString(this->db_th_box_r->Text) << std::endl;
			 /* 16 */if (this->reset_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 17 */if (this->all_ack_r) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 18 */if (this->sub_flag_r->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 19 */if (this->kalman_flag_r->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 20 */if (this->offset_check->Checked) out << this->ToStdString(this->linear_a2->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 21 */if (this->offset_check->Checked) out << this->ToStdString(this->linear_a1->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 22 */if (this->offset_check->Checked) out << this->ToStdString(this->linear_a0->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 23 */out << this->ToStdString(this->plat_th_box->Text) << std::endl;
			 /* 24 */if (this->plat_home_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 25 */if (this->plat_move_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 26 */if (this->plat_stop_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 27 */out << this->ToStdString(this->true_value->Text) << std::endl;
			 /* 28 */out << this->ToStdString(this->filename_box->Text) << std::endl;
			 /* 29 */out << this->ToStdString(this->flame_num->Text) << std::endl;
			 /* 30 */if (this->csv_check->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 31 */if (this->save_ack) out << "T" << std::endl; else out << "F" << std::endl;

			 out.close();


			 std::ofstream ofs(QUIT_FILENAME);
			 ofs.close();
}

	private: System::Void ParamShow_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 this->output();
				 this->input();
				 this->center_output();
				 this->center_input();
				 this->server_output();
				 this->pc_input();
				 this->pc_output();
	}
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void all_flag_l_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->thl->Enabled = this->all_flag_l->Checked;
			 this->th_box_l->Enabled = this->all_flag_l->Checked;
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void db_flag_l_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 this->db_all_l->Enabled = this->db_flag_l->Checked;
//			 this->db_reset_l->Enabled = this->db_flag_l->Checked;
}
private: System::Void all_flag_r_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->thr->Enabled = this->all_flag_r->Checked;
			 this->th_box_r->Enabled = this->all_flag_r->Checked;
}
private: System::Void db_flag_r_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 this->db_all_r->Enabled = this->db_flag_r->Checked;
//			 this->db_reset_r->Enabled = this->db_flag_r->Checked;
}
private: System::Void label4_Click_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void db_reset_l_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->reset_ack_l = true;
}
private: System::Void db_all_l_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->all_ack_l = true;
}
private: System::Void db_reset_r_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->reset_ack_r = true;
}
private: System::Void db_all_r_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->all_ack_r = true;
}
private: System::Void offset_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->linear_a2->Enabled = this->offset_check->Checked;
			 this->linear_a1->Enabled = this->offset_check->Checked;
			 this->linear_a0->Enabled = this->offset_check->Checked;
}
private: System::Void save_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->calib_check->Checked){
				 fname = "tool.cfg\\Temp.cfg";
				 StreamWriter^ swriter = gcnew StreamWriter(fname,true);
				 swriter->WriteLine(this->true_value->Text);
				 swriter->WriteLine(this->origin_measure_before->Text);
				 swriter->Close();
			 }
			 this->save_ack = true;
}
private: System::Void plat_home_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->plat_home_ack = true;
}
private: System::Void plat_move_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->plat_move_ack = true;
}
private: System::Void plat_stop_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->plat_stop_ack = true;
}
private: System::Void tool_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->offset_check->Checked = false;
			 this->linear_a2->Enabled = false;
			 this->linear_a1->Enabled = false;
			 this->linear_a0->Enabled = false;
			 ParallelOffsetTool ^pot = gcnew ParallelOffsetTool();
			 pot->Owner = this;
			 pot->Show();
}
		 private: String ^fname;
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
}
private: System::Void output_button_Click(System::Object^  sender, System::EventArgs^  e) {

			 SaveFileDialog^ sfdlg = gcnew SaveFileDialog();
			 String ^path = Path::GetFullPath("main.cfg\\");
			 sfdlg->InitialDirectory = path;
			 sfdlg->Filter = "設定ファイル(*cfg)|*.cfg";
			 if (sfdlg->ShowDialog() != Windows::Forms::DialogResult::OK) return;
			 this->saveConfigFile(sfdlg->FileName);
}
private: System::Void read_button_Click(System::Object^  sender, System::EventArgs^  e) {

			 OpenFileDialog^ ofdlg = gcnew OpenFileDialog();
			 String ^path = Path::GetFullPath("main.cfg\\");
			 ofdlg->InitialDirectory = path;
			 ofdlg->Filter = "設定ファイル(*cfg)|*.cfg";
			 if (ofdlg->ShowDialog() != Windows::Forms::DialogResult::OK) return;
			 this->readConfigFile(ofdlg->FileName);
}
private: System::Void saveConfigFile(String ^filename){
			 StreamWriter^ swriter = gcnew StreamWriter(filename);
			 /* 01 */swriter->WriteLine(this->base_box->Text);
			 /* 02 */swriter->WriteLine(this->focal_box->Text);
			 /* 03 */swriter->WriteLine(this->pixel_box->Text);
			 /* 04 */if (this->offset_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 05 */swriter->WriteLine(this->linear_a2->Text);
			 /* 06 */if (this->offset_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 07 */swriter->WriteLine(this->linear_a1->Text);
			 /* 08 */swriter->WriteLine(this->linear_a0->Text);
			 /* 09 */if (this->roll_flag_l->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 10 */swriter->WriteLine(this->roll_box_l->Text);
			 /* 11 */if (this->all_flag_l->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 12 */swriter->WriteLine(this->th_box_l->Text);
			 /* 13 */if (this->db_flag_l->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 14 */swriter->WriteLine(this->db_th_box_l->Text);
			 /* 15 */if (this->sub_flag_l->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 16 */if (this->kalman_flag_l->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* -- */
			 /* 17 */if (this->roll_flag_r->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 18 */swriter->WriteLine(this->roll_box_r->Text);
			 /* 19 */if (this->all_flag_r->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 20 */swriter->WriteLine(this->th_box_r->Text);
			 /* 21 */if (this->db_flag_r->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 22 */swriter->WriteLine(this->db_th_box_r->Text);
			 /* 23 */if (this->sub_flag_r->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 24 */if (this->kalman_flag_r->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* -- */
			 /* -- */
			 /* 25 */swriter->WriteLine(this->plat_th_box->Text);
			 /* 26 */swriter->WriteLine(this->filename_box->Text);
			 /* 27 */swriter->WriteLine(this->flame_num->Text);
			 /* 28 */swriter->WriteLine(this->true_value->Text);
			 /* 29 */if (this->calib_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 30 */if (this->csv_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 31 */if (this->server_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 32 */if (this->a_radio->Checked) swriter->WriteLine("A"); else swriter->WriteLine("B");
			 /* 33 */swriter->WriteLine(this->server_dir_box->Text);


			 reset_ack_l = false;
			 reset_ack_r = false;
			 all_ack_l = false;
			 all_ack_r = false;
			 save_ack = false;

			 plat_home_ack = false;
			 plat_move_ack = false;
			 plat_stop_ack = false;


			 swriter->Close();
}
private: System::Void reset_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->readConfigFile("main.cfg\\Defalt.cfg");
}
private: System::Void readConfigFile(String ^filename){
			 StreamReader^ sreader = gcnew StreamReader(filename);
			 int i = 0;
			 while (sreader->Peek() > -1){
				 i++;
				 if (i == 1){ this->base_box->Text = sreader->ReadLine(); }
				 if (i == 2){ this->focal_box->Text = sreader->ReadLine(); }
				 if (i == 3){ this->pixel_box->Text = sreader->ReadLine(); }
				 if (i == 4){ if (sreader->ReadLine() == "T") this->offset_check->Checked = true; else this->offset_check->Checked = false; }
				 if (i == 5){ this->linear_a2->Text = sreader->ReadLine(); }
				 if (i == 6){ if (sreader->ReadLine() == "T") this->offset_check->Checked = true; else this->offset_check->Checked = false; }
				 if (i == 7){ this->linear_a1->Text = sreader->ReadLine(); }
				 if (i == 8){ this->linear_a0->Text = sreader->ReadLine(); }
				 if (i == 9){ if (sreader->ReadLine() == "T") this->roll_flag_l->Checked = true; else this->roll_flag_l->Checked = false; }
				 if (i == 10){ this->roll_box_l->Text = sreader->ReadLine(); }
				 if (i == 11){ if (sreader->ReadLine() == "T") this->all_flag_l->Checked = true; else this->all_flag_l->Checked = false; }
				 if (i == 12){ this->th_box_l->Text = sreader->ReadLine(); }
				 if (i == 13){ if (sreader->ReadLine() == "T") this->db_flag_l->Checked = true; else this->db_flag_l->Checked = false; }
				 if (i == 14){ this->db_th_box_l->Text = sreader->ReadLine(); }
				 if (i == 15){ if (sreader->ReadLine() == "T") this->sub_flag_l->Checked = true; else this->sub_flag_l->Checked = false; }
				 if (i == 16){ if (sreader->ReadLine() == "T") this->kalman_flag_l->Checked = true; else this->kalman_flag_l->Checked = false; }

				 if (i == 17){ if (sreader->ReadLine() == "T") this->roll_flag_r->Checked = true; else this->roll_flag_r->Checked = false; }
				 if (i == 18){ this->roll_box_r->Text = sreader->ReadLine(); }
				 if (i == 19){ if (sreader->ReadLine() == "T") this->all_flag_r->Checked = true; else this->all_flag_r->Checked = false; }
				 if (i == 20){ this->th_box_r->Text = sreader->ReadLine(); }
				 if (i == 21){ if (sreader->ReadLine() == "T") this->db_flag_r->Checked = true; else this->db_flag_r->Checked = false; }
				 if (i == 22){ this->db_th_box_r->Text = sreader->ReadLine(); }
				 if (i == 23){ if (sreader->ReadLine() == "T") this->sub_flag_r->Checked = true; else this->sub_flag_r->Checked = false; }
				 if (i == 24){ if (sreader->ReadLine() == "T") this->kalman_flag_r->Checked = true; else this->kalman_flag_r->Checked = false; }

				 if (i == 25){ this->plat_th_box->Text = sreader->ReadLine(); }
				 if (i == 26){ this->filename_box->Text = sreader->ReadLine(); }
				 if (i == 27){ this->flame_num->Text = sreader->ReadLine(); }
				 if (i == 28){ this->true_value->Text = sreader->ReadLine(); }
				 if (i == 29){ if (sreader->ReadLine() == "T") this->calib_check->Checked = true; else this->calib_check->Checked = false; }
				 if (i == 30){ if (sreader->ReadLine() == "T") this->csv_check->Checked = true; else this->csv_check->Checked = false; }
				 if (i == 31){ if (sreader->ReadLine() == "T") this->server_check->Checked = true; else this->server_check->Checked = false; }
				 if (i == 32){ if (sreader->ReadLine() == "A") this->a_radio->Checked = true; else this->b_radio->Checked = true; }
				 if (i == 33){ this->server_dir_box->Text = sreader->ReadLine(); }

			 }
			 sreader->Close();
			 Invalidate();
}
private: System::Void linear_flag_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void calib_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label7_Click_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void server_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void server_dir_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
			 {
				 this->server_dir_box->Text = folderBrowserDialog1->SelectedPath;
			 }
}
private: System::Void server_output(){
			 if (this->server_check->Checked){
				 String ^dir = this->server_dir_box->Text;
				 if (this->a_radio->Checked) dir += "\\L";
				 if (this->b_radio->Checked) dir += "\\R";
				 StreamWriter^ swriter = gcnew StreamWriter(dir);
				 swriter->WriteLine(this->label3->Text);
				 swriter->WriteLine(DEG2RAD(Convert::ToDouble(this->platform_pan->Text)) + DEG2RAD(Convert::ToDouble(this->theta->Text)));
				 swriter->WriteLine(DEG2RAD(Convert::ToDouble(this->platform_tilt->Text)) + DEG2RAD(Convert::ToDouble(this->move_tilt->Text)));
				 swriter->Close();
			 }
}
private: System::Void platform_state_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void domainUpDown1_SelectedItemChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: bool pc_up_ack;
private: bool pc_down_ack;
private: bool pc_left_ack;
private: bool pc_right_ack;
private: bool pc_absolute_ack;
private: bool pc_relative_ack;
private: System::Void pc_up_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_up_ack = true;
}
private: System::Void pc_left_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_left_ack = true;
}
private: System::Void pc_right_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_right_ack = true;
}
private: System::Void pc_down_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_down_ack = true;
}
private: System::Void pc_absolute_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_absolute_ack = true; 
}
private: System::Void pc_relative_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_relative_ack = true;
}
private: System::Void pc_output(){
			 std::ofstream out(PLATFORMCONTROLLER_OUTPUT_FILENAME);

			 /* 01 */out << this->ToStdString(this->movestep->Text) << std::endl;
			 /* 02 */if (this->pc_up_ack) out << "UP" << std::endl;
			 /* -- */else if (this->pc_down_ack) out << "DOWN" << std::endl;
			 /* -- */else if (this->pc_left_ack) out << "LEFT" << std::endl;
			 /* -- */else if (this->pc_right_ack) out << "RIGHT" << std::endl;
			 /* -- */else out << "NON" << std::endl;
			 /* 03 */out << this->ToStdString(this->pc_pan->Text) << std::endl;
			 /* 04 */out << this->ToStdString(this->pc_tilt->Text) << std::endl;
			 /* 05 */if (this->pc_absolute_ack) out << "ABSOLUTE" << std::endl;
			 /* -- */else if (this->pc_relative_ack) out << "RELATIVE" << std::endl;
			 /* -- */else out << "NON" << std::endl;

			 out.close();
}
private: System::Void pc_input(){
			 std::ifstream in(PLATFORMCONTROLLER_INPUT_FILENAME);
			 std::string str;
			 int i = 0;
			 while (in && std::getline(in, str)){
				 i++;
				 if (i == 1){
					 if ("T" == ToSystemString(str)) { 
						 this->pc_up_ack = false;
						 this->pc_down_ack = false;
						 this->pc_left_ack = false;
						 this->pc_right_ack = false;
						 this->pc_absolute_ack = false;
						 this->pc_relative_ack = false;
					 }
				 }
			 }
			 in.close();
}
private: System::Void pc_up_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 this->pc_up_ack = true;
}
private: System::Void b_radio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}


private: int readInitFile(std::string filename){
			 std::ifstream ifs(filename);
			 if (ifs.fail()){
				 return -1;
			 }

			 std::string str;
			 while (ifs&&std::getline(ifs, str)){
				 if (str.size() > 1){
					 if (str.c_str()[0] == '%'){
						 continue;
					 }
				 }
				 std::string token1, token2;
				 std::istringstream stream(str);
				 std::getline(stream, token1, ' ');
				 std::getline(stream, token2);
				 std::stringstream ss;
				 ss << token2;
				 if (token1 == "SERVER_DIRECTRY") this->server_dir_box->Text = this->ToSystemString(token2);
				 else if (token1 == "CLIENT_ID"){
					 if (token2 == "L") this->a_radio->Checked = true;
					 else if (token2 == "R") this->b_radio->Checked = true;
				 }
				 else if (token1 == "AUTOMATICALLY_TRANSMIT"){
					 this->server_check->Checked = true;
				 }
				 
			 }
			 return 0;
		 }
private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void Quit_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->saveConfigFile("main.cfg\\Defalt.cfg");
			 std::ofstream ofs(QUIT_FILENAME);
			 ofs << "quit" << std::endl;
			 ofs.close();
			 this->~ParamShow();
}
};
}

