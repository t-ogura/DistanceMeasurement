#include "ParallelOffsetTool.h"
#include "ParamShow.h"

using namespace Parameters;

System::Void ParallelOffsetTool::get_distance_button_Click(System::Object^  sender, System::EventArgs^  e) {

	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		this->measure_vaule_box->Text = ps->label3->Text;
	}
}
System::Void ParallelOffsetTool::getBaseLength(){

	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		this->base_length->Text = ps->base_box->Text;
	}
}

System::Void ParallelOffsetTool::ApplyOffset(){
	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		ps->offset->Text = this->offset_box->Text;
		ps->linear_a->Text = this->linear_a->Text;
		ps->linear_b->Text = this->linear_b->Text;
		ps->offset_check->Checked = true;
		ps->linear_flag->Checked = true;
	}
}