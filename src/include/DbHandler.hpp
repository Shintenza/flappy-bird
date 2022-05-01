# pragma once
#include "utils/logging.hpp"
#include <sqlite3.h>
#include <stdlib.h>
#include <iostream>

class DbHandler {
private:
    sqlite3 *db;
    void initDb();
    unsigned& highestScore;
    friend int getHighestScoreCallback(void *data, int argc, char** argv, char**colName);
public:
    DbHandler(unsigned& highestScore);
    ~DbHandler();
    void getHighestScore();
    void insertSession(int session_started, int n_of_tries);
    void updateHighestScore(int score);
};
