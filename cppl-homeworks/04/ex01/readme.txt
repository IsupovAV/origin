Установка библиотеки Catch2 для Windows
Из командной строки выполнить:
1. git clone https://github.com/catchorg/Catch2.git
2. cd Catch2
3. cmake -Bbuild -H. -DBUILD_TESTING=OFF 
4. cmake --build build/ --target install
Библиотека находится в папке C:\Program Files (x86)\Catch2

Запустить build.cmd из папки проекта.
