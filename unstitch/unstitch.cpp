#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

using namespace std;

enum
{
	NO_ERROR,
	ERROR_ARGS,
	ERROR_COULDNOTOPENSTFILE
};

void split(char *source, char dest[][80], int fields, char s = ':')
{
	int k = 0;
	int i = 0;
	while(*source && k < fields && i < 80)
	{
		if (s != *source)
			dest[k][i++] = *source;
		else
		{
			dest[k++][i] = 0;
			i = 0 ;
		}
		source ++;
	}
	if (!(*source)) dest[k][i] = 0;
}

int main(int argc, char *args[])
{
	char stitched_file[80];
	if (argc < 2)
	{
		cerr << "Not enough arguments!\n";
		cerr << "Usage:\n\t";
		cerr << args[0] << " stitched_file\n";
		return ERROR_ARGS;
	}
	else
	{
		strcpy(stitched_file, args[1]);
		ifstream fin;
		fstream fout;
		fin.open(stitched_file);

		if (!fin)
		{
			cerr << "Error: could not open " << stitched_file << endl;
			return ERROR_COULDNOTOPENSTFILE;
		}
		cout << stitched_file << endl;

		char header[80];
		/*	char filedet[3][80];
				fin.read(header,80);
				split(header, filedet, 3, ':');
				cout << filedet[0] << endl;
				cout << filedet[1] << endl;
				cout << atoi(filedet[2]) << endl;*/
		while(fin.read(header,80))
		{
			char filedet[3][80];
			split(header, filedet, 3, ':');
			cout << "Unstitching: " << filedet[1] << endl;
			if (strcmp(filedet[0], "stitch"))
			{
				cerr << "Error:illegal stitched file " << stitched_file << endl;
				break;
			}
			//fout.open(filedet[1]);
			fout.open("file");
			for(int i = 0 ; i < atoi(filedet[2]); i++)
			{
				char c;
				fin.get(c);
				fout.put(c);
			}
			fout.close();
			cout << filedet[2] << " bytes written to " << filedet[1]<< endl;
		}
	}
	return NO_ERROR;
}
