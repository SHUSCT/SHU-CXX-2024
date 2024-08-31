export SPDLOG_HOME="$ProjectHome/build/externals/spdlog"

git submodule update --init

cmake -G Ninja -S . -B ./build -DCMAKE_BUILD_TYPE=Release

cmake --build ./build -j $(nproc)
