#pragma once

#include "AsyncCommandWriter.h"

class ConsoleCommandWriter : public AsyncCommandWriter {
public:
    ConsoleCommandWriter();

protected:
    void write(const CommandBlock& commands, NumberOfThreads threadNumber) override;

};

