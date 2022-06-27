#include <iostream>
#include "Logger.h"
#include <string>
#include <ctime>
#include <sstream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

int main(int argc, char** argv) {
	
	time_t now = time(0);
   	char* dt = ctime(&now);

	Logger log;
	log.Trace("Trace test demo",dt);
	log.Debug("Debug test demo",dt);
	log.Info("Info test demo",dt);
	log.Warn("Warn test demo",dt);
	log.Error("Error test demo",dt);
	

	return 0;
}
