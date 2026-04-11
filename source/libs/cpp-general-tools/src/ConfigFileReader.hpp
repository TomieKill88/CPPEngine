#pragma once

#include <vector>
#include <string>

namespace Tools
{
	void readFile(std::string& fileName, std::vector<std::string>& lines);

	void tokenizeLine(std::string& line, std::vector<std::string>& tokens);

	void getFileTokens(std::string& fileName, std::vector<std::vector<std::string>>& tokens);
}