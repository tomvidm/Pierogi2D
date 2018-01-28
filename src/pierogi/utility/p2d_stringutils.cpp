#include "p2d_stringutils.hpp"

namespace p2d { namespace utility {
    std::string ntabs(uint n) {
        std::string result;
        for (uint i = 0; i < n; i++) {
            result = result + "  ";
        } return result;
    } // nTabs
} // namespace utility
} // namespace p2d