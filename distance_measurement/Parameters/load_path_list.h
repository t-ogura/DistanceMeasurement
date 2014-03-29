#include <filesystem>
#include <vector>
#include <string>

using namespace std::tr2::sys;

bool loadPathList(std::string Dir, std::vector<std::string> *out_PathData, std::string extension)
{
	bool result = false;

	path parent_path(Dir);

	if (exists(parent_path))
	{
		for (directory_iterator itr(parent_path); itr != directory_iterator(); ++itr)
		{
			path p(*itr);
			std::string str = itr->path();
			if (std::string::npos != str.find(extension))
			{
				out_PathData->push_back(str);
			}
			else
			{
				continue;
			}
		}
		result = (bool)out_PathData->size();
	}
	return result;
}
