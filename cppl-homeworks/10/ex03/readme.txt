В проекте используется Catch2
Порядок установки библиотеки Catch2 для Windows
Из командной строки выполнить:
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF 
cmake --build build/ --target install
Библиотека будет находится в папке C:\Program Files (x86)\Catch2

Потом запустить build.cmd из папки проекта.
