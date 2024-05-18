#pragma once
#include "CompressionAlgorithm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#define MAX 4294967295
using namespace std;
class HuffmanCompression:public CompressionAlgorithm {
private:
    struct TmpNode {
        unsigned char uch;
        unsigned long w;
    };

    struct Haff_Node {
        unsigned char uch;
        unsigned long w;
        char* code;
        int parent, left, right;
    };

    unsigned int bit_cnt;

    void choose(Haff_Node* haff_tree, unsigned int n, int* s1, int* s2);//ѡ����
    void CreateTree(Haff_Node* haff_tree, unsigned int bit_cnt, unsigned int node_num);//���ɹ�������
    void Haff_Code(Haff_Node* haff_tree, unsigned int bit_cnt);//���ɹ���������

public:

    int compress(string ins, string outs);
    int decompress(string ins, string outs);
};

