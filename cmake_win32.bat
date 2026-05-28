mkdir build\basilisk-test-runner\Debug && mkdir build\basilisk-test-runner\Release && mkdir build\basilisk-test-runner\RelWithDebInfo
cmake -S . -B build -G "Visual Studio 17 2022" -D ENABLE_OPT=OFF -D CMAKE_BUILD_TYPE=Debug
