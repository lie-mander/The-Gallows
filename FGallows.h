#pragma once
#include <string>
#include <list>

using int32 = int;
using FString = std::string;

enum class ELetterStatus 
{
	Invalid_Status,
	OK,
	Not_TrueLanguage,
	Wrong_Lenght,
	Already
};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_TrueLanguage,
	Wrong_Lenght,
};

class FGallows
{
public:

	FGallows();

	void Reset();
	void GetPicture();
	void PuzzleWordList();
	void GetPictureKeyboard();
	void GetPlaceOfLeter();
	void IncorectLetter();

	int32 GetMaxTries();
	int32 GetPictureNumber();
	int32 GetHiddenWordLenght() const;
	int32 GetMaxWordLenght() const;
	int32 GetMinWordLenght() const;

	void GetHiddenWord();
	FString ToLowercaseWord(FString);
	FString HiddenHelpWord;
	FString HiddenWord;
	char ToLowercase(FString);
	
	ELetterStatus CheckLetterValidity(FString);
	EWordStatus CheckWordValidity(FString);

	bool CheckValidityOfOpponent(int32) const;
	bool CheckLetterPlace();
	bool IsGameWin;

private:

	std::list<char> LetterList;
	std::list<char> NumberList;
	std::list<char> AlreadyList;
	std::list<char> AlreadyWordList;
	std::list<char> PuzzleWordPlayer;

	char Alphabit[32];
	char GetPuzzleLetter();
	char PuzzleLetter;
	char AlreadyPuzzleLetter;

	void PutLetterInArray();

	bool IsTrueLanguage(FString);
	bool IsTrueLanguageWord(FString);
	bool IsAlready(FString);

	int32 GetLetterLenght();
	int32 LetterLenght;
	int32 HiddenWordLenght;
	int32 MaxTries;
	int32 MaxWordLenght;
	int32 MinWordLenght;
	int32 PictureNumber;
	int32 LetterPlace;
};

