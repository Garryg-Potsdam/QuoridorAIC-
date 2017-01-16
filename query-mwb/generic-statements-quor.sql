use quordb;

/* Insert a game into the games table */
INSERT INTO games(idgames, isWinner) VALUES(3,'1'); 
SELECT * FROM games;

/* Insert a state into the states table */
INSERT INTO states(idstates, string_representation, int_representation, games_idgames)
VALUES(4, 'ASCII STRING', '1.1293129', 1);

/* Select all the winning states from the game_id is won */
SELECT * FROM states WHERE games_idgames = 0;
