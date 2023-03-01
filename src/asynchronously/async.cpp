#include "async.h"
#include "CommandProcessingFacade.h"

#include <string>

namespace async {

    CommandProcessingFacade context;

    async::handle_t connect(std::size_t blockSize) {
        return context.connect(blockSize);
    }

    void receive(async::handle_t handle, const char* data, std::size_t dataSize) {
        std::string command(data, dataSize);
        context.receive(handle, command);
    }

    void disconnect(async::handle_t handle) {
        context.disconnect(handle);
    }
}
