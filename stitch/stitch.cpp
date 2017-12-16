#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>

using namespace std;

enum {
	NO_ERROR,
	ERROR_ARGS
};

int main(int argc, char *args[])
{
	char *in_file_list, out_file[80];
	if (argc < 4)
	{
		cerr << "NOT ENOUGH ARGUMENTS!\n";
		cerr << "Usage:\n";
		cerr << "\t" << args[0] << " file1 file2 [file3 file4 ....] output_file\n";
		cerr << "\t Two files are mandatory\n";
		return ERROR_ARGS;
	}
	else
	{
		in_file_list = new char[80 * (argc - 2)];
		for (int i = 0; i < argc - 2; i++)
			strcpy(in_file_list + 80 * i, args[i+1]);
		strcpy(out_file, args[argc-1]);
	}

	fstream fin;
	ofstream fout(out_file);

	for (int i = 0; i < argc-2; i++)
	{
		cout << "Stitching file " << in_file_list + 80 * i << " into " << out_file << " ...\n";
		fin.open(in_file_list + 80  * i, ios::in  );
		if ( !fin )
			cerr << "Error: could not open " << in_file_list + 80 * i << endl;
		else
		{
			char header[80];
			fin.seekg(0, fin.end); // goto the end of the file
			long size = fin.tellg();
			sprintf(header, "stitch:%s:%ld:", in_file_list + 80 * i, size);
			fout.write(header,80); // writing the header text
			fin.close();
			fin.open(in_file_list + 80  * i, ios::in  );
			char c;
			while(fin.get(c))
			{
				fout.put(c);
			}
			cout << size <<" bytes written\n";
		}
		fin.close();
	}
	fout.close();
	return NO_ERROR;
}
