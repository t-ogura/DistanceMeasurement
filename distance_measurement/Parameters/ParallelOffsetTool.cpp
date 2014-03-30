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