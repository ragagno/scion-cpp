#include "scion/scion.hpp"
#include "scion/prelude/prelude.hpp"

#include <format>

auto scion::bytes_to_string(usize const size) -> std::string {
    if (size < 1ull << 10ull) {
        return std::format("{}B", size >> 0);
    } else if (size < 1ull << 20ull) {
        return std::format("{}KiB", size >> 10);
    } else if (size < 1ull << 30ull) {
        return std::format("{}MiB", size >> 20);
    } else if (size < 1ull << 40ull) {
        return std::format("{}GiB", size >> 30);
    } else {
        return std::format("{}TiB", size >> 40);
    }
}
