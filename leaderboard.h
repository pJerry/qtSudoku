/**
  * Die LeaderBoard-Klasse kümmert sich um die Datenbank-Verbindung, abfragen und
  * änderungen.
  *
  * @author Jerome Wirth (532939)
  */
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#include "user.h"

class LeaderBoard
{
public:
    LeaderBoard();
    void printRankings(User users[5]);
    void insertRaninking(QString name, int score);
    void closeConn();

private:
    QSqlDatabase db;
    bool ok;
};

#endif // LEADERBOARD_H
