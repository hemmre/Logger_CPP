#include "Logger.h"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <dirent.h>
#include<vector>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
Logger::Logger()
{
	//G�ncel tarih ve zaman� al�p log yap�lcak text dosyas�n�n ismi i�in haz�rlanmas�
	time_t t = time(0);   
    struct tm * now = localtime( & t );
    char temp_date [80]; 
	strftime (temp_date,80,"%y-%m-%d.txt",now);
    file_out.open(temp_date, std::ios_base::app);
    
    //json dosyas�ndan bilgi okuma ve set get operasyonlar�
    json jsonfile;
    std::ifstream file("config.json");
    file >> jsonfile;
    setNumber_of_logs(jsonfile["number_of_logs"]);
    setLog_frequency(jsonfile["log_frequency"]);
    cout<<"Number of logs preferred "<<getNumber_of_logs()<<" and log frequency is "<<getLog_frequency()<<endl;
    
    //G�ncel klas�redeki dosya adllar�n� ve txt. uzant�l� dosya adlar�n� tutan vekt�rler
    vector<string> files;
    vector<string> text_files;
    
    //Files vekt�r�ne dosya adlar�n�n at�lmas�
    DIR *dir = opendir("."); // current dir
	struct dirent *dirent;
	while ((dirent = readdir(dir)) != NULL) 
	{
		files.push_back(dirent->d_name);
	}
	closedir(dir);
	
	//Files vekt�r�ndeki .txt uzant�l� dosya adlar�n�n text_files vekt�r�ne at�lmas�
	int i =0;
	string searchString=".txt";
	for(std::string& txt_extension  : files)
	{
  		if(txt_extension.find(searchString) != std::string::npos)
  		{
     		i++;
     		cout<<txt_extension<<endl;
     		text_files.push_back(txt_extension);
     		printf("size: %u\n", text_files.size());
  		}
	}
	
	//Dosya say�s� belirlenen say�dan fazla ise ilk log dosyas�n�n silinmesi
	string first_log = text_files.front();
	if(text_files.size()==getNumber_of_logs())
	{
		const char *c =first_log.c_str();
		if( remove( c ) != 0 )
    		perror( "Error deleting file" );
  		else
   			puts( "File successfully deleted" );
	}
}
void Logger::Trace(string message,char* time)
{
	cout<<"[Trace]\t--"<<message<<"--\t"<<time;
	file_out<<"[Trace]\t--"<<message<<"--\t"<<time;
}
void Logger::Debug(string message,char* time)
{
	cout<<"[Debug]\t--"<<message<<"--\t"<<time;
	file_out<<"[Debug]\t--"<<message<<"--\t"<<time;
}
void Logger::Info(string message,char* time)
{
	cout<<"[Info]\t--"<<message<<"--\t"<<time;
	file_out<<"[Info]\t--"<<message<<"--\t"<<time;
}
void Logger::Warn(string message,char* time)
{
	cout<<"[Warn]\t--"<<message<<"--\t"<<time;
	file_out<<"[Warn]\t--"<<message<<"--\t"<<time;
}
void Logger::Error(string message,char* time)
{
	cout<<"[Error]\t--"<<message<<"--\t"<<time;
	file_out<<"[Error]\t--"<<message<<"--\t"<<time;
}
void Logger::setNumber_of_logs(int a)
{
	number_of_logs=a;
}
void Logger::setLog_frequency(int a)
{
	log_frequency=a;
}
int Logger::getNumber_of_logs(void)
{
	return number_of_logs;
}
int Logger::getLog_frequency(void)
{
	return log_frequency;
}
Logger::~Logger()
{
	file_out.close();
}

