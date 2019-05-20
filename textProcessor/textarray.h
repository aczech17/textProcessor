#ifndef TEXTARRAY
#define TEXTARRAY

#include <cstddef>//size_t
#include <string>
#include <vector>
#include <utility>//pair
typedef  std::vector< std::pair<std::string, std::string> > stringPairs;//wektor par stringow
template <size_t ARRAY_SIZE=1024, size_t DB_SIZE=ARRAY_SIZE>
class TextArray
{
	std::vector<std::string> text;
	std::vector<stringPairs> database;
	const char separator;
	int replaceWord(std::string &text,const int begin,const int end, stringPairs replacements);//zwraca dlugosc slowa zastepujacego
public:
	TextArray(char sep = '*') : separator(sep) {}//explicit?
	int addText(std::string);
	int addRecord(stringPairs);
	void replacement(size_t textNumber, size_t dbNumber);
	std::string textWithNumber(size_t);//rzutowanie!
};

template <size_t ARRAY_SIZE, size_t DB_SIZE>
int TextArray<ARRAY_SIZE, DB_SIZE>::addText(std::string newString)
{
	if (text.capacity() >= ARRAY_SIZE)
		return 1;
	text.push_back(newString);
	return 0;
}
template<size_t ARRAY_SIZE, size_t DB_SIZE>
int TextArray<ARRAY_SIZE, DB_SIZE>::addRecord(stringPairs newRecord)
{
	if (database.capacity() >= DB_SIZE)
		return 1;
	database.push_back(newRecord);
	return 0;
}
template<size_t ARRAY_SIZE, size_t DB_SIZE>
void TextArray<ARRAY_SIZE, DB_SIZE>:: replacement(size_t textNumber, size_t dbNumber)
{
	std::string &stringToBeReplaced = text[textNumber];
	stringPairs replacementVector = database[dbNumber];
	int iterator = 0;
	while (iterator < stringToBeReplaced.size())
	{
		while (iterator < stringToBeReplaced.size() && stringToBeReplaced[iterator] != separator)
			iterator++;
		if (iterator >= stringToBeReplaced.size())
			break;
		int end = iterator + 1;
		while (end < stringToBeReplaced.size() && stringToBeReplaced[end] != separator)
			end++;
		iterator += replaceWord(stringToBeReplaced, iterator, end, replacementVector);//PROBLEM!!!
	}//WHILE
}

template<size_t ARRAY_SIZE, size_t DB_SIZE>
std::string TextArray<ARRAY_SIZE, DB_SIZE>::textWithNumber(size_t number)
{
	return text[number];
}

template<size_t ARRAY_SIZE, size_t DB_SIZE>
int TextArray<ARRAY_SIZE, DB_SIZE>::replaceWord(std::string &text, const int begin,const int end, stringPairs replacements)
{
	std::string wordToBeReplaced(text.begin() + begin, text.begin() + end + 1);
	for (int i = 0; i != replacements.size(); i++)
	{
		if (replacements[i].first == wordToBeReplaced)
		{
			text.replace(text.begin() + begin, text.begin() + end + 1, replacements[i].second);
			return replacements[i].second.size();
		}
	}//for
	return end - begin + 1;
}
#endif TEXTARRAY