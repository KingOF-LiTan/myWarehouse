#pragma once
#include <bits/stdc++.h>
using namespace std;
class CompressionAlgorithm {
public:
    virtual int compress(string ins, string outs) = 0;
    virtual int decompress(string ins, string outs) = 0;
    virtual ~CompressionAlgorithm() {}
};