SPDLOG_HOME="$(pwd)/build/externals/spdlog/install"

cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_HOME="$SPDLOG_HOME" \
    -DBUILD_SHARED_LIBS=OFF

cmake --build ./build -j $(nproc)
