#define _CRT_SECURE_NO_WARNINGS 1
#include "CompressionAlgorithm.h"
using namespace std;
class RleCompression :public CompressionAlgorithm {
private:
	void Rlecompress(const char* filename, const char* outfile);
	void Rledecompress(char* filename, char* outfile);

public:
	int compress(std::string ins, std::string outs);
	int decompress(std::string ins, std::string outs);

};