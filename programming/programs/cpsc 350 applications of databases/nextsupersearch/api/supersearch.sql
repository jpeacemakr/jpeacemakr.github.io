\c postgres
DROP DATABASE supersearch;
CREATE DATABASE supersearch;
\c supersearch;

-----------------------------------
-- create movie tables
-----------------------------------
CREATE TABLE movies
(
	movie_id SERIAL PRIMARY KEY,
	movie_name TEXT
);

CREATE TABLE theaters
(
	theater_id SERIAL PRIMARY KEY,
	theater_name TEXT,
	theater_address TEXT,
	theater_city TEXT,	
	theater_zip TEXT
);

CREATE TABLE now_playing
(
	movie_id INTEGER REFERENCES movies(movie_id),
	theater_id INTEGER REFERENCES theaters(theater_id),
	PRIMARY KEY (movie_id, theater_id)
);

---------------------------------------------
-- create store tables
--------------------------------------------
CREATE TABLE stores
(
	store_id SERIAL PRIMARY KEY,
	store_name TEXT,
	store_address TEXT,
	store_city TEXT,
	store_zip TEXT
);

CREATE TABLE storetypes
(
	storetype_id SERIAL PRIMARY KEY,
	storetype_name TEXT
);

CREATE TABLE now_eating
(
	store_id INTEGER REFERENCES stores(store_id),
	storetype_id INTEGER REFERENCES storetypes(storetype_id),
	PRIMARY KEY (store_id, storetype_id)
);



------------------------------------
-- create users 
------------------------------------
CREATE TABLE users
(
	user_id SERIAL PRIMARY KEY,
	user_name TEXT,
	user_username TEXT,
	user_password TEXT,
	user_zip TEXT
);

----------------------------------
-- enter data for movies
----------------------------------
INSERT INTO movies (movie_id, movie_name) VALUES
(1, 'Nobody''s Watching'),
(2, 'It'),
(3, 'The Limehouse Golem'),
(4, 'Despicable Me 3'),
(5, 'Wonder Woman'),
(6, 'The Emoji Movie'),
(7, 'Year By The Sea'),
(8, 'Rememory'),
(9, 'Dunkirk'),
(10, 'Anti Matter');

INSERT INTO theaters (theater_id, theater_name, theater_address, theater_city, theater_zip) VALUES
(1, 'Regal Fredericksburg 15', '3301 Plank Road Route 3W', 'Fredericksburg', 22401),
(2, 'Marquee Cinemas Southpoint 9', '5800 South Point Centre', 'Fredericksburg',  22401),
(3, 'Allen Cinema 4 Mesilla Valley', '700 South Telshor Boulevard', 'Las Cruces', 88005);

INSERT INTO now_playing (movie_id, theater_id) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 2),
(8, 3),
(5, 3),
(9, 3),
(10, 3);

--------------------------------------
-- Enter data for stores
--------------------------------------
INSERT INTO stores (store_id, store_name, store_address, store_city, store_zip) VALUES
(1, 'Hyperion Espresso', '301 William St.', 'Fredericksburg', 22401),
(2, 'Starbucks', '2001 Plank Road', 'Fredericksburg', 22401),
(3, '25 30 Expresso', '400 Princess Anne St', 'Fredericksburg', 22401),
(4, 'Agora Downtown', '520 Caroline St', 'Fredericksburg', 22401),
(5, 'Highpoint Coffee', '615 Caroline St', 'Fredericksburg', 22401),
(6, 'Duck Donuts', '1223 Jefferson Davis Hwy', 'Fredericksburg', 22401),
(7, 'Basilico', '2577 Cowan Blvd', 'Fredericksburg',  22401),
(8, 'Cork and Table', '909 Caroline', 'Fredericksburg',  22401),
(9, 'Orofino', '1251 Carl D Silver Parkway', 'Fredericksburg',  22401),
(10, 'Pancho Villa Mexican Rest', '10500 Spotsylvania Ave', 'Fredericksburg', 22401),
(11, 'Chipotle', '5955 Kingstowne', 'Fredericksburg', 22401),
(12, 'Sedona Taphouse', '591 Williams', 'Fredericksburg', 22401),
(13, 'Pueblo''s Tex Mex Grill', '1320 Jefferson Davis Hwy', 'Fredericksburg', 22401),
(14, 'El Pino', '4211 Plank Road', 'Fredericksburg', 22401),
(15, 'Starbucks', '2808 Telshor Blvd', 'Las Cruces', 88005),
(16, 'Starbucks', '2511 Lohman Ave', 'Las Cruces', 88005),
(17, 'Milagro Coffee Y Espresso', '1733 E. University Ave', 'Las Cruces', 88005),
(18, 'Starbucks', '1500 South Valley',  'Las Cruces', 88005),
(19, 'Bean', '2011 Avenida De Mesilla',  'Las Cruces', 88005),
(20, 'El Comedor', '2190 Avenida De  Mesilla', 'Las Cruces', 88005),
(21, 'Los Compas', '603 S Nevarez St.',  'Las Cruces', 88005),
(22, 'La Fuente', '1710 S Espina',  'Las Cruces', 88005),
(23, 'La Posta', '2410 Calle De San Albino',  'Las Cruces', 88005),
(24, 'El Jacalito', '2215 Missouri Ave',  'Las Cruces', 88005),
(25, 'Peet''s', '2260 Locust',  'Las Cruces', 88005);

INSERT INTO storetypes (storetype_id, storetype_name) VALUES
(1, 'coffee'),
(2, 'Italian'),
(3, 'American'),
(4, 'Mexican restaurant'),
(5, 'donuts'),
(6, 'beer and wine');

INSERT INTO now_eating (store_id, storetype_id) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 2),
(8, 3),
(9, 2),
(10, 4),
(11, 4),
(12, 3),
(13, 4),
(14, 4),
(15, 1),
(16, 1),
(17, 1),
(18, 1),
(19, 1),
(20, 4),
(21, 4),
(22, 4),
(23, 4),
(24, 4),
(25, 1),
(6, 5),
(4, 6),
(12, 6),
(13, 6),
(14, 6),
(20, 6),
(21, 6),
(22, 6),
(23, 6),
(24, 6);


----------------------------------------------------------
-- grant access to users
-------------------------------------------------------------
GRANT SELECT, INSERT on movies to parky;
GRANT USAGE on movies_movie_id_seq to parky;
GRANT SELECT, INSERT on stores to parky;
GRANT USAGE on stores_store_id_seq to parky;
GRANT SELECT, INSERT on storetypes to parky;
GRANT USAGE on storetypes_storetype_id_seq to parky;
GRANT SELECT, INSERT on theaters to parky;
GRANT USAGE on theaters_theater_id_seq to parky;
GRANT SELECT, INSERT on users to parky;
GRANT USAGE on users_user_id_seq to parky;
GRANT SELECT, INSERT on now_playing to parky;
GRANT SELECT, INSERT on now_eating to parky;
