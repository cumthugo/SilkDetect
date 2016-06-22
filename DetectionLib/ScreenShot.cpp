#include "ScreenShot.h"

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <boost/format.hpp>
#include <ctime>

using namespace boost::filesystem;


void SaveImageCount(const string& path, int count)
{
	ptree p;
	p.put("count",count);
	write_ini(path+"\\count.ini",p);
}

int GetImageCount(const string& path)
{
	ptree p;
	read_ini(path+"\\count.ini",p);
	try
	{
		int count = p.get<int>("count",-1);
		return count;
	}
	catch (...)
	{
		return -1;
	}	
}

void SaveImage(const string& filename, IplImage_Ptr img)
{
	cvSaveImage(filename.c_str(),img);
}


string FormatTimeOnlyNumber(time_t t)
{
	string str;
	time_t temp = t;
	struct tm local;;    
	localtime_s(&local,&temp);
	boost::format fmt("%4d%02d%02d%02d%02d%02d");
	fmt % (local.tm_year+1900) % (local.tm_mon+1) % local.tm_mday % local.tm_hour % local.tm_min % local.tm_sec;
	str = fmt.str() + ".jpg";
	return str;
}
string GetRandomName()
{
	string str;
	time_t temp = time(NULL);
	struct tm local;;    
	localtime_s(&local,&temp);
	boost::format fmt("%4d%02d%02d%02d%02d%02d_%03d");
	int rnd = rand()%1000;
	fmt % (local.tm_year+1900) % (local.tm_mon+1) % local.tm_mday % local.tm_hour % local.tm_min % local.tm_sec% rnd;
	str = fmt.str() + ".jpg";
	return str;
}

void ScreenShot::Save( const string& unitName, IplImage_Ptr img, shared_ptr<DetectionUnit> du )
{
	string unitPath = itsFolderPath + "\\" + unitName;
	try
	{
		if(processFolder(unitPath,du))
		{
			string fileName = GetRandomName();
			int imageCount = GetImageCount(unitPath);
			if(imageCount < itsMaxNumber)
			{
				SaveImage(unitPath + "\\" + fileName, img);
				SaveImageCount(unitPath,++imageCount);
			}
		}
	}
	catch (...)
	{
		// do nothing
	}	
}

bool ScreenShot::processFolder( const string& p ,shared_ptr<DetectionUnit> du)
{
	int imageCount;
	boost::system::error_code ec;
	if (!exists(path(p),ec))
	{
		create_directories(path(p));
		write_xml(p+ "\\param.xml",du->GetTree());
		SaveImageCount(p,0);
	}
	else
	{
		imageCount = GetImageCount(p);
		if (imageCount == -1)
		{			
			remove_all(path(p));
			create_directories(path(p));
			SaveImageCount(p,0);
		}
	}
	return exists(path(p),ec) && (GetImageCount(p) >= 0);
}
