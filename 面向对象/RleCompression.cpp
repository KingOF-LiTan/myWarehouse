#define _CRT_SECURE_NO_WARNINGS 1
#include "RleCompression.h"
using namespace std;
void RleCompression::Rlecompress(const char* filename, const char* outfile) {
	FILE* in = nullptr;
	FILE* out = nullptr;
	in = fopen(filename, "rb");
	int filelen;
	char cur, tmp;
	if ((in == NULL))
		cout << "文件打开失败" << endl;
	else
	{
		out = fopen(outfile, "wb");
		cur = fgetc(in);
		tmp = cur;
		filelen = 1;
		while (!feof(in)) {
			cur = fgetc(in);
			if (cur == tmp) {
				filelen++;
			}
			else {
				fputc(filelen + '0', out);
				fputc(tmp, out);
				tmp = cur;
				filelen = 1;
			}
		}
	}
	fclose(in);
	fclose(out);
}
void RleCompression::Rledecompress(char* filename, char* outfile) {
	FILE* in = nullptr;
	FILE* out = nullptr;
	int filelen;
	char cur;	//光标
	if (!(in = fopen(filename, "rb")))
		cout << "文件打开失败" << endl;
	else
	{
		out = fopen(outfile, "wb");
		while (!feof(in)) {
			filelen = fgetc(in) - '0';
			if (feof(in))break;	//feof的问题,折腾了好一会,不好表述,总之在feof应当在每一次读操作之后判断是否到文件末, 不然会造成多读一次的错误
			cur = fgetc(in);
			while (filelen--)
				fputc(cur, out);
		}
	}
	fclose(in);
	fclose(out);
}
int RleCompression::compress(string ins, string outs)  {
	char ifname[256];//输入的文件
	std::strcpy(ifname, ins.c_str());
	char ofname[256];
	strcpy(ofname, outs.c_str());
	Rlecompress(ifname, ofname);
	return 0;
}
int RleCompression:: decompress(string ins, string outs) {
	char ifname[256];//输入的文件
	strcpy(ifname, ins.c_str());
	char ofname[256];
	strcpy(ofname, outs.c_str());
	Rledecompress(ifname, ofname);
	return 0;
}