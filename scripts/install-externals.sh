mkdir -p "./build/externals"
ProjectHome=$(pwd)

git submodule update --init

pushd "./externals/spdlog"

    CC=clang CXX=clang++ \
    cmake -G Ninja -B ./build -S . \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPDLOG_BUILD_SHARED=ON \
        -DSPDLOG_ENABLE_PCH=ON \
        -DSPDLOG_BUILD_PIC=ON \
        -DSPDLOG_USE_STD_FORMAT=ON \
        -DSPDLOG_BUILD_EXAMPLE=OFF

    cmake --build ./build -j 8

    cmake --install ./build --prefix "$ProjectHome/build/externals/spdlog"

popd
