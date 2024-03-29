SELECT T.TeamNameShort,B.FirstName, B.LastName, BS.HomeRuns, BS.AVG FROM TEAM AS T
JOIN BATTERSTATS AS BS ON BS.TeamID = T.TeamID
JOIN BATTER AS B ON BS.BatterID = B.BatterID
WHERE T.LeagueID = 7 AND T.ConferenceID = 12 AND T.DivisionID = 1
ORDER BY BS.HomeRuns DESC, BS.AVG DESC LIMIT 10;