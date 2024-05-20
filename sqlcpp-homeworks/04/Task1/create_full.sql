/*
	Создание базы/примера под Windows и заполнение данными
	Объединины файлы create_base.sql и insert_data.sql
	1. Запустить SQL Shell postgres
	2. Выполнить команду: \i [путь к файлу]/create_full.sql
*/
CREATE DATABASE music_site;

\c music_site;

--- Создание таблиц ---
-- Жанры музыки
CREATE TABLE IF NOT EXISTS genres
(
    genre_id SERIAL PRIMARY KEY,
    genre_name VARCHAR(150) NOT NULL
);

-- Исполнители
CREATE TABLE IF NOT EXISTS artists
(
    artist_id SERIAL PRIMARY KEY,
		artist_name VARCHAR(128) NOT NULL
);

-- Связи жанры - исполнители
CREATE TABLE IF NOT EXISTS genres_artists
(
		genre_id INT REFERENCES genres(genre_id) NOT NULL ,
		artist_id INT REFERENCES artists(artist_id) NOT NULL,
		PRIMARY KEY (genre_id, artist_id)
);

-- Альбомы
CREATE TABLE IF NOT EXISTS albums
(
    album_id SERIAL PRIMARY KEY,
		album_name VARCHAR(150) NOT NULL,
		year_release INT NOT NULL
);

-- Связи исполнители - альбомы
CREATE TABLE IF NOT EXISTS artists_albums
(
		artist_id INT REFERENCES artists(artist_id) NOT NULL,
		album_id INT REFERENCES albums(album_id) NOT NULL,
		PRIMARY KEY (artist_id, album_id)
);

-- Треки
CREATE TABLE IF NOT EXISTS tracks
(
    track_id SERIAL PRIMARY KEY,
		track_name VARCHAR(150) NOT NULL,
		duration INTERVAL NOT NULL,
		album_id INT REFERENCES albums(album_id) NOT NULL
);


-- Сборники
CREATE TABLE IF NOT EXISTS collections
(
    collection_id SERIAL PRIMARY KEY,
		collection_name VARCHAR(150) NOT NULL,
		year_release INT NOT NULL
);

-- Содержимое сборников
CREATE TABLE IF NOT EXISTS compilations
(
		collection_id INT REFERENCES collections(collection_id) NOT NULL,
		track_id INT REFERENCES tracks(track_id) NOT NULL,
		PRIMARY KEY (collection_id, track_id)
);


--- Заполнение таблиц данными
--- insert genres ---
INSERT INTO genres(genre_id, genre_name)
VALUES
(1, 'Heavy metal'),
(2, 'Blues rock'), 
(3, 'Hard rock'),
(4, 'Русский рок');

--- insert artists ---
INSERT INTO artists(artist_id, artist_name)
VALUES
(1, 'Black Sabbath'),
(2, 'Ozzy Osbourne'),
(3, 'Led Zeppelin'),
(4, 'Plant'),
(5, 'Jimmy Page'),
(6, 'Deep Purple'),
(7, 'Jon Lord'),
(8, 'Ritchie Blackmore'),
(9, 'Gillan'),
(10,'David Coverdale'),
(11,'Rainbow'),
(12,'Машина Времени'),
(13,'Би-2'),
(14,'ДДТ'),
(15,'Nautilus Pompilius');

--- insert genres_artists ---
INSERT INTO genres_artists(genre_id, artist_id)
VALUES
(1, 1),
(1, 2),
(2, 3),
(3, 3),
(2, 4),
(3, 4),
(3, 5),
(3, 6),
(3, 7),
(2, 8),
(3, 8),
(3, 9),
(1, 10),
(3, 10),
(3, 11),
(4, 12),
(4, 13),
(4, 14),
(4, 15);

--- insert albums ---
INSERT INTO albums(album_id, album_name, year_release)
VALUES
(1, 'Black Sabbath', 1970),
(2, 'Nostradamus', 2008),
(3, 'Led Zeppelin II', 1969),
(4, 'Led Zeppelin IV', 1971),
(5, 'Physical Graffiti', 1975),
(6, 'Machine Head', 1972),
(7, 'Stormbringer', 1974),
(8, 'In Rock', 1970),
(9, 'Ritchie Blackmore''s Rainbow', 1975),
(10,'Rising', 1976),
(11,'Difficult to Cure', 1981),
(12,'В Метре', 2020),
(13,'В Добрый Час', 1986),
(14,'Аллилуйя', 2022),
(15,'Горизонт событий', 2017),
(16,'Это всё…', 1995),
(17,'Творчество в пустоте', 2021),
(18,'Крылья', 1995);


