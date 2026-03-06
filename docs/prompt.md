Generate the initial skeleton for the Aqua Desktop Platform repository.

This repository implements the platform layer for the Aqua Runtime on
desktop operating systems.

The Aqua Runtime is a C++23 portable runtime that runs deterministic
applications across multiple platforms including WebAssembly and
native desktop environments.

This repository contains the DESKTOP platform implementation that
connects the runtime to operating system services such as windows,
events, and timing.


==================================================
IMPORTANT CONTEXT ABOUT AQUA RUNTIME
==================================================

The runtime lives in a separate repository:

    aqua-runtime

which is clone at C:\dev\aqua-runtime. Before continuing, read and be famililar with the following files:

C:\dev\aqua-runtime\README.md
C:\dev\aqua-runtime\include\aqua\platform\platform.hpp
C:\dev\aqua-runtime\include\aqua\platform\window.hpp

That repository defines the following interfaces:

    aqua::platform::Platform
    aqua::platform::Window

Platform implementations must implement BOTH of these interfaces.

This repository will provide DESKTOP implementations of those interfaces.


==================================================
REPOSITORY GOAL
==================================================

Provide a portable desktop platform implementation supporting:

    Windows
    Linux
    macOS

The platform layer is responsible for:

    - window creation
    - event translation
    - timing
    - OS integration

The runtime itself remains completely platform independent.


==================================================
DESIGN REQUIREMENTS
==================================================

Use the following architecture pattern used in professional engines:

    Platform  -> OS services and event pumping
    Window    -> individual window instance

This separation is critical because it enables:

    - multiple windows
    - headless execution
    - renderer/window decoupling
    - cleaner platform code

Platform objects CREATE windows but do not own them.


==================================================
FILES TO CREATE
==================================================

Create the following structure.


include/aqua/platform/desktop/

    desktop_platform.hpp
    desktop_window.hpp


src/

    desktop_platform.cpp
    desktop_window.cpp


CMakeLists.txt

README.md



==================================================
DESKTOP PLATFORM CLASS
==================================================

Create class:

    aqua::platform::desktop::DesktopPlatform

This class must implement:

    aqua::platform::Platform

Responsibilities:

    - store pointer to EventQueue
    - pump OS events
    - provide time()
    - create windows


Public interface:

class DesktopPlatform final : public aqua::platform::Platform
{
public:
    DesktopPlatform() noexcept;
    ~DesktopPlatform() override;

    void set_event_queue(aqua::events::EventQueue*) noexcept override;

    void poll_events() noexcept override;

    [[nodiscard]] double time() const noexcept override;

    [[nodiscard]] std::unique_ptr<aqua::platform::Window>
    create_window(std::uint32_t width,
                  std::uint32_t height,
                  const char* title) override;

private:
    aqua::events::EventQueue* m_event_queue {nullptr};
};


For now, poll_events() should be implemented as a stub.

Time can be implemented using std::chrono.



==================================================
DESKTOP WINDOW CLASS
==================================================

Create class:

    aqua::platform::desktop::DesktopWindow

This class must implement:

    aqua::platform::Window


Example structure:

class DesktopWindow final : public aqua::platform::Window
{
public:
    DesktopWindow(std::uint32_t width,
                  std::uint32_t height,
                  const char* title);

    ~DesktopWindow() override;

    [[nodiscard]] std::uint32_t width() const noexcept override;
    [[nodiscard]] std::uint32_t height() const noexcept override;

    void set_title(const char* title) noexcept override;

private:
    std::uint32_t m_width;
    std::uint32_t m_height;
    std::string   m_title;
};


No OS APIs should be used yet.

This is just a clean architecture skeleton.



==================================================
NAMESPACE LAYOUT
==================================================

Use this namespace hierarchy:

    aqua::platform::desktop



==================================================
CMAKE CONFIGURATION
==================================================

Create a CMake project that builds a static library:

    aqua_platform_desktop

It must:

- require C++23
- include the include/ directory
- expose public headers
- link to aqua-runtime

Add aqua-runtime according the instructions in C:\dev\aqua-runtime\README.md

Use modern CMake best practices.


==================================================
README CONTENT
==================================================

Create a README.md describing:

- purpose of the repository
- relationship to aqua-runtime
- Platform vs Window architecture
- supported operating systems
- future work (Win32, X11/Wayland, Cocoa)



==================================================
CODING REQUIREMENTS
==================================================

Follow modern C++ best practices:

- C++23
- const correctness
- constexpr where appropriate
- noexcept where possible
- [[nodiscard]] where appropriate
- avoid macros
- avoid global state
- use std::unique_ptr for ownership
- clean header/source separation



==================================================
DO NOT DO THESE THINGS
==================================================

Do NOT:

- implement Win32
- implement X11
- implement Cocoa
- include OS headers
- add threading
- add rendering
- change runtime interfaces
- invent new abstractions


This repository should only contain a clean skeleton implementation
of Platform and Window for desktop platforms.


==================================================
EXPECTED RESULT
==================================================

After generation the repository should:

- compile as a static library
- implement Platform and Window
- contain no OS code yet
- provide a clean base for adding Win32, X11, and Cocoa later.