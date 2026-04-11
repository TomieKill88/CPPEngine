#include <iostream>
#include <fstream>
#include <sstream>

#include "ConfigFileReader.hpp"


namespace Tools
{
	void readFile(std::string& fileName, std::vector<std::string>& lines)
	{
		std::string line = "";

		std::ifstream configFile(fileName);

		while (std::getline(configFile, line))
		{
			lines.push_back(line);
		}
	}

	void tokenizeLine(std::string& line, std::vector<std::string>& tokens)
	{
		std::string token = "";
		std::stringstream streamedLine(line);

		while (std::getline(streamedLine, token, ' '))
		{
			tokens.push_back(token);
		}
	}

	void getFileTokens(std::string& fileName, std::vector<std::vector<std::string>>& tokens)
	{
		std::vector<std::string> lines;
		std::vector<std::string> tokenized;
		readFile(fileName, lines);

		for each (auto line in lines)
		{
			tokenizeLine(line, tokenized);
			tokens.push_back(tokenized);

			tokenized.clear();
		}
	}
}