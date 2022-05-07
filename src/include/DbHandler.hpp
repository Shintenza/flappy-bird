# pragma once
#include "utils/logging.hpp"
#include <sqlite3.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

struct bestScores {
    int time;
    int score;
    int number_of_tries;
};

class DbHandler {
private:
    sqlite3 *db;
    void initDb();
    unsigned& highestScore;
    friend int getHighestScoreCallback(void *data, int argc, char** argv, char**colName);
public:
    DbHandler(unsigned& highestScore);
    ~DbHandler();
    void getDbHighestScore();
    void insertSession(int session_started, int n_of_tries, int flap_count, int obstacles_count);
    void updateHighestScore(int score);
    std::vector<bestScores> getBestScores();
};
