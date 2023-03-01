#include "Util.h"

namespace util {
    void writeCommandsToStream(const CommandBlock& source, std::ostream& target) {
        target << "bulk: " << source[0];
        for (std::size_t i = 1; i < source.size(); ++i) {
            target << ", " << source[i];
        }
    }
}