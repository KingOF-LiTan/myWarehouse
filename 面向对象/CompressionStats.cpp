#define _CRT_SECURE_NO_WARNINGS 1
#include "CompressionStats.h"
void CompressionStats::addOriginalSize(long size) {
    originalSize += size;
}

void CompressionStats::addCompressedSize(long size) {
    compressedSize += size;
}

double CompressionStats::calculateCompressionRatio() const {
    if (originalSize == 0) {
        return 0.0;
    }
    return (double)compressedSize / originalSize;
}

void CompressionStats::printStats() const {
    std::cout << "原始文件大小: " << originalSize << " 字节\n";
    std::cout << "压缩后文件大小: " << compressedSize << " 字节\n";
    std::cout << "压缩率: " << (1-calculateCompressionRatio()) * 100 << "%\n";
    //std::cout << "调试信息：压缩后文件大小是否为0？ " << (compressedSize == 0 ? "是" : "否") << std::endl;
}
