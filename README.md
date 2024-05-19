# ClubSimulation

# Тестовое задание в компанию YADRO 

# Текст задания
Создать программу имитирующую работу компьютерного клуба, обрабатывая события

# Системные требования
CMake (version >=3.10)

MinGW (for Windows)

Googletests

# Инструкция по установке

## Общие шаги
Клонировать данный репозиторий себе на компьютер для этого в нужной папке выполните следующую команду
```
git clone https://github.com/gsgol/ClubSimulation.git
```
затем клонировать репозиторий с гугл тестами
```
git clone https://github.com/google/googletest.git
```
затем создать папку build 
```
mkdir build
```
далее шаги несколько отличаются для разных операционных систем
### Linux
перейти в папку build
```
cd build
```
запустить cmake
```
cmake ..
```
запустить make 
```
make
```
после этого должны появиться 2 .exe файла ClubSimulation.exe и runTests.exe
для запуска приложения с шаблонным вводом выполнить команду 
```
.\ClubSimulation.exe ../input.txt
```
для запуска тестов выполнить комнаду 
```
.\runTests.exe
```
### Windows
выполнить следующую команду
```
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=ПУТЬ_ДО_GCC_НА_ВАШЕМ_КОМПЬЮТЕРЕ -DCMAKE_CXX_COMPILER:FILEPATH=ПУТЬ_ДО_G++_НА_ВАШЕМ_КОМПЬЮТЕРЕ -S ПУТЬ_ДО_ДАННОЙ_ПАПКИ_НА_ВАШЕМ_КОМПЬЮТЕРЕ -B ПУТЬ_ДО_ПАПКИ_build -G "MinGW Makefiles"
```
далее перейти в папку build
```
cd build
```
запустить make 
```
make
```
после этого должны появиться 2 .exe файла ClubSimulation.exe и runTests.exe
для запуска приложения с шаблонным вводом выполнить команду 
```
ClubSimulation.exe ПУТЬ_ДО_ДАННОЙ_ПАПКИ_НА_ВАШЕМ_КОМПЬЮТЕРЕ/input.txt
```
для запуска тестов выполнить комнаду 
```
runTests.exe
```
