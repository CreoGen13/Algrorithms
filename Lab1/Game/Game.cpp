#include <fstream>
#include <functional>
#include "Game.h"
#include "iostream"

std::random_device rd;
std::mt19937 gen(rd());

void Game::StartGame() {
    std::cout << dialogues["startGame"];
    int input = GetDefaultUserInput();

    turnData.Reset();
    gameData.Reset();

    if(!input) {
        LoadGame();
    }
//    else {
//        gameData = GameData(0,0,0,0);
//    }

    MainLoop();
}

void Game::MainLoop()
{
    while (gameData.year < 10)
    {
        gameData.acrePrice = RandomRangeInt(17, 26);
        PrintStats();

        std::cout << dialogues["saveGame"];
        if (GetDefaultUserInput())
        {
            SaveGame();
        }

        int toBuy = 0;
        int toSell = 0;
        int toEat = 0;
        int toSow = 0;

        int bushelsTemp = gameData.bushels;
        int acresTemp = gameData.acres;

        while (!GetSpecialUserInput(toBuy, toSell, toEat, toSow, bushelsTemp, acresTemp))
        {
            toBuy = 0;
            toSell = 0;
            toEat = 0;
            toSow = 0;
            bushelsTemp = gameData.bushels;
            acresTemp = gameData.acres;
        };

        ChangeStats(toEat, toSow, bushelsTemp, acresTemp);
    }

    PrintStats();
    PrintGameResults();
}
void Game::ChangeStats(int toEat, int toSow, int& bushels, int& acres) {
    turnData.bushelsPerAcre = RandomRangeInt(1, 6);
    turnData.bushelsIncome = toSow * turnData.bushelsPerAcre;
    bushels += turnData.bushelsIncome;

    turnData.bushelsEatenByRats = int(std::ceil(float(bushels) * RandomRangeFloat(.01f, .07f)));
    bushels -= turnData.bushelsEatenByRats;

    if (toEat - gameData.citizens * kCitizenCostInBushels < 0)
    {
        int hungryCitizens = -int(std::ceil(toEat / kCitizenCostInBushels - gameData.citizens));
        const float deathRate = float(hungryCitizens) / float(gameData.citizens);
        if (deathRate > 0.45f)
        {
            GameOver();

            return;
        }

        gameData.citizens -= hungryCitizens;
        gameData.deaths += hungryCitizens;
        turnData.turnDeaths = hungryCitizens;
    }

    int newCitizens = std::clamp(turnData.turnDeaths / 2 + (5 - turnData.bushelsPerAcre) * gameData.bushels / 600 + 1, 0, 50);
    turnData.newCitizens = newCitizens;
    gameData.citizens += newCitizens;

    float plague = RandomRangeFloat(0.f, 1.f);
    if (plague < kPlagueChance)
    {
        gameData.deaths += gameData.citizens / 2;
        gameData.citizens /= 2;
        turnData.isPlague = true;
    }
    else
    {
        turnData.isPlague = false;
    }

    gameData.bushels = bushels;
    gameData.acres = acres;

    ++gameData.year;
}
void Game::GameOver()
{
    std::cout << dialogues["resultBad"];
    StartGame();
}

bool Game::CheckIsInputInt(const std::string& input) {
    for (char i : input) {
        if (isdigit(i) == false) {
            return false;
        }
    }
    return true;
}
bool Game::GetDefaultUserInput() {
    std::string input;
    while (true) {
        std::cout << dialogues["startInput1"];
        std::cin >> input;

        if(!CheckIsInputInt(input)) {
            std::cout << dialogues["inputWrong"];
            continue;
        }
        if(input.length() > 1 || input.empty()) {
            std::cout << dialogues["inputWrong"];
            continue;
        }
        int inputInt = std::stoi(input);
        if(inputInt < 0 || inputInt > 1) {
            std::cout << dialogues["inputWrong"];
            continue;
        }

        return inputInt;
    }
}
int Game::GetIntUserInput ()
{
    std::string input;
    while (true) {
        std::cout << dialogues["startInput2"];
        std::cin >> input;

        if(!CheckIsInputInt(input)) {
            std::cout << dialogues["inputWrong"];
            continue;
        }
        if(input.length() > 6 || input.empty()) {
            std::cout << dialogues["inputWrong"];
            continue;
        }
        int inputInt = std::stoi(input);
        if(inputInt < 0 || inputInt > 100000) {
            std::cout << dialogues["inputWrong"];
            continue;
        }

        return inputInt;
    }
}
bool Game::GetSpecialUserInput(int& toBuy, int& toSell, int& toEat, int& toSow, int& bushels, int& acres) {
    std::cout << dialogues["startSpecial"] << dialogues["specialAcresBuy"];

    toBuy = GetIntUserInput();
    if (bushels < toBuy * gameData.acrePrice)
    {
        PrintNotEnough(1, bushels);

        return false;
    }
    else
    {
        bushels -= toBuy * gameData.acrePrice;
        acres += toBuy;
    }

    std::cout << dialogues["specialAcresSell"];
    toSell = GetIntUserInput();
    if (acres < toSell)
    {
        PrintNotEnough(2, acres);

        return false;
    }
    else
    {
        bushels += toSell * gameData.acrePrice;
        acres -= toSell;
    }

    std::cout << dialogues["specialEatBushels"];
    toEat =  GetIntUserInput();
    if(bushels < toEat)
    {
        PrintNotEnough(1, bushels);

        return false;
    }
    else
    {
        bushels -= toEat;
    }

    std::cout << dialogues["specialAcresSow"];
    toSow = GetIntUserInput();
    if (bushels < int(toSow * kAcreCostInBushels))
    {
        PrintNotEnough(1, bushels);

        return false;
    } else {
        if (gameData.citizens * kCitizenProduction < toSow) {
            PrintNotEnough(3, gameData.citizens);

            return false;
        } else {
            if (toSow > acres) {
                PrintNotEnough(2, acres);

                return false;
            } else {
                bushels -= int(toSow * kAcreCostInBushels);
            }
        }
    }

    return true;
}

int Game::RandomRangeInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
float Game::RandomRangeFloat(float min, float max) {
    std::uniform_real_distribution<> dist(min, max);
    return float(dist(gen));
}

void Game::PrintNotEnough(int resourceType, int resource) {
    switch (resourceType) {
        case 1: {
            std::cout << dialogues["specialNotEnough"] << resource << " Bushels" << std::endl;
            break;
        }
        case 2: {
            std::cout << dialogues["specialNotEnough"] << resource << " Acres" << std::endl;
            break;
        }
        case 3: {
            std::cout << dialogues["specialNotEnough"] << resource << " Citizens" << std::endl;
            break;
        }
    }
}
void Game::PrintStats() {
    std::cout << dialogues["startStats"] << gameData.year << std::endl;

    if (turnData.turnDeaths > 0)
    {
        std::cout << "\t" << turnData.turnDeaths << dialogues["statsDied"];
    }
    if (turnData.newCitizens > 0)
    {
        std::cout << "\t" << turnData.newCitizens << dialogues["statsArrived"];
    }
    if(turnData.isPlague)
    {
        std::cout << "\t" << dialogues["statsPlague"];
    }

    std::cout << "\t" << dialogues["statsDueTo"] << turnData.bushelsPerAcre << dialogues["statsBushels1"] << turnData.bushelsIncome << dialogues["statsBushels2"];
    std::cout << "\t" << dialogues["statsDueTo"] << turnData.bushelsEatenByRats << dialogues["statsRats1"] << gameData.bushels << dialogues["statsRats2"];
    std::cout << "\t" << gameData.acres << dialogues["statsAcres"];
    std::cout << "\t" << gameData.citizens << dialogues["statsCitizens"];
    std::cout << "\t" << gameData.acrePrice << dialogues["statsAcrePrice"];
    std::cout << std::endl;
}
void Game::PrintGameResults()
{
    float P = float(gameData.deaths) / float(gameData.deaths + gameData.citizens);
    float L = float(gameData.acres) / float(gameData.citizens);

    if( P > 0.33 && L < 7) {
        std::cout << dialogues["resultBad"];
    } else if(P > 0.1 && L < 9) {
        std::cout << dialogues["resultOk"];
    } else if(P > 0.03 && L < 01) {
        std::cout << dialogues["resultGood"];
    } else {
        std::cout << dialogues["resultPerfect"];
    }

    StartGame();
}

bool Game::SaveGame()
{
    std::ofstream outputFileStream (kSaveFilePath,std::ios::out | std::ios::trunc);
    if(!outputFileStream.is_open())
    {
        std::cout << dialogues["saveFailed"];
        outputFileStream.close();

        return false;
    }

    outputFileStream << gameData.ToString();
    outputFileStream << turnData.ToString();

    if(outputFileStream.fail())
    {
        std::cout << dialogues["saveFailed"];
        outputFileStream.close();

        return false;
    }

    std::cout << dialogues["saveSucceed"];
    outputFileStream.close();

    return true;

}
bool Game::LoadGame() {
    std::ifstream inputFileStream (kSaveFilePath);
    if(!inputFileStream.is_open())
    {
        std::cout << dialogues["loadFailed"];
        inputFileStream.close();

        return false;
    }

    inputFileStream >> gameData.year >> gameData.citizens >> gameData.bushels >> gameData.acres
       >> gameData.acrePrice >> gameData.deaths >>
       turnData.turnDeaths >> turnData.newCitizens >> turnData.isPlague >> turnData.bushelsIncome
       >> turnData.bushelsPerAcre >> turnData.bushelsEatenByRats;
    std::cout << dialogues["loadSucceed"];

    return true;
}