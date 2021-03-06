Compiling the Collab3 microservices are fairly easy.

### Dependencies

GCC 10+ or Clang 11+ are recommended compiler versions.

* Boost 1.75 or above
* fmt
* spdlog

You can use either system library versions (if preferred) or use vcpkg for the grunt of them.

### Invoking CMake

These example directions are for Linux, but they should work basically everywhere CMake is.

```bash
$ cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Release
$ cd build
$ cmake --build . # or if you know your generator, use make, ninja, whatever.
# ...
# profit?
```

To use vcpkg, add `-DCMAKE_TOOLCHAIN_FILE=$VCPKG/scripts/buildsystems/vcpkg.cmake` to the first CMake invocation (clue:
the one with `-B build`).

## Building Collab3 Repository Documentation

You'll need to install `mkdocs` and `mkdocs-windmill-dark` via pip.

Run `mkdocs build`. The resulting output will be in `site/`.