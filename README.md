# Aqua Platform Desktop

This repository provides the **desktop platform layer** for the Aqua Runtime.

It implements the runtime’s platform contracts for native desktop operating systems while keeping the core runtime completely platform-independent.

## Relationship to `aqua-runtime`

The Aqua Runtime lives in a separate repository (expected at `../aqua-runtime` by default) and defines the platform interfaces:

- `aqua::Platform` (OS services + event pumping + window creation)
- `aqua::platform::Window` (an individual window instance)

This repository links against `aqua-runtime` and provides desktop implementations under:

- `aqua::platform::desktop`

## Architecture: Platform vs Window

This repo follows a common professional engine pattern:

- **Platform**: owns OS integration responsibilities (event pumping, timing, window creation).
- **Window**: represents a single window instance.

This separation enables:

- multiple windows
- headless execution
- renderer/window decoupling
- cleaner, testable platform code

Important: the platform **creates** windows but does **not** own them (ownership is returned via `std::unique_ptr`).

## Supported operating systems

This repository is intended to support:

- Windows
- Linux
- macOS

Current status: **skeleton only** (no OS APIs are used yet).

## Build

This project builds a static library target:

- `aqua_platform_desktop`

It depends on the `aqua-runtime` CMake target `aqua-runtime`.

Typical usage (vendored alongside the runtime):

```cmake
add_subdirectory(../aqua-runtime)
add_subdirectory(../aqua-platform-desktop)

target_link_libraries(your_app PRIVATE aqua_platform_desktop)
```

If you vendored `aqua-runtime` as a submodule at `external/aqua-runtime`, no extra configuration is required.

If your `aqua-runtime` checkout is elsewhere, configure with:

```sh
cmake -S . -B build -DAQUA_RUNTIME_DIR=C:/path/to/aqua-runtime
cmake --build build --config Debug
```

## Future work

This repository is designed to be extended with OS-specific backends later, such as:

- Win32
- X11 / Wayland
- Cocoa

Those backends will be responsible for creating real native windows and translating native events into Aqua events.
