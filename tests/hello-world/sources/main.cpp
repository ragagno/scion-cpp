#include "scion/scion.hpp"

auto main() -> int {
    scion::log::info("hello", "scion {}.{}.{}", scion::version::MAJOR, scion::version::MINOR, scion::version::PATCH);

    return 0;
}
