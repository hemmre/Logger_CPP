#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Logger
{
	private:
		int number_of_logs;
		int log_frequency;
	public:
		Logger();
		~Logger();
		
		void Trace(string,char*);
		void Debug(string,char*);
		void Info(string,char*);
		void Warn(string,char*);
		void Error(string,char*);
		void setNumber_of_logs(int);
		void setLog_frequency(int);
		int getNumber_of_logs(void);
		int getLog_frequency(void);
		ofstream file_out;
		string file;

		
};

#endif
