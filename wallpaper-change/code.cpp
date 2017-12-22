#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>

using namespace std;

int main(int argc, char *args[])
{

	if (argc < 4)
	{
		cerr << "Usage:\n";
		cerr << "\t " << args[0] << " directory extension noOfWallpapers\n";
		return 1;
	}

	srand(time(NULL));

	int noOfWallpapers = atoi(args[3]);
	int chosenWallpaper = rand() % noOfWallpapers;
	char dir[100];
	strcpy(dir, args[1]);
	char extension[5];
	strcpy(extension, args[2]);

	char command[200];
	sprintf(command, "gsettings set org.gnome.desktop.background picture-uri \"file:///%s/%d.%s\"", dir, chosenWallpaper, extension);

	cout << command << endl;
	system(command);
	return 0;
}
