export CXX="clang++"

mkdir -p ./build/01-introduction-to-cxx

pushd 01-introduction-to-cxx

$CXX -std=c++23 \
    -o ../build/01-introduction-to-cxx/main \
    -I ./include \
    -D YEAR=\"2024\" \
    ./src/main.cpp ./src/Helloworld.cpp

popd