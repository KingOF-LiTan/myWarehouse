#pragma once
#include "Choose_algorithm.h"
class CompressionStats {
private:
    long originalSize;
    long compressedSize;

public:
    CompressionStats() : originalSize(0), compressedSize(0) {}

    void addOriginalSize(long size);

    void addCompressedSize(long size);
    double calculateCompressionRatio() const;
    void printStats() const;
};