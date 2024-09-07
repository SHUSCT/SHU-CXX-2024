export CXX="clang++"

mkdir -p ./build/01-introduction-to-cxx

pushd 01-introduction-to-cxx

    $CXX -std=c++23 \
        -D YEAR=\"2024\" \
        -I ./include \
        -c ./src/Helloworld.cpp \
        -o ../build/01-introduction-to-cxx/Helloworld.o

    $CXX -std=c++23 \
        -D YEAR=\"2024\" \
        -I ./include \
        -c ./src/main.cpp \
        -o ../build/01-introduction-to-cxx/main.o

    $CXX -std=c++23 \
        -o ../build/01-introduction-to-cxx/01-introduction-to-cxx \
        ../build/01-introduction-to-cxx/Helloworld.o \
        ../build/01-introduction-to-cxx/main.o

popd