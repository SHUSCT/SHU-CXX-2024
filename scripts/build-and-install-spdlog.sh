mkdir -p "./build/externals"

pushd "./externals/spdlog"

    cmake -G Ninja -B ./build -S . \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPDLOG_BUILD_SHARED=ON \
        -DSPDLOG_ENABLE_PCH=ON \
        -DSPDLOG_BUILD_PIC=ON

    cmake --build ./build

    cmake --install ./build --prefix "../../build/externals/spdlog"

popd