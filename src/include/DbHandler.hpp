# pragma once
#include "utils/logging.hpp"
#include <sqlite3.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <array>

struct bestScore {
    int time;
    int score;
    int number_of_tries;
};

class DbHandler {
private:
    sqlite3 *db;
    void initDb();

    int highestScore;
    int numberOfTries;
    int flapCount;
    int obstaclesCount;

    std::vector<bestScore> bestScores;
    std::array<int, 2> secondaryStats;

    friend int getHighestScoreCallback(void *data, int argc, char** argv, char**colName);
    friend int getBestScoresCallback(void* data, int argc, char** argv, char** colName);
    friend int getSecondaryStatsCallback(void* data, int argc, char** argv, char** colName);
    friend int checkIfSessionsExistsCallback(void* data, int argc, char** argv, char** colName);
public:
    DbHandler();
    ~DbHandler();

    bool checkIfSessionsExists(int started);
    void addSession(int started, int score, int tries, int flap_count, int obstacles_count, bool update);
    unsigned getDbHighestScore();
    std::vector<bestScore> getBestScores();
    std::array<int, 2> getSecondaryStats();
};
