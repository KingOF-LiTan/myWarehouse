#define _CRT_SECURE_NO_WARNINGS 1
#include "HuffmanCompression.h"
using namespace std;
// ѡ������Ȩ����С�Ľڵ�
void HuffmanCompression::choose(HuffmanCompression::Haff_Node* haff_tree, unsigned int n, int* s1, int* s2) {
	unsigned int i;
	unsigned long min = MAX;
	// �������нڵ�
	for (i = 0; i < n; ++i)
		// �ҵ�Ȩ����С����δ��ѡ�еĽڵ�
		if (haff_tree[i].parent == 0 && haff_tree[i].w < min) {
			min = haff_tree[i].w;
			*s1 = i;
		}
	// ��ǵ�һ��ѡ��Ľڵ�
	haff_tree[*s1].parent = 1;

	min = MAX;
	// �����ҵ�Ȩ����С����δ��ѡ�еĽڵ�
	for (i = 0; i < n; ++i)
		if (haff_tree[i].parent == 0 && haff_tree[i].w < min) {
			min = haff_tree[i].w;
			*s2 = i;
		}
}

// ������������
void HuffmanCompression::CreateTree(HuffmanCompression::Haff_Node* haff_tree, unsigned int bit_cnt, unsigned int node_num) {
	unsigned int i;
	int s1, s2;
	// �� bit_cnt ��ʼ������������
	for (i = bit_cnt; i < node_num; ++i) {
		choose(haff_tree, i, &s1, &s2); // ѡ������Ȩ����С�Ľڵ�
		// ��ѡ��������ڵ�����Ϊ�µĸ��ڵ�
		haff_tree[s1].parent = haff_tree[s2].parent = i;
		haff_tree[i].left = s1;
		haff_tree[i].right = s2;
		haff_tree[i].w = haff_tree[s1].w + haff_tree[s2].w; // �����½ڵ��Ȩ��
	}
}

// ���ɹ���������
void HuffmanCompression::Haff_Code(HuffmanCompression::Haff_Node* haff_tree, unsigned int bit_cnt) {
	unsigned int i;
	int cur, next, index;
	char* code_tmp = new char[256];
	code_tmp[256 - 1] = '\0';
	// ��������Ҷ�ӽڵ�
	for (i = 0; i < bit_cnt; ++i) {
		index = 256 - 1;
		// �ӵ�ǰ�ڵ����ϻ��ݣ����ɹ���������
		for (cur = i, next = haff_tree[i].parent; next != 0; cur = next, next = haff_tree[next].parent) {
			if (haff_tree[next].left == cur)
				code_tmp[--index] = '0'; // ����ǰ�ڵ��Ǹ��ڵ�����ӣ������Ϊ0
			else
				code_tmp[--index] = '1'; // ����ǰ�ڵ��Ǹ��ڵ���Һ��ӣ������Ϊ1
		}
		// �����ɵı��뱣�浽��Ӧ�Ľڵ���
		haff_tree[i].code = new char[256 - index];
		strcpy(haff_tree[i].code, &code_tmp[index]);
	}
	delete[] code_tmp;
}



