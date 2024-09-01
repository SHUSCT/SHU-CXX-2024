# Build This Project

This project is consisted of several sub-projects:

- 01-introduction-to-cxx
- 02-basic-cmake-example
- 03-build-and-link-against-libraries

Except for the first one, the rest of the sub-projects are designed to be built using CMake.

To build the first sub-project, you can simply run the following command:

```bash
bash 01-introduction-to-cxx/scripts/build.sh
```

You can find the generated executable in the "build/01-introduction" directory.

To build the rest of the sub-projects, run the following command:

```bash
bash scripts/install-externals.sh
bash scripts/build-all.sh
```

The generated executables can be found in the "build" directory.

## Notice

- The 01-introduction-to-cxx/Makefile will use a environment variable `SHU_CXX_2024_ROOT_DIR`,
  which should be set to the root directory of this project.
  When you are in the root director of this project, can run with below to build.
  The 01-introduction-to-cxx/Makefile will use `bear` to generate `compile_commands.json` for `clangd`.
  so maybe you should install `bear` first. Or you can remove the `bear` command in the Makefile.

```bash
SHU_CXX_2024_ROOT_DIR=$(pwd) make -f 01-introduction-to-cxx/Makefile
```

