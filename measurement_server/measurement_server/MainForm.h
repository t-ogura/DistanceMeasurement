#define _USE_MATH_DEFINES
#include <math.h>

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
			//
			//TODO: ここにコンストラクター コードを追加します
			//
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
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  savefilename_box;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::Button^  save_button;
	private: System::Windows::Forms::Button^  stop_button;


	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
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
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->savefilename_box = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->tableLayoutPanel10->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Data File Directory";
			// 
			// dir_box
			// 
			this->dir_box->Location = System::Drawing::Point(13, 29);
			this->dir_box->Name = L"dir_box";
			this->dir_box->Size = System::Drawing::Size(216, 19);
			this->dir_box->TabIndex = 1;
			// 
			// dir_browse
			// 
			this->dir_browse->Location = System::Drawing::Point(235, 28);
			this->dir_browse->Name = L"dir_browse";
			this->dir_browse->Size = System::Drawing::Size(54, 20);
			this->dir_browse->TabIndex = 2;
			this->dir_browse->Text = L"browse";
			this->dir_browse->UseVisualStyleBackColor = true;
			this->dir_browse->Click += gcnew System::EventHandler(this, &MainForm::dir_browse_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tableLayoutPanel1);
			this->groupBox1->Location = System::Drawing::Point(12, 105);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(277, 122);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"A";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				41.2844F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				58.7156F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				48)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(7, 19);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(264, 97);
			this->tableLayoutPanel1->TabIndex = 2;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->Controls->Add(this->label19, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(218, 3);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(37, 13);
			this->tableLayoutPanel4->TabIndex = 10;
			// 
			// label19
			// 
			this->label19->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(7, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(23, 12);
			this->label19->TabIndex = 8;
			this->label19->Text = L"mm";
			this->label19->Click += gcnew System::EventHandler(this, &MainForm::label19_Click);
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
			this->tableLayoutPanel3->Location = System::Drawing::Point(218, 22);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 4;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(37, 72);
			this->tableLayoutPanel3->TabIndex = 9;
			// 
			// label10
			// 
			this->label10->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(7, 21);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(23, 12);
			this->label10->TabIndex = 9;
			this->label10->Text = L"rad.";
			// 
			// label11
			// 
			this->label11->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(7, 3);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(23, 12);
			this->label11->TabIndex = 8;
			this->label11->Text = L"rad.";
			// 
			// label12
			// 
			this->label12->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 39);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(25, 12);
			this->label12->TabIndex = 10;
			this->label12->Text = L"deg.";
			// 
			// label13
			// 
			this->label13->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 57);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(25, 12);
			this->label13->TabIndex = 11;
			this->label13->Text = L"deg.";
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 52);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(81, 12);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Platform Angle";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(19, 3);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 12);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Distance";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25.78125F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				74.21875F)));
			this->tableLayoutPanel2->Controls->Add(this->a_tilt_deg, 1, 3);
			this->tableLayoutPanel2->Controls->Add(this->a_pan_deg, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->a_tilt_rad, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->a_pan_rad, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->label7, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->label6, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->label8, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->label9, 0, 3);
			this->tableLayoutPanel2->Location = System::Drawing::Point(92, 22);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 4;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(120, 72);
			this->tableLayoutPanel2->TabIndex = 8;
			// 
			// a_tilt_deg
			// 
			this->a_tilt_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_tilt_deg->AutoSize = true;
			this->a_tilt_deg->Location = System::Drawing::Point(106, 57);
			this->a_tilt_deg->Name = L"a_tilt_deg";
			this->a_tilt_deg->Size = System::Drawing::Size(11, 12);
			this->a_tilt_deg->TabIndex = 15;
			this->a_tilt_deg->Text = L"0";
			this->a_tilt_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// a_pan_deg
			// 
			this->a_pan_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_pan_deg->AutoSize = true;
			this->a_pan_deg->Location = System::Drawing::Point(106, 39);
			this->a_pan_deg->Name = L"a_pan_deg";
			this->a_pan_deg->Size = System::Drawing::Size(11, 12);
			this->a_pan_deg->TabIndex = 14;
			this->a_pan_deg->Text = L"0";
			this->a_pan_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// a_tilt_rad
			// 
			this->a_tilt_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_tilt_rad->AutoSize = true;
			this->a_tilt_rad->Location = System::Drawing::Point(106, 21);
			this->a_tilt_rad->Name = L"a_tilt_rad";
			this->a_tilt_rad->Size = System::Drawing::Size(11, 12);
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
			this->a_pan_rad->Size = System::Drawing::Size(11, 12);
			this->a_pan_rad->TabIndex = 12;
			this->a_pan_rad->Text = L"0";
			this->a_pan_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label7
			// 
			this->label7->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(4, 21);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(22, 12);
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
			this->label6->Size = System::Drawing::Size(24, 12);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Pan";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// label8
			// 
			this->label8->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 39);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(24, 12);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Pan";
			this->label8->Click += gcnew System::EventHandler(this, &MainForm::label8_Click);
			// 
			// label9
			// 
			this->label9->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(4, 57);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(22, 12);
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
			this->tableLayoutPanel5->Size = System::Drawing::Size(120, 12);
			this->tableLayoutPanel5->TabIndex = 11;
			// 
			// a_dist
			// 
			this->a_dist->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->a_dist->AutoSize = true;
			this->a_dist->Location = System::Drawing::Point(106, 0);
			this->a_dist->Name = L"a_dist";
			this->a_dist->Size = System::Drawing::Size(11, 12);
			this->a_dist->TabIndex = 1;
			this->a_dist->Text = L"0";
			this->a_dist->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->tableLayoutPanel6);
			this->groupBox2->Location = System::Drawing::Point(13, 233);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(277, 122);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"B";
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 3;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40.36697F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				59.63303F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				48)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 2, 0);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 2, 1);
			this->tableLayoutPanel6->Controls->Add(this->label17, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->label18, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel9, 1, 1);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel10, 1, 0);
			this->tableLayoutPanel6->Location = System::Drawing::Point(7, 19);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(264, 97);
			this->tableLayoutPanel6->TabIndex = 2;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 1;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel7->Controls->Add(this->label3, 0, 0);
			this->tableLayoutPanel7->Location = System::Drawing::Point(218, 3);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 1;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(37, 13);
			this->tableLayoutPanel7->TabIndex = 10;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(23, 12);
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
			this->tableLayoutPanel8->Location = System::Drawing::Point(218, 22);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 4;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(37, 72);
			this->tableLayoutPanel8->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(7, 21);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(23, 12);
			this->label5->TabIndex = 9;
			this->label5->Text = L"rad.";
			// 
			// label14
			// 
			this->label14->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(7, 3);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(23, 12);
			this->label14->TabIndex = 8;
			this->label14->Text = L"rad.";
			// 
			// label15
			// 
			this->label15->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 39);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(25, 12);
			this->label15->TabIndex = 10;
			this->label15->Text = L"deg.";
			// 
			// label16
			// 
			this->label16->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 57);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(25, 12);
			this->label16->TabIndex = 11;
			this->label16->Text = L"deg.";
			// 
			// label17
			// 
			this->label17->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(3, 52);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(81, 12);
			this->label17->TabIndex = 6;
			this->label17->Text = L"Platform Angle";
			// 
			// label18
			// 
			this->label18->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(18, 3);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(50, 12);
			this->label18->TabIndex = 0;
			this->label18->Text = L"Distance";
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25.78125F)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				74.21875F)));
			this->tableLayoutPanel9->Controls->Add(this->b_tilt_deg, 1, 3);
			this->tableLayoutPanel9->Controls->Add(this->b_pan_deg, 1, 2);
			this->tableLayoutPanel9->Controls->Add(this->b_tilt_rad, 1, 1);
			this->tableLayoutPanel9->Controls->Add(this->b_pan_rad, 1, 0);
			this->tableLayoutPanel9->Controls->Add(this->label24, 0, 1);
			this->tableLayoutPanel9->Controls->Add(this->label25, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->label26, 0, 2);
			this->tableLayoutPanel9->Controls->Add(this->label27, 0, 3);
			this->tableLayoutPanel9->Location = System::Drawing::Point(90, 22);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 4;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(122, 72);
			this->tableLayoutPanel9->TabIndex = 8;
			// 
			// b_tilt_deg
			// 
			this->b_tilt_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_tilt_deg->AutoSize = true;
			this->b_tilt_deg->Location = System::Drawing::Point(108, 57);
			this->b_tilt_deg->Name = L"b_tilt_deg";
			this->b_tilt_deg->Size = System::Drawing::Size(11, 12);
			this->b_tilt_deg->TabIndex = 15;
			this->b_tilt_deg->Text = L"0";
			this->b_tilt_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_pan_deg
			// 
			this->b_pan_deg->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_pan_deg->AutoSize = true;
			this->b_pan_deg->Location = System::Drawing::Point(108, 39);
			this->b_pan_deg->Name = L"b_pan_deg";
			this->b_pan_deg->Size = System::Drawing::Size(11, 12);
			this->b_pan_deg->TabIndex = 14;
			this->b_pan_deg->Text = L"0";
			this->b_pan_deg->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_tilt_rad
			// 
			this->b_tilt_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_tilt_rad->AutoSize = true;
			this->b_tilt_rad->Location = System::Drawing::Point(108, 21);
			this->b_tilt_rad->Name = L"b_tilt_rad";
			this->b_tilt_rad->Size = System::Drawing::Size(11, 12);
			this->b_tilt_rad->TabIndex = 13;
			this->b_tilt_rad->Text = L"0";
			this->b_tilt_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// b_pan_rad
			// 
			this->b_pan_rad->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_pan_rad->AutoSize = true;
			this->b_pan_rad->Location = System::Drawing::Point(108, 3);
			this->b_pan_rad->Name = L"b_pan_rad";
			this->b_pan_rad->Size = System::Drawing::Size(11, 12);
			this->b_pan_rad->TabIndex = 12;
			this->b_pan_rad->Text = L"0";
			this->b_pan_rad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label24
			// 
			this->label24->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(4, 21);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(22, 12);
			this->label24->TabIndex = 9;
			this->label24->Text = L"Tilt";
			// 
			// label25
			// 
			this->label25->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(3, 3);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(24, 12);
			this->label25->TabIndex = 8;
			this->label25->Text = L"Pan";
			// 
			// label26
			// 
			this->label26->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(3, 39);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(24, 12);
			this->label26->TabIndex = 10;
			this->label26->Text = L"Pan";
			// 
			// label27
			// 
			this->label27->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(4, 57);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(22, 12);
			this->label27->TabIndex = 11;
			this->label27->Text = L"Tilt";
			// 
			// tableLayoutPanel10
			// 
			this->tableLayoutPanel10->ColumnCount = 1;
			this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel10->Controls->Add(this->b_dist, 0, 0);
			this->tableLayoutPanel10->Location = System::Drawing::Point(90, 3);
			this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
			this->tableLayoutPanel10->RowCount = 1;
			this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel10->Size = System::Drawing::Size(122, 12);
			this->tableLayoutPanel10->TabIndex = 11;
			// 
			// b_dist
			// 
			this->b_dist->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->b_dist->AutoSize = true;
			this->b_dist->Location = System::Drawing::Point(108, 0);
			this->b_dist->Name = L"b_dist";
			this->b_dist->Size = System::Drawing::Size(11, 12);
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
			this->label20->Location = System::Drawing::Point(12, 58);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(139, 12);
			this->label20->TabIndex = 5;
			this->label20->Text = L"Distance between Targets";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(180, 55);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(109, 19);
			this->textBox1->TabIndex = 6;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(180, 80);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(109, 19);
			this->textBox2->TabIndex = 8;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(12, 83);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(149, 12);
			this->label21->TabIndex = 7;
			this->label21->Text = L"Distance between Measures";
			// 
			// savefilename_box
			// 
			this->savefilename_box->Location = System::Drawing::Point(102, 361);
			this->savefilename_box->Name = L"savefilename_box";
			this->savefilename_box->Size = System::Drawing::Size(94, 19);
			this->savefilename_box->TabIndex = 9;
			this->savefilename_box->Text = L"data01";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(10, 364);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(86, 12);
			this->label22->TabIndex = 10;
			this->label22->Text = L"Save File Name";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripStatusLabel1,
					this->toolStripStatusLabel2
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 386);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(304, 23);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 11;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 18);
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(12, 18);
			this->toolStripStatusLabel2->Text = L" ";
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(202, 361);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(41, 19);
			this->save_button->TabIndex = 12;
			this->save_button->Text = L"Save";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &MainForm::save_button_Click);
			// 
			// stop_button
			// 
			this->stop_button->Location = System::Drawing::Point(249, 361);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(43, 19);
			this->stop_button->TabIndex = 13;
			this->stop_button->Text = L"Stop";
			this->stop_button->UseVisualStyleBackColor = true;
			this->stop_button->Click += gcnew System::EventHandler(this, &MainForm::stop_button_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->menuStrip1->Size = System::Drawing::Size(304, 26);
			this->menuStrip1->TabIndex = 14;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadToolStripMenuItem,
					this->saveToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(40, 22);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(105, 22);
			this->loadToolStripMenuItem->Text = L"Load";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(105, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(304, 409);
			this->Controls->Add(this->stop_button);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->savefilename_box);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->dir_browse);
			this->Controls->Add(this->dir_box);
			this->Controls->Add(this->label1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Mesurement Result";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
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
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
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
				 sr = gcnew StreamReader(file);
			 }
			 catch (FileNotFoundException ^ex)
			 {
				 return;
			 }
			 if (ab == "A"){
				 distance = sr->ReadLine();
				 double d_dist = Convert::ToDouble(distance);
				 this->a_dist->Text = String::Format("{0:#0.00}", d_dist);
				 pan_angle = sr->ReadLine();
				 String ^get_t = sr->ReadLine();
				 double pan_rad = Convert::ToDouble(pan_angle);
				 double tilt_rad = Convert::ToDouble(get_t);
				 this->a_pan_rad->Text = String::Format("{0:#0.##########}", pan_rad);
				 this->a_tilt_rad->Text = String::Format("{0:#0.##########}", tilt_rad);
				 this->a_pan_deg->Text = String::Format("{0:#0.##########}", pan_rad*180.0 / M_PI);
				 this->a_tilt_deg->Text = String::Format("{0:#0.##########}", tilt_rad*180.0 / M_PI);
			 }
			 else if (ab == "B"){
				 distance = sr->ReadLine();
				 double d_dist = Convert::ToDouble(distance);
				 this->b_dist->Text = String::Format("{0:#0.00}", d_dist);
				 pan_angle = sr->ReadLine();
				 String ^get_t = sr->ReadLine();
				 double pan_rad = Convert::ToDouble(pan_angle);
				 double tilt_rad = Convert::ToDouble(get_t);
				 this->b_pan_rad->Text = String::Format("{0:#0.##########}", pan_rad);
				 this->b_tilt_rad->Text = String::Format("{0:#0.##########}", tilt_rad);
				 this->b_pan_deg->Text = String::Format("{0:#0.##########}", pan_rad*180.0 / M_PI);
				 this->b_tilt_deg->Text = String::Format("{0:#0.##########}", tilt_rad*180.0 / M_PI);

			 }
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 String ^ad, ^bd, ^ap, ^bp;
			 this->readData("A",ad,ap);
			 this->readData("B",bd,bp);
			 if (this->save_flag){
				 sw->WriteLine("{0},{1},{2},{3}", ad, ap, bd, bp);
			 }
}
private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}
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
			 String ^filename = "..\\save_files\\" + this->savefilename_box->Text + ".csv";
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
};
}
