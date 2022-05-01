#include "include/DbHandler.hpp"

DbHandler::DbHandler(unsigned& highest_score) : highestScore(highest_score) {
    initDb();
    getDbHighestScore();
}
DbHandler::~DbHandler() {
    sqlite3_close(db);
}
// friend funcion
int getHighestScoreCallback(void *data, int argc, char** argv, char**colName) {
    DbHandler *dbHandler = static_cast<DbHandler*>(data);
    if (argc > 0) {
        dbHandler->highestScore = std::stoi(argv[0]);
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
    std::string sql = "CREATE TABLE IF NOT EXISTS game (session_date INT, best_score INT, number_of_tries INT);";
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
void DbHandler::insertSession(int session_started, int n_of_tries) {
    std::string sql = "INSERT INTO game (session_date, best_score, number_of_tries) VALUES ("\
        + std::to_string(session_started)+","\
        + std::to_string(highestScore)+","\
        + std::to_string(n_of_tries) +")";
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
