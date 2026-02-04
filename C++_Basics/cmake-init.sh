#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR=${BUILD_DIR:-build}
CXX_STANDARD=${CXX_STANDARD:-23}

CXX_FLAGS=(
  -Wall
    -Wextra
      -Wconversion
        -Wsign-conversion
          -Werror
            -pedantic-errors
              -Weffc++
            )

            cmake -S . -B "$BUILD_DIR" \
                -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
                  -DCMAKE_CXX_STANDARD="$CXX_STANDARD" \
                    -DCMAKE_CXX_FLAGS="${CXX_FLAGS[*]}"

            # Symlink compile_commands.json at project root
            # if [[ -f "$BUILD_DIR/compile_commands.json" ]]; then
            #   ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json
            #   fi
            #
            #   echo "✔ CMake configured in '$BUILD_DIR'"
            #

# chmod +x cmake-init.sh