int HuffmanCompression::compress(string ins, string outs) {
	char ifname[256] ;//������ļ�
	//����Ϊ�ַ���������ֱ������char����ĳ�ʼ��
	//����.c_str������ת�����ٸ�ֵ
	strcpy(ifname, ins.c_str());
	char ofname[256];// = "D:\\codex vs2022\\Project12\\ofn.huf";//����ļ�·�����ļ�����ʽ
	strcpy(ofname, outs.c_str());
	FILE* infile, * outfile;//�������������ļ���ָ��
	unsigned int bit_cnt;		// �ַ�����
	unsigned char char_temp;		// �ݴ��ַ�
	unsigned long file_len = 0;//�ļ�����
	TmpNode node_temp;//�ݴ�ڵ�
	unsigned int node_num;//�ڵ�����
	Haff_Node *haff_tree;//�������������
	char code_buf[256] = "\0";		// ������뻺������������������ȡ�ļ����ٶ�
	unsigned int code_len;//������볤��
	TmpNode* tmp_nodes = (TmpNode*)malloc(256 * sizeof(TmpNode));// ��ʼ���ݴ���
	//Ϊʲô���ݴ�ڵ㣿 ��Ϊ��ͳ��Ƶ�ȹ��̣����ֱ����HN����ͳ�ƣ���Ҫ��ͣ��������
	//�ݴ�ڵ���ASCII��Ϊ�±�������������������ȡ����������Ч��
	unsigned int i, j;
	for (i = 0; i < 256; ++i)
	{
		tmp_nodes[i].w = 0;
		tmp_nodes[i].uch = (unsigned char)i;		// �����256���±���256���ַ���Ӧ
	}//��ʼ���ڵ㣬w��0����ʼ��256�����ܵ��ַ�
	infile = fopen(ifname, "rb"); //������ֻ�����ļ�
	if (infile == NULL)// �ж������ļ��Ƿ����
		return -1;
	fread((char*)&char_temp, sizeof(unsigned char), 1, infile);		// ����һ���ַ���char_temp
	while (!feof(infile))//feof �ļ���ĩβ��־
	{
		file_len++;
		tmp_nodes[char_temp].w++;// ��ӦASCII���±�++
		fread((char*)&char_temp, sizeof(unsigned char), 1, infile);		// ����һ���ַ�
	}
	fclose(infile);
	//ǰ���ݴ����������256���ַ���ʵ�ʲ���ȫ�����֣���Ҫ�޳�Ƶ��Ϊ0��
	for (i = 0; i < 256 - 1; ++i)
		for (j = i + 1; j < 256; ++j)
			if (tmp_nodes[i].w < tmp_nodes[j].w)
			{
				node_temp = tmp_nodes[i];
				tmp_nodes[i] = tmp_nodes[j];
				tmp_nodes[j] = node_temp;
			}//ð������ �Ӵ�С
	// ͳ��ʵ�ʵ��ַ����ࣨ���ִ�����Ϊ0��
	for (i = 0; i < 256; ++i)
		if (tmp_nodes[i].w == 0)
			break;
	bit_cnt = i;//
	if (bit_cnt == 1)//����ֻ��һ���ַ�������Ҫ������ֱ��д��
	{
		outfile = fopen(ofname, "wb");// ����ѹ�������ɵ��ļ�
		fwrite((char*)&bit_cnt, sizeof(unsigned int), 1, outfile);// д���ַ�����
		fwrite((char*)&tmp_nodes[0].uch, sizeof(unsigned char), 1, outfile);	// д��Ψһ���ַ�
		fwrite((char*)&tmp_nodes[0].w, sizeof(unsigned long), 1, outfile);// д���ļ�����
		free(tmp_nodes);
		fclose(outfile);
	}
	else
	{
		node_num = 2 * bit_cnt - 1;		// �ڵ���Ϊ�ַ�2*n-1
		haff_tree = (Haff_Node*)malloc(node_num * sizeof(Haff_Node));// ��̬������������������ ��СΪ2*n-1
		// ��ʼ��ǰbit_cnt�����
		for (i = 0; i < bit_cnt; ++i)
		{
			// ���ݴ�����ַ���Ƶ�ȿ����������
			haff_tree[i].uch = tmp_nodes[i].uch;
			haff_tree[i].w = tmp_nodes[i].w;
			haff_tree[i].parent = 0;
		}
		free(tmp_nodes); // �ͷ��ݴ���

		for (; i < node_num; ++i)
			haff_tree[i].parent = 0;//��ʼ�������ڵ���0
		CreateTree(haff_tree, bit_cnt, node_num);		// ������������
		Haff_Code(haff_tree, bit_cnt);		// ���ɹ���������   ��aaabbcccccddd 
		//'a': 3 �� 0
		//'b': 2 �� 10
		//'c' : 5 �� 11
		//'d' : 3 �� 111
		// д���ַ�����ӦȨ�أ�����ѹʱ�ؽ��������� 
		outfile = fopen(ofname, "wb");					// ��ѹ�������ɵ��ļ�
		//ѹ���ļ���  �ַ����� �ַ� ��ӦȨ�� �ַ� ��ӦȨ��-----�ļ�����--����--		
		fwrite((char*)&bit_cnt, sizeof(unsigned int), 1, outfile);		// д���ַ�����
		for (i = 0; i < bit_cnt; ++i)
		{
			fwrite((char*)&haff_tree[i].uch, sizeof(unsigned char), 1, outfile);// д���ַ�
			fwrite((char*)&haff_tree[i].w, sizeof(unsigned long), 1, outfile);	// д���ַ���ӦȨ��
		}

		// �������ַ���Ȩ����Ϣ����д���ļ����Ⱥ��ַ�����
		fwrite((char*)&file_len, sizeof(unsigned long), 1, outfile);// д���ļ�����
		infile = fopen(ifname, "rb");// �Զ�������ʽ�򿪴�ѹ�����ļ�
		fread((char*)&char_temp, sizeof(unsigned char), 1, infile);     // ÿ�ζ�ȡ8bits
		while (!feof(infile))
		{
			// ƥ���ַ���Ӧ����
			for (i = 0; i < bit_cnt; ++i)
				if (char_temp == haff_tree[i].uch)
					strcat(code_buf, haff_tree[i].code);

			// ��8λ��һ���ֽڳ��ȣ�Ϊ����Ԫ
			while (strlen(code_buf) >= 8)//�ֽ�8bit
			{
				char_temp = '\0';
				for (i = 0; i < 8; ++i)
				{
					char_temp <<= 1;		// ����һλ��Ϊ��һ��bit�ڳ�λ��
					if (code_buf[i] == '1')
						char_temp |= 1;		// ������Ϊ"1"��ͨ���������������ӵ��ֽڵ����λ
				}//���������� code_buf �е�ÿ���ַ���'0' �� '1'�������ȡ��Ȼ�������������� char_temp �ֽ���
				fwrite((char*)&char_temp, sizeof(unsigned char), 1, outfile);		// ���ֽڶ�Ӧ��������ļ�
				strcpy(code_buf, code_buf + 8);		// ���뻺��ȥ���Ѵ����ǰ��λ
			}
			fread((char*)&char_temp, sizeof(unsigned char), 1, infile);     // ÿ�ζ�ȡ8bits
		}
		// ���������8bits����
		code_len = strlen(code_buf);
		if (code_len > 0)
		{
			char_temp = '\0';
			for (i = 0; i < code_len; ++i)
			{
				char_temp <<= 1;//<<=����λ��ֵ�������������λ����һλ
				if (code_buf[i] == '1')
					char_temp |= 1;//��λ��ֵ�����
			}
			char_temp <<= 8 - code_len;       // �������ֶδ�β���Ƶ��ֽڵĸ�λ
			fwrite((char*)&char_temp, sizeof(unsigned char), 1, outfile);       // �������һ���ֽ�
		}

		// �ر��ļ�
		fclose(infile);
		fclose(outfile);

		// �ͷ��ڴ�
		for (i = 0; i < bit_cnt; ++i)
			free(haff_tree[i].code);
		free(haff_tree);
	}

    return 0; // Success
}

