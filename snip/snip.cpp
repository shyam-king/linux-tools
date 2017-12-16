#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//FLAGS
#define HELP_FLAG 1u
#define SNIP_FRONT 2u
#define SNIP_BACK 4u
#define VERBOSE_FLAG 8u
#define LONGHELP_FLAG 16u

using namespace std;

enum {
	NO_ERROR,
	ERROR_ARGC,
	ERROR_SRC,
	ERROR_NOHELP
};

int main(int argc, char *args[])
{
	int nonflagargs = 2;
	unsigned int flags = 0;

	char filename[20]; //source file
	char tofilename[20]; //dest file

	char replaceChar = '\n';
	char replaceToChar = 0;

	int maxRepititions = 0;

	//parsing the arguments
	for (int i = 1; i < argc; i++)
	{
		if (args[i][0] != '-')
		{
			if (strcmp(args[i],"help") == 0)
			{
				flags |= HELP_FLAG;
			}
			else 
			{
				if (nonflagargs == 2)
				{
					strcpy(filename, args[i]);
					nonflagargs --;
				}
				else if (nonflagargs == 1)
				{
					strcpy(tofilename, args[i]);
					nonflagargs --;
				}
				else 
				{
					cerr << "Warning: too many arguments - extra arguments are being omitted\n";
				}
			}
		}
		else
		{
			if (strcmp(args[i], "-h") == 0)
				flags |= HELP_FLAG;
			else if (strcmp(args[i], "-f") == 0)
				flags |= SNIP_FRONT;
			else if (strcmp(args[i], "-H") == 0)
				flags |= LONGHELP_FLAG;
			else if (strcmp(args[i], "-F") == 0)
				flags &= ~SNIP_FRONT;
			else if (strcmp(args[i], "-v") == 0)
				flags |= VERBOSE_FLAG;
			else if (strcmp(args[i], "-r") == 0)
			{
				i++;
				if (i == argc)
				{
					cerr << "Error: no replacechar provided!\n";
					return ERROR_ARGC;
				}

				if (strcmp(args[i], "\\n") == 0)
					replaceChar = '\n';
				else if (strcmp(args[i], "\\t") == 0)
					replaceChar = '\t';
				else
					replaceChar  = args[i][0];
			}
			else if (strcmp(args[i], "-R") == 0)
			{
				i++;
				if (i == argc)
				{
					cerr << "Error: no replacetochar provided!\n";
					return ERROR_ARGC;
				}

				if (strcmp(args[i], "\\n") == 0)
					replaceToChar = '\n';
				else if (strcmp(args[i], "\\t") == 0)
					replaceToChar = '\t';
				else
					replaceToChar  = args[i][0];
			}
			else if (strcmp(args[i], "-m") == 0)
			{
				i++;
				if (i == argc)
				{
					cerr << "Error: no maxRepititions provided!";
					return ERROR_ARGC;
				}
				maxRepititions = atoi(args[i]); 
			}
		}

	}		


	if (flags & LONGHELP_FLAG)
	{
		char home[20]; 
		strcpy(home,getenv("HOME"));

		char helpfile[120];
		sprintf(helpfile, "%s/bin/sourceCode/snip/help.txt", home);

		ifstream help(helpfile);
		if (!help)
		{
			cerr << "Error: help.txt not found in " << helpfile << endl;
			return ERROR_NOHELP;
		}

		char helpstr[80];
		while(help.getline(helpstr, 80))
		{
			cout << helpstr << endl;
		}

		help.close();

		return NO_ERROR;
	}

	if (flags & HELP_FLAG)
	{
		cout << "Usage:\n";
		cout << args[0] << "\tsourcefile destfile [flags]\n";
		return NO_ERROR;
	}

	if (nonflagargs )
	{
		cerr << "Error: Not enough arguments please refer help using -h flag\n";
		return ERROR_ARGC;
	}

	cout << "Source file: " << filename << endl;
	cout << "Target file: " << tofilename << endl;

	if ( flags & VERBOSE_FLAG )
	{
		cout << "replacechar:" << replaceChar << endl;
		cout << "replacetochar:" << replaceToChar << endl;
	}

	//actual impplementation

	ifstream file(filename);
	ofstream ofile(tofilename);

	if (!file)
	{
		cerr << "Error: source file could not be opened!\n";
		return ERROR_SRC;
	}

	char c;
	int limit = maxRepititions;
	int beg = 0;
	while(file.get(c))
	{
		if (c == replaceChar)
		{
			if (!limit)
			{
				c = replaceToChar;
			}
			else 
				limit--;
		}
		else 
		{
			limit = maxRepititions;
			beg = 1;
		}

		if ((flags & SNIP_FRONT) && !beg)
			c = 0;


		if (c)
			ofile.put(c);
	}

	ofile.close();
	file.close();

	return NO_ERROR;
}
