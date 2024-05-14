/*
	создание базы/примера под Windows
	1. Запустить SQL Shell postgres
	2. Выполнить команду: \i [путь к файлу]/emp.sql
*/
CREATE DATABASE emp;

\c emp;

--- Создание таблиц ---

CREATE TABLE IF NOT EXISTS employees
(
  employee_id SERIAL PRIMARY KEY,
	employee_name VARCHAR(150) NOT NULL,
	department INT NOT NULL,
	manager_id INT NULL,
	CHECK(manager_id != employee_id)
);


ALTER TABLE employees 
ADD CONSTRAINT 
fk_manager_id 
FOREIGN KEY (manager_id) 
REFERENCES employees(employee_id)
ON DELETE CASCADE
ON UPDATE RESTRICT
;


INSERT INTO employees(employee_name, department, manager_id)
VALUES
('Коробейников Варфоломей', 1, 3),
('Боур Елена', 2, 10),
('Бендер Остап', 3, NULL),
('Щукина Эллочка', 2, 3),
('Щукин Эрнест', 3, 4),
('Воробьянинов Киса', 2, 3),
('Грицацуева Мадам', 2, 3),
('Востриков Федор', 1, 3),
('Чарушников Максим', 3, 10),
('Ляпис-Трубецкой', 3, NULL);


