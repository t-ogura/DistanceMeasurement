#pragma once
#include <fstream>
#include <string>
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(121, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &ParamShow::label1_Click);
			this->label1->DoubleClick += gcnew System::EventHandler(this, &ParamShow::label1_DoubleClick);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &ParamShow::timer1_Tick);
			// 
			// ParamShow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 114);
			this->Controls->Add(this->label1);
			this->Name = L"ParamShow";
			this->Text = L"ParamShow";
			this->Load += gcnew System::EventHandler(this, &ParamShow::ParamShow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ParamShow_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::ifstream in(INFILE);
				 std::string str;
				 while (in && std::getline(in, str))
				 {
					 this->label1->Text = ToSystemString(str);
				 }
				 in.close();
	}
	private: System::Void label1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 std::ifstream in(INFILE);
				 std::string str;
				 while (in && std::getline(in, str))
				 {
					 //Threading::Mutex ^mtx = gcnew Threading::Mutex(false, "label1");
					 //if (mtx->WaitOne()){
						 this->label1->Text = ToSystemString(str);
					 //}
					 //mtx->ReleaseMutex();
				 }
				 in.close();
	}
};
}
