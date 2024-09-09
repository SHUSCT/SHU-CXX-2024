# 01 Env Setup

## 1. Windows

## 2. Mac

## 3. Linux

### Fedora
> Assuming that the version of your Fedora is 22 or later.
* The out-of-box approach is run `sudo dnf groupinstall "Development Tools"`, which will install serials of tools like `gcc`, `make`, `autoconf`, etc. It will install the latest version available in `DNF` package manger. Much like `apt install build-essentials` in Debian.
* (Recommended) `sudo dnf install gcc-<version> make-<version> autoconf-<version> automake-<version> libtool-<version> pkgconfig-<version>`, replace the `<version>` with the version you need. Then, you can have a precise version control over the packages.
  * Tip: If you cannot find the package you want, try `dnf search <package name>`. Some package names are different in Fedora.
* If you want to use the latest version that `DNF` hasn't supported, say the `cmake-3.30`, compile it from scratch.
  * Find the source code on Github
  * Download the code (or `git clone`)
  * Install following the instructions in the repo
  * Add to `PATH` through `~/.bashrc`
  > The method above also applys to the circumstance where you need to downgrade your version of packages. And it occurs often on Fedora.
## 4. Visual Studio Code
### 4.1. Extensions

[.vscode/extensions.json](../.vscode/extensions.json) lists the extensions that are recommended for this project.

### 4.2. Settings

[.vscode/settings.json](../.vscode/settings.json) is the setting file for this project, which overrides the default user settings, if any.

It is worth noting that the default C_Cpp extension is disabled, and Clangd is used instead.

