git submodule update --init

# IF SPDLOG_HOME is not set:
if [ -z "$SPDLOG_HOME" ]; then
    echo "SPDLOG_HOME is not set. Checking \"build/externals/spdlog/install\"..."
    SupposedSpdlogHome="$(pwd)/build/externals/spdlog/install"
    if [ -d $SupposedSpdlogHome ]; then
        SPDLOG_HOME=$SupposedSpdlogHome
    else
        echo "SPDLOG_HOME is not set and \"$SupposedSpdlogHome\" does not exist."
        echo "Using \"./scripts/install-spdlog.sh\" to build and install spdlog as a git submodule."
        # Clone, build and install.
        ./scripts/install-spdlog.sh
        if [ -d $SupposedSpdlogHome ]; then
            SPDLOG_HOME=$SupposedSpdlogHome
        else
            echo "Installation of submodule spdlog failed. Can't find a valid SPDLOG_HOME."
            echo "Aborting."
            exit 1
        fi
    fi
else 
    # Simply trust that your $SPDLOG_HOME is valid.
    echo "Found system variable SPDLOG_HOME: $SPDLOG_HOME"
    # If the path does not exist, exit.
    if [ ! -d $SPDLOG_HOME ]; then
        echo "The path does not exist. Can't fina a valid SPDLOG_HOME."
        echo "Aborting."
        exit 1
    fi
fi

cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_HOME="$SPDLOG_HOME" \
    -DBUILD_SHARED_LIBS=OFF

cmake --build ./build -j $(nproc)
