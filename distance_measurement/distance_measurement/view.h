#include "global.h"
#include "vcc.h"
#define VIEW_DROW_RECTANGLE_THICKNESS 1

class View{
public:
	View(std::string windowName, int windowPlace_x, int windowPlace_y);
	~View();
	void show(cv::Mat image, int ditectionPoint_x, int ditectionPoint_y, bool isColor = false);
	static void onMouse(int event, int x, int y, int flags, void* param);

private:
	std::string myWindowName;
};