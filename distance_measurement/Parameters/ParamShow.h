#pragma once
#include <fstream>
#include <string>

#include "ParallelOffsetTool.h"
#define INFILE "../param_files/send.param"
#define OUTFILE "../param_files/receive.param"


namespace Parameters {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ParamShow の概要
	/// </summary>
	public ref class ParamShow : public System::Windows::Forms::Form
	{
	public:
		ParamShow(void)
		{
			InitializeComponent();
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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  theta;

	private: System::Windows::Forms::Label^  pan_label;





	private: System::Windows::Forms::Label^  mid;

	private: System::Windows::Forms::Label^  Origin;
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
	private: System::Windows::Forms::GroupBox^  ofset_group;

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
public: System::Windows::Forms::TextBox^  ofset;
public: System::Windows::Forms::CheckBox^  ofset_check;
private: System::Windows::Forms::Label^  move_tilt;
private: System::Windows::Forms::GroupBox^  save_box;


private: System::Windows::Forms::Label^  save_label;

private: System::Windows::Forms::ComboBox^  comboBox1;
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
public: System::Windows::Forms::TextBox^  linear_b;
private: System::Windows::Forms::Label^  label4;
public: System::Windows::Forms::TextBox^  linear_a;
public: System::Windows::Forms::CheckBox^  linear_flag;
private: System::Windows::Forms::Label^  kalman;
public: System::Windows::Forms::Label^  label3;
private:
private: System::Windows::Forms::GroupBox^  groupBox4;
public:
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::GroupBox^  before_ofset_group;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  origin_measure_before;
private: System::Windows::Forms::Label^  mid_measure_before;
public: System::Windows::Forms::Label^  kf_measure_before;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->theta = (gcnew System::Windows::Forms::Label());
			this->pan_label = (gcnew System::Windows::Forms::Label());
			this->mid = (gcnew System::Windows::Forms::Label());
			this->Origin = (gcnew System::Windows::Forms::Label());
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
			this->ofset_group = (gcnew System::Windows::Forms::GroupBox());
			this->linear_b = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->linear_a = (gcnew System::Windows::Forms::TextBox());
			this->ofset = (gcnew System::Windows::Forms::TextBox());
			this->linear_flag = (gcnew System::Windows::Forms::CheckBox());
			this->tool_button = (gcnew System::Windows::Forms::Button());
			this->ofset_check = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
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
			this->csv_check = (gcnew System::Windows::Forms::CheckBox());
			this->save_label = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
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
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->before_ofset_group = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->origin_measure_before = (gcnew System::Windows::Forms::Label());
			this->mid_measure_before = (gcnew System::Windows::Forms::Label());
			this->kf_measure_before = (gcnew System::Windows::Forms::Label());
			this->leftcamera->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->rightcamera->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->ofset_group->SuspendLayout();
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
			this->groupBox5->SuspendLayout();
			this->before_ofset_group->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(212, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"0000.00";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label1->Click += gcnew System::EventHandler(this, &ParamShow::label1_Click);
			this->label1->DoubleClick += gcnew System::EventHandler(this, &ParamShow::label1_DoubleClick);
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
			this->label2->Location = System::Drawing::Point(212, 15);
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
			this->pan_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pan_label->AutoSize = true;
			this->pan_label->Location = System::Drawing::Point(7, 14);
			this->pan_label->Name = L"pan_label";
			this->pan_label->Size = System::Drawing::Size(28, 12);
			this->pan_label->TabIndex = 7;
			this->pan_label->Text = L"PAN";
			this->pan_label->Click += gcnew System::EventHandler(this, &ParamShow::label5_Click);
			// 
			// mid
			// 
			this->mid->AutoSize = true;
			this->mid->Location = System::Drawing::Point(3, 15);
			this->mid->Name = L"mid";
			this->mid->Size = System::Drawing::Size(81, 12);
			this->mid->TabIndex = 5;
			this->mid->Text = L"中心からの距離";
			this->mid->Click += gcnew System::EventHandler(this, &ParamShow::label7_Click);
			// 
			// Origin
			// 
			this->Origin->AutoSize = true;
			this->Origin->Location = System::Drawing::Point(3, 0);
			this->Origin->Name = L"Origin";
			this->Origin->Size = System::Drawing::Size(41, 12);
			this->Origin->TabIndex = 4;
			this->Origin->Text = L"計測値";
			this->Origin->Click += gcnew System::EventHandler(this, &ParamShow::label8_Click);
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
			this->leftcamera->Location = System::Drawing::Point(12, 346);
			this->leftcamera->Name = L"leftcamera";
			this->leftcamera->Size = System::Drawing::Size(143, 286);
			this->leftcamera->TabIndex = 8;
			this->leftcamera->TabStop = false;
			this->leftcamera->Text = L"左カメラ";
			// 
			// db_th_label_l
			// 
			this->db_th_label_l->AutoSize = true;
			this->db_th_label_l->Location = System::Drawing::Point(46, 116);
			this->db_th_label_l->Name = L"db_th_label_l";
			this->db_th_label_l->Size = System::Drawing::Size(45, 12);
			this->db_th_label_l->TabIndex = 23;
			this->db_th_label_l->Text = L"しきい値";
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
			this->roll_label_l->Location = System::Drawing::Point(27, 37);
			this->roll_label_l->Name = L"roll_label_l";
			this->roll_label_l->Size = System::Drawing::Size(41, 12);
			this->roll_label_l->TabIndex = 21;
			this->roll_label_l->Text = L"補正値";
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
			this->roll_flag_l->Size = System::Drawing::Size(100, 16);
			this->roll_flag_l->TabIndex = 19;
			this->roll_flag_l->Text = L"ROLL回転補正";
			this->roll_flag_l->UseVisualStyleBackColor = true;
			// 
			// kalman_flag_l
			// 
			this->kalman_flag_l->AutoSize = true;
			this->kalman_flag_l->Checked = true;
			this->kalman_flag_l->CheckState = System::Windows::Forms::CheckState::Checked;
			this->kalman_flag_l->Location = System::Drawing::Point(10, 181);
			this->kalman_flag_l->Name = L"kalman_flag_l";
			this->kalman_flag_l->Size = System::Drawing::Size(94, 16);
			this->kalman_flag_l->TabIndex = 18;
			this->kalman_flag_l->Text = L"カルマンフィルタ";
			this->kalman_flag_l->UseVisualStyleBackColor = true;
			// 
			// sub_flag_l
			// 
			this->sub_flag_l->AutoSize = true;
			this->sub_flag_l->Checked = true;
			this->sub_flag_l->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sub_flag_l->Location = System::Drawing::Point(10, 164);
			this->sub_flag_l->Name = L"sub_flag_l";
			this->sub_flag_l->Size = System::Drawing::Size(104, 16);
			this->sub_flag_l->TabIndex = 17;
			this->sub_flag_l->Text = L"サブピクセル手法";
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
			this->db_all_l->Text = L"全探索";
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
			this->db_reset_l->Text = L"リセット";
			this->db_reset_l->UseVisualStyleBackColor = true;
			this->db_reset_l->Click += gcnew System::EventHandler(this, &ParamShow::db_reset_l_Click);
			// 
			// thl
			// 
			this->thl->AutoSize = true;
			this->thl->Location = System::Drawing::Point(46, 77);
			this->thl->Name = L"thl";
			this->thl->Size = System::Drawing::Size(45, 12);
			this->thl->TabIndex = 14;
			this->thl->Text = L"しきい値";
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
			this->all_flag_l->Size = System::Drawing::Size(112, 16);
			this->all_flag_l->TabIndex = 12;
			this->all_flag_l->Text = L"全探索を使用する";
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
			this->db_flag_l->Size = System::Drawing::Size(124, 16);
			this->db_flag_l->TabIndex = 11;
			this->db_flag_l->Text = L"ターゲットデータベース";
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
			this->tableLayoutPanel3->Size = System::Drawing::Size(116, 19);
			this->tableLayoutPanel3->TabIndex = 10;
			// 
			// corr_l
			// 
			this->corr_l->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->corr_l->AutoSize = true;
			this->corr_l->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->corr_l->Location = System::Drawing::Point(72, 0);
			this->corr_l->Name = L"corr_l";
			this->corr_l->Size = System::Drawing::Size(41, 12);
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
			this->correlatel->Size = System::Drawing::Size(63, 12);
			this->correlatel->TabIndex = 3;
			this->correlatel->Text = L"相関値";
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
				40)));
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
			this->xl->Location = System::Drawing::Point(65, 0);
			this->xl->Name = L"xl";
			this->xl->Size = System::Drawing::Size(22, 12);
			this->xl->TabIndex = 0;
			this->xl->Text = L"x";
			this->xl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// yl
			// 
			this->yl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->yl->AutoSize = true;
			this->yl->Location = System::Drawing::Point(93, 0);
			this->yl->Name = L"yl";
			this->yl->Size = System::Drawing::Size(35, 12);
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
			this->coodinatel->Size = System::Drawing::Size(56, 12);
			this->coodinatel->TabIndex = 2;
			this->coodinatel->Text = L"検出座標";
			this->coodinatel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// databasel
			// 
			this->databasel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->databasel->AutoSize = true;
			this->databasel->Location = System::Drawing::Point(3, 38);
			this->databasel->Name = L"databasel";
			this->databasel->Size = System::Drawing::Size(56, 12);
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
			this->coor_xl->Location = System::Drawing::Point(65, 19);
			this->coor_xl->Name = L"coor_xl";
			this->coor_xl->Size = System::Drawing::Size(22, 19);
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
			this->coor_yl->Location = System::Drawing::Point(93, 19);
			this->coor_yl->Name = L"coor_yl";
			this->coor_yl->Size = System::Drawing::Size(35, 12);
			this->coor_yl->TabIndex = 5;
			this->coor_yl->Text = L"000";
			this->coor_yl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_xl
			// 
			this->db_xl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_xl->AutoSize = true;
			this->db_xl->Location = System::Drawing::Point(65, 38);
			this->db_xl->Name = L"db_xl";
			this->db_xl->Size = System::Drawing::Size(22, 12);
			this->db_xl->TabIndex = 6;
			this->db_xl->Text = L"4";
			this->db_xl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// db_yl
			// 
			this->db_yl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->db_yl->AutoSize = true;
			this->db_yl->Location = System::Drawing::Point(93, 38);
			this->db_yl->Name = L"db_yl";
			this->db_yl->Size = System::Drawing::Size(35, 12);
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
			this->rightcamera->Location = System::Drawing::Point(161, 346);
			this->rightcamera->Name = L"rightcamera";
			this->rightcamera->Size = System::Drawing::Size(143, 286);
			this->rightcamera->TabIndex = 9;
			this->rightcamera->TabStop = false;
			this->rightcamera->Text = L"右カメラ";
			// 
			// db_th_label_r
			// 
			this->db_th_label_r->AutoSize = true;
			this->db_th_label_r->Location = System::Drawing::Point(45, 116);
			this->db_th_label_r->Name = L"db_th_label_r";
			this->db_th_label_r->Size = System::Drawing::Size(45, 12);
			this->db_th_label_r->TabIndex = 34;
			this->db_th_label_r->Text = L"しきい値";
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
			this->roll_label_r->Location = System::Drawing::Point(26, 37);
			this->roll_label_r->Name = L"roll_label_r";
			this->roll_label_r->Size = System::Drawing::Size(41, 12);
			this->roll_label_r->TabIndex = 32;
			this->roll_label_r->Text = L"補正値";
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
			this->correlater->Text = L"相関値";
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
			this->coodinater->Text = L"検出座標";
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
			this->roll_flag_r->Size = System::Drawing::Size(100, 16);
			this->roll_flag_r->TabIndex = 30;
			this->roll_flag_r->Text = L"ROLL回転補正";
			this->roll_flag_r->UseVisualStyleBackColor = true;
			// 
			// thr
			// 
			this->thr->AutoSize = true;
			this->thr->Location = System::Drawing::Point(45, 77);
			this->thr->Name = L"thr";
			this->thr->Size = System::Drawing::Size(45, 12);
			this->thr->TabIndex = 25;
			this->thr->Text = L"しきい値";
			// 
			// kalman_flag_r
			// 
			this->kalman_flag_r->AutoSize = true;
			this->kalman_flag_r->Checked = true;
			this->kalman_flag_r->CheckState = System::Windows::Forms::CheckState::Checked;
			this->kalman_flag_r->Location = System::Drawing::Point(8, 181);
			this->kalman_flag_r->Name = L"kalman_flag_r";
			this->kalman_flag_r->Size = System::Drawing::Size(94, 16);
			this->kalman_flag_r->TabIndex = 29;
			this->kalman_flag_r->Text = L"カルマンフィルタ";
			this->kalman_flag_r->UseVisualStyleBackColor = true;
			// 
			// db_flag_r
			// 
			this->db_flag_r->AutoSize = true;
			this->db_flag_r->Checked = true;
			this->db_flag_r->CheckState = System::Windows::Forms::CheckState::Checked;
			this->db_flag_r->Location = System::Drawing::Point(9, 96);
			this->db_flag_r->Name = L"db_flag_r";
			this->db_flag_r->Size = System::Drawing::Size(124, 16);
			this->db_flag_r->TabIndex = 22;
			this->db_flag_r->Text = L"ターゲットデータベース";
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
			this->sub_flag_r->Size = System::Drawing::Size(104, 16);
			this->sub_flag_r->TabIndex = 28;
			this->sub_flag_r->Text = L"サブピクセル手法";
			this->sub_flag_r->UseVisualStyleBackColor = true;
			// 
			// all_flag_r
			// 
			this->all_flag_r->AutoSize = true;
			this->all_flag_r->Checked = true;
			this->all_flag_r->CheckState = System::Windows::Forms::CheckState::Checked;
			this->all_flag_r->Location = System::Drawing::Point(9, 56);
			this->all_flag_r->Name = L"all_flag_r";
			this->all_flag_r->Size = System::Drawing::Size(112, 16);
			this->all_flag_r->TabIndex = 23;
			this->all_flag_r->Text = L"全探索を使用する";
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
			this->db_all_r->Text = L"全探索";
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
			this->db_reset_r->Text = L"リセット";
			this->db_reset_r->UseVisualStyleBackColor = true;
			this->db_reset_r->Click += gcnew System::EventHandler(this, &ParamShow::db_reset_r_Click);
			// 
			// ofset_group
			// 
			this->ofset_group->Controls->Add(this->linear_b);
			this->ofset_group->Controls->Add(this->label4);
			this->ofset_group->Controls->Add(this->linear_a);
			this->ofset_group->Controls->Add(this->ofset);
			this->ofset_group->Controls->Add(this->linear_flag);
			this->ofset_group->Controls->Add(this->tool_button);
			this->ofset_group->Controls->Add(this->ofset_check);
			this->ofset_group->Location = System::Drawing::Point(12, 187);
			this->ofset_group->Name = L"ofset_group";
			this->ofset_group->Size = System::Drawing::Size(216, 107);
			this->ofset_group->TabIndex = 10;
			this->ofset_group->TabStop = false;
			this->ofset_group->Text = L"補正";
			// 
			// linear_b
			// 
			this->linear_b->Enabled = false;
			this->linear_b->Location = System::Drawing::Point(131, 80);
			this->linear_b->Name = L"linear_b";
			this->linear_b->Size = System::Drawing::Size(79, 19);
			this->linear_b->TabIndex = 25;
			this->linear_b->Text = L"0.0";
			this->linear_b->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Enabled = false;
			this->label4->Location = System::Drawing::Point(104, 83);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 12);
			this->label4->TabIndex = 24;
			this->label4->Text = L"x  +";
			// 
			// linear_a
			// 
			this->linear_a->Enabled = false;
			this->linear_a->Location = System::Drawing::Point(6, 80);
			this->linear_a->Name = L"linear_a";
			this->linear_a->Size = System::Drawing::Size(97, 19);
			this->linear_a->TabIndex = 12;
			this->linear_a->Text = L"0.0";
			this->linear_a->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// ofset
			// 
			this->ofset->Enabled = false;
			this->ofset->Location = System::Drawing::Point(6, 36);
			this->ofset->Name = L"ofset";
			this->ofset->Size = System::Drawing::Size(203, 19);
			this->ofset->TabIndex = 9;
			this->ofset->Text = L"0.0";
			this->ofset->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// linear_flag
			// 
			this->linear_flag->AutoSize = true;
			this->linear_flag->Location = System::Drawing::Point(6, 62);
			this->linear_flag->Name = L"linear_flag";
			this->linear_flag->Size = System::Drawing::Size(72, 16);
			this->linear_flag->TabIndex = 11;
			this->linear_flag->Text = L"線形補正";
			this->linear_flag->UseVisualStyleBackColor = true;
			// 
			// tool_button
			// 
			this->tool_button->Location = System::Drawing::Point(149, 14);
			this->tool_button->Name = L"tool_button";
			this->tool_button->Size = System::Drawing::Size(61, 20);
			this->tool_button->TabIndex = 10;
			this->tool_button->Text = L"ツール";
			this->tool_button->UseVisualStyleBackColor = true;
			this->tool_button->Click += gcnew System::EventHandler(this, &ParamShow::tool_button_Click);
			// 
			// ofset_check
			// 
			this->ofset_check->AutoSize = true;
			this->ofset_check->Location = System::Drawing::Point(6, 18);
			this->ofset_check->Name = L"ofset_check";
			this->ofset_check->Size = System::Drawing::Size(72, 16);
			this->ofset_check->TabIndex = 8;
			this->ofset_check->Text = L"平行補正";
			this->ofset_check->UseVisualStyleBackColor = true;
			this->ofset_check->CheckedChanged += gcnew System::EventHandler(this, &ParamShow::ofset_check_CheckedChanged);
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				53.37423F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				46.62577F)));
			this->tableLayoutPanel6->Controls->Add(this->Origin, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->mid, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->kalman, 0, 2);
			this->tableLayoutPanel6->Controls->Add(this->label1, 1, 0);
			this->tableLayoutPanel6->Controls->Add(this->label2, 1, 1);
			this->tableLayoutPanel6->Controls->Add(this->label3, 1, 2);
			this->tableLayoutPanel6->Location = System::Drawing::Point(7, 18);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 3;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(258, 45);
			this->tableLayoutPanel6->TabIndex = 0;
			// 
			// kalman
			// 
			this->kalman->AutoSize = true;
			this->kalman->Location = System::Drawing::Point(3, 30);
			this->kalman->Name = L"kalman";
			this->kalman->Size = System::Drawing::Size(55, 12);
			this->kalman->TabIndex = 6;
			this->kalman->Text = L"KF適用後";
			this->kalman->Click += gcnew System::EventHandler(this, &ParamShow::label6_Click);
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(212, 30);
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
			this->filename_label->Size = System::Drawing::Size(51, 12);
			this->filename_label->TabIndex = 7;
			this->filename_label->Text = L"ファイル名";
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
			this->pan_tilt_unit_group->Location = System::Drawing::Point(12, 638);
			this->pan_tilt_unit_group->Name = L"pan_tilt_unit_group";
			this->pan_tilt_unit_group->Size = System::Drawing::Size(292, 88);
			this->pan_tilt_unit_group->TabIndex = 11;
			this->pan_tilt_unit_group->TabStop = false;
			this->pan_tilt_unit_group->Text = L"電動雲台";
			// 
			// plat_th_label
			// 
			this->plat_th_label->AutoSize = true;
			this->plat_th_label->Location = System::Drawing::Point(14, 66);
			this->plat_th_label->Name = L"plat_th_label";
			this->plat_th_label->Size = System::Drawing::Size(69, 12);
			this->plat_th_label->TabIndex = 23;
			this->plat_th_label->Text = L"動作しきい値";
			// 
			// plat_th_box
			// 
			this->plat_th_box->Location = System::Drawing::Point(84, 63);
			this->plat_th_box->Name = L"plat_th_box";
			this->plat_th_box->Size = System::Drawing::Size(42, 19);
			this->plat_th_box->TabIndex = 22;
			this->plat_th_box->Text = L"200";
			this->plat_th_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// plat_home_button
			// 
			this->plat_home_button->Location = System::Drawing::Point(131, 61);
			this->plat_home_button->Name = L"plat_home_button";
			this->plat_home_button->Size = System::Drawing::Size(48, 23);
			this->plat_home_button->TabIndex = 4;
			this->plat_home_button->Text = L"ホーム";
			this->plat_home_button->UseVisualStyleBackColor = true;
			this->plat_home_button->Click += gcnew System::EventHandler(this, &ParamShow::plat_home_button_Click);
			// 
			// plat_move_button
			// 
			this->plat_move_button->Location = System::Drawing::Point(185, 61);
			this->plat_move_button->Name = L"plat_move_button";
			this->plat_move_button->Size = System::Drawing::Size(48, 23);
			this->plat_move_button->TabIndex = 3;
			this->plat_move_button->Text = L"稼働";
			this->plat_move_button->UseVisualStyleBackColor = true;
			this->plat_move_button->Click += gcnew System::EventHandler(this, &ParamShow::plat_move_button_Click);
			// 
			// plat_stop_button
			// 
			this->plat_stop_button->Location = System::Drawing::Point(239, 61);
			this->plat_stop_button->Name = L"plat_stop_button";
			this->plat_stop_button->Size = System::Drawing::Size(48, 23);
			this->plat_stop_button->TabIndex = 2;
			this->plat_stop_button->Text = L"停止";
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
			this->tilt_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tilt_label->AutoSize = true;
			this->tilt_label->Location = System::Drawing::Point(7, 28);
			this->tilt_label->Name = L"tilt_label";
			this->tilt_label->Size = System::Drawing::Size(28, 12);
			this->tilt_label->TabIndex = 11;
			this->tilt_label->Text = L"TILT";
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
			this->pla_move_label->Location = System::Drawing::Point(73, 0);
			this->pla_move_label->Name = L"pla_move_label";
			this->pla_move_label->Size = System::Drawing::Size(41, 12);
			this->pla_move_label->TabIndex = 8;
			this->pla_move_label->Text = L"制御量";
			this->pla_move_label->Click += gcnew System::EventHandler(this, &ParamShow::label4_Click_1);
			// 
			// pla_pos_label
			// 
			this->pla_pos_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pla_pos_label->AutoSize = true;
			this->pla_pos_label->Location = System::Drawing::Point(141, 0);
			this->pla_pos_label->Name = L"pla_pos_label";
			this->pla_pos_label->Size = System::Drawing::Size(53, 12);
			this->pla_pos_label->TabIndex = 12;
			this->pla_pos_label->Text = L"現在角度";
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
			this->pan_tilt_status->Text = L"ステータス";
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
			this->platform_state->Location = System::Drawing::Point(27, 0);
			this->platform_state->Name = L"platform_state";
			this->platform_state->Size = System::Drawing::Size(41, 12);
			this->platform_state->TabIndex = 0;
			this->platform_state->Text = L"未稼働";
			this->platform_state->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// save_box
			// 
			this->save_box->Controls->Add(this->csv_check);
			this->save_box->Controls->Add(this->save_label);
			this->save_box->Controls->Add(this->comboBox1);
			this->save_box->Controls->Add(this->save_button);
			this->save_box->Controls->Add(this->groupBox1);
			this->save_box->Controls->Add(this->flame);
			this->save_box->Controls->Add(this->flame_num);
			this->save_box->Controls->Add(this->filename_box);
			this->save_box->Controls->Add(this->filename_label);
			this->save_box->Location = System::Drawing::Point(12, 732);
			this->save_box->Name = L"save_box";
			this->save_box->Size = System::Drawing::Size(292, 112);
			this->save_box->TabIndex = 12;
			this->save_box->TabStop = false;
			this->save_box->Text = L"保存関係";
			// 
			// csv_check
			// 
			this->csv_check->AutoSize = true;
			this->csv_check->Location = System::Drawing::Point(167, 59);
			this->csv_check->Name = L"csv_check";
			this->csv_check->Size = System::Drawing::Size(103, 16);
			this->csv_check->TabIndex = 10;
			this->csv_check->Text = L"ログを記録(.csv)";
			this->csv_check->UseVisualStyleBackColor = true;
			// 
			// save_label
			// 
			this->save_label->AutoSize = true;
			this->save_label->Location = System::Drawing::Point(165, 14);
			this->save_label->Name = L"save_label";
			this->save_label->Size = System::Drawing::Size(53, 12);
			this->save_label->TabIndex = 13;
			this->save_label->Text = L"保存対象";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"KF適用後", L"中心からの距離", L"計測値" });
			this->comboBox1->Location = System::Drawing::Point(167, 31);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(120, 20);
			this->comboBox1->TabIndex = 12;
			this->comboBox1->Text = L"KF適用後";
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(167, 77);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(119, 23);
			this->save_button->TabIndex = 11;
			this->save_button->Text = L"保存開始";
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
			this->groupBox1->Text = L"ステータス";
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
			this->save_state->Location = System::Drawing::Point(62, -2);
			this->save_state->Name = L"save_state";
			this->save_state->Size = System::Drawing::Size(73, 12);
			this->save_state->TabIndex = 0;
			this->save_state->Text = L"保存可能です";
			this->save_state->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// flame
			// 
			this->flame->AutoSize = true;
			this->flame->Location = System::Drawing::Point(49, 41);
			this->flame->Name = L"flame";
			this->flame->Size = System::Drawing::Size(54, 12);
			this->flame->TabIndex = 10;
			this->flame->Text = L"フレーム数";
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
			this->filename_box->Location = System::Drawing::Point(66, 15);
			this->filename_box->Name = L"filename_box";
			this->filename_box->Size = System::Drawing::Size(86, 19);
			this->filename_box->TabIndex = 8;
			this->filename_box->Text = L"distance01";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->reset_button);
			this->groupBox2->Controls->Add(this->output_button);
			this->groupBox2->Controls->Add(this->read_button);
			this->groupBox2->Location = System::Drawing::Point(235, 187);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(68, 107);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"設定";
			// 
			// reset_button
			// 
			this->reset_button->Location = System::Drawing::Point(7, 76);
			this->reset_button->Name = L"reset_button";
			this->reset_button->Size = System::Drawing::Size(53, 23);
			this->reset_button->TabIndex = 2;
			this->reset_button->Text = L"初期化";
			this->reset_button->UseVisualStyleBackColor = true;
			this->reset_button->Click += gcnew System::EventHandler(this, &ParamShow::reset_button_Click);
			// 
			// output_button
			// 
			this->output_button->Location = System::Drawing::Point(7, 48);
			this->output_button->Name = L"output_button";
			this->output_button->Size = System::Drawing::Size(53, 23);
			this->output_button->TabIndex = 1;
			this->output_button->Text = L"出力";
			this->output_button->UseVisualStyleBackColor = true;
			this->output_button->Click += gcnew System::EventHandler(this, &ParamShow::output_button_Click);
			// 
			// read_button
			// 
			this->read_button->Location = System::Drawing::Point(7, 20);
			this->read_button->Name = L"read_button";
			this->read_button->Size = System::Drawing::Size(53, 23);
			this->read_button->TabIndex = 0;
			this->read_button->Text = L"読込";
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
			this->groupBox3->Location = System::Drawing::Point(13, 300);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(290, 40);
			this->groupBox3->TabIndex = 14;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"構成";
			// 
			// base_box
			// 
			this->base_box->Location = System::Drawing::Point(54, 15);
			this->base_box->Name = L"base_box";
			this->base_box->Size = System::Drawing::Size(30, 19);
			this->base_box->TabIndex = 19;
			this->base_box->Text = L"300";
			this->base_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// base_label
			// 
			this->base_label->AutoSize = true;
			this->base_label->Location = System::Drawing::Point(9, 18);
			this->base_label->Name = L"base_label";
			this->base_label->Size = System::Drawing::Size(41, 12);
			this->base_label->TabIndex = 18;
			this->base_label->Text = L"基線長";
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
			this->pixel_label->Location = System::Drawing::Point(174, 18);
			this->pixel_label->Name = L"pixel_label";
			this->pixel_label->Size = System::Drawing::Size(62, 12);
			this->pixel_label->TabIndex = 16;
			this->pixel_label->Text = L"ﾋﾟｸｾﾙｻｲｽﾞ";
			// 
			// focal_box
			// 
			this->focal_box->Location = System::Drawing::Point(145, 15);
			this->focal_box->Name = L"focal_box";
			this->focal_box->Size = System::Drawing::Size(25, 19);
			this->focal_box->TabIndex = 15;
			this->focal_box->Text = L"25";
			this->focal_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// focal_label
			// 
			this->focal_label->AutoSize = true;
			this->focal_label->Location = System::Drawing::Point(88, 18);
			this->focal_label->Name = L"focal_label";
			this->focal_label->Size = System::Drawing::Size(53, 12);
			this->focal_label->TabIndex = 8;
			this->focal_label->Text = L"焦点距離";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->groupBox5);
			this->groupBox4->Controls->Add(this->before_ofset_group);
			this->groupBox4->Location = System::Drawing::Point(13, 13);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(290, 168);
			this->groupBox4->TabIndex = 15;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"距離計測";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->tableLayoutPanel6);
			this->groupBox5->Location = System::Drawing::Point(8, 94);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(273, 69);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"補正後";
			// 
			// before_ofset_group
			// 
			this->before_ofset_group->Controls->Add(this->tableLayoutPanel9);
			this->before_ofset_group->Location = System::Drawing::Point(7, 19);
			this->before_ofset_group->Name = L"before_ofset_group";
			this->before_ofset_group->Size = System::Drawing::Size(273, 69);
			this->before_ofset_group->TabIndex = 0;
			this->before_ofset_group->TabStop = false;
			this->before_ofset_group->Text = L"補正前";
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				53.37423F)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				46.62577F)));
			this->tableLayoutPanel9->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->label6, 0, 1);
			this->tableLayoutPanel9->Controls->Add(this->label7, 0, 2);
			this->tableLayoutPanel9->Controls->Add(this->origin_measure_before, 1, 0);
			this->tableLayoutPanel9->Controls->Add(this->mid_measure_before, 1, 1);
			this->tableLayoutPanel9->Controls->Add(this->kf_measure_before, 1, 2);
			this->tableLayoutPanel9->Location = System::Drawing::Point(8, 18);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 3;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(258, 45);
			this->tableLayoutPanel9->TabIndex = 7;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(41, 12);
			this->label5->TabIndex = 4;
			this->label5->Text = L"計測値";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 15);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(81, 12);
			this->label6->TabIndex = 5;
			this->label6->Text = L"中心からの距離";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(3, 30);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(55, 12);
			this->label7->TabIndex = 6;
			this->label7->Text = L"KF適用後";
			// 
			// origin_measure_before
			// 
			this->origin_measure_before->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->origin_measure_before->AutoSize = true;
			this->origin_measure_before->Location = System::Drawing::Point(212, 0);
			this->origin_measure_before->Name = L"origin_measure_before";
			this->origin_measure_before->Size = System::Drawing::Size(43, 12);
			this->origin_measure_before->TabIndex = 0;
			this->origin_measure_before->Text = L"0000.00";
			this->origin_measure_before->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// mid_measure_before
			// 
			this->mid_measure_before->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->mid_measure_before->AutoSize = true;
			this->mid_measure_before->Location = System::Drawing::Point(212, 15);
			this->mid_measure_before->Name = L"mid_measure_before";
			this->mid_measure_before->Size = System::Drawing::Size(43, 12);
			this->mid_measure_before->TabIndex = 1;
			this->mid_measure_before->Text = L"0000.00";
			this->mid_measure_before->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// kf_measure_before
			// 
			this->kf_measure_before->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->kf_measure_before->AutoSize = true;
			this->kf_measure_before->Location = System::Drawing::Point(212, 30);
			this->kf_measure_before->Name = L"kf_measure_before";
			this->kf_measure_before->Size = System::Drawing::Size(43, 12);
			this->kf_measure_before->TabIndex = 2;
			this->kf_measure_before->Text = L"0000.00";
			this->kf_measure_before->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// ParamShow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(315, 852);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->save_box);
			this->Controls->Add(this->rightcamera);
			this->Controls->Add(this->leftcamera);
			this->Controls->Add(this->ofset_group);
			this->Controls->Add(this->pan_tilt_unit_group);
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
			this->ofset_group->ResumeLayout(false);
			this->ofset_group->PerformLayout();
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
			this->groupBox5->ResumeLayout(false);
			this->before_ofset_group->ResumeLayout(false);
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void input(){
	std::ifstream in(INFILE);
	std::string str;
	int i = 0;
	while (in && std::getline(in, str)){
		i++;
		if (i == 1) this->origin_measure_before->Text = ToSystemString(str);
		if (i == 2) this->mid_measure_before->Text = ToSystemString(str);
		if (i == 3) this->kf_measure_before->Text = ToSystemString(str);
		if (i == 4) this->label1->Text = ToSystemString(str);
		if (i == 5) this->label2->Text = ToSystemString(str);
		if (i == 6) this->label3->Text = ToSystemString(str);
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
		if (i == 22) this->theta->Text = ToSystemString(str);
		if (i == 23) this->move_tilt->Text = ToSystemString(str);
		if (i == 24) this->platform_pan->Text = ToSystemString(str);
		if (i == 25) this->platform_tilt->Text = ToSystemString(str);
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
private: bool all_ack_l;
private: bool all_ack_r;
private: bool save_ack;

private: bool plat_home_ack;
private: bool plat_move_ack;
private: bool plat_stop_ack;

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
			 /* 20 */if (this->ofset_check->Checked) out << this->ToStdString(this->ofset->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 21 */if (this->linear_flag->Checked) out << this->ToStdString(this->linear_a->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 22 */if (this->linear_flag->Checked) out << this->ToStdString(this->linear_b->Text) << std::endl; else out << "0.0" << std::endl;
			 /* 23 */out << this->ToStdString(this->plat_th_box->Text) << std::endl;
			 /* 24 */if (this->plat_home_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 25 */if (this->plat_move_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 26 */if (this->plat_stop_ack) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 27 */out << this->ToStdString(this->filename_box->Text) << std::endl;
			 /* 28 */out << this->ToStdString(this->flame_num->Text) << std::endl;
			 /* 29 */out << this->ToStdString(this->comboBox1->Text) << std::endl;
			 /* 30 */if (this->csv_check->Checked) out << "T" << std::endl; else out << "F" << std::endl;
			 /* 31 */if (this->save_ack) out << "T" << std::endl; else out << "F" << std::endl;

			 out.close();
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
			 this->db_all_l->Enabled = this->db_flag_l->Checked;
			 this->db_reset_l->Enabled = this->db_flag_l->Checked;
}
private: System::Void all_flag_r_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->thr->Enabled = this->all_flag_r->Checked;
			 this->th_box_r->Enabled = this->all_flag_r->Checked;
}
private: System::Void db_flag_r_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->db_all_r->Enabled = this->db_flag_r->Checked;
			 this->db_reset_r->Enabled = this->db_flag_r->Checked;
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
private: System::Void ofset_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->ofset->Enabled = this->ofset_check->Checked;
}
private: System::Void save_button_Click(System::Object^  sender, System::EventArgs^  e) {
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
			 this->linear_flag->Checked = false;
			 this->linear_a->Enabled = false;
			 this->linear_b->Enabled = false;
			 this->ofset_check->Checked = false;
			 this->ofset->Enabled = false;
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
			 fname = sfdlg->FileName;
			 StreamWriter^ swriter = gcnew StreamWriter(fname);
			 /* 01 */swriter->WriteLine(this->base_box->Text);
			 /* 02 */swriter->WriteLine(this->focal_box->Text);
			 /* 03 */swriter->WriteLine(this->pixel_box->Text);
			 /* 04 */if (this->ofset_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 05 */swriter->WriteLine(this->ofset->Text);
			 /* 06 */if (this->linear_flag->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");
			 /* 07 */swriter->WriteLine(this->linear_a->Text);
			 /* 08 */swriter->WriteLine(this->linear_b->Text);
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
			 /* 28 */swriter->WriteLine(this->comboBox1->Text);
			 /* 29 */if (this->csv_check->Checked) swriter->WriteLine("T"); else swriter->WriteLine("F");


reset_ack_l=false;
reset_ack_r = false;
all_ack_l = false;
all_ack_r = false;
save_ack = false;

plat_home_ack = false;
plat_move_ack = false;
plat_stop_ack = false;
			 

			 swriter->Close();
}
private: System::Void read_button_Click(System::Object^  sender, System::EventArgs^  e) {

			 OpenFileDialog^ ofdlg = gcnew OpenFileDialog();
			 String ^path = Path::GetFullPath("main.cfg\\");
			 ofdlg->InitialDirectory = path;
			 ofdlg->Filter = "設定ファイル(*cfg)|*.cfg";
			 if (ofdlg->ShowDialog() != Windows::Forms::DialogResult::OK) return;
			 fname = ofdlg->FileName;
			 StreamReader^ sreader = gcnew StreamReader(fname);
			 int i = 0;
			 while (sreader->Peek() > -1){
				 i++;
				 if (i == 1){ this->base_box->Text = sreader->ReadLine(); }
				 if (i == 2){ this->focal_box->Text = sreader->ReadLine(); }
				 if (i == 3){ this->pixel_box->Text = sreader->ReadLine(); }
				 if (i == 4){ if (sreader->ReadLine() == "T") this->ofset_check->Checked = true; else this->ofset_check->Checked = false; }
				 if (i == 5){ this->ofset->Text = sreader->ReadLine(); }
				 if (i == 6){ if (sreader->ReadLine() == "T") this->linear_flag->Checked = true; else this->linear_flag->Checked = false; }
				 if (i == 7){ this->linear_a->Text = sreader->ReadLine(); }
				 if (i == 8){ this->linear_b->Text = sreader->ReadLine(); }
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
				 if (i == 28){ this->comboBox1->Text = sreader->ReadLine(); }
				 if (i == 29){ if (sreader->ReadLine() == "T") this->csv_check->Checked = true; else this->csv_check->Checked = false; }
			 }			   
			 sreader->Close();
			 Invalidate();
}
private: System::Void reset_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 fname = "main.cfg\\Defalt.cfg";
			 StreamReader^ sreader = gcnew StreamReader(fname);
			 int i = 0;
			 while (sreader->Peek() > -1){
				 i++;
				 if (i == 1){ this->base_box->Text = sreader->ReadLine(); }
				 if (i == 2){ this->focal_box->Text = sreader->ReadLine(); }
				 if (i == 3){ this->pixel_box->Text = sreader->ReadLine(); }
				 if (i == 4){ if (sreader->ReadLine() == "T") this->ofset_check->Checked = true; else this->ofset_check->Checked = false; }
				 if (i == 5){ this->ofset->Text = sreader->ReadLine(); }
				 if (i == 6){ if (sreader->ReadLine() == "T") this->linear_flag->Checked = true; else this->linear_flag->Checked = false; }
				 if (i == 7){ this->linear_a->Text = sreader->ReadLine(); }
				 if (i == 8){ this->linear_b->Text = sreader->ReadLine(); }
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
				 if (i == 28){ this->comboBox1->Text = sreader->ReadLine(); }
				 if (i == 29){ if (sreader->ReadLine() == "T") this->csv_check->Checked = true; else this->csv_check->Checked = false; }
			 }
			 sreader->Close();
			 Invalidate();
}
};
}
