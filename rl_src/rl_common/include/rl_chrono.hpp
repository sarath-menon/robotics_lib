#pragma once
#include <chrono>
#include <cstdint>
#include <zephyr/zephyr.h>

namespace rl {

struct chrono {

  // gives the system uptime in milliseconds
  static std::int64_t now() {
    std::chrono::duration now_ms = std::chrono::milliseconds(k_uptime_get());
    return now_ms.count();
  }

  // puts current thread to sleep for specific duration
  static void this_thread_sleep(
      const std::chrono::duration<std::int64_t, std::milli> &dur) {
    k_sleep(K_MSEC(dur.count()));
  }

private:
  std::chrono::seconds z_seconds{};
};

} // namespace rl