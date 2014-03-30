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

System::Void ParallelOffsetTool::ApplyOfset(){
	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		ps->ofset->Text = this->ofset_box->Text;
		ps->linear_a->Text = this->linear_a->Text;
		ps->linear_b->Text = this->linear_b->Text;
		ps->ofset_check->Checked = true;
		ps->linear_flag->Checked = true;
	}
}