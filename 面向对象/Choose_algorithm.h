#pragma once
#include "Choose_algorithm.h"
#include <memory>
#include <string>
#include "CompressionAlgorithm.h"
#include "HuffmanCompression.h"
#include "RleCompression.h"
using namespace std;
class Choose_algorithm {
public:
	static std::unique_ptr<CompressionAlgorithm> createCompressionAlgorithm(const std::string& extension);
};