int HuffmanCompression::decompress(string ins, string outs) {
	char ifname[256];//������ļ�
	//����Ϊ�ַ���������ֱ������char����ĳ�ʼ��
	//����.c_str������ת�����ٸ�ֵ
	strcpy(ifname, ins.c_str());
	char ofname[256];// = "D:\\codex vs2022\\Project12\\ofn.huf";//����ļ�·�����ļ�����ʽ
	strcpy(ofname, outs.c_str());
	unsigned int i;
	unsigned long file_len;
	unsigned long writen_len = 0;// �����ļ�д�볤��
	FILE* infile, * outfile;
	unsigned int bit_cnt;// �洢�ַ�����
	unsigned int node_num;
	Haff_Node *haff_tree;
	unsigned char code_temp;	// �ݴ�8bits����
	unsigned int root;// ������ڵ���������ƥ�����ʹ��
	//����Ϊaaabbcccccddd���ı��ļ�ѹ�����ö����ƴ�
	//04 00 00 00 63 05 00 00 00 61 03 00 00 00 64 03 00 00 00 62 02 00 00 00 0D 00 54 3F FA 80
	infile = fopen(ifname, "rb");		// �Զ����Ʒ�ʽ��ѹ���ļ�
	// �ж������ļ��Ƿ����
	if (infile == NULL)
		return -1;

	// ��ȡѹ���ļ�ǰ�˵��ַ�����Ӧ���룬�����ؽ��������� 04 00 00 00
	fread((char*)&bit_cnt, sizeof(unsigned int), 1, infile);     // ��ȡ�ַ�������
	if (bit_cnt == 1)
	{
		fread((char*)&code_temp, sizeof(unsigned char), 1, infile);     // ��ȡΨһ���ַ�
		fread((char*)&file_len, sizeof(unsigned long), 1, infile);     // ��ȡ�ļ�����
		outfile = fopen(ofname, "wb");					// ��ѹ�������ɵ��ļ�
		while (file_len--)
			fwrite((char*)&code_temp, sizeof(unsigned char), 1, outfile);
		fclose(infile);
		fclose(outfile);
	}//�ַ�����Ϊ1������Ҫ����
	else
	{
		node_num = 2 * bit_cnt - 1;		// �����ַ������������㽨������������������ 04 00 00 00���ַ�����Ϊ4
		haff_tree = (Haff_Node*)malloc(node_num * sizeof(Haff_Node));		// ��̬��������������ռ�
		// ��ȡ�ַ�����ӦȨ�أ�������������ڵ�
		for (i = 0; i < bit_cnt; ++i)
		{
			//63 05 00 00  �����ַ�Ϊ63->c, Ȩ��Ϊ5
			fread((char*)&haff_tree[i].uch, sizeof(unsigned char), 1, infile);		// �����ַ�
			fread((char*)&haff_tree[i].w, sizeof(unsigned long), 1, infile);	// �����ַ���ӦȨ��
			haff_tree[i].parent = 0;
		}
		// ��ʼ����node_num-char_kins������parent
		for (; i < node_num; ++i)
			haff_tree[i].parent = 0;

		CreateTree(haff_tree, bit_cnt, node_num);		// �ؽ�������������ѹ��ʱ��һ�£�

		// �����ַ���Ȩ����Ϣ�������Ŷ�ȡ�ļ����Ⱥͱ��룬���н���
		//0D 00 00 00 =13
		fread((char*)&file_len, sizeof(unsigned long), 1, infile);	// �����ļ�����
		outfile = fopen(ofname, "wb");		// ��ѹ�������ɵ��ļ�
		root = node_num - 1;
		while (1)
		{
			fread((char*)&code_temp, sizeof(unsigned char), 1, infile);		// ��ȡһ���ַ����ȵı���

			// �����ȡ��һ���ַ����ȵı��루ͨ��Ϊ8λ��
			for (i = 0; i < 8; ++i)
			{
				// �ɸ�����ֱ��Ҷ�ڵ�����ƥ������Ӧ�ַ�
				if (code_temp & 128)//��λ�� �������λ1����0����
					root = haff_tree[root].right;
				else
					root = haff_tree[root].left;

				if (root < bit_cnt)//�жϸ��ڵ������Ƿ�С���ַ���������������Ҷ�ӽڵ�
				{
					fwrite((char*)&haff_tree[root].uch, sizeof(unsigned char), 1, outfile);
					++writen_len;
					if (writen_len == file_len) break;		// �����ļ����ȣ������ڲ�ѭ��
					root = node_num - 1;        // ��λΪ��������ƥ����һ���ַ�
				}
				code_temp <<= 1;		// �����뻺�����һλ�Ƶ����λ����ƥ��
			}
			if (writen_len == file_len) break;		// �����ļ����ȣ��������ѭ��
		}

		// �ر��ļ�
		fclose(infile);
		fclose(outfile);

		// �ͷ��ڴ�
		free(haff_tree);
	}

}

