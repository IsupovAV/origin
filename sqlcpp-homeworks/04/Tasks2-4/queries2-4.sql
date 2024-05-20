/*
 Удобнее проссматривать результаты выполнения запросов в DBeaver
*/

/*
Задание 2
 Написать SELECT-запросы, которые выведут информацию согласно инструкциям ниже.
 Внимание: результаты запросов не должны быть пустыми, учтите это при заполнении таблиц.
*/
-- 1. Название и продолжительность самого длительного трека.
SELECT track_name, duration FROM tracks WHERE duration = (SELECT MAX(duration) FROM tracks);

-- 2. Название треков, продолжительность которых не менее 3,5 минут.
SELECT track_name, duration FROM tracks WHERE duration >= '00:03:30' ORDER BY duration;

--3 Названия сборников, вышедших в период с 2018 по 2020 годы включительно.
SELECT collection_name, year_release FROM collections WHERE year_release BETWEEN 2018 AND 2020;

-- 4. Исполнители, чьё имя состоит из одного слова.
-- Слова разделяются миниму одним пробелом
SELECT artist_name FROM artists WHERE artist_name NOT LIKE '% %';

-- 5. Название треков, которые содержат слова мой или my.
-- Использовал регулярное выражение postresql взято 
-- из https://support.google.com/a/answer/1371417?hl=ru
SELECT track_name FROM tracks WHERE track_name ~ '(?i)(\W|^)(мой|my)(\W|$)'; 

/*
Задание 3
 Написать SELECT-запросы, которые выведут информацию согласно инструкциям ниже.
 Внимание: результаты запросов не должны быть пустыми, при необходимости добавьте 
 данные в таблицы.
*/

-- 1. Количество исполнителей в каждом жанре.
SELECT g.genre_name, (SELECT COUNT(artist_id) FROM genres_artists ga GROUP BY genre_id
HAVING g.genre_id = ga.genre_id)
FROM genres g
ORDER BY genre_id; 

-- 2. Количество треков, вошедших в альбомы 2019–2020 годов.
SELECT count(*) FROM tracks WHERE album_id IN 
	(SELECT album_id FROM albums WHERE year_release between 2019 AND 2020 ORDER BY year_release);

-- 3. средняя продолжительность треков по каждому альбому.
SELECT a.album_id, album_name, date_trunc('second', AVG(duration))  FROM albums a 
INNER JOIN tracks t ON a.album_id = t.album_id
GROUP BY a.album_id
ORDER BY a.album_id;

-- 4. Все исполнители, которые не выпустили альбомы в 2020 году.
SELECT artist_id, artist_name FROM artists a WHERE a.artist_id NOT IN 
	(SELECT distinct a.artist_id FROM artists a, artists_albums aa, albums a2
	WHERE a.artist_id = aa.artist_id AND aa.album_id = a2.album_id AND a2.year_release IN (2020))
ORDER BY artist_id;

-- 5. Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами).
SELECT DISTINCT collection_name FROM collections c, compilations c2, tracks t, artists_albums aa, albums a  WHERE 
c.collection_id = c2.collection_id AND c2.track_id = t.track_id AND t.album_id = a.album_id AND aa.album_id = a.album_id 
AND aa.artist_id = 6; -- Deep Purple

-- 5'. Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами).
-- Через join
SELECT DISTINCT collection_name FROM collections c 
INNER JOIN compilations c2 ON c.collection_id = c2.collection_id
INNER JOIN tracks t ON c2.track_id = t.track_id
INNER JOIN albums a ON t.album_id = a.album_id
INNER JOIN artists_albums aa ON aa.album_id = a.album_id and aa.artist_id = 6; -- Deep Purple


/*
Задание 4*
 Написать SELECT-запросы, которые выведут информацию согласно инструкциям ниже.
 Внимание: результаты запросов не должны быть пустыми, при необходимости добавьте данные в таблицы.
*/

-- 1.  Названия альбомов, в которых присутствуют исполнители более чем одного жанра.
SELECT album_name FROM albums a WHERE 
album_id IN (
	SELECT distinct album_id FROM artists_albums aa WHERE aa.artist_id IN 
		(SELECT artist_id FROM genres_artists ga GROUP BY artist_id HAVING count(genre_id) > 1)
);


-- 2. Наименования треков, которые не входят в сборники.
SELECT track_id, track_name FROM tracks WHERE track_id NOT IN (SELECT track_id FROM compilations c)
ORDER BY track_id;

-- 3. Исполнитель или исполнители, написавшие самый короткий по продолжительности трек, — теоретически таких треков может быть несколько.
SELECT artist_name FROM artists 
WHERE artist_id  IN (
	SELECT artist_id FROM artists_albums aa WHERE album_id IN 
		(
			SELECT album_id FROM tracks t WHERE t.duration = (SELECT min(duration) FROM tracks)
		)
);


-- 4. Названия альбомов, содержащих наименьшее количество треков.
SELECT album_id, album_name FROM albums  
WHERE album_id  IN (SELECT album_id FROM tracks 
GROUP BY album_id 
HAVING count(album_id) = (
	SELECT min(cnt) FROM (
	SELECT count(album_id) cnt FROM tracks GROUP BY album_id
	) 
)
ORDER BY album_id);





