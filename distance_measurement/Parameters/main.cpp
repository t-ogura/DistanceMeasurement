#include "ParamShow.h"


using namespace Parameters;

int main(){
	ParamShow ^ps = gcnew ParamShow();
	ps->ShowDialog();
	return 0;
}