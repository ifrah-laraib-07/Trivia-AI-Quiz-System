@echo off
g++ -std=c++17 main.cpp src/*.cpp -o TriviaBot.exe
if %ERRORLEVEL% == 0 (
    echo Build successful. Run TriviaBot.exe
) else (
    echo Build failed.
)
