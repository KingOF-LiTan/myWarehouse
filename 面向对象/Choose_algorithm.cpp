#define _CRT_SECURE_NO_WARNINGS 1
#include "Choose_algorithm.h"
using namespace std;
std::unique_ptr<CompressionAlgorithm> Choose_algorithm::createCompressionAlgorithm(const std::string& extension) {
    if (extension == "huf"||extension=="doc"||extension=="jpg"||extension=="jpeg") {
        return std::make_unique<HuffmanCompression>();
    }
    else if (extension == "rle") {
        return std::make_unique<RleCompression>();
    }
    else if (extension == "dhuf") {
        return std::make_unique<HuffmanCompression>();
    }
    else {
        return nullptr; // 无法识别的文件格式
    }
}