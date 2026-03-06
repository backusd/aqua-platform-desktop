
#include "aqua/platform/desktop/desktop_window.hpp"

namespace aqua::platform::desktop {

DesktopWindow::DesktopWindow(std::uint32_t width, std::uint32_t height,
                             const char *title)
    : m_width{width}, m_height{height}, m_title{title != nullptr ? title : ""} {
}

DesktopWindow::~DesktopWindow() = default;

std::uint32_t DesktopWindow::width() const noexcept { return m_width; }

std::uint32_t DesktopWindow::height() const noexcept { return m_height; }

void DesktopWindow::set_title(const char *title) noexcept {
  m_title = (title != nullptr) ? title : "";
}

} // namespace aqua::platform::desktop
