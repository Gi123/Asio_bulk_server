#pragma once

#include "AsyncCommandWriter.h"


using handle_t = void*;

class FileCommandWriter : public AsyncCommandWriter {
public:
    FileCommandWriter();

protected:
    void write(const CommandBlock& commands, NumberOfThreads threadNumber) override;

private:
    /**
     * @return a filename in the format: <timespamp sec>-th-<thread number>[-<file number>].log
     */
    std::string createFilename(NumberOfThreads threadNumber) const;

};

