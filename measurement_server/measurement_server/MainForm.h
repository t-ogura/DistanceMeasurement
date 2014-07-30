#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#define CONFIG_FILENAME "server.cfg"

#pragma once

namespace measurement_server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// MainForm の概要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			this->readConfigFile(CONFIG_FILENAME);
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}
		/// std::string -> System::String への変換
		String^ ToSystemString(const std::string& i_src){
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  dir_box;
	private: System::Windows::Forms::Button^  dir_browse;
	protected:


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label4;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  a_dist;



	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  a_tilt_deg;

	private: System::Windows::Forms::Label^  a_pan_deg;

	private: System::Windows::Forms::Label^  a_tilt_rad;

	private: System::Windows::Forms::Label^  a_pan_rad;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
	private: System::Windows::Forms::Label^  b_tilt_deg;
	private: System::Windows::Forms::Label^  b_pan_deg;
	private: System::Windows::Forms::Label^  b_tilt_rad;
	private: System::Windows::Forms::Label^  b_pan_rad;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel10;
	private: System::Windows::Forms::Label^  b_dist;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  f_distanceBetweenTargets;
	private: System::Windows::Forms::TextBox^  f_distanceBetweenSystems;


	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  savefilename_box;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::Button^  save_button;
	private: System::Windows::Forms::Button^  stop_button;






private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel11;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel12;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel13;
private: System::Windows::Forms::Label^  vessel_angle_deg;
private: System::Windows::Forms::Label^  vessel_angle_rad;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel14;
private: System::Windows::Forms::Label^  vessel_pos_y;
private: System::Windows::Forms::Label^  vessel_pos_x;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel15;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel16;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label38;





















private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::TextBox^  inst_pos_x;
private: System::Windows::Forms::TextBox^  inst_pos_y;


private: System::Windows::Forms::Label^  label73;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel23;
private: System::Windows::Forms::Label^  label59;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel24;
private: System::Windows::Forms::Label^  label60;
private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel25;
private: System::Windows::Forms::Label^  label62;
private: System::Windows::Forms::Label^  label63;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel26;
private: System::Windows::Forms::Label^  label64;
private: System::Windows::Forms::Label^  label65;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel27;
private: System::Windows::Forms::Label^  label66;
private: System::Windows::Forms::Label^  label67;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel28;
private: System::Windows::Forms::Label^  label68;
private: System::Windows::Forms::Label^  label69;
private: System::Windows::Forms::Label^  label70;
private: System::Windows::Forms::Label^  label72;
private: System::Windows::Forms::Label^  label71;
private: System::Windows::Forms::TextBox^  textBox9;
private: System::Windows::Forms::TextBox^  textBox10;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::TextBox^  shift_pos_y;

private: System::Windows::Forms::TextBox^  shift_pos_x;

private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::TextBox^  textBox5;
private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel17;
private: System::Windows::Forms::Label^  label44;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel18;
private: System::Windows::Forms::Label^  label45;
private: System::Windows::Forms::Label^  label46;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel19;
private: System::Windows::Forms::Label^  vessel_deg;

private: System::Windows::Forms::Label^  vessel_rad;

private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel20;
private: System::Windows::Forms::Label^  vessel_y;

private: System::Windows::Forms::Label^  vessel_x;

private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel21;
private: System::Windows::Forms::Label^  label51;
private: System::Windows::Forms::Label^  label52;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel22;
private: System::Windows::Forms::Label^  label53;
private: System::Windows::Forms::Label^  label54;
private: System::Windows::Forms::Label^  label55;
private: System::Windows::Forms::Label^  label56;
private: System::Windows::Forms::TextBox^  offset_angle_left;
private: System::Windows::Forms::TextBox^  offset_angle_right;


private: System::Windows::Forms::Label^  label57;
private: System::Windows::Forms::Label^  label58;
private: System::Windows::Forms::FontDialog^  fontDialog1;
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::Label^  label75;
private: System::Windows::Forms::TextBox^  output_dir;
private: System::Windows::Forms::Button^  output_dir_browse;


private: System::Windows::Forms::Label^  label74;
private: System::Windows::Forms::TextBox^  interval;
private: System::Windows::Forms::Label^  label76;
	private: System::ComponentModel::IContainer^  components;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dir_box = (gcnew System::Windows::Forms::TextBox());
			this->dir_browse = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->a_tilt_deg = (gcnew System::Windows::Forms::Label());
			this->a_pan_deg = (gcnew System::Windows::Forms::Label());
			this->a_tilt_rad = (gcnew System::Windows::Forms::Label());
			this->a_pan_rad = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->a_dist = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->b_tilt_deg = (gcnew System::Windows::Forms::Label());
			this->b_pan_deg = (gcnew System::Windows::Forms::Label());
			this->b_tilt_rad = (gcnew System::Windows::Forms::Label());
			this->b_pan_rad = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->b_dist = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->f_distanceBetweenTargets = (gcnew System::Windows::Forms::TextBox());
			this->f_distanceBetweenSystems = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->savefilename_box = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel11 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel13 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->vessel_angle_deg = (gcnew System::Windows::Forms::Label());
			this->vessel_angle_rad = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel14 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->vessel_pos_y = (gcnew System::Windows::Forms::Label());
			this->vessel_pos_x = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel15 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel16 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel23 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel24 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel25 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel26 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel27 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel28 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->inst_pos_x = (gcnew System::Windows::Forms::TextBox());
			this->inst_pos_y = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->shift_pos_y = (gcnew System::Windows::Forms::TextBox());
			this->shift_pos_x = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel17 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel18 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel19 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->vessel_deg = (gcnew System::Windows::Forms::Label());
			this->vessel_rad = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel20 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->vessel_y = (gcnew System::Windows::Forms::Label());
			this->vessel_x = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel21 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel22 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->offset_angle_left = (gcnew System::Windows::Forms::TextBox());
			this->offset_angle_right = (gcnew System::Windows::Forms::TextBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->interval = (gcnew System::Windows::Forms::TextBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->output_dir = (gcnew System::Windows::Forms::TextBox());
			this->output_dir_browse = (gcnew System::Windows::Forms::Button());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->tableLayoutPanel10->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel11->SuspendLayout();
			this->tableLayoutPanel12->SuspendLayout();
			this->tableLayoutPanel13->SuspendLayout();
			this->tableLayoutPanel14->SuspendLayout();
			this->tableLayoutPanel15->SuspendLayout();
			this->tableLayoutPanel16->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tableLayoutPanel23->SuspendLayout();
			this->tableLayoutPanel24->SuspendLayout();
			this->tableLayoutPanel25->SuspendLayout();
			this->tableLayoutPanel26->SuspendLayout();
			this->tableLayoutPanel27->SuspendLayout();
			this->tableLayoutPanel28->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tableLayoutPanel17->SuspendLayout();
			this->tableLayoutPanel18->SuspendLayout();
			this->tableLayoutPanel19->SuspendLayout();
			this->tableLayoutPanel20->SuspendLayout();
			this->tableLayoutPanel21->SuspendLayout();
			this->tableLayoutPanel22->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Data File Directory";
			// 
			// dir_box
			// 
			this->dir_box->Location = System::Drawing::Point(51, 73);
			this->dir_box->Name = L"dir_box";
			this->dir_box->Size = System::Drawing::Size(161, 20);
			this->dir_box->TabIndex = 1;
			this->dir_box->Text = L"C:\\share";
			// 
			// dir_browse
			// 
			this->dir_browse->Location = System::Drawing::Point(215, 72);
			this->dir_browse->Name = L"dir_browse";
			this->dir_browse->Size = System::Drawing::Size(54, 22);
			this->dir_browse->TabIndex = 2;
			this->dir_browse->Text = L"browse";
			this->dir_browse->UseVisualStyleBackColor = true;
			this->dir_browse->Click += gcnew System::EventHandler(this, &MainForm::dir_browse_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tableLayoutPanel1);
			this->groupBox1->Location = System::Drawing::Point(294, 118);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(277, 132);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Measure-L";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				41.2844F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				58.7156F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				46)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 2, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(7, 21);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(264, 105);
			this->tableLayoutPanel1->TabIndex = 2;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->Controls->Add(this->label19, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(220, 3);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(37, 14);
			this->tableLayoutPanel4->TabIndex = 10;
			// 
			// label19
			// 
			this->label19->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(7, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(23, 13);
			this->label19->TabIndex = 8;
			this->label19->Text = L"mm";
			this->label19->Click += gcnew System::EventHandler(this, &MainForm::label19_Click);
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 56);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(75, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Platform Angle";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(20, 4);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Distance";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				27.19298F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				72.80701F)));
			this->tableLayoutPanel2->Controls->Add(this->a_tilt_deg, 1, 3);
			this->tableLayoutPanel2->Controls->Add(this->a_pan_deg, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->a_tilt_rad, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->a_pan_rad, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->label7, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->label6, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->label8, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->label9, 0, 3);
			this->tableLayoutPanel2->Location = System::Drawing::Point(92, 24);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 4;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(122, 78);
			this->tableLayoutPanel2->TabIndex = 8;
			// 
			// a_tilt_deg
			// 
			this->a_tilt_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_tilt_deg->AutoSize = true;
			this->a_tilt_deg->Location = System::Drawing::Point(106, 61);
			this->a_tilt_deg->Name = L"a_tilt_deg";
			this->a_tilt_deg->Size = System::Drawing::Size(13, 13);
			this->a_tilt_deg->TabIndex = 15;
			this->a_tilt_deg->Text = L"0";
			this->a_tilt_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// a_pan_deg
			// 
			this->a_pan_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_pan_deg->AutoSize = true;
			this->a_pan_deg->Location = System::Drawing::Point(106, 41);
			this->a_pan_deg->Name = L"a_pan_deg";
			this->a_pan_deg->Size = System::Drawing::Size(13, 13);
			this->a_pan_deg->TabIndex = 14;
			this->a_pan_deg->Text = L"0";
			this->a_pan_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// a_tilt_rad
			// 
			this->a_tilt_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_tilt_rad->AutoSize = true;
			this->a_tilt_rad->Location = System::Drawing::Point(106, 22);
			this->a_tilt_rad->Name = L"a_tilt_rad";
			this->a_tilt_rad->Size = System::Drawing::Size(13, 13);
			this->a_tilt_rad->TabIndex = 13;
			this->a_tilt_rad->Text = L"0";
			this->a_tilt_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// a_pan_rad
			// 
			this->a_pan_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_pan_rad->AutoSize = true;
			this->a_pan_rad->Location = System::Drawing::Point(106, 3);
			this->a_pan_rad->Name = L"a_pan_rad";
			this->a_pan_rad->Size = System::Drawing::Size(13, 13);
			this->a_pan_rad->TabIndex = 12;
			this->a_pan_rad->Text = L"0";
			this->a_pan_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label7
			// 
			this->label7->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(21, 13);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Tilt";
			this->label7->Click += gcnew System::EventHandler(this, &MainForm::label7_Click);
			// 
			// label6
			// 
			this->label6->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 3);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Pan";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// label8
			// 
			this->label8->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 41);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(26, 13);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Pan";
			this->label8->Click += gcnew System::EventHandler(this, &MainForm::label8_Click);
			// 
			// label9
			// 
			this->label9->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 61);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(21, 13);
			this->label9->TabIndex = 11;
			this->label9->Text = L"Tilt";
			this->label9->Click += gcnew System::EventHandler(this, &MainForm::label9_Click);
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 1;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel5->Controls->Add(this->a_dist, 0, 0);
			this->tableLayoutPanel5->Location = System::Drawing::Point(92, 3);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(122, 11);
			this->tableLayoutPanel5->TabIndex = 11;
			// 
			// a_dist
			// 
			this->a_dist->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_dist->AutoSize = true;
			this->a_dist->Location = System::Drawing::Point(106, 0);
			this->a_dist->Name = L"a_dist";
			this->a_dist->Size = System::Drawing::Size(13, 11);
			this->a_dist->TabIndex = 1;
			this->a_dist->Text = L"0";
			this->a_dist->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->Controls->Add(this->label10, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->label11, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label12, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->label13, 0, 3);
			this->tableLayoutPanel3->Location = System::Drawing::Point(220, 24);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 4;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(37, 78);
			this->tableLayoutPanel3->TabIndex = 9;
			// 
			// label10
			// 
			this->label10->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 22);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(25, 13);
			this->label10->TabIndex = 9;
			this->label10->Text = L"rad.";
			// 
			// label11
			// 
			this->label11->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 3);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(25, 13);
			this->label11->TabIndex = 8;
			this->label11->Text = L"rad.";
			// 
			// label12
			// 
			this->label12->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(4, 41);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(28, 13);
			this->label12->TabIndex = 10;
			this->label12->Text = L"deg.";
			// 
			// label13
			// 
			this->label13->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(4, 61);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(28, 13);
			this->label13->TabIndex = 11;
			this->label13->Text = L"deg.";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->tableLayoutPanel6);
			this->groupBox2->Location = System::Drawing::Point(294, 257);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(277, 132);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Measure-R";
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 3;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40.36697F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				59.63303F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				44)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 2, 0);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 2, 1);
			this->tableLayoutPanel6->Controls->Add(this->label17, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->label18, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel9, 1, 1);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel10, 1, 0);
			this->tableLayoutPanel6->Location = System::Drawing::Point(7, 21);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(264, 105);
			this->tableLayoutPanel6->TabIndex = 2;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 1;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel7->Controls->Add(this->label3, 0, 0);
			this->tableLayoutPanel7->Location = System::Drawing::Point(222, 3);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 1;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(37, 14);
			this->tableLayoutPanel7->TabIndex = 10;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(23, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"mm";
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->ColumnCount = 1;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel8->Controls->Add(this->label5, 0, 1);
			this->tableLayoutPanel8->Controls->Add(this->label14, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->label15, 0, 2);
			this->tableLayoutPanel8->Controls->Add(this->label16, 0, 3);
			this->tableLayoutPanel8->Location = System::Drawing::Point(222, 24);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 4;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(37, 78);
			this->tableLayoutPanel8->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(25, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"rad.";
			// 
			// label14
			// 
			this->label14->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 3);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(25, 13);
			this->label14->TabIndex = 8;
			this->label14->Text = L"rad.";
			// 
			// label15
			// 
			this->label15->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(4, 41);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(28, 13);
			this->label15->TabIndex = 10;
			this->label15->Text = L"deg.";
			// 
			// label16
			// 
			this->label16->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(4, 61);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(28, 13);
			this->label16->TabIndex = 11;
			this->label16->Text = L"deg.";
			// 
			// label17
			// 
			this->label17->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(3, 56);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(75, 13);
			this->label17->TabIndex = 6;
			this->label17->Text = L"Platform Angle";
			// 
			// label18
			// 
			this->label18->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(19, 4);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(49, 13);
			this->label18->TabIndex = 0;
			this->label18->Text = L"Distance";
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.72414F)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				73.27586F)));
			this->tableLayoutPanel9->Controls->Add(this->b_tilt_deg, 1, 3);
			this->tableLayoutPanel9->Controls->Add(this->b_pan_deg, 1, 2);
			this->tableLayoutPanel9->Controls->Add(this->b_tilt_rad, 1, 1);
			this->tableLayoutPanel9->Controls->Add(this->b_pan_rad, 1, 0);
			this->tableLayoutPanel9->Controls->Add(this->label24, 0, 1);
			this->tableLayoutPanel9->Controls->Add(this->label25, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->label26, 0, 2);
			this->tableLayoutPanel9->Controls->Add(this->label27, 0, 3);
			this->tableLayoutPanel9->Location = System::Drawing::Point(91, 24);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 4;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(125, 78);
			this->tableLayoutPanel9->TabIndex = 8;
			// 
			// b_tilt_deg
			// 
			this->b_tilt_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_tilt_deg->AutoSize = true;
			this->b_tilt_deg->Location = System::Drawing::Point(109, 61);
			this->b_tilt_deg->Name = L"b_tilt_deg";
			this->b_tilt_deg->Size = System::Drawing::Size(13, 13);
			this->b_tilt_deg->TabIndex = 15;
			this->b_tilt_deg->Text = L"0";
			this->b_tilt_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_pan_deg
			// 
			this->b_pan_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_pan_deg->AutoSize = true;
			this->b_pan_deg->Location = System::Drawing::Point(109, 41);
			this->b_pan_deg->Name = L"b_pan_deg";
			this->b_pan_deg->Size = System::Drawing::Size(13, 13);
			this->b_pan_deg->TabIndex = 14;
			this->b_pan_deg->Text = L"0";
			this->b_pan_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_tilt_rad
			// 
			this->b_tilt_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_tilt_rad->AutoSize = true;
			this->b_tilt_rad->Location = System::Drawing::Point(109, 22);
			this->b_tilt_rad->Name = L"b_tilt_rad";
			this->b_tilt_rad->Size = System::Drawing::Size(13, 13);
			this->b_tilt_rad->TabIndex = 13;
			this->b_tilt_rad->Text = L"0";
			this->b_tilt_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_pan_rad
			// 
			this->b_pan_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_pan_rad->AutoSize = true;
			this->b_pan_rad->Location = System::Drawing::Point(109, 3);
			this->b_pan_rad->Name = L"b_pan_rad";
			this->b_pan_rad->Size = System::Drawing::Size(13, 13);
			this->b_pan_rad->TabIndex = 12;
			this->b_pan_rad->Text = L"0";
			this->b_pan_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label24
			// 
			this->label24->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(6, 22);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(21, 13);
			this->label24->TabIndex = 9;
			this->label24->Text = L"Tilt";
			// 
			// label25
			// 
			this->label25->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(3, 3);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(26, 13);
			this->label25->TabIndex = 8;
			this->label25->Text = L"Pan";
			// 
			// label26
			// 
			this->label26->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(3, 41);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(26, 13);
			this->label26->TabIndex = 10;
			this->label26->Text = L"Pan";
			// 
			// label27
			// 
			this->label27->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(6, 61);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(21, 13);
			this->label27->TabIndex = 11;
			this->label27->Text = L"Tilt";
			// 
			// tableLayoutPanel10
			// 
			this->tableLayoutPanel10->ColumnCount = 1;
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel10->Controls->Add(this->b_dist, 0, 0);
			this->tableLayoutPanel10->Location = System::Drawing::Point(91, 3);
			this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
			this->tableLayoutPanel10->RowCount = 1;
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel10->Size = System::Drawing::Size(125, 13);
			this->tableLayoutPanel10->TabIndex = 11;
			// 
			// b_dist
			// 
			this->b_dist->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_dist->AutoSize = true;
			this->b_dist->Location = System::Drawing::Point(109, 0);
			this->b_dist->Name = L"b_dist";
			this->b_dist->Size = System::Drawing::Size(13, 13);
			this->b_dist->TabIndex = 1;
			this->b_dist->Text = L"0";
			this->b_dist->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &MainForm::folderBrowserDialog1_HelpRequest);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(5, 138);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(132, 13);
			this->label20->TabIndex = 5;
			this->label20->Text = L"Distance between Targets";
			// 
			// f_distanceBetweenTargets
			// 
			this->f_distanceBetweenTargets->Location = System::Drawing::Point(173, 134);
			this->f_distanceBetweenTargets->Name = L"f_distanceBetweenTargets";
			this->f_distanceBetweenTargets->Size = System::Drawing::Size(96, 20);
			this->f_distanceBetweenTargets->TabIndex = 6;
			this->f_distanceBetweenTargets->Text = L"1090";
			this->f_distanceBetweenTargets->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// f_distanceBetweenSystems
			// 
			this->f_distanceBetweenSystems->Location = System::Drawing::Point(173, 161);
			this->f_distanceBetweenSystems->Name = L"f_distanceBetweenSystems";
			this->f_distanceBetweenSystems->Size = System::Drawing::Size(96, 20);
			this->f_distanceBetweenSystems->TabIndex = 8;
			this->f_distanceBetweenSystems->Text = L"840";
			this->f_distanceBetweenSystems->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(5, 165);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(142, 13);
			this->label21->TabIndex = 7;
			this->label21->Text = L"Distance between Measures";
			// 
			// savefilename_box
			// 
			this->savefilename_box->Location = System::Drawing::Point(102, 355);
			this->savefilename_box->Name = L"savefilename_box";
			this->savefilename_box->Size = System::Drawing::Size(90, 20);
			this->savefilename_box->TabIndex = 9;
			this->savefilename_box->Text = L"data01";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(10, 359);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(82, 13);
			this->label22->TabIndex = 10;
			this->label22->Text = L"Save File Name";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripStatusLabel1,
					this->toolStripStatusLabel2
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 398);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(582, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 11;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(10, 17);
			this->toolStripStatusLabel2->Text = L" ";
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(198, 355);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(41, 21);
			this->save_button->TabIndex = 12;
			this->save_button->Text = L"Save";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &MainForm::save_button_Click);
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(245, 355);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(43, 21);
			this->stop_button->TabIndex = 13;
			this->stop_button->Text = L"Stop";
			this->stop_button->UseVisualStyleBackColor = true;
			this->stop_button->Click += gcnew System::EventHandler(this, &MainForm::stop_button_Click);
			// 
			// tableLayoutPanel11
			// 
			this->tableLayoutPanel11->ColumnCount = 4;
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.43478F)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				103)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				43)));
			this->tableLayoutPanel11->Controls->Add(this->label23, 0, 0);
			this->tableLayoutPanel11->Controls->Add(this->tableLayoutPanel12, 3, 0);
			this->tableLayoutPanel11->Controls->Add(this->tableLayoutPanel13, 2, 0);
			this->tableLayoutPanel11->Controls->Add(this->tableLayoutPanel14, 2, 1);
			this->tableLayoutPanel11->Controls->Add(this->tableLayoutPanel15, 3, 1);
			this->tableLayoutPanel11->Controls->Add(this->tableLayoutPanel16, 1, 1);
			this->tableLayoutPanel11->Controls->Add(this->label38, 0, 1);
			this->tableLayoutPanel11->Location = System::Drawing::Point(6, 20);
			this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
			this->tableLayoutPanel11->RowCount = 2;
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50.74627F)));
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.25373F)));
			this->tableLayoutPanel11->Size = System::Drawing::Size(264, 73);
			this->tableLayoutPanel11->TabIndex = 15;
			// 
			// label23
			// 
			this->label23->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(14, 12);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(68, 13);
			this->label23->TabIndex = 1;
			this->label23->Text = L"Vessel Angle";
			// 
			// tableLayoutPanel12
			// 
			this->tableLayoutPanel12->ColumnCount = 1;
			this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel12->Controls->Add(this->label28, 0, 1);
			this->tableLayoutPanel12->Controls->Add(this->label29, 0, 0);
			this->tableLayoutPanel12->Location = System::Drawing::Point(224, 3);
			this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
			this->tableLayoutPanel12->RowCount = 2;
			this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel12->Size = System::Drawing::Size(37, 30);
			this->tableLayoutPanel12->TabIndex = 10;
			// 
			// label28
			// 
			this->label28->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(4, 16);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(28, 13);
			this->label28->TabIndex = 9;
			this->label28->Text = L"deg.";
			// 
			// label29
			// 
			this->label29->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(6, 1);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(25, 13);
			this->label29->TabIndex = 8;
			this->label29->Text = L"rad.";
			// 
			// tableLayoutPanel13
			// 
			this->tableLayoutPanel13->ColumnCount = 1;
			this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel13->Controls->Add(this->vessel_angle_deg, 0, 1);
			this->tableLayoutPanel13->Controls->Add(this->vessel_angle_rad, 0, 0);
			this->tableLayoutPanel13->Location = System::Drawing::Point(121, 3);
			this->tableLayoutPanel13->Name = L"tableLayoutPanel13";
			this->tableLayoutPanel13->RowCount = 2;
			this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel13->Size = System::Drawing::Size(97, 30);
			this->tableLayoutPanel13->TabIndex = 11;
			// 
			// vessel_angle_deg
			// 
			this->vessel_angle_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_angle_deg->AutoSize = true;
			this->vessel_angle_deg->Location = System::Drawing::Point(81, 16);
			this->vessel_angle_deg->Name = L"vessel_angle_deg";
			this->vessel_angle_deg->Size = System::Drawing::Size(13, 13);
			this->vessel_angle_deg->TabIndex = 9;
			this->vessel_angle_deg->Text = L"0";
			this->vessel_angle_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// vessel_angle_rad
			// 
			this->vessel_angle_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_angle_rad->AutoSize = true;
			this->vessel_angle_rad->Location = System::Drawing::Point(81, 1);
			this->vessel_angle_rad->Name = L"vessel_angle_rad";
			this->vessel_angle_rad->Size = System::Drawing::Size(13, 13);
			this->vessel_angle_rad->TabIndex = 8;
			this->vessel_angle_rad->Text = L"0";
			this->vessel_angle_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel14
			// 
			this->tableLayoutPanel14->ColumnCount = 1;
			this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel14->Controls->Add(this->vessel_pos_y, 0, 1);
			this->tableLayoutPanel14->Controls->Add(this->vessel_pos_x, 0, 0);
			this->tableLayoutPanel14->Location = System::Drawing::Point(121, 40);
			this->tableLayoutPanel14->Name = L"tableLayoutPanel14";
			this->tableLayoutPanel14->RowCount = 2;
			this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel14->Size = System::Drawing::Size(97, 29);
			this->tableLayoutPanel14->TabIndex = 12;
			// 
			// vessel_pos_y
			// 
			this->vessel_pos_y->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_pos_y->AutoSize = true;
			this->vessel_pos_y->Location = System::Drawing::Point(81, 15);
			this->vessel_pos_y->Name = L"vessel_pos_y";
			this->vessel_pos_y->Size = System::Drawing::Size(13, 13);
			this->vessel_pos_y->TabIndex = 9;
			this->vessel_pos_y->Text = L"0";
			this->vessel_pos_y->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// vessel_pos_x
			// 
			this->vessel_pos_x->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_pos_x->AutoSize = true;
			this->vessel_pos_x->Location = System::Drawing::Point(81, 0);
			this->vessel_pos_x->Name = L"vessel_pos_x";
			this->vessel_pos_x->Size = System::Drawing::Size(13, 13);
			this->vessel_pos_x->TabIndex = 8;
			this->vessel_pos_x->Text = L"0";
			this->vessel_pos_x->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel15
			// 
			this->tableLayoutPanel15->ColumnCount = 1;
			this->tableLayoutPanel15->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel15->Controls->Add(this->label34, 0, 1);
			this->tableLayoutPanel15->Controls->Add(this->label35, 0, 0);
			this->tableLayoutPanel15->Location = System::Drawing::Point(224, 40);
			this->tableLayoutPanel15->Name = L"tableLayoutPanel15";
			this->tableLayoutPanel15->RowCount = 2;
			this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel15->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel15->Size = System::Drawing::Size(37, 29);
			this->tableLayoutPanel15->TabIndex = 13;
			// 
			// label34
			// 
			this->label34->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(7, 15);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(23, 13);
			this->label34->TabIndex = 9;
			this->label34->Text = L"mm";
			// 
			// label35
			// 
			this->label35->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(7, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(23, 13);
			this->label35->TabIndex = 8;
			this->label35->Text = L"mm";
			// 
			// tableLayoutPanel16
			// 
			this->tableLayoutPanel16->ColumnCount = 1;
			this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel16->Controls->Add(this->label36, 0, 1);
			this->tableLayoutPanel16->Controls->Add(this->label37, 0, 0);
			this->tableLayoutPanel16->Location = System::Drawing::Point(99, 40);
			this->tableLayoutPanel16->Name = L"tableLayoutPanel16";
			this->tableLayoutPanel16->RowCount = 2;
			this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel16->Size = System::Drawing::Size(16, 29);
			this->tableLayoutPanel16->TabIndex = 14;
			// 
			// label36
			// 
			this->label36->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(3, 15);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(10, 13);
			this->label36->TabIndex = 9;
			this->label36->Text = L"y";
			// 
			// label37
			// 
			this->label37->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(3, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(10, 13);
			this->label37->TabIndex = 8;
			this->label37->Text = L"x";
			// 
			// label38
			// 
			this->label38->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(9, 48);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(78, 13);
			this->label38->TabIndex = 15;
			this->label38->Text = L"Vessel Position";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label73);
			this->groupBox4->Controls->Add(this->tableLayoutPanel11);
			this->groupBox4->Controls->Add(this->groupBox5);
			this->groupBox4->Controls->Add(this->label72);
			this->groupBox4->Controls->Add(this->label71);
			this->groupBox4->Controls->Add(this->textBox9);
			this->groupBox4->Controls->Add(this->textBox10);
			this->groupBox4->Location = System::Drawing::Point(295, 13);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(276, 99);
			this->groupBox4->TabIndex = 18;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Common Information";
			this->groupBox4->Enter += gcnew System::EventHandler(this, &MainForm::groupBox4_Enter);
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Location = System::Drawing::Point(138, -37);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(54, 13);
			this->label73->TabIndex = 33;
			this->label73->Text = L"theta right";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->tableLayoutPanel23);
			this->groupBox5->Location = System::Drawing::Point(0, 0);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(276, 99);
			this->groupBox5->TabIndex = 18;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Common Information";
			this->groupBox5->Enter += gcnew System::EventHandler(this, &MainForm::groupBox4_Enter);
			// 
			// tableLayoutPanel23
			// 
			this->tableLayoutPanel23->ColumnCount = 4;
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.43478F)));
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				103)));
			this->tableLayoutPanel23->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				43)));
			this->tableLayoutPanel23->Controls->Add(this->label59, 0, 0);
			this->tableLayoutPanel23->Controls->Add(this->tableLayoutPanel24, 3, 0);
			this->tableLayoutPanel23->Controls->Add(this->tableLayoutPanel25, 2, 0);
			this->tableLayoutPanel23->Controls->Add(this->tableLayoutPanel26, 2, 1);
			this->tableLayoutPanel23->Controls->Add(this->tableLayoutPanel27, 3, 1);
			this->tableLayoutPanel23->Controls->Add(this->tableLayoutPanel28, 1, 1);
			this->tableLayoutPanel23->Controls->Add(this->label70, 0, 1);
			this->tableLayoutPanel23->Location = System::Drawing::Point(6, 20);
			this->tableLayoutPanel23->Name = L"tableLayoutPanel23";
			this->tableLayoutPanel23->RowCount = 2;
			this->tableLayoutPanel23->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50.74627F)));
			this->tableLayoutPanel23->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.25373F)));
			this->tableLayoutPanel23->Size = System::Drawing::Size(264, 73);
			this->tableLayoutPanel23->TabIndex = 15;
			// 
			// label59
			// 
			this->label59->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(14, 12);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(68, 13);
			this->label59->TabIndex = 1;
			this->label59->Text = L"Vessel Angle";
			// 
			// tableLayoutPanel24
			// 
			this->tableLayoutPanel24->ColumnCount = 1;
			this->tableLayoutPanel24->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel24->Controls->Add(this->label60, 0, 1);
			this->tableLayoutPanel24->Controls->Add(this->label61, 0, 0);
			this->tableLayoutPanel24->Location = System::Drawing::Point(224, 3);
			this->tableLayoutPanel24->Name = L"tableLayoutPanel24";
			this->tableLayoutPanel24->RowCount = 2;
			this->tableLayoutPanel24->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel24->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel24->Size = System::Drawing::Size(37, 30);
			this->tableLayoutPanel24->TabIndex = 10;
			// 
			// label60
			// 
			this->label60->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(4, 16);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(28, 13);
			this->label60->TabIndex = 9;
			this->label60->Text = L"deg.";
			// 
			// label61
			// 
			this->label61->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(6, 1);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(25, 13);
			this->label61->TabIndex = 8;
			this->label61->Text = L"rad.";
			// 
			// tableLayoutPanel25
			// 
			this->tableLayoutPanel25->ColumnCount = 1;
			this->tableLayoutPanel25->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel25->Controls->Add(this->label62, 0, 1);
			this->tableLayoutPanel25->Controls->Add(this->label63, 0, 0);
			this->tableLayoutPanel25->Location = System::Drawing::Point(121, 3);
			this->tableLayoutPanel25->Name = L"tableLayoutPanel25";
			this->tableLayoutPanel25->RowCount = 2;
			this->tableLayoutPanel25->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel25->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel25->Size = System::Drawing::Size(97, 30);
			this->tableLayoutPanel25->TabIndex = 11;
			// 
			// label62
			// 
			this->label62->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(81, 16);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(13, 13);
			this->label62->TabIndex = 9;
			this->label62->Text = L"0";
			this->label62->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label63
			// 
			this->label63->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(81, 1);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(13, 13);
			this->label63->TabIndex = 8;
			this->label63->Text = L"0";
			this->label63->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel26
			// 
			this->tableLayoutPanel26->ColumnCount = 1;
			this->tableLayoutPanel26->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel26->Controls->Add(this->label64, 0, 1);
			this->tableLayoutPanel26->Controls->Add(this->label65, 0, 0);
			this->tableLayoutPanel26->Location = System::Drawing::Point(121, 40);
			this->tableLayoutPanel26->Name = L"tableLayoutPanel26";
			this->tableLayoutPanel26->RowCount = 2;
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel26->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel26->Size = System::Drawing::Size(97, 29);
			this->tableLayoutPanel26->TabIndex = 12;
			// 
			// label64
			// 
			this->label64->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label64->AutoSize = true;
			this->label64->Location = System::Drawing::Point(81, 15);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(13, 13);
			this->label64->TabIndex = 9;
			this->label64->Text = L"0";
			this->label64->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label65
			// 
			this->label65->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(81, 0);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(13, 13);
			this->label65->TabIndex = 8;
			this->label65->Text = L"0";
			this->label65->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel27
			// 
			this->tableLayoutPanel27->ColumnCount = 1;
			this->tableLayoutPanel27->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel27->Controls->Add(this->label66, 0, 1);
			this->tableLayoutPanel27->Controls->Add(this->label67, 0, 0);
			this->tableLayoutPanel27->Location = System::Drawing::Point(224, 40);
			this->tableLayoutPanel27->Name = L"tableLayoutPanel27";
			this->tableLayoutPanel27->RowCount = 2;
			this->tableLayoutPanel27->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel27->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel27->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel27->Size = System::Drawing::Size(37, 29);
			this->tableLayoutPanel27->TabIndex = 13;
			// 
			// label66
			// 
			this->label66->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(7, 15);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(23, 13);
			this->label66->TabIndex = 9;
			this->label66->Text = L"mm";
			// 
			// label67
			// 
			this->label67->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(7, 0);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(23, 13);
			this->label67->TabIndex = 8;
			this->label67->Text = L"mm";
			// 
			// tableLayoutPanel28
			// 
			this->tableLayoutPanel28->ColumnCount = 1;
			this->tableLayoutPanel28->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel28->Controls->Add(this->label68, 0, 1);
			this->tableLayoutPanel28->Controls->Add(this->label69, 0, 0);
			this->tableLayoutPanel28->Location = System::Drawing::Point(99, 40);
			this->tableLayoutPanel28->Name = L"tableLayoutPanel28";
			this->tableLayoutPanel28->RowCount = 2;
			this->tableLayoutPanel28->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel28->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel28->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel28->Size = System::Drawing::Size(16, 29);
			this->tableLayoutPanel28->TabIndex = 14;
			// 
			// label68
			// 
			this->label68->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(3, 15);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(10, 13);
			this->label68->TabIndex = 9;
			this->label68->Text = L"y";
			// 
			// label69
			// 
			this->label69->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(3, 0);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(10, 13);
			this->label69->TabIndex = 8;
			this->label69->Text = L"x";
			// 
			// label70
			// 
			this->label70->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(9, 48);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(78, 13);
			this->label70->TabIndex = 15;
			this->label70->Text = L"Vessel Position";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(138, -64);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(48, 13);
			this->label72->TabIndex = 32;
			this->label72->Text = L"theta left";
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(0, -64);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(94, 13);
			this->label71->TabIndex = 21;
			this->label71->Text = L"Offset angle [deg.]";
			this->label71->Click += gcnew System::EventHandler(this, &MainForm::label32_Click);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(201, -67);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(76, 20);
			this->textBox9->TabIndex = 30;
			this->textBox9->Text = L"0";
			this->textBox9->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(201, -40);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(76, 20);
			this->textBox10->TabIndex = 31;
			this->textBox10->Text = L"0";
			this->textBox10->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(5, 200);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(98, 13);
			this->label30->TabIndex = 19;
			this->label30->Text = L"Install position [mm]";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(6, 226);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(92, 13);
			this->label31->TabIndex = 20;
			this->label31->Text = L"Shift position [mm]";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(6, 264);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(94, 13);
			this->label32->TabIndex = 21;
			this->label32->Text = L"Offset angle [deg.]";
			this->label32->Click += gcnew System::EventHandler(this, &MainForm::label32_Click);
			// 
			// inst_pos_x
			// 
			this->inst_pos_x->Location = System::Drawing::Point(137, 194);
			this->inst_pos_x->Name = L"inst_pos_x";
			this->inst_pos_x->Size = System::Drawing::Size(54, 20);
			this->inst_pos_x->TabIndex = 22;
			this->inst_pos_x->Text = L"0";
			this->inst_pos_x->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->inst_pos_x->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// inst_pos_y
			// 
			this->inst_pos_y->Location = System::Drawing::Point(215, 194);
			this->inst_pos_y->Name = L"inst_pos_y";
			this->inst_pos_y->Size = System::Drawing::Size(54, 20);
			this->inst_pos_y->TabIndex = 23;
			this->inst_pos_y->Text = L"0";
			this->inst_pos_y->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(120, 197);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(12, 13);
			this->label33->TabIndex = 24;
			this->label33->Text = L"x";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(201, 197);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(12, 13);
			this->label39->TabIndex = 25;
			this->label39->Text = L"y";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(201, 226);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(12, 13);
			this->label40->TabIndex = 29;
			this->label40->Text = L"y";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(120, 226);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(12, 13);
			this->label41->TabIndex = 28;
			this->label41->Text = L"x";
			// 
			// shift_pos_y
			// 
			this->shift_pos_y->Location = System::Drawing::Point(215, 223);
			this->shift_pos_y->Name = L"shift_pos_y";
			this->shift_pos_y->Size = System::Drawing::Size(54, 20);
			this->shift_pos_y->TabIndex = 27;
			this->shift_pos_y->Text = L"0";
			this->shift_pos_y->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// shift_pos_x
			// 
			this->shift_pos_x->Location = System::Drawing::Point(137, 223);
			this->shift_pos_x->Name = L"shift_pos_x";
			this->shift_pos_x->Size = System::Drawing::Size(54, 20);
			this->shift_pos_x->TabIndex = 26;
			this->shift_pos_x->Text = L"0";
			this->shift_pos_x->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(130, 264);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(48, 13);
			this->label43->TabIndex = 32;
			this->label43->Text = L"theta left";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(193, 288);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(76, 20);
			this->textBox5->TabIndex = 31;
			this->textBox5->Text = L"0";
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(193, 261);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(76, 20);
			this->textBox6->TabIndex = 30;
			this->textBox6->Text = L"0";
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(130, 291);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(54, 13);
			this->label42->TabIndex = 33;
			this->label42->Text = L"theta right";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tableLayoutPanel17);
			this->groupBox3->Location = System::Drawing::Point(295, 13);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(276, 99);
			this->groupBox3->TabIndex = 18;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Common Information";
			this->groupBox3->Enter += gcnew System::EventHandler(this, &MainForm::groupBox4_Enter);
			// 
			// tableLayoutPanel17
			// 
			this->tableLayoutPanel17->ColumnCount = 4;
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				55.43478F)));
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				103)));
			this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				43)));
			this->tableLayoutPanel17->Controls->Add(this->label44, 0, 0);
			this->tableLayoutPanel17->Controls->Add(this->tableLayoutPanel18, 3, 0);
			this->tableLayoutPanel17->Controls->Add(this->tableLayoutPanel19, 2, 0);
			this->tableLayoutPanel17->Controls->Add(this->tableLayoutPanel20, 2, 1);
			this->tableLayoutPanel17->Controls->Add(this->tableLayoutPanel21, 3, 1);
			this->tableLayoutPanel17->Controls->Add(this->tableLayoutPanel22, 1, 1);
			this->tableLayoutPanel17->Controls->Add(this->label55, 0, 1);
			this->tableLayoutPanel17->Location = System::Drawing::Point(6, 20);
			this->tableLayoutPanel17->Name = L"tableLayoutPanel17";
			this->tableLayoutPanel17->RowCount = 2;
			this->tableLayoutPanel17->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50.74627F)));
			this->tableLayoutPanel17->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.25373F)));
			this->tableLayoutPanel17->Size = System::Drawing::Size(264, 73);
			this->tableLayoutPanel17->TabIndex = 15;
			// 
			// label44
			// 
			this->label44->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(14, 12);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(68, 13);
			this->label44->TabIndex = 1;
			this->label44->Text = L"Vessel Angle";
			// 
			// tableLayoutPanel18
			// 
			this->tableLayoutPanel18->ColumnCount = 1;
			this->tableLayoutPanel18->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel18->Controls->Add(this->label45, 0, 1);
			this->tableLayoutPanel18->Controls->Add(this->label46, 0, 0);
			this->tableLayoutPanel18->Location = System::Drawing::Point(224, 3);
			this->tableLayoutPanel18->Name = L"tableLayoutPanel18";
			this->tableLayoutPanel18->RowCount = 2;
			this->tableLayoutPanel18->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel18->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel18->Size = System::Drawing::Size(37, 30);
			this->tableLayoutPanel18->TabIndex = 10;
			// 
			// label45
			// 
			this->label45->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(4, 16);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(28, 13);
			this->label45->TabIndex = 9;
			this->label45->Text = L"deg.";
			// 
			// label46
			// 
			this->label46->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(6, 1);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(25, 13);
			this->label46->TabIndex = 8;
			this->label46->Text = L"rad.";
			// 
			// tableLayoutPanel19
			// 
			this->tableLayoutPanel19->ColumnCount = 1;
			this->tableLayoutPanel19->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel19->Controls->Add(this->vessel_deg, 0, 1);
			this->tableLayoutPanel19->Controls->Add(this->vessel_rad, 0, 0);
			this->tableLayoutPanel19->Location = System::Drawing::Point(121, 3);
			this->tableLayoutPanel19->Name = L"tableLayoutPanel19";
			this->tableLayoutPanel19->RowCount = 2;
			this->tableLayoutPanel19->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel19->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel19->Size = System::Drawing::Size(97, 30);
			this->tableLayoutPanel19->TabIndex = 11;
			// 
			// vessel_deg
			// 
			this->vessel_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_deg->AutoSize = true;
			this->vessel_deg->Location = System::Drawing::Point(81, 16);
			this->vessel_deg->Name = L"vessel_deg";
			this->vessel_deg->Size = System::Drawing::Size(13, 13);
			this->vessel_deg->TabIndex = 9;
			this->vessel_deg->Text = L"0";
			this->vessel_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// vessel_rad
			// 
			this->vessel_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_rad->AutoSize = true;
			this->vessel_rad->Location = System::Drawing::Point(81, 1);
			this->vessel_rad->Name = L"vessel_rad";
			this->vessel_rad->Size = System::Drawing::Size(13, 13);
			this->vessel_rad->TabIndex = 8;
			this->vessel_rad->Text = L"0";
			this->vessel_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel20
			// 
			this->tableLayoutPanel20->ColumnCount = 1;
			this->tableLayoutPanel20->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel20->Controls->Add(this->vessel_y, 0, 1);
			this->tableLayoutPanel20->Controls->Add(this->vessel_x, 0, 0);
			this->tableLayoutPanel20->Location = System::Drawing::Point(121, 40);
			this->tableLayoutPanel20->Name = L"tableLayoutPanel20";
			this->tableLayoutPanel20->RowCount = 2;
			this->tableLayoutPanel20->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel20->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel20->Size = System::Drawing::Size(97, 29);
			this->tableLayoutPanel20->TabIndex = 12;
			// 
			// vessel_y
			// 
			this->vessel_y->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_y->AutoSize = true;
			this->vessel_y->Location = System::Drawing::Point(81, 15);
			this->vessel_y->Name = L"vessel_y";
			this->vessel_y->Size = System::Drawing::Size(13, 13);
			this->vessel_y->TabIndex = 9;
			this->vessel_y->Text = L"0";
			this->vessel_y->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// vessel_x
			// 
			this->vessel_x->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->vessel_x->AutoSize = true;
			this->vessel_x->Location = System::Drawing::Point(81, 0);
			this->vessel_x->Name = L"vessel_x";
			this->vessel_x->Size = System::Drawing::Size(13, 13);
			this->vessel_x->TabIndex = 8;
			this->vessel_x->Text = L"0";
			this->vessel_x->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tableLayoutPanel21
			// 
			this->tableLayoutPanel21->ColumnCount = 1;
			this->tableLayoutPanel21->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel21->Controls->Add(this->label51, 0, 1);
			this->tableLayoutPanel21->Controls->Add(this->label52, 0, 0);
			this->tableLayoutPanel21->Location = System::Drawing::Point(224, 40);
			this->tableLayoutPanel21->Name = L"tableLayoutPanel21";
			this->tableLayoutPanel21->RowCount = 2;
			this->tableLayoutPanel21->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel21->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel21->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel21->Size = System::Drawing::Size(37, 29);
			this->tableLayoutPanel21->TabIndex = 13;
			// 
			// label51
			// 
			this->label51->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(7, 15);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(23, 13);
			this->label51->TabIndex = 9;
			this->label51->Text = L"mm";
			// 
			// label52
			// 
			this->label52->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(7, 0);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(23, 13);
			this->label52->TabIndex = 8;
			this->label52->Text = L"mm";
			// 
			// tableLayoutPanel22
			// 
			this->tableLayoutPanel22->ColumnCount = 1;
			this->tableLayoutPanel22->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel22->Controls->Add(this->label53, 0, 1);
			this->tableLayoutPanel22->Controls->Add(this->label54, 0, 0);
			this->tableLayoutPanel22->Location = System::Drawing::Point(99, 40);
			this->tableLayoutPanel22->Name = L"tableLayoutPanel22";
			this->tableLayoutPanel22->RowCount = 2;
			this->tableLayoutPanel22->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel22->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel22->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				22)));
			this->tableLayoutPanel22->Size = System::Drawing::Size(16, 29);
			this->tableLayoutPanel22->TabIndex = 14;
			// 
			// label53
			// 
			this->label53->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(3, 15);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(10, 13);
			this->label53->TabIndex = 9;
			this->label53->Text = L"y";
			// 
			// label54
			// 
			this->label54->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(3, 0);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(10, 13);
			this->label54->TabIndex = 8;
			this->label54->Text = L"x";
			// 
			// label55
			// 
			this->label55->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(9, 48);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(78, 13);
			this->label55->TabIndex = 15;
			this->label55->Text = L"Vessel Position";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(6, 264);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(94, 13);
			this->label56->TabIndex = 21;
			this->label56->Text = L"Offset angle [deg.]";
			this->label56->Click += gcnew System::EventHandler(this, &MainForm::label32_Click);
			// 
			// offset_angle_left
			// 
			this->offset_angle_left->Location = System::Drawing::Point(193, 261);
			this->offset_angle_left->Name = L"offset_angle_left";
			this->offset_angle_left->Size = System::Drawing::Size(76, 20);
			this->offset_angle_left->TabIndex = 30;
			this->offset_angle_left->Text = L"0";
			this->offset_angle_left->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// offset_angle_right
			// 
			this->offset_angle_right->Location = System::Drawing::Point(193, 288);
			this->offset_angle_right->Name = L"offset_angle_right";
			this->offset_angle_right->Size = System::Drawing::Size(76, 20);
			this->offset_angle_right->TabIndex = 31;
			this->offset_angle_right->Text = L"0";
			this->offset_angle_right->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(130, 264);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(48, 13);
			this->label57->TabIndex = 32;
			this->label57->Text = L"theta left";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(130, 291);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(54, 13);
			this->label58->TabIndex = 33;
			this->label58->Text = L"theta right";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->interval);
			this->groupBox6->Controls->Add(this->label76);
			this->groupBox6->Controls->Add(this->label75);
			this->groupBox6->Controls->Add(this->output_dir);
			this->groupBox6->Controls->Add(this->output_dir_browse);
			this->groupBox6->Controls->Add(this->label74);
			this->groupBox6->Controls->Add(this->dir_box);
			this->groupBox6->Controls->Add(this->label58);
			this->groupBox6->Controls->Add(this->dir_browse);
			this->groupBox6->Controls->Add(this->label42);
			this->groupBox6->Controls->Add(this->label20);
			this->groupBox6->Controls->Add(this->label57);
			this->groupBox6->Controls->Add(this->label1);
			this->groupBox6->Controls->Add(this->f_distanceBetweenTargets);
			this->groupBox6->Controls->Add(this->label43);
			this->groupBox6->Controls->Add(this->label21);
			this->groupBox6->Controls->Add(this->offset_angle_right);
			this->groupBox6->Controls->Add(this->f_distanceBetweenSystems);
			this->groupBox6->Controls->Add(this->textBox5);
			this->groupBox6->Controls->Add(this->label30);
			this->groupBox6->Controls->Add(this->offset_angle_left);
			this->groupBox6->Controls->Add(this->label31);
			this->groupBox6->Controls->Add(this->textBox6);
			this->groupBox6->Controls->Add(this->label32);
			this->groupBox6->Controls->Add(this->label40);
			this->groupBox6->Controls->Add(this->label56);
			this->groupBox6->Controls->Add(this->label41);
			this->groupBox6->Controls->Add(this->inst_pos_x);
			this->groupBox6->Controls->Add(this->shift_pos_y);
			this->groupBox6->Controls->Add(this->inst_pos_y);
			this->groupBox6->Controls->Add(this->shift_pos_x);
			this->groupBox6->Controls->Add(this->label33);
			this->groupBox6->Controls->Add(this->label39);
			this->groupBox6->Location = System::Drawing::Point(12, 13);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(277, 324);
			this->groupBox6->TabIndex = 34;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Parameters";
			// 
			// interval
			// 
			this->interval->Location = System::Drawing::Point(203, 16);
			this->interval->Name = L"interval";
			this->interval->Size = System::Drawing::Size(66, 20);
			this->interval->TabIndex = 39;
			this->interval->Text = L"30";
			this->interval->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Location = System::Drawing::Point(47, 20);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(128, 13);
			this->label76->TabIndex = 38;
			this->label76->Text = L"Interval time [ms]   ( > 10 )";
			this->label76->Click += gcnew System::EventHandler(this, &MainForm::label76_Click);
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->Location = System::Drawing::Point(9, 103);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(39, 13);
			this->label75->TabIndex = 37;
			this->label75->Text = L"Output";
			// 
			// output_dir
			// 
			this->output_dir->Location = System::Drawing::Point(51, 100);
			this->output_dir->Name = L"output_dir";
			this->output_dir->Size = System::Drawing::Size(161, 20);
			this->output_dir->TabIndex = 35;
			this->output_dir->Text = L"C:\\share";
			// 
			// output_dir_browse
			// 
			this->output_dir_browse->Location = System::Drawing::Point(215, 99);
			this->output_dir_browse->Name = L"output_dir_browse";
			this->output_dir_browse->Size = System::Drawing::Size(54, 22);
			this->output_dir_browse->TabIndex = 36;
			this->output_dir_browse->Text = L"browse";
			this->output_dir_browse->UseVisualStyleBackColor = true;
			this->output_dir_browse->Click += gcnew System::EventHandler(this, &MainForm::output_dir_browse_Click);
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->Location = System::Drawing::Point(9, 76);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(31, 13);
			this->label74->TabIndex = 34;
			this->label74->Text = L"Input";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 420);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->stop_button);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->savefilename_box);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MainForm";
			this->Text = L"Mesurement Result";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			this->tableLayoutPanel10->ResumeLayout(false);
			this->tableLayoutPanel10->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tableLayoutPanel11->ResumeLayout(false);
			this->tableLayoutPanel11->PerformLayout();
			this->tableLayoutPanel12->ResumeLayout(false);
			this->tableLayoutPanel12->PerformLayout();
			this->tableLayoutPanel13->ResumeLayout(false);
			this->tableLayoutPanel13->PerformLayout();
			this->tableLayoutPanel14->ResumeLayout(false);
			this->tableLayoutPanel14->PerformLayout();
			this->tableLayoutPanel15->ResumeLayout(false);
			this->tableLayoutPanel15->PerformLayout();
			this->tableLayoutPanel16->ResumeLayout(false);
			this->tableLayoutPanel16->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->tableLayoutPanel23->ResumeLayout(false);
			this->tableLayoutPanel23->PerformLayout();
			this->tableLayoutPanel24->ResumeLayout(false);
			this->tableLayoutPanel24->PerformLayout();
			this->tableLayoutPanel25->ResumeLayout(false);
			this->tableLayoutPanel25->PerformLayout();
			this->tableLayoutPanel26->ResumeLayout(false);
			this->tableLayoutPanel26->PerformLayout();
			this->tableLayoutPanel27->ResumeLayout(false);
			this->tableLayoutPanel27->PerformLayout();
			this->tableLayoutPanel28->ResumeLayout(false);
			this->tableLayoutPanel28->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->tableLayoutPanel17->ResumeLayout(false);
			this->tableLayoutPanel17->PerformLayout();
			this->tableLayoutPanel18->ResumeLayout(false);
			this->tableLayoutPanel18->PerformLayout();
			this->tableLayoutPanel19->ResumeLayout(false);
			this->tableLayoutPanel19->PerformLayout();
			this->tableLayoutPanel20->ResumeLayout(false);
			this->tableLayoutPanel20->PerformLayout();
			this->tableLayoutPanel21->ResumeLayout(false);
			this->tableLayoutPanel21->PerformLayout();
			this->tableLayoutPanel22->ResumeLayout(false);
			this->tableLayoutPanel22->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label19_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void readData(String ^ab,String ^%distance,String ^%pan_angle){
			 String ^dir = this->dir_box->Text;
			 String ^file = dir + "\\" + ab;
			 StreamReader ^sr;
			 try{
				 FileStream ^fs = gcnew FileStream(file, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
				 sr = gcnew StreamReader(fs);
			 }
			 catch (FileNotFoundException ^ex)
			 {
				 std::cout << "FileNotFoundException" << std::endl;
				 return;
			 }
			 catch (DirectoryNotFoundException ^ex)
			 {
				 std::cout << "FileNotFoundException" << std::endl;
				 return;
			 }
			 if (ab == "L"){
				 distance = sr->ReadLine();
				 if (!distance) return;
				 //Console::WriteLine(distance);
				 distance_L = Convert::ToDouble(distance);
				 this->a_dist->Text = String::Format("{0:#0.00}", distance_L);
				 pan_angle = sr->ReadLine();
				 String ^get_t = sr->ReadLine();
				 pan_angle_L = Convert::ToDouble(pan_angle);
				 double tilt_rad = Convert::ToDouble(get_t);
				 this->a_pan_rad->Text = String::Format("{0:#0.0000}", pan_angle_L);
				 this->a_tilt_rad->Text = String::Format("{0:#0.0000}", tilt_rad);
				 this->a_pan_deg->Text = String::Format("{0:#0.0000}", pan_angle_L*180.0 / M_PI);
				 this->a_tilt_deg->Text = String::Format("{0:#0.0000}", tilt_rad*180.0 / M_PI);
			 }
			 else if (ab == "R"){
				 distance = sr->ReadLine();
				 if (!distance) return;
				 distance_R = Convert::ToDouble(distance);
				 this->b_dist->Text = String::Format("{0:#0.00}", distance_R);
				 pan_angle = sr->ReadLine();
				 String ^get_t = sr->ReadLine();
				 pan_angle_R = Convert::ToDouble(pan_angle);
				 double tilt_rad = Convert::ToDouble(get_t);
				 this->b_pan_rad->Text = String::Format("{0:#0.0000}", pan_angle_R);
				 this->b_tilt_rad->Text = String::Format("{0:#0.0000}", tilt_rad);
				 this->b_pan_deg->Text = String::Format("{0:#0.0000}", pan_angle_R*180.0 / M_PI);
				 this->b_tilt_deg->Text = String::Format("{0:#0.0000}", tilt_rad*180.0 / M_PI);

			 }
			 sr->Close();
}
private: double pan_angle_L;
private: double pan_angle_R;
private: double distance_L;
private: double distance_R;
private: double fiducial_pan_angle_L;
private: double fiducial_pan_angle_R;
private: double fiducial_distance_L;
private: double fiducial_distance_R;
private: clock_t start, stamp;
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 String ^dist_L, ^dist_R, ^pan_L, ^pan_R;
			 double ca, cx, cy, ba=0, bx=0, by=0;
			 this->readData("L", dist_L, pan_L);
			 this->readData("R", dist_R, pan_R);
			 //this->vessel_pose_view(ca, cx, cy, ba, bx, by);
			 //this->vessel_pose_view2(ca, cx, cy);
			 this->vessel_pose_view3(ca, cx, cy);
			 this->stamp = clock();
			 if (this->save_flag){
				 sw->WriteLine("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10}", this->stamp - this->start, dist_L, pan_L, dist_R, pan_R, ca, cx, cy, ba, bx, by);
			 }
			 //this->outTimeFile(this->stamp - this->start);
			 this->outputToController(this->output_dir->Text);
			 try{
				 if (Convert::ToInt32(this->interval->Text) > 10) this->timer1->Interval = Convert::ToInt32(this->interval->Text);
			 }
			 catch (FormatException ^ex){
			 }
}
private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}
private: void outTimeFile(long time);
private: System::Void dir_browse_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
			 {
				 this->dir_box->Text = folderBrowserDialog1->SelectedPath;
			 }
}
private: StreamWriter ^sw;
private: bool save_flag;
private: System::Void save_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->save_flag) return;
			 String ^filename = "save_files\\" + this->savefilename_box->Text + ".csv";
			 try{
				sw = gcnew StreamWriter(filename);
			 }
			 catch (FileNotFoundException ^ex)
			 {
				 this->toolStripStatusLabel2->Text = String::Format("File not found file \"{0}\"", this->savefilename_box->Text);
				 this->save_flag = false;
				 return;
			 }
			 catch (UnauthorizedAccessException ^ex)
			 {
				 this->toolStripStatusLabel2->Text = String::Format("Can not open file \"{0}\"", this->savefilename_box->Text);
				 this->save_flag = false;
				 return;
			 }
			 catch (DirectoryNotFoundException ^ex)
			 {
				 this->toolStripStatusLabel2->Text = String::Format("Directory not found \"{0}\"", this->savefilename_box->Text);
				 this->save_flag = false;
				 return;
			 }
			 catch (FileLoadException ^ex)
			 {
				 this->toolStripStatusLabel2->Text = String::Format("Can not load file \"{0}\"", this->savefilename_box->Text);
				 this->save_flag = false;
				 return;
			 }
			 catch (IOException ^ex)
			 {
				 this->toolStripStatusLabel2->Text = String::Format("File open error \"{0}\"", this->savefilename_box->Text);
				 this->save_flag = false;
				 return;
			 }
			 this->start = clock();
			 this->toolStripStatusLabel2->Text = String::Format("Saving file \"{0}\"", this->savefilename_box->Text);
			 this->save_flag = true;
}
private: System::Void stop_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->save_flag){
				 sw->Close();
				 this->toolStripStatusLabel2->Text = String::Format("Stop saving file");
			 }
			 this->save_flag = false;
}
private: System::Void vessel_pose_view(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y, double &relative_angle, double &relative_x, double &relative_y);
private: System::Void vessel_pose_view2(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y);
private: System::Void vessel_pose_view3(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y);
private: System::Void groupBox4_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: bool Flag_UseFiducialPoint;
private: System::Void set_stay_button_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->fiducial_distance_L = this->distance_L;
			 this->fiducial_pan_angle_L = this->pan_angle_L;
			 this->fiducial_distance_R = this->distance_R;
			 this->fiducial_pan_angle_R = this->pan_angle_R;
			 this->Flag_UseFiducialPoint = true;
}
private: System::Void readConfigFile(System::String ^filename){
			 StreamReader ^sr;
			 try{
				 sr = gcnew StreamReader(filename);
			 }
			 catch (FileNotFoundException ^ex){
				 return;
			 }
			 int i = 0;
			 while (sr->Peek() > -1){
				 i++;
				 if (i == 1){ this->interval->Text = sr->ReadLine(); }
				 else if (i == 2){ this->dir_box->Text = sr->ReadLine(); }
				 else if (i == 3){ this->output_dir->Text = sr->ReadLine(); }
				 else if (i == 4){ this->f_distanceBetweenTargets->Text = sr->ReadLine(); }
				 else if (i == 5){ this->f_distanceBetweenSystems->Text = sr->ReadLine(); }
				 else if (i == 6){ this->inst_pos_x->Text = sr->ReadLine(); }
				 else if (i == 7){ this->inst_pos_y->Text = sr->ReadLine(); }
				 else if (i == 8){ this->shift_pos_x->Text = sr->ReadLine(); }
				 else if (i == 9){ this->shift_pos_y->Text = sr->ReadLine(); }
				 else if (i == 10){ this->offset_angle_left->Text = sr->ReadLine(); }
				 else if (i == 11){ this->offset_angle_right->Text = sr->ReadLine(); }
			 }
			 sr->Close();
}
private: System::Void saveConfigFile(System::String ^filename){
			 StreamWriter ^sw;
			 try{
				 sw = gcnew StreamWriter(filename);
			 }
			 catch (FileNotFoundException ^ex)
			 {
				 return;
			 }
			 sw->WriteLine(this->interval->Text);
			 sw->WriteLine(this->dir_box->Text);
			 sw->WriteLine(this->output_dir->Text);
			 sw->WriteLine(this->f_distanceBetweenTargets->Text);
			 sw->WriteLine(this->f_distanceBetweenSystems->Text);
			 sw->WriteLine(this->inst_pos_x->Text);
			 sw->WriteLine(this->inst_pos_y->Text);
			 sw->WriteLine(this->shift_pos_x->Text);
			 sw->WriteLine(this->shift_pos_y->Text);
			 sw->WriteLine(this->offset_angle_left->Text);
			 sw->WriteLine(this->offset_angle_right->Text);
			 sw->Close();
}
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 saveConfigFile(CONFIG_FILENAME);
}
private: System::Void label32_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void outputToController(System::String ^filename){
			 std::string filestring = this->ToStdString(filename);
			 filestring += "\\Measure.dat";
			 std::ofstream out(filestring);
			 if (out.fail()) return;
			 out << this->ToStdString(this->vessel_pos_x->Text) << std::endl;
			 out << this->ToStdString(this->vessel_pos_y->Text) << std::endl;
			 out << this->ToStdString(this->vessel_angle_rad->Text) << std::endl;
			 out.close();
}

private: System::Void output_dir_browse_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
			 {
				 this->output_dir->Text = folderBrowserDialog1->SelectedPath;
			 }
}
private: System::Void label76_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
