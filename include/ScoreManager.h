#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H// to prevent from multiple inclusions of the ScoreManager class definition

#include <string>

using namespace std;

class ScoreManager {
public:
    void saveScore(const string& playerName, const string& courseName, int score, int total);
    void showScores() const;
};

#endif
