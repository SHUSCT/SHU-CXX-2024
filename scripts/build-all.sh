SPDLOG_HOME="$(pwd)/build/externals/spdlog"

CC=clang CXX=clang++ \
cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_HOME="$(pwd)/build/externals/spdlog" \
    -DBUILD_SHARED_LIBS=OFF

cmake --build ./build -j $(nproc)
