INSERT INTO ELEMENT (ID, LOCKED, ELEMENT_TYPE)
VALUES (1, 0, 'SIGNAL'),
       (2, 0, 'SIGNAL'),
       (3, 0, 'SIGNAL'),
       (4, 0, 'SIGNAL'),
       (5, 0, 'SIGNAL'),
       (6, 0, 'SIGNAL'),
       (7, 0, 'SWITCH'),
       (8, 0, 'SWITCH'),
       (9, 0, 'OPEN_TRACK'),
       (10, 0, 'OPEN_TRACK');

INSERT INTO SIGNAL (ID, DISPLAY_NAME, POINTS_TO)
VALUES (1, 'A', 7),
       (2, 'F', 8),
       (3, 'N1', 7),
       (4, 'N2', 7),
       (5, 'P1', 8),
       (6, 'P2', 8);

SELECT ID, DISPLAY_NAME, INDICATION
FROM SIGNAL;

INSERT INTO SWITCH (ID, DISPLAY_NAME, POSITION, BASE_POSITION, LEFT_ID, RIGHT_ID)
VALUES (7, 'W1', 1, 1, 4, 3),
       (8, 'W2', 0, 0, 5, 6);

SELECT ID, DISPLAY_NAME, POSITION, BASE_POSITION, LEFT_ID, RIGHT_ID
FROM SWITCH;

INSERT INTO OPEN_TRACK (ID, DISPLAY_NAME)
VALUES (9, 'v.u.n. links'),
       (10, 'v.u.n. rechts');

INSERT INTO GRAPH (VERTEX, NEIGHBOUR)
VALUES (9, 1),
       (1, 7),
       (7, 3),
       (7, 4),
       (3, 5),
       (4, 6),
       (5, 8),
       (6, 8),
       (8, 2),
       (2, 10),
       (10, 2),
       (2, 8),
       (8, 5),
       (8, 6),
       (5, 3),
       (6, 4),
       (3, 7),
       (4, 7),
       (7, 1),
       (1, 9);
