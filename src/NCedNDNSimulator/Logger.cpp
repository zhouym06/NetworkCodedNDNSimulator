
#include "Logger.h"
#include "NullStream.h"

char path[PATH_LEN];
const char* pathRoot = "d:/NDNlog/";
const char* fileName = "test.txt";

bool Logger::configured = false;
ofstream Logger::ofs;
NullStream Logger::nfs;
int Logger::log_level = LOGGER_INFO;
int Logger::current_log_level = LOGGER_INFO;

void Logger::Configure(const char* fName, int lLevel)
{
	log_level = lLevel;
	current_log_level = LOGGER_INFO;
	memset(path,0, PATH_LEN);
	strcpy(path,pathRoot);
	strcat(path,fName);
	if(configured)
		ofs.close();
	ofs.open(path);
	configured = true;
}


ostream& Logger::Log()
{
	if(!configured)
	{
		log_level = LOGGER_INFO;
		current_log_level = LOGGER_DEBUG;
		memset(path,0, PATH_LEN);
		strcpy(path,pathRoot);
		strcat(path,fileName);
		ofs.open(path);
		configured = true;
	}
	if(log_level == LOGGER_ERROR)
	{
		ofs << "ERROR! ";
	}
	
	if(current_log_level < log_level)
		return nfs;
	else
		return ofs;
}

bool Logger::Exist(const char* fName)
{
	char full_path[PATH_LEN];
	memset(full_path,0, PATH_LEN);
	strcpy(full_path,pathRoot);
	strcat(full_path,fName);
	ifstream fin(full_path);
	if (!fin)
	{
		return false;
	}
	return true;
}


ostream& Logger::Log(int level)
{
	if(!configured)
	{
		log_level = LOGGER_INFO;
		current_log_level = LOGGER_DEBUG;
		memset(path,0, PATH_LEN);
		strcpy(path,pathRoot);
		strcat(path,fileName);
		ofs.open(path);
		configured = true;
	}
	current_log_level = level;
	return Log();
}

