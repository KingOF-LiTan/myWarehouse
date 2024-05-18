#define _CRT_SECURE_NO_WARNINGS 1
#include "HuffmanCompression.h"
using namespace std;
// 选择两个权重最小的节点
void HuffmanCompression::choose(HuffmanCompression::Haff_Node* haff_tree, unsigned int n, int* s1, int* s2) {
	unsigned int i;
	unsigned long min = MAX;
	// 遍历所有节点
	for (i = 0; i < n; ++i)
		// 找到权重最小的且未被选中的节点
		if (haff_tree[i].parent == 0 && haff_tree[i].w < min) {
			min = haff_tree[i].w;
			*s1 = i;
		}
	// 标记第一个选择的节点
	haff_tree[*s1].parent = 1;

	min = MAX;
	// 重新找到权重最小的且未被选中的节点
	for (i = 0; i < n; ++i)
		if (haff_tree[i].parent == 0 && haff_tree[i].w < min) {
			min = haff_tree[i].w;
			*s2 = i;
		}
}

// 创建哈夫曼树
void HuffmanCompression::CreateTree(HuffmanCompression::Haff_Node* haff_tree, unsigned int bit_cnt, unsigned int node_num) {
	unsigned int i;
	int s1, s2;
	// 从 bit_cnt 开始创建哈夫曼树
	for (i = bit_cnt; i < node_num; ++i) {
		choose(haff_tree, i, &s1, &s2); // 选择两个权重最小的节点
		// 将选择的两个节点连接为新的父节点
		haff_tree[s1].parent = haff_tree[s2].parent = i;
		haff_tree[i].left = s1;
		haff_tree[i].right = s2;
		haff_tree[i].w = haff_tree[s1].w + haff_tree[s2].w; // 更新新节点的权重
	}
}

// 生成哈夫曼编码
void HuffmanCompression::Haff_Code(HuffmanCompression::Haff_Node* haff_tree, unsigned int bit_cnt) {
	unsigned int i;
	int cur, next, index;
	char* code_tmp = new char[256];
	code_tmp[256 - 1] = '\0';
	// 遍历所有叶子节点
	for (i = 0; i < bit_cnt; ++i) {
		index = 256 - 1;
		// 从当前节点向上回溯，生成哈夫曼编码
		for (cur = i, next = haff_tree[i].parent; next != 0; cur = next, next = haff_tree[next].parent) {
			if (haff_tree[next].left == cur)
				code_tmp[--index] = '0'; // 若当前节点是父节点的左孩子，则编码为0
			else
				code_tmp[--index] = '1'; // 若当前节点是父节点的右孩子，则编码为1
		}
		// 将生成的编码保存到相应的节点中
		haff_tree[i].code = new char[256 - index];
		strcpy(haff_tree[i].code, &code_tmp[index]);
	}
	delete[] code_tmp;
}



