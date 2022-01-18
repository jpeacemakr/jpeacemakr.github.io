\c postgres;

DROP DATABASE workshop2;

CREATE DATABASE workshop2;

\c workshop2;

-- creates a table called workshop
CREATE TABLE workshops
(
	workshop_id SERIAL PRIMARY KEY,
	workshop_name TEXT,
	workshop_date DATE,
	workshop_location TEXT,
	workshop_max_seats INTEGER,
	workshop_instructor TEXT
	-- Or this? PRIMARY KEY (workshop_name, workshop_date, workshop_location)
);


CREATE TABLE users
(
	user_name TEXT PRIMARY KEY,
	first_name TEXT,
	last_name TEXT,
	email TEXT
);


CREATE TABLE attends 
(
	user_name TEXT REFERENCES users(user_name),
	workshop_id INTEGER REFERENCES workshops(workshop_id),
	PRIMARY KEY (user_name, workshop_id)
);


-- add default content into workshop for testing
/* INSERT INTO workshops (workshop_name, workshop_date, workshop_location, workshop_max_seats, workshop_instructor) VALUES 
('Library Research', '2019-12-31', 'Richmond, Va.', 30, 'Bettina Phifer'),
('Intro to Databases', '2019-12-29', 'Fredericksburg, Va.', 25, 'Ron Zacharski'),
('Object Orientd Design', '2019-12-27', 'Stafford, Va.', 20, 'Stephen Davies'),
('Multimedia Journalism', '2019-12-25', 'Petersburg, Va.', 15, 'Brian Couturier');

-- add default content into workshop for testing
INSERT INTO users (user_name, first_name, last_name, email) VALUES 
('japples', 'Johnny', 'Appleseed', 'jappleseed@apple.com'),
('honestabe', 'Abraham', 'Linclon', 'lincoln@lincoln.com'),
('geowash', 'George', 'Washington', 'number1prez@dc.gov'),
('superman', 'Clarke', 'Kent', 'superman@justiceleague.org');

-- add default content into workshop for testing
INSERT INTO attends (workshop_id, user_name) VALUES 
(1, 'japples'),
(1, 'honestabe'),
(2, 'geowash'),
(3, 'japples'),
(4, 'superman')
;
*/


-- grant access to users
GRANT SELECT, INSERT, DELETE, UPDATE on workshops to parky;
GRANT SELECT, INSERT, DELETE, UPDATE on users to parky;
GRANT SELECT, INSERT, DELETE, UPDATE on attends to parky;
GRANT USAGE on workshops_workshop_id_seq to parky;
