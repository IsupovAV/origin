В проекте используется Catch2
Порядок установки библиотеки Catch2 для Windows
Из командной строки выполнить:
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF 
cmake --build build/ --target install
Библиотека будет находится в папке C:\Program Files (x86)\Catch2

Для построения версии - примера запустить из каталога scripts
build.cmd.

Для построения версии с тестами запустить из каталога scripts
test_build.cmd

Результат в папке: bin\Debug 
ex03.exe
unit_tests.exe
