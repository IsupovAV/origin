Решение к занятию "Многопоточность"
Задание 1
 Очередь клиентов
 Создать приложение, которое имитирует очередь в окошко. 
 Для этого нужно создать два потока, работающие с одной разделяемой переменной.
 Первый поток имитирует клиента: раз в секунду он обращается к счётчику клиентов
 и увеличивает его на 1. Максимальное количество клиентов должно быть 
 параметризировано.
 Второй поток имитирует операциониста: раз в 2 секунды он обращается к счётчику 
 клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.

Открыть в Visual Studio файл task1.sln
Собрать исполняемый файл.
