
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "NullStream.h"
#include <iostream>
#include <fstream>
using namespace std;

#define LOGGER_VERY_DETAIL	0
#define LOGGER_DETAIL		10
#define LOGGER_ROUTER		15
#define LOGGER_DEBUG		20
#define LOGGER_INFO			30
#define LOGGER_WARNING		40
#define LOGGER_ERROR		50
#define LOGGER_NONE			100


#define PATH_LEN 120




class Logger{
	static bool			configured;
	static ofstream		ofs;
	static NullStream	nfs;
	static int			log_level;
	static int			current_log_level;
public:
	Logger();
	~Logger();

	static void Configure(const char* fName, int lLevel);
	static bool Exist(const char* fName);

	static ostream& Log();
	static ostream& Log(int);
};

#endif
