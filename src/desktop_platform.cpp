
#include "aqua/platform/desktop/desktop_platform.hpp"

#include "aqua/platform/desktop/desktop_window.hpp"

#include <chrono>
#include <memory>

namespace aqua::platform::desktop {

DesktopPlatform::DesktopPlatform() noexcept
    : m_start{std::chrono::steady_clock::now()} {}

DesktopPlatform::~DesktopPlatform() = default;

void DesktopPlatform::set_event_queue(events::EventQueue *queue) noexcept {
  m_event_queue = queue;
}

void DesktopPlatform::poll_events() noexcept {
  // Stub: OS event pumping will be implemented per-platform later.
  (void)m_event_queue;
}

double DesktopPlatform::time() const noexcept {
  const auto now = std::chrono::steady_clock::now();
  const std::chrono::duration<double> elapsed = now - m_start;
  return elapsed.count();
}

std::unique_ptr<platform::Window>
DesktopPlatform::create_window(std::uint32_t width, std::uint32_t height,
                               const char *title) {
  return std::make_unique<DesktopWindow>(width, height, title);
}

} // namespace aqua::platform::desktop
