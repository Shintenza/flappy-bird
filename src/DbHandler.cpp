#include "include/DbHandler.hpp"

DbHandler::DbHandler() {
    initDb();
}

DbHandler::~DbHandler() {
    sqlite3_close(db);
}

int getHighestScoreCallback(void *data, int argc, char** argv, char**colName) {
    unsigned* highestScore = (unsigned*) data;
    if (argc > 0 && argv[0] != NULL) {
        *highestScore = std::stoi(argv[0]);
    } else {
        highestScore = 0;
    }
    return 0;
}
int getBestScoresCallback(void* data, int argc, char** argv, char** colName) {
    std::vector<bestScores> *scores = static_cast<std::vector<bestScores>*>(data);
    if (argc > 0 && argv[0] != NULL && argv[1] != NULL && argv[2] != NULL) {
        bestScores data { std::stoi(argv[0]), std::stoi(argv[1]), std::stoi(argv[2])};
        scores->push_back(data);
    }
    return 0; 
}
int getSecondaryStatsCallback(void* data, int argc, char** argv, char** colName) {
    std::array<int, 2> *stats = static_cast<std::array<int, 2>*>(data);
    if (argc > 0 && argv[0] != NULL && argv[1] != NULL) {
        (*stats)[0] = std::stoi(argv[0]);
        (*stats)[1] = std::stoi(argv[1]);
    }
    return 0;
}
int checkIfSessionsExistsCallback(void* data, int argc, char** argv, char** colName) {
    bool* exists = (bool*) data;
    if (argc > 0 && argv[0]) {
        *exists = true;
    }
    return 0;
}
void DbHandler::initDb() {
    int rc;

    rc = sqlite3_open("data.db", &db);
    if (rc) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(1, "Couldn't open database: " + dbErrorMsg);
        exit(1);
    } else {
        log(0, "Connected to the database!");
    }
    std::string sql = "CREATE TABLE IF NOT EXISTS game (session_date INT, best_score INT, number_of_tries INT, flap_count INT, obstacles_count INT);";
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during creating table: " +  dbErrorMsg);
        exit(1);
    }
}
bool DbHandler::checkIfSessionsExists(int started) {
    bool exists = false;
    int rc;
    std::string sql = "SELECT session_date FROM game WHERE session_date=" + std::to_string(started) + ";";
    rc = sqlite3_exec(db, sql.c_str(), checkIfSessionsExistsCallback, &exists, NULL);

    if (rc != SQLITE_OK) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during searching for db entry: " +  dbErrorMsg);
        exit(1);
    }
    return exists;
}
unsigned DbHandler::getDbHighestScore() {
    unsigned highestScore = 0;
    int rc;
    std::string sql = "SELECT MAX(best_score) FROM game";

    rc = sqlite3_exec(db, sql.c_str(), getHighestScoreCallback, &highestScore, 0);

    if (rc != SQLITE_OK ) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during getting highest score: ");
        exit(1);
    }
    return highestScore;
}
void DbHandler::addSession(int started,int score, int tries, int flap_count, int obstacles_count, bool update) {
    std::string sql; 
    int rc;

    if (update) {
        sql = "UPDATE game SET\
               best_score = " + std::to_string(score) + ",\
               number_of_tries = number_of_tries +" + std::to_string(tries) + ", \
               flap_count = flap_count +" + std::to_string(flap_count) + ", \
               obstacles_count = obstacles_count +" + std::to_string(obstacles_count) + " WHERE session_date = " + std::to_string(started);
    } else {
        sql = "INSERT INTO game (session_date, best_score, number_of_tries, flap_count, obstacles_count) VALUES ("\
            + std::to_string(started)+","\
            + std::to_string(score)+","\
            + std::to_string(tries) +","\
            + std::to_string(flap_count) +","\
            + std::to_string(obstacles_count) +");";
    }

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK ) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during inserting session: " + dbErrorMsg);
        exit(1);
    }
}

std::vector<bestScores> DbHandler::getBestScores() {
    static std::vector<bestScores> scores;
    int rc;
    std::string sql = "SELECT * FROM game ORDER BY best_score DESC LIMIT 5";
    rc = sqlite3_exec(db, sql.c_str(), getBestScoresCallback, &scores, 0);
    if (rc !=SQLITE_OK) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during getting best scores: " + dbErrorMsg);
        exit(1);
    }
    return scores;
}
std::array<int, 2> DbHandler::getSecondaryStats() {
    std::array<int, 2> stats; 
    int rc;
    std::string sql = "SELECT SUM(flap_count) AS flapCount, SUM(obstacles_count) AS obstaclesCount FROM game";
    rc = sqlite3_exec(db, sql.c_str(), getSecondaryStatsCallback, &stats, 0);
    if (rc != SQLITE_OK ) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during getting secondary stats: " + dbErrorMsg);
        exit(1);
    }
    printf("%d, %d\n", stats[0], stats[1]);
    return stats;
}
