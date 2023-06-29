#pragma once
#include "FGallows.h"
#include <iostream>
#include <limits>
#include <string>
#include <Windows.h>

// TODO music

using int32 = int;
using FString = std::string;

void Intro();
void PlayGame();
void EnterAnswer();
void GameWin();
bool AskOpponent();
bool AskToPlayAgain();
FString EnterHiddenWord(FString); //VS Player

FGallows ManderGame;
FString PuzzledWord;

int32 main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Intro();
    PlayGame();

    return 0;
}

void Intro()
{
    Beep(200, 200);
    Beep(300, 200);
    Beep(400, 200);
    Beep(200, 200);
    std::cout << "                  |                          " << std::endl;
    std::cout << "                  |                          " << std::endl;
    std::cout << "                 ___                         " << std::endl;
    std::cout << "                /   \\                        " << std::endl;
    std::cout << "                \\___/        THE              " << std::endl;
    std::cout << "                 /|\\       GALLOWS           " << std::endl;
    std::cout << "                | | |                        " << std::endl;
    std::cout << "                  |                          " << std::endl;
    std::cout << "                 / \\                         " << std::endl;
    std::cout << "                 | |                         " << std::endl << std::endl;
    
    return;
}

void PlayGame()
{
    do {
        ManderGame.Reset();

        if (AskOpponent())
        {
            Beep(400, 200);
            Beep(300, 200);
            Beep(400, 200);
            Beep(300, 200);
            std::cout << "\n\n   ������� ������� ��������� ���� �� ��������\n\n";
            ManderGame.GetHiddenWord();
        }
        else {
            Beep(200, 200);
            Beep(300, 200);
            Beep(200, 200);
            Beep(300, 200);
            std::cout << "\n\n   ����� ������� ��������� ���� �� ��������\n\n";
            EnterHiddenWord(PuzzledWord);
        }
        EnterAnswer();
        GameWin();
    } while (AskToPlayAgain());
    return;
}

void EnterAnswer()
{
    FString PlayerLetter;

    std::cin.ignore();
    system("cls");

    Beep(200, 200);
    std::cout << "\n\n   ���-�� ������ ���������: " << ManderGame.HiddenHelpWord << "\n\n";
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    
    system("cls");
    std::cout << "\n\n   ���-�� ������ ���������: " << ManderGame.HiddenHelpWord << "\n\n";


    for (int32 TriesNumber = 0; TriesNumber < ManderGame.GetMaxTries(); TriesNumber)
    {
        ELetterStatus Status = ELetterStatus::Invalid_Status;
        do
        {
            Beep(300, 200);
            std::cout << "\n\n   �������� �����: ";
            
            std::cin >> PlayerLetter;
            
            Status = ManderGame.CheckLetterValidity(PlayerLetter);
            switch (Status)
            {
            case ELetterStatus::Not_TrueLanguage:
                Beep(100, 300);
                std::cout << "   ����� ���������� ������ ";
                break;
            case ELetterStatus::Wrong_Lenght:
                Beep(100, 300);
                std::cout << "   ����� ���� ����� ";
                break;
            case ELetterStatus::Already:
                Beep(100, 300);
                std::cout << "   �� ��� ����������� ��� ����� ";
                break;
            default:
                break;
            } 
        } while (Status != ELetterStatus::OK);

        std::cin.ignore();
        system("cls");

        ManderGame.ToLowercase(PlayerLetter);
        
        if (ManderGame.CheckLetterPlace())
        {
            Beep(800, 200);
            Beep(500, 200);
            Beep(800, 200);
            ManderGame.GetPicture();
            ManderGame.GetPlaceOfLeter();
            if (ManderGame.IsGameWin) 
            {
                std::cout << "\n\n\n";
                Beep(400, 800);
                std::cin.ignore();
                system("cls");
                return;
            }
            ManderGame.GetPictureKeyboard();

            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            system("cls");
        }
        else 
        {
            Beep(100, 800);
            
            ManderGame.IncorectLetter();
            ManderGame.GetPicture();
            ManderGame.GetPlaceOfLeter(); 
            ManderGame.GetPictureKeyboard();

            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            system("cls");

            TriesNumber++;
        }
    }
    return;
}
    
bool AskOpponent()
{
    std::cin.ignore();
    system("cls");
    Beep(300, 200);
    std::cout << "\n\n   ��� ����� �������� ��� ��������?\n";
    std::cout << "                                  |\n";
    std::cout << "                                  |\n";
    std::cout << "                                  |\n";
    std::cout << "            1. ���������          |\n";
    std::cout << "            2. �����             ###\n";
    std::cout << "                                ##  ##\n";
    std::cout << "                               #     #\n";
    std::cout << "                                ##  ##\n";
    std::cout << "                                  ##\n";
    std::cout << "  (1 / 2) : ";
    int Opponent;

    do
    {
        if (!(std::cin >> Opponent))
        {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    } while (!ManderGame.CheckValidityOfOpponent(Opponent));

    std::cin.ignore();
    system("cls");

    if (Opponent == 1) { return true; }
    else return false;
}

FString EnterHiddenWord(FString)
{
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    system("cls");

    EWordStatus Status = EWordStatus::Invalid_Status;
    do
    {
        Beep(300, 200);
        std::cout << "\n\n   ����� �����: ";
        std::cin >> PuzzledWord;

        Status = ManderGame.CheckWordValidity(PuzzledWord);
        switch (Status)
        {
        case EWordStatus::Not_TrueLanguage:
            Beep(100, 300);
            std::cout << "   ����� ���������� ������ ";
            break;
        case EWordStatus::Wrong_Lenght:
            Beep(100, 300);
            std::cout << "   ��������� ���������� ����� ����� ( 3-15 ) ";
            break;
        default:
            break;
        }
    } while (Status != EWordStatus::OK);

    std::cin.ignore();
    system("cls");

    Beep(300, 200);
    std::cout << "\n\n   ����� ���������: ";

    std::getline(std::cin, ManderGame.HiddenHelpWord);

    Beep(300, 200);
    std::cout << "\n\n   �����? ";

    ManderGame.ToLowercaseWord(PuzzledWord);
    return PuzzledWord;
}

bool AskToPlayAgain()
{
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    system("cls");

    FString Response = "";
    do
    {
        Beep(300, 200);
        std::cout << "\n\n\n    ������ ������? (� / �) ";
        std::cin >> Response;
        if (Response == "�" || Response == "�")
        {
            std::cin.ignore();
            system("cls");
            Beep(150, 500);
            std::cout << "              \n";
            std::cout << "              \n";
            std::cout << "    �����     \n";
            std::cout << "              \n";
            return false;
        }
    } while (!(Response == "�" || Response == "�"));

    return (Response == "�") || (Response == "�");
}

void GameWin()
{
    if (ManderGame.IsGameWin)
    {
        Beep(1500, 150);
        Beep(1500, 150);
        Beep(2000, 300);
        Beep(1500, 150);
        Beep(2000, 300);
        std::cout << "                                \n";
        std::cout << "                                \n";
        std::cout << "           �����                \n";
        std::cout << "                                \n";
        std::cout << "     �����: " << ManderGame.HiddenWord << "\n\n";
    }
    else 
    { 
        Beep(100, 150);
        Beep(150, 800);
        Beep(100, 150);
        Beep(100, 150);
        std::cout << "                                \n";
        std::cout << "                                \n";
        std::cout << "           ̨���                \n";
        std::cout << "                                \n";
        std::cout << "     �����: " << ManderGame.HiddenWord << "\n\n";
    }
    return;
}

