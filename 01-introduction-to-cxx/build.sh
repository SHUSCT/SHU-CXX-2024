export CXX="clang++"

$CXX -std=c++23 \
    -o ./main.exe \
    -I ./include \
    -D YEAR=\"2024\" \
    ./src/main.cpp ./src/Helloworld.cpp