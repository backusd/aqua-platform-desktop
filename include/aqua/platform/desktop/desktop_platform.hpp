#pragma once

#include <chrono>
#include <cstdint>
#include <memory>

#include "aqua/events/event_queue.hpp"
#include "aqua/platform/platform.hpp"
#include "aqua/platform/window.hpp"

namespace aqua::platform::desktop {

class DesktopPlatform final : public aqua::Platform {
public:
  DesktopPlatform() noexcept;
  ~DesktopPlatform() override;

  void set_event_queue(events::EventQueue *queue) noexcept override;
  void poll_events() noexcept override;

  [[nodiscard]] double time() const noexcept override;

  [[nodiscard]] std::unique_ptr<platform::Window>
  create_window(std::uint32_t width, std::uint32_t height,
                const char *title) override;

private:
  events::EventQueue *m_event_queue{nullptr};
  std::chrono::steady_clock::time_point m_start;
};

} // namespace aqua::platform::desktop
