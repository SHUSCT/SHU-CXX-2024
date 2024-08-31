CC=clang CXX=clang++ \
cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_HOME="$(pwd)/build/externals/spdlog" \

cmake --build ./build -j $(nproc)
