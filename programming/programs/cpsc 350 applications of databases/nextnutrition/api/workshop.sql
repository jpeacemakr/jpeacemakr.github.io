CREATE DATABASE workshop;

\c workshop;

-- creates a table called workshop
CREATE TABLE workshop
(
	id SERIAL PRIMARY KEY,
	workshop_name TEXT,
	attendee_name TEXT
);

-- add default content into workshop for testing
INSERT INTO workshop (workshop_name, attendee_name) VALUES 
('Intro to Databases', 'James Peacemaker'),
('Object Oriented Design', 'James Peacemaker'),
('Intro to Databases', 'Harold Johnson'),
('Intro to Databases', 'Kumar Taylor');


-- grant access to users
GRANT SELECT, INSERT on workshop to parky;
GRANT USAGE on workshop_id_seq to parky;
