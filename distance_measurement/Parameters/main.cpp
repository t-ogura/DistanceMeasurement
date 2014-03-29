#include "ParamShow.h"


using namespace Parameters;

[STAThreadAttribute]
int main(){
	ParamShow ^ps = gcnew ParamShow();
	ps->ShowDialog();
	return 0;
}