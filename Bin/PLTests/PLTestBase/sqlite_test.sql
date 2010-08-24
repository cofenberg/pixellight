CREATE TABLE TestTable (
id INTEGER PRIMARY KEY,
name VARCHAR(64),
livel INT NOT NULL
);

CREATE INDEX tt_livel_idx ON TestTable(livel);

INSERT INTO TestTable VALUES (1, 'pippo', 5);
INSERT INTO TestTable VALUES (2, 'pippo2', 4);
INSERT INTO TestTable VALUES (3, 'pipo3', 3);
INSERT INTO TestTable VALUES (4, 'pio4', 3);
INSERT INTO TestTable VALUES (5, 'pi "5"', 3);

CREATE TABLE News (
 id INTEGER PRIMARY KEY,
 author_id INT NOT NULL,
 newsdate DATETIME,
 title VARCHAR(64),
 summary TEXT
);

CREATE INDEX news_author_id_idx ON News(author_id);

CREATE TABLE Authors (
 id INTEGER PRIMARY KEY,
 name VARCHAR(64),
 email VARCHAR(64)
);
