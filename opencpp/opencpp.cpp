#include<fstream>
#include<string.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

int main(int argc, char *args[])
{
	system("cp ~/.dosbox/dosbox-0.74.conf ~/.dosbox/turboc++.conf");
	char filename[10];
	if (argc < 2)
	{
		cout << "Opening file noname00.cpp\n";
		strcpy(filename, "noname00");
	}
	else
		strcpy(filename, args[1]);

	strcat(filename, ".cpp");

	ofstream file("/home/shyam/.dosbox/turboc++.conf", ios::app);

	file << "mount c ~/Desktop\n";
	file << "c:\n";
	file << "cd TURBOC3\n";
	file << "cd BIN\n";
	file << "TC ";
	file.write(filename, strlen(filename));
	file.put('\n');
	file.close();

	
	system("dosbox -conf ~/.dosbox/turboc++.conf");
		
	return 0;
}
