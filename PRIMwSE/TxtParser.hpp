#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <limits>

using NeighMatrix = std::vector<int>;
using FileName = std::string;
using TokenVec = std::vector<std::string>;

class TxtParser
{
public:
	[[nodiscard]]
	static int MakeMatrix(NeighMatrix& out_matrix, const FileName& file);

private:

	static bool ReadNextLine(std::ifstream& file, std::string& out_readLine);
	static bool IsComment(std::string& line);

	class Tokenizer
	{
	public:
		Tokenizer() = default;
		void Tokenize(const std::string& str, char delim);
		std::string NextToken();
		int GetNumOfTokens() {
			return tokens.size();
		}

	private:
		int iterPos = 0;
		std::string inputString;
		TokenVec tokens;
	};
};