int HuffmanCompression::compress(string ins, string outs) {
	char ifname[256] ;//输入的文件
	//输入为字符串，不能直接用于char数组的初始化
	//采用.c_str来进行转化，再赋值
	strcpy(ifname, ins.c_str());
	char ofname[256];// = "D:\\codex vs2022\\Project12\\ofn.huf";//输出文件路径即文件名格式
	strcpy(ofname, outs.c_str());
	FILE* infile, * outfile;//定义两个操作文件的指针
	unsigned int bit_cnt;		// 字符种类
	unsigned char char_temp;		// 暂存字符
	unsigned long file_len = 0;//文件长度
	TmpNode node_temp;//暂存节点
	unsigned int node_num;//节点数量
	Haff_Node *haff_tree;//定义哈夫树数组
	char code_buf[256] = "\0";		// 待存编码缓冲区，有利于提升读取文件的速度
	unsigned int code_len;//定义编码长度
	TmpNode* tmp_nodes = (TmpNode*)malloc(256 * sizeof(TmpNode));// 初始化暂存结点
	//为什么用暂存节点？ 因为在统计频度过程，如果直接在HN进行统计，需要不停遍历数组
	//暂存节点用ASCII作为下表，可以利用数组的随机存取来提升程序效率
	unsigned int i, j;
	for (i = 0; i < 256; ++i)
	{
		tmp_nodes[i].w = 0;
		tmp_nodes[i].uch = (unsigned char)i;		// 数组的256个下标与256种字符对应
	}//初始化节点，w置0，初始化256个可能的字符
	infile = fopen(ifname, "rb"); //二进制只读打开文件
	if (infile == NULL)// 判断输入文件是否存在
		return -1;
	fread((char*)&char_temp, sizeof(unsigned char), 1, infile);		// 读入一个字符到char_temp
	while (!feof(infile))//feof 文件流末尾标志
	{
		file_len++;
		tmp_nodes[char_temp].w++;// 对应ASCII码下标++
		fread((char*)&char_temp, sizeof(unsigned char), 1, infile);		// 读入一个字符
	}
	fclose(infile);
	//前面暂存数组假设了256种字符，实际不会全部出现，需要剔除频度为0的
	for (i = 0; i < 256 - 1; ++i)
		for (j = i + 1; j < 256; ++j)
			if (tmp_nodes[i].w < tmp_nodes[j].w)
			{
				node_temp = tmp_nodes[i];
				tmp_nodes[i] = tmp_nodes[j];
				tmp_nodes[j] = node_temp;
			}//冒泡排序 从大到小
	// 统计实际的字符种类（出现次数不为0）
	for (i = 0; i < 256; ++i)
		if (tmp_nodes[i].w == 0)
			break;
	bit_cnt = i;//
	if (bit_cnt == 1)//假设只有一种字符，不需要建树，直接写入
	{
		outfile = fopen(ofname, "wb");// 创建压缩后将生成的文件
		fwrite((char*)&bit_cnt, sizeof(unsigned int), 1, outfile);// 写入字符种类
		fwrite((char*)&tmp_nodes[0].uch, sizeof(unsigned char), 1, outfile);	// 写入唯一的字符
		fwrite((char*)&tmp_nodes[0].w, sizeof(unsigned long), 1, outfile);// 写入文件长度
		free(tmp_nodes);
		fclose(outfile);
	}
	else
	{
		node_num = 2 * bit_cnt - 1;		// 节点数为字符2*n-1
		haff_tree = (Haff_Node*)malloc(node_num * sizeof(Haff_Node));// 动态建立哈夫曼树所需结点 大小为2*n-1
		// 初始化前bit_cnt个结点
		for (i = 0; i < bit_cnt; ++i)
		{
			// 将暂存结点的字符和频度拷贝到树结点
			haff_tree[i].uch = tmp_nodes[i].uch;
			haff_tree[i].w = tmp_nodes[i].w;
			haff_tree[i].parent = 0;
		}
		free(tmp_nodes); // 释放暂存区

		for (; i < node_num; ++i)
			haff_tree[i].parent = 0;//初始化，父节点置0
		CreateTree(haff_tree, bit_cnt, node_num);		// 创建哈夫曼树
		Haff_Code(haff_tree, bit_cnt);		// 生成哈夫曼编码   如aaabbcccccddd 
		//'a': 3 次 0
		//'b': 2 次 10
		//'c' : 5 次 11
		//'d' : 3 次 111
		// 写入字符和相应权重，供解压时重建哈夫曼树 
		outfile = fopen(ofname, "wb");					// 打开压缩后将生成的文件
		//压缩文件内  字符种类 字符 对应权重 字符 对应权重-----文件长度--编码--		
		fwrite((char*)&bit_cnt, sizeof(unsigned int), 1, outfile);		// 写入字符种类
		for (i = 0; i < bit_cnt; ++i)
		{
			fwrite((char*)&haff_tree[i].uch, sizeof(unsigned char), 1, outfile);// 写入字符
			fwrite((char*)&haff_tree[i].w, sizeof(unsigned long), 1, outfile);	// 写入字符对应权重
		}

		// 紧接着字符和权重信息后面写入文件长度和字符编码
		fwrite((char*)&file_len, sizeof(unsigned long), 1, outfile);// 写入文件长度
		infile = fopen(ifname, "rb");// 以二进制形式打开待压缩的文件
		fread((char*)&char_temp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
		while (!feof(infile))
		{
			// 匹配字符对应编码
			for (i = 0; i < bit_cnt; ++i)
				if (char_temp == haff_tree[i].uch)
					strcat(code_buf, haff_tree[i].code);

			// 以8位（一个字节长度）为处理单元
			while (strlen(code_buf) >= 8)//字节8bit
			{
				char_temp = '\0';
				for (i = 0; i < 8; ++i)
				{
					char_temp <<= 1;		// 左移一位，为下一个bit腾出位置
					if (code_buf[i] == '1')
						char_temp |= 1;		// 当编码为"1"，通过或操作符将其添加到字节的最低位
				}//将编码序列 code_buf 中的每个字符（'0' 或 '1'）逐个读取，然后将它们依次填入 char_temp 字节中
				fwrite((char*)&char_temp, sizeof(unsigned char), 1, outfile);		// 将字节对应编码存入文件
				strcpy(code_buf, code_buf + 8);		// 编码缓存去除已处理的前八位
			}
			fread((char*)&char_temp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
		}
		// 处理最后不足8bits编码
		code_len = strlen(code_buf);
		if (code_len > 0)
		{
			char_temp = '\0';
			for (i = 0; i < code_len; ++i)
			{
				char_temp <<= 1;//<<=左移位赋值运算符，将所有位左移一位
				if (code_buf[i] == '1')
					char_temp |= 1;//按位或赋值运算符
			}
			char_temp <<= 8 - code_len;       // 将编码字段从尾部移到字节的高位
			fwrite((char*)&char_temp, sizeof(unsigned char), 1, outfile);       // 存入最后一个字节
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		for (i = 0; i < bit_cnt; ++i)
			free(haff_tree[i].code);
		free(haff_tree);
	}

    return 0; // Success
}

int HuffmanCompression::decompress(string ins, string outs) {
	char ifname[256];//输入的文件
	//输入为字符串，不能直接用于char数组的初始化
	//采用.c_str来进行转化，再赋值
	strcpy(ifname, ins.c_str());
	char ofname[256];// = "D:\\codex vs2022\\Project12\\ofn.huf";//输出文件路径即文件名格式
	strcpy(ofname, outs.c_str());
	unsigned int i;
	unsigned long file_len;
	unsigned long writen_len = 0;// 控制文件写入长度
	FILE* infile, * outfile;
	unsigned int bit_cnt;// 存储字符种类
	unsigned int node_num;
	Haff_Node *haff_tree;
	unsigned char code_temp;	// 暂存8bits编码
	unsigned int root;// 保存根节点索引，供匹配编码使用
	//内容为aaabbcccccddd的文本文件压缩后用二进制打开
	//04 00 00 00 63 05 00 00 00 61 03 00 00 00 64 03 00 00 00 62 02 00 00 00 0D 00 54 3F FA 80
	infile = fopen(ifname, "rb");		// 以二进制方式打开压缩文件
	// 判断输入文件是否存在
	if (infile == NULL)
		return -1;

	// 读取压缩文件前端的字符及对应编码，用于重建哈夫曼树 04 00 00 00
	fread((char*)&bit_cnt, sizeof(unsigned int), 1, infile);     // 读取字符种类数
	if (bit_cnt == 1)
	{
		fread((char*)&code_temp, sizeof(unsigned char), 1, infile);     // 读取唯一的字符
		fread((char*)&file_len, sizeof(unsigned long), 1, infile);     // 读取文件长度
		outfile = fopen(ofname, "wb");					// 打开压缩后将生成的文件
		while (file_len--)
			fwrite((char*)&code_temp, sizeof(unsigned char), 1, outfile);
		fclose(infile);
		fclose(outfile);
	}//字符种类为1，不需要建树
	else
	{
		node_num = 2 * bit_cnt - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 04 00 00 00，字符种类为4
		haff_tree = (Haff_Node*)malloc(node_num * sizeof(Haff_Node));		// 动态分配哈夫曼树结点空间
		// 读取字符及对应权重，存入哈夫曼树节点
		for (i = 0; i < bit_cnt; ++i)
		{
			//63 05 00 00  读入字符为63->c, 权重为5
			fread((char*)&haff_tree[i].uch, sizeof(unsigned char), 1, infile);		// 读入字符
			fread((char*)&haff_tree[i].w, sizeof(unsigned long), 1, infile);	// 读入字符对应权重
			haff_tree[i].parent = 0;
		}
		// 初始化后node_num-char_kins个结点的parent
		for (; i < node_num; ++i)
			haff_tree[i].parent = 0;

		CreateTree(haff_tree, bit_cnt, node_num);		// 重建哈夫曼树（与压缩时的一致）

		// 读完字符和权重信息，紧接着读取文件长度和编码，进行解码
		//0D 00 00 00 =13
		fread((char*)&file_len, sizeof(unsigned long), 1, infile);	// 读入文件长度
		outfile = fopen(ofname, "wb");		// 打开压缩后将生成的文件
		root = node_num - 1;
		while (1)
		{
			fread((char*)&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

			// 处理读取的一个字符长度的编码（通常为8位）
			for (i = 0; i < 8; ++i)
			{
				// 由根向下直至叶节点正向匹配编码对应字符
				if (code_temp & 128)//按位与 假如最高位1则右0则左
					root = haff_tree[root].right;
				else
					root = haff_tree[root].left;

				if (root < bit_cnt)//判断根节点索引是否小于字符种类数，是则是叶子节点
				{
					fwrite((char*)&haff_tree[root].uch, sizeof(unsigned char), 1, outfile);
					++writen_len;
					if (writen_len == file_len) break;		// 控制文件长度，跳出内层循环
					root = node_num - 1;        // 复位为根索引，匹配下一个字符
				}
				code_temp <<= 1;		// 将编码缓存的下一位移到最高位，供匹配
			}
			if (writen_len == file_len) break;		// 控制文件长度，跳出外层循环
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		free(haff_tree);
	}

}

