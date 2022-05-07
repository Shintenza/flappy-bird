#include "include/DbHandler.hpp"

DbHandler::DbHandler(unsigned& highest_score) : highestScore(highest_score) {
    initDb();
    getDbHighestScore();
    /* getBestScores(); */
}
DbHandler::~DbHandler() {
    sqlite3_close(db);
}
// friend funcion
int getHighestScoreCallback(void *data, int argc, char** argv, char**colName) {
    DbHandler *dbHandler = static_cast<DbHandler*>(data);
    printf("%d\n", argc);
    if (argc > 1) {
        dbHandler->highestScore = std::stoi(argv[0]);
    } else {
        dbHandler->highestScore = 0;
    }
    return 0;
}
int getBestScoresCallback(void* data, int argc, char** argv, char** colName) {
    std::vector<bestScores> *scores = static_cast<std::vector<bestScores>*>(data);
    if (argc > 0) {
        bestScores data { std::stoi(argv[0]), std::stoi(argv[1]), std::stoi(argv[2])};
        scores->push_back(data);
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
void DbHandler::getDbHighestScore() {
    int rc;
    std::string sql = "SELECT MAX(best_score) FROM game";
    rc = sqlite3_exec(db, sql.c_str(), getHighestScoreCallback, this, 0);
    if (rc != SQLITE_OK ) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during getting highest score: ");
        exit(1);
    }
}
void DbHandler::insertSession(int session_started, int n_of_tries, int flap_count, int obstacles_count) {
    std::string sql = "INSERT INTO game (session_date, best_score, number_of_tries, flap_count, obstacles_count) VALUES ("\
        + std::to_string(session_started)+","\
        + std::to_string(highestScore)+","\
        + std::to_string(n_of_tries) +","\
        + std::to_string(flap_count) +","\
        + std::to_string(obstacles_count) +");";
    int rc;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK ) {
        std::string dbErrorMsg = sqlite3_errmsg(db);
        log(2, "SQL error during inserting session: " + dbErrorMsg);
        exit(1);
    }
}
void DbHandler::updateHighestScore(int score) {
    highestScore = score;
}
std::vector<bestScores> DbHandler::getBestScores() {
    std::vector<bestScores> scores;
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
