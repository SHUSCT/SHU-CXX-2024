export CXX="clang++"

mkdir -p ./build/01-introduction-to-cxx

pushd 01-introduction-to-cxx

    $CXX -std=c++23 \
        -D YEAR=\"2024\" \
        -I ./include \
        -c ./src/HelloWorld.cpp \
        -o ../build/01-introduction-to-cxx/HelloWorld.o

    $CXX -std=c++23 \
        -D YEAR=\"2024\" \
        -I ./include \
        -c ./src/main.cpp \
        -o ../build/01-introduction-to-cxx/main.o

    $CXX -std=c++23 \
        -o ../build/01-introduction-to-cxx/01-introduction-to-cxx \
        ../build/01-introduction-to-cxx/HelloWorld.o \
        ../build/01-introduction-to-cxx/main.o

popd