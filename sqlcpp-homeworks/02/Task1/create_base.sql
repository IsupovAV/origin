/*
	Создание базы/примера под Windows
	1. Запустить SQL Shell postgres
	2. Выполнить команду: \i [путь к файлу]/create_base.sql
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