--- insert artists_albums ---
INSERT INTO artists_albums(artist_id, album_id)
VALUES
(1, 1),
(2, 1),
(1, 2),
(2, 2),
(3, 3),
(4, 3),
(5, 3),
(3, 4),
(3, 5),
(4, 5),
(6, 6),
(7, 6),
(8, 6),
(9, 6),
(6, 7),
(6, 8),
(10, 7),
(7, 8),
(9, 8),
(8, 8),
(11, 9),
(11, 10),
(11, 11),
(12, 12),
(12, 13),
(13, 14),
(13, 15),
(14, 16),
(14, 17),
(15, 18);


--- insert tracks ---
INSERT INTO tracks(track_id, track_name, duration, album_id)
VALUES
(1, 'Sabbath Bloody Sabbath', '00:05:45', 1),
(2, 'A National Acrobat', '00:06:15', 1),
(3, 'Killing Yourself to Live', '00:05:42', 1),
(4, 'Dawn of Creation', '00:02:32', 2),
(5, 'Prophecy', '00:05:27', 2),
(6, 'Awakening', '00:00:53', 2),
(7, 'Whole Lotta Love', '00:05:33', 3),
(8, 'What Is and What Should Never Be', '00:04:47', 3),
(9, 'Ramble On', '00:04:35', 3),
(10,'Moby Dick', '00:04:25', 3),
(11,'Black Dog', '00:04:55', 4),
(12,'Stairway to Heaven', '00:08:02', 4),
(13,'When the Levee Breaks', '00:07:08', 4),
(14,'Custard Pie', '00:04:13', 5),
(15,'Kashmir', '00:08:37', 5),
(16,'Highway Star', '00:06:05', 6),
(17,'Smoke on the Water', '00:05:40', 6),
(18,'Lazy', '00:07:19', 6),
(19,'Stormbringer', '00:04:03', 7),
(20,'Lady Double Dealer', '00:03:19', 7),
(21,'Soldier of Fortune', '00:03:14', 7),
(22,'Speed King', '00:05:54', 8),
(23,'Child in Time', '00:10:20', 8),
(24,'Into the Fire', '00:03:30', 8),
(25,'Man on the Silver Mountain', '00:04:42', 9),
(26,'Catch the Rainbow', '00:06:27', 9),
(27,'Stargazer', '00:08:26', 10),
(28,'Tarot Woman', '00:05:58', 10),
(29,'I Surrender', '00:04:10', 11),
(30,'Difficult To Cure (Beethoven’s Ninth)', '00:05:58', 11),
(31,'In My Time of Dying', '00:11:06', 5),
(32,'Просыпается ветер', '00:04:08', 12),
(33,'Часы', '00:04:26', 12),
(34,'Время ходит на мягких лапах', '00:01:45', 12),
(35,'Мой Путь', '00:03:19', 13),
(36,'Пока горит свеча', '00:04:10', 13),
(37,'За тех, кто в море', '00:03:42', 13),
(38,'Беглый огонь мой', '00:05:58', 14),	
(39,'Волки (2022 version)', '00:04:59', 14),
(40,'Чёрное солнце', '00:04:49', 15),
(41,'Это всё…','00:07:46', 16),
(42,'Глазища','00:05:09', 16),
(43,'Муха','00:06:56', 17),
(44,'Маме','00:00:53', 17),
(45,'Солнце взойдёт','00:03:59', 17),
(46,'Крылья','00:03:46', 18),
(47,'Кто ещё...','00:04:19', 18),
(48,'Одинокая птица','00:04:48', 18),
(49,'Родина', '00:05:26', 15);

--- insert collections ---
INSERT INTO collections(collection_id, collection_name, year_release)
VALUES
(1, 'Made In Japan', 1972),
(2, 'Deep Purple: Collections', 2008),
(3, 'Mothership', 2007),
(4, 'The Very Best of Rainbow', 2020),
(5, 'Серебряный век. Лучшие песни 1991—1997', 2018);

--- insert compilations ---
INSERT INTO compilations(collection_id, track_id)
VALUES
(1, 16),
(1, 23),
(1, 17),
(1, 18),
(1, 22),
(2, 16),
(2, 17), 
(2, 23),
(3, 13),
(3, 15),
(3, 11),
(4, 25),
(4, 26),
(4, 27),
(4, 29),
(5, 48);
