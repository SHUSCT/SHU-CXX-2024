# This script builds and installs spdlog to the specified path.

SpdlogProjectDir=$1
SpdlogInstallPath=$2
mkdir -p "$SpdlogInstallPath"
ProjectHome=$(pwd)

echo "Building spdlog from $SpdlogProjectDir and installing to $SpdlogInstallPath..."

pushd $SpdlogProjectDir

    rm -rf build

    cmake -G Ninja -B ./build -S . \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPDLOG_BUILD_SHARED=OFF \
        -DSPDLOG_ENABLE_PCH=ON \
        -DSPDLOG_BUILD_PIC=ON \
        -DSPDLOG_USE_STD_FORMAT=OFF \
        -DSPDLOG_BUILD_EXAMPLE=OFF

    cmake --build ./build -j 8

    cmake --install ./build --prefix "$SpdlogInstallPath"

popd

echo "================================================================================"
echo "Note: spdlog has been installed to \"$SpdlogInstallPath\"."
echo "================================================================================"

