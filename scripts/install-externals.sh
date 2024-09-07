mkdir -p "./build/externals"
ProjectHome=$(pwd)
InstallPath="$ProjectHome/build/externals/spdlog/install"

git submodule update --init

pushd "./externals/spdlog"

    rm -rf build

    cmake -G Ninja -B ./build -S . \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPDLOG_BUILD_SHARED=OFF \
        -DSPDLOG_ENABLE_PCH=ON \
        -DSPDLOG_BUILD_PIC=ON \
        -DSPDLOG_USE_STD_FORMAT=OFF \
        -DSPDLOG_BUILD_EXAMPLE=OFF

    cmake --build ./build -j 8

    cmake --install ./build --prefix "$InstallPath"

popd

echo
echo "================================================================================"
echo "Note: spdlog has been installed to \"$InstallPath\"."
echo "Remember to set SPDLOG_HOME to this path when building the project."
echo "================================================================================"

