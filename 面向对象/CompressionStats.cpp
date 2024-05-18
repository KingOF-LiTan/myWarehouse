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
    std::cout << "ԭʼ�ļ���С: " << originalSize << " �ֽ�\n";
    std::cout << "ѹ�����ļ���С: " << compressedSize << " �ֽ�\n";
    std::cout << "ѹ����: " << (1-calculateCompressionRatio()) * 100 << "%\n";
    //std::cout << "������Ϣ��ѹ�����ļ���С�Ƿ�Ϊ0�� " << (compressedSize == 0 ? "��" : "��") << std::endl;
}
