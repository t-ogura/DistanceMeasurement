#include "MainForm.h"

using namespace measurement_server;

[STAThreadAttribute]
int main(){
	MainForm ^mf = gcnew MainForm();
	mf->ShowDialog();
	return 0;
}