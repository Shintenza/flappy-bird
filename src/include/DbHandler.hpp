# pragma once
#include "utils/logging.hpp"
#include <sqlite3.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <array>

struct bestScores {
    int time;
    int score;
    int number_of_tries;
};

class DbHandler {
private:
    sqlite3 *db;
    void initDb();
public:
    DbHandler();
    ~DbHandler();

    bool checkIfSessionsExists(int started);
    void addSession(int started, int score, int tries, int flap_count, int obstacles_count, bool update);
    unsigned getDbHighestScore();
    std::vector<bestScores> getBestScores();
    std::array<int, 2> getSecondaryStats();
};
