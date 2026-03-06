#pragma once

#include <cstdint>
#include <string>

#include "aqua/platform/window.hpp"

namespace aqua::platform::desktop {

class DesktopWindow final : public aqua::platform::Window {
public:
  DesktopWindow(std::uint32_t width, std::uint32_t height, const char *title);
  ~DesktopWindow() override;

  [[nodiscard]] std::uint32_t width() const noexcept override;
  [[nodiscard]] std::uint32_t height() const noexcept override;

  void set_title(const char *title) noexcept override;

private:
  std::uint32_t m_width{};
  std::uint32_t m_height{};
  std::string m_title;
};

} // namespace aqua::platform::desktop
