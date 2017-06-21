 #include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <windows.h>
using namespace std;
#include "execute.h"

std::string nconvert(int i){
	std::ostringstream ss;
	ss << i;
	return ss.str();
}

int main(int argc, char *argv[])
{
	std::string xvarname=argv[1];
	std::string yvarname=argv[2];
	std::string basename=argv[3];
	int from=atoi(argv[4]);
	int to=atoi(argv[5]);
	std::string cmd="\"C:\\Program Files\\Python26\\python.exe\" plot.py --outfile gnup.p \""+xvarname+"\" \""+yvarname+"\"";
	for(int i=0;i<=to;++i)
	{
		cmd+=" ..\\results\\"+basename+"-"+nconvert(i)+".sca";
	}
	std::cout << cmd << std::endl;
	ExecuteProcessWait(cmd, ".");
	return 1;
}