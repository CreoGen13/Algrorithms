#ifndef LAB1_GAME_H
#define LAB1_GAME_H

//#include <limits>
#include <random>
#include <map>

const std::string kSaveFilePath = "Save.txt";

constexpr int kCitizenProduction = 10;
constexpr int kCitizenCostInBushels = 20;
constexpr double kAcreCostInBushels = 0.5;
constexpr float kPlagueChance = 0.15f;

struct GameData {
    int year = 0;
    int citizens = 100;
    int bushels = 2800;
    int acres = 1000;

    int acrePrice = 0;
    int deaths = 0;

//public:
    void Reset() {
        year = 0;
        citizens = 100;
        bushels = 2800;
        acres = 1000;
        acrePrice = 0;
        deaths = 0;
    }
    GameData(int year, int citizens, int bushels, int acres) {
        this->year = year;
        this->citizens = citizens;
        this->bushels = bushels;
        this->acres = acres;
    }

    [[nodiscard]] std::string ToString() const {
        std::string gameData = std::to_string(year) + "\t"
                               + std::to_string(citizens) + "\t"
                               + std::to_string(bushels) + "\t"
                               + std::to_string(acres) + "\t"
                               + std::to_string(acrePrice) + "\t"
                               + std::to_string(deaths) + "\n";
        return gameData;
    }
};

struct TurnData {
    int turnDeaths = 0;
    int newCitizens = 0;
    bool isPlague = false;
    int bushelsIncome = 0;
    int bushelsPerAcre = 0;
    int bushelsEatenByRats = 0;

    void Reset() {
        turnDeaths = 0;
        newCitizens = 0;
        isPlague = false;
        bushelsIncome = 0;
        bushelsPerAcre = 0;
        bushelsEatenByRats = 0;
    }
    [[nodiscard]] std::string ToString() const {
        std::string turnData = std::to_string(turnDeaths) + "\t" +
                               std::to_string(newCitizens) + "\t" +
                               std::to_string(isPlague) + "\t" +
                               std::to_string(bushelsIncome) + "\t" +
                               std::to_string(bushelsPerAcre) + "\t" +
                               std::to_string(bushelsEatenByRats) + "\n";
                               //std::to_string(isGameOver) + "\n";
        return turnData;
    }
};

class Game {
public:
    Game() = default;
    void StartGame();

private:
    GameData gameData = GameData(0, 100, 2800, 1000);
    TurnData turnData;

    void MainLoop();
    void ChangeStats(int toEat, int toSow, int& bushels, int& acres);
    void GameOver();

    static bool CheckIsInputInt(const std::string& input);
    bool GetDefaultUserInput();
    int GetIntUserInput();
    bool GetSpecialUserInput(int& toBuy, int& toSell, int& toEat, int& toSow, int& bushels, int& acres);

    int RandomRangeInt(int min, int max);
    float RandomRangeFloat(float min, float max);

    void PrintNotEnough(int resourceType, int resource);
    void PrintStats();
    void PrintGameResults();

    bool SaveGame();
    bool LoadGame();

    std::map<std::string, std::string> dialogues = {
            // Main dialogues
            {"startGame","Choose load last saved game or start a new one\n 0 - Load game\n 1 - Start new game\n"},
            {"saveGame","Save game?\n 0 - No\n 1 - Yes\n"},

            // Statistics dialogues
            {"startStats","Your statistics for the year number "},
            {"statsDied"," citizens died from starvation\n"},
            {"statsArrived"," citizens arrived to Your city\n"},
            {"statsPlague","Plague killed half of the citizens amount\n"},

            {"statsDueTo","Due to "},
            {"statsBushels1"," bushels per acre, "},
            {"statsBushels2"," bushels of wheat were harvested.\n"},
            {"statsRats1"," bushels eaten by rats, now we have "},
            {"statsRats2"," bushels of wheat.\n"},
            {"statsAcres"," is now the size of Your city.\n"},
            {"statsCitizens"," citizens live in Your city.\n"},
            {"statsAcrePrice"," bushels of wheat is the price for acre for now.\n"},

            // Input dialogues

            {"startInput1","Type number between 0 and 1 inclusive\n"},
            {"startInput2","Type number between 0 and 100000 inclusive\n"},
            {"inputWrong","Wrong input. Try again\n"},

            // Special input dialogues
            {"startSpecial","Order wisely.\n"},
            {"specialAcresBuy","How many acres of land do you order to buy?\n"},
            {"specialAcresSell","How many acres of land do you order to sell?\n"},
            {"specialEatBushels","How many bushels of wheat do you order to eat?\n"},
            {"specialAcresSow","How many acres of land do you order to sow?\n"},

            {"specialNotEnough","You can't do this, you have only "},

            // Results dialogues
            {"resultBad","Because of your incompetence in government, the people revolted and drove you out of their cities. Now you forced to drag out a miserable existence in exile\n"},
            {"resultOk","You ruled the iron hand, like Nero and Ivan the Terrible. The people sighed relief, and no one else wants to see you as the ruler\n"},
            {"resultGood","You did pretty well, you of course, there are ill-wishers, but many would like to see you in head of the city again"},
            {"resultPerfect","Fantastico! Charlemagne, Disraeli and Jefferson couldn't have done better together."},

            // Save dialogues
            {"loadFailed","Unable to read save file\n"},
            {"loadSucceed","Game loaded\n"},

            {"saveFailed","Unable to read save file\n"},
            {"saveSucceed","Game saved\n"}
    };
};





#endif //LAB1_GAME_H
