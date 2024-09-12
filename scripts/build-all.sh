git submodule update --remote

# IF: SPDLOG_HOME is not set or does not exist, build and install spdlog:
if [ -z "$SPDLOG_HOME" ] || [ ! -d "$SPDLOG_HOME" ]; then
    SupposedSpdlogHome="$(pwd)/build/externals/spdlog/install"
    echo "SPDLOG_HOME is not set. Checking \"$SupposedSpdlogHome\"..."
    if [ -d $SupposedSpdlogHome ]; then
        echo -e "\e[0;32mFound valid spdlog in: $SupposedSpdlogHome"
        echo -e "Setting SPDLOG_HOME to $SupposedSpdlogHome\e[0m"
        SPDLOG_HOME=$SupposedSpdlogHome
    else
        echo "SPDLOG_HOME is not set and \"$SupposedSpdlogHome\" does not exist."
        echo "Using \"./scripts/install-spdlog.sh\" to build and install spdlog as a git submodule."
        # Build and install spdlog.
        # $1: spdlog project directory
        # $2: spdlog install path, i.e., SPDLOG_HOME
        bash ./scripts/build-and-install-spdlog.sh "./externals/spdlog" "$SupposedSpdlogHome"
        if [ -d $SupposedSpdlogHome ]; then
            echo -e "\e[0;32mSuccessfully installed spdlog to: $SupposedSpdlogHome"
            echo -e "Setting SPDLOG_HOME to $SupposedSpdlogHome\e[0m"
            SPDLOG_HOME=$SupposedSpdlogHome
        else
            echo -e "\e[0;31mInstallation of submodule spdlog failed. Can't find a valid SPDLOG_HOME."
            echo -e "Aborting.\e[0m"
            exit 1
        fi
    fi
else 
    # Simply trust that your $SPDLOG_HOME is valid.
    echo -m "\e[0;32mFound valid SPDLOG_HOME in system variable: $SPDLOG_HOME\e[0m"
fi

cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_HOME="$SPDLOG_HOME" \
    -DBUILD_SHARED_LIBS=OFF

cmake --build ./build -j $(nproc)
