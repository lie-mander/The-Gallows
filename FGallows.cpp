// The game logic (only code without direct player interaction)
#pragma once
#include "FGallows.h"
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <random>

// for UnrealEngine syntax
#define TMap std::map

FGallows::FGallows() { Reset(); }
int32 FGallows::GetMaxTries() { return MaxTries; }
int32 FGallows::GetPictureNumber() { return PictureNumber; }
int32 FGallows::GetLetterLenght() { return LetterLenght; }
int32 FGallows::GetHiddenWordLenght() const { return HiddenWord.length(); }
int32 FGallows::GetMaxWordLenght() const { return MaxWordLenght; }
int32 FGallows::GetMinWordLenght() const { return MinWordLenght; }
char FGallows::GetPuzzleLetter() { return PuzzleLetter; }
void FGallows::IncorectLetter() { PictureNumber++; return; }

void FGallows::Reset()
{
	const int32 MAX_TRIES = 9;
	MaxTries = MAX_TRIES;

	const int32 MAX_WORD_LENGHT = 15;
	MaxWordLenght = MAX_WORD_LENGHT;

	const int32 MIN_WORD_LENGHT = 3;
	MinWordLenght = MIN_WORD_LENGHT;

	const int32 LETTER_LENGHT = 1;
	LetterLenght = LETTER_LENGHT;

	const int32 PICTURE_NUMBER = 0; 
	PictureNumber = PICTURE_NUMBER;

	LetterList.clear();
	NumberList.clear();
	AlreadyList.clear();
	PuzzleWordPlayer.clear();

	IsGameWin = false;

	int32 c = 0;
	for (char a = 'А', b = 'Я'; a <= b; a++, c++)
	{
		Alphabit[c] = a;
	}

	PuzzleLetter = '0';
}

void FGallows::GetHiddenWord()
{
	TMap <int, FString> HiddenWords
	{	
		{1,"ася"}, {2,"камень"}, {3,"картина"}, {4,"планета"}, {5,"стадион"}, {6,"графика"}, {7,"монитор"},
	};
	TMap <int, FString> HiddenHelpWords
	{
		{1,"любимая кошка"}, {2,"порода земли"}, {3,"исскуство"}, {4,"космос"}, {5,"футбол"}, {6,"3D"}, {7,"для PC"}
	};
	
	std::random_device random_device; 
	std::mt19937 generator(random_device()); 
	std::uniform_int_distribution<> distribution(1, 7);

	int i = distribution(generator); //TODO не повторять слово после победы
	
	const FString HIDDEN_WORD = HiddenWords[i];
	const FString HIDDEN_HELP_WORD = HiddenHelpWords[i];
	HiddenWord = HIDDEN_WORD;
	HiddenHelpWord = HIDDEN_HELP_WORD;
}

void FGallows::PutLetterInArray()
{
	char i = 'С';
	int32 a = 0;
	do 
	{
		if (Alphabit[a] == PuzzleLetter - 32)
		{
			Alphabit[a] = '#';
			return;
		}
		a++;
	} while (!Alphabit[a] != PuzzleLetter - 32);
}

void FGallows::PuzzleWordList()
{
	LetterList.push_back(PuzzleLetter); 
	NumberList.push_back(LetterPlace); 
	return;
}

bool FGallows::CheckValidityOfOpponent(int32 Opponent) const
{
	const int32 MIN_NUMBER = 1;
	int32 MinNumber = MIN_NUMBER;

	const int32 MAX_NUMBER = 2;
	int32 MaxNumber = MAX_NUMBER;

	int32 CheckNumber = MIN_NUMBER;

	for (int32 CheckNumber = MIN_NUMBER; CheckNumber <= MAX_NUMBER; CheckNumber++)
	{
		if ((Opponent == CheckNumber)) { return true; }
	}

	return false;
}

ELetterStatus FGallows::CheckLetterValidity(FString PlayerLetter)
{
	if (PlayerLetter.length() != GetLetterLenght()) { return ELetterStatus::Wrong_Lenght; }
		else if (!IsTrueLanguage(PlayerLetter)) { return ELetterStatus::Not_TrueLanguage; }
			else if(!IsAlready(PlayerLetter)) { return ELetterStatus::Already; }
				else { return ELetterStatus::OK; };
}

EWordStatus FGallows::CheckWordValidity(FString PuzzledWord)
{
	if (!(GetMinWordLenght() <= PuzzledWord.length()) || !(PuzzledWord.length() <= GetMaxWordLenght())) { return EWordStatus::Wrong_Lenght; }
		else if (!IsTrueLanguageWord(PuzzledWord)) { return EWordStatus::Not_TrueLanguage; }
			else { return EWordStatus::OK; };
}

bool FGallows::IsTrueLanguage(FString Check)
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Check)
	{
		char Alphabet = 'А';
		do
		{
			if (Letter == Alphabet) { return true; }
			Alphabet++;
		} while (Alphabet <= 'я');
	}
	return false;
}

bool FGallows::IsTrueLanguageWord(FString Check)
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Check)
	{
		char Alphabet = 'А';
		do
		{
			if (Letter == Alphabet) 
			{
				LetterSeen[Letter] = true;
			}
			Alphabet++;
		} while (Alphabet <= 'я');
	}
	for (auto Letter : Check)
	{
		if(LetterSeen[Letter] != true) return false;
	}
	return true;
}

