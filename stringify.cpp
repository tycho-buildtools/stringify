//////////////////////////////////////////////////////////////////////////////
// Copyright 2006  Martin Slater
// Outputs the passed files as a C style string with appropriate line escapes
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("stringify input_file output_file (var_name)\n"
			"  Creates a c++ const char[] array containing quoted version of input file");
		return EXIT_FAILURE;
	}

	std::string input_file = argv[1];
	std::string output_file = argv[2];
	std::string var_name;

	if(argc == 4)
		var_name = argv[3];
	else
	{
		// remove extension of output filename name
		int end = (int)output_file.length()-1;
		int start = 0;
		for(int i = (int)output_file.length()-1; i > 0; --i)
		{
			if(output_file[i] == '.')
				end = i;
			if(output_file[i] == '/' || output_file[i] == '\\')
			{
				start = i + 1;
				break;
			}
		}
		var_name = output_file.substr(start, end - start);
	}

	std::ifstream istr(input_file.c_str());
	if(!istr)
	{
		std::cout << "Unable to open input file : " << input_file << "\n";
		return EXIT_FAILURE;
	}

	std::ofstream ostr(output_file.c_str());
	if(!ostr)
	{
		std::cout << "Unable to open output file : " << output_file << "\n";
		return EXIT_FAILURE;
	}

	// output definition
	ostr << "const char " << var_name << "[] = \"\\\n";
	std::string line;
	while(istr.good())
	{
		std::getline(istr, line);
		ostr << line << " \\n\\\n";
	}
	ostr << "\";\n";

	return EXIT_SUCCESS;
}

