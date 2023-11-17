INSERT INTO ELEMENT (ID, ELEMENT_TYPE)
VALUES (1, 'signal'),
       (2, 'signal'),
       (3, 'signal'),
       (4, 'signal'),
       (5, 'signal'),
       (6, 'signal'),
       (7, 'switch'),
       (8, 'switch'),
       (9, 'open-track'),
       (10, 'open-track');

INSERT INTO SIGNAL (ID, DISPLAY_NAME, POINTS_TO_TYPE, POINTS_TO)
VALUES (1, 'A', 'switch', 7),
       (2, 'F', 'switch', 8),
       (3, 'N1', 'switch', 7),
       (4, 'N2', 'switch', 7),
       (5, 'P1', 'switch', 8),
       (6, 'P2', 'switch', 8);

INSERT INTO SWITCH (ID, DISPLAY_NAME, BASE_POSITION, LEFT_ID, RIGHT_ID)
VALUES (7, 'W1', 1, 4, 3),
       (8, 'W2', 0, 5, 6);

INSERT INTO OPEN_TRACK (ID, DISPLAY_NAME)
VALUES (9, 'v.u.n. links'),
       (10, 'v.u.n. rechts');

INSERT INTO GRAPH (VERTEX, EDGE)
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
