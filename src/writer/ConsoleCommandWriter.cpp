#include "ConsoleCommandWriter.h"
#include "Util.h"

#include <iostream>

ConsoleCommandWriter::ConsoleCommandWriter() : AsyncCommandWriter(1) {
}

void ConsoleCommandWriter::write(const CommandBlock& commands, NumberOfThreads threadNumber) {
    util::writeCommandsToStream(commands, std::cout);
    std::cout << std::endl;
}
