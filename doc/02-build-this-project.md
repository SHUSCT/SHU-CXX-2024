# Build This Project

This project is consisted of several sub-projects:

- 01-introduction-to-cxx
- 02-basic-cmake-example
- 03-build-and-link-against-libraries
- 06-concept-crtp

> Except for the first one, the rest of the sub-projects are designed to be built using CMake.

To build `01-introduction-to-cxx`, simply run the following command:

```bash
# The generated executable will be placed in the "build/01-introduction" directory
bash 01-introduction-to-cxx/scripts/build.sh
```

To build the rest of the sub-projects, run the following command:

```bash
# The following script will check if $SPDLOG_HOME is set at first;
# If not, clone the spdlog repo (as a submodule), build from source and install it to
# "$ProjectHome/build/externals/spdlog/install".
bash scripts/build-all.sh
```

The generated executables can be found in the "build" directory.
