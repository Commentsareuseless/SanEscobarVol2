#include "TxtParser.hpp"


void TxtParser::MakeMatrix(NeighMatrix& out_matrix, const FileName& file)
{
	std::ifstream file2Parse(file);
	std::string fileBuffer;
	NeighMatrix buffMatrix;
	std::string currentToken;
	Tokenizer tokenizer;

	int numOfTokens{ 0 };
	int matrixSize{ 0 };
	int matrixElem{ 0 };
	bool matrixFound{ false };
	bool eomFound{ false };
	
	if (!file2Parse)
	{
		printf("Plik z macierza nie istnieje :(\n");
		return;
	}
	fileBuffer.reserve(100); // wild guess :)

	while (ReadNextLine(file2Parse, fileBuffer))
	{
		if (IsComment(fileBuffer)) { continue; }
		if (eomFound) { break; }
		tokenizer.Tokenize(fileBuffer, ' ');
		numOfTokens = tokenizer.GetNumOfTokens();
		do{
			currentToken = tokenizer.NextToken();
			// printf("%s ", currentToken.c_str()); // debug
			if (currentToken[0] == '[')
			{
				matrixFound = true;
				matrixSize = numOfTokens - 1;
				continue;
			}
			if (currentToken[0] == ']')
			{
				if (!(matrixSize == numOfTokens - 1) || !matrixFound)
				{
					printf("Error! invalid matrix\n");
					return;
				}
				eomFound = true;
				break;
			}
			if (matrixFound)
			{
				try // In case of characters other than nums
				{
					matrixElem = std::stoi(currentToken);
				}
				catch (std::invalid_argument& arg)
				{
					continue;
				}

				out_matrix.push_back(matrixElem);
			}
		} while (!currentToken.empty());
		// printf("\n"); // debug
	}
	printf("Output vector: \n");
	for (auto num : out_matrix)
	{
		printf("%d ", num);
	}
	printf("\n");

}

bool TxtParser::ReadNextLine(std::ifstream& file, std::string& out_readLine)
{
	if (!file.eof())
	{
		std::getline(file, out_readLine);
		return true;
	}
	return false;
}

bool TxtParser::IsComment(std::string& line)
{
	if (line[0] == '#') { return true; }

	return false;
}

TxtParser::Tokenizer::Tokenizer()
{
}

void TxtParser::Tokenizer::Tokenize(const std::string& str, char delim)
{
	char currentChar{};
	bool newToken = true;
	auto strIter = str.begin();
	tokens.clear();

	for (; strIter != str.end(); strIter++)
	{
		if (*strIter == delim) 
		{
			continue;	// ignore additional delimiters
		}

		std::string tmpStr{};
		tmpStr.clear();
		tmpStr.reserve(10);
		try
		{
			while (strIter != str.end() && *strIter != delim)
			{
				tmpStr.push_back(*strIter);
				++strIter;
			}
		}
		catch (std::exception& exc)
		{
			printf("Wyjatek %s\n", exc.what());
			return;
		}
		tmpStr.shrink_to_fit();
		tokens.push_back(tmpStr);
		if (strIter == str.end()) { return; }
	}
}

std::string TxtParser::Tokenizer::NextToken()
{
	std::string ret{};
	if (iterPos < tokens.size())
	{
		ret = tokens[iterPos];
		++iterPos;
	}
	else
	{
		iterPos = 0;
	}
	return ret;
}
