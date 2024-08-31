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
