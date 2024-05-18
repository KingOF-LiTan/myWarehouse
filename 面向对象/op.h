#pragma once
#include "Choose_algorithm.h"
#include "CompressionStats.h"
#include "Log.h"
using namespace std;
class Operation {
private:
    CompressionStats compressionStats;
    Logger logger;
public:
    void generateOutputPath(const std::string& inputPath, std::string& outputPath, const std::string& newExtension);
    void execute();
    CompressionStats& getCompressionStats() {
        return compressionStats;
    }
    long getFileSize(const std::string& filename);
};