bool FGallows::IsAlready(FString PlayerLetter)
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : PlayerLetter)
	{
		for (auto Liter1 = AlreadyList.begin(); Liter1 != AlreadyList.end(); Liter1++)
		{
			if (*Liter1 == Letter || *Liter1 - 32 == Letter)
			{
				return false;
			}

		}
		char i = -33;
		while (i != 'я')
		{
			i++;
			if (Letter == i)
			{
				AlreadyList.push_back(Letter);
				AlreadyList.push_back(Letter - 32);
				return true;
			}
			
		}
		i = -65;
		while (i != 'Я')
		{
			i++;
			if (Letter == i)
			{
				AlreadyList.push_back(Letter);
				AlreadyList.push_back(Letter + 32);
				return true;
			}
		}
	}
	return true;
}

char FGallows::ToLowercase(FString PlayerLetter)
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : PlayerLetter)
	{
		char Alphabet = 'А';
		do
		{
			if (Letter == Alphabet)
			{
				PuzzleLetter = Alphabet + 32;
				return PuzzleLetter;
			}
			Alphabet++;
		} while (Alphabet <= 'Я');
		PuzzleLetter = Letter;
	}

	return PuzzleLetter;
}



FString FGallows::ToLowercaseWord(FString PuzzledWord)
{
	HiddenWord = PuzzledWord;
	TMap<char, bool> LetterSeen;
	for (auto Letter : PuzzledWord)
	{
		char Alphabet = 'А';
		do
		{
			if (Letter == Alphabet)
			{
				LetterSeen[Letter] = true;
			}
			Alphabet++;
		} while (Alphabet <= 'Я');
	}

	FString x;
	int32 a = 0;
	for (auto Letter : PuzzledWord)
	{

		if (LetterSeen[Letter])
		{
			char i = Letter + 32;
			FString u;
			u.push_back(i);
			x = PuzzledWord.replace(a,1,u);
			HiddenWord = x;
		}
		a++;
	}
	return HiddenWord;
}

bool FGallows::CheckLetterPlace()
{
	TMap<char, bool> LetterSeen;
	int32 u = 0;
	int32 FirstLetterPlace = 1;
	for (auto Letter : HiddenWord)
	{
		if (PuzzleLetter == Letter)
		{
			u = 1;
			LetterPlace = FirstLetterPlace;
			PuzzleWordList();
		}
		FirstLetterPlace++;
	}
	
	if (u == 1) return true;
	return false;
}

void FGallows::GetPlaceOfLeter()
{
	std::cout << "\n      ";
	for (int32 i = 1; i <= GetHiddenWordLenght(); i++)
	{
		int32 u = 0;
		char y = '0';
		auto Liter = LetterList.begin();
		for (auto Niter = NumberList.begin(); Niter != NumberList.end(); Niter++, Liter++)
		{
			if (*Niter == i)
			{
				u = 1;
				y = *Liter - 32;
				std::cout << " " << y;
			}
			int32 Size = NumberList.size();
			if (Size == GetHiddenWordLenght()) IsGameWin = true;
		}
		if (u==0) std::cout << " _";
	}
	std::cout << std::endl;
	return;
}

void FGallows::GetPicture()
{
	GetPictureNumber();
	if (PictureNumber == 0)
	{
		std::cout << "\n\n       /-                        " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                           " << std::endl;
		std::cout << "       /                           " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 1)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                           " << std::endl;
		std::cout << "       /                           " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 2)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |                           " << std::endl;
		std::cout << "       /                           " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 3)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |          //\\                 " << std::endl;
		std::cout << "       /          \\//                  " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 4)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |          //\\                 " << std::endl;
		std::cout << "       /          \\//                  " << std::endl;
		std::cout << "       |           |                 " << std::endl;
		std::cout << "       |           |                 " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 5)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |          //\\                 " << std::endl;
		std::cout << "       /          \\//                  " << std::endl;
		std::cout << "       |          /|                 " << std::endl;
		std::cout << "       |         | |                 " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       /                          " << std::endl;
		std::cout << "       |                          " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 6)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |          //\\                 " << std::endl;
		std::cout << "       /          \\//                  " << std::endl;
		std::cout << "       |          /|                 " << std::endl;
		std::cout << "       |         | |                 " << std::endl;
		std::cout << "       /          /                  " << std::endl;
		std::cout << "       /         |                   " << std::endl;
		std::cout << "       |                         " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else if (PictureNumber == 7)
	{
		std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
		std::cout << "       |           *                 " << std::endl;
		std::cout << "       /           *                 " << std::endl;
		std::cout << "       |          //\\                 " << std::endl;
		std::cout << "       /          \\//                  " << std::endl;
		std::cout << "       |          /|\\                " << std::endl;
		std::cout << "       |         | | |               " << std::endl;
		std::cout << "       /          /                  " << std::endl;
		std::cout << "       /         |                   " << std::endl;
		std::cout << "       |                           " << std::endl;
		std::cout << "       |                          " << std::endl << std::endl;
	}
	else
	{
	std::cout << "\n\n       /-_--_---__-\\                  " << std::endl;
	std::cout << "       |           *                 " << std::endl;
	std::cout << "       /           *                 " << std::endl;
	std::cout << "       |          /##\\                 " << std::endl;
	std::cout << "       /          \\##/                  " << std::endl;
	std::cout << "       |          /|\\                " << std::endl;
	std::cout << "       |         | | |               " << std::endl;
	std::cout << "       /          / \\                " << std::endl;
	std::cout << "       /         |   |               " << std::endl;
	std::cout << "       |                            " << std::endl;
	std::cout << "       |                          " << std::endl << std::endl;
	}
	return;
}

void FGallows::GetPictureKeyboard()
{
	std::cout << "\n\n";
	PutLetterInArray();
	for (int a = 0, b = 32; a < b; a) 
	{
		std::cout << "  ";
		for (int x = 0, b = 8; x < b; a++, x++)
		{
			std::cout << Alphabit[a] << "   ";
		}
		std::cout << "\n\n";
	}	
}
