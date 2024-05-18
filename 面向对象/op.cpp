#define _CRT_SECURE_NO_WARNINGS 1
#include "op.h"
#include "Log.h"
#include <filesystem>
namespace fs = std::filesystem;
//c++ 17
void Operation::generateOutputPath(const std::string& inputPath, std::string& outputPath, const std::string& newExtension) {
    fs::path inputFilePath(inputPath);
    fs::path outputFilePath;

    if (!outputPath.empty()) {
        outputFilePath = fs::path(outputPath);
    }
    else {
        // ����û�δ�������·������Ĭ���������ļ���ͬһĿ¼������ͬ���ļ�
        std::string newFilename = inputFilePath.stem().string() + newExtension;
        outputFilePath = inputFilePath.parent_path() / newFilename;
    }

    // ����µ��ļ���չ��
    

    // �����ɵ����·������
    outputPath = outputFilePath.string();
}
long Operation::getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "�����޷����ļ� " << filename << "��" << std::endl;
        return -1;
    }
    long fileSize = file.tellg();
    if (fileSize == -1) {
        std::cerr << "�����޷���ȡ�ļ���С��" << std::endl;
        return -1;
    }
    return fileSize;
}
void Operation:: execute() {
    std::cout << "*********************easy ��ѹ������*********************" << endl;
    //std::cout << "****֧�ֵĸ�ʽ: ���ڹ����������txt��doc��docx��jpg��jpeg�ļ�ѹ�� \n                ����rle�γ̱����txt�ı�ѹ��\n" << endl;
    //std::cout << "��������չ���Ե��ò��� ���� .huf .doc .rle(���� 'exit' �˳�): \n";
    CompressionStats compressionStats;
    while (true) {
        // �����ļ���
        std::cout << "****֧�ֵĸ�ʽ: ���ڹ����������txt��doc��docx��jpg��jpeg�ļ�ѹ�� \n                ����rle�γ̱����txt�ı�ѹ��\n" << endl;
        std::cout << "��������չ���Ե��ò��� ���� .huf .doc .rle(���� 'exit' �˳�): \n";
        std::string filename;
        std::getline(std::cin, filename);

        if (filename == "exit") {
            break;
        }

        // ��ȡ�ļ���չ��
        size_t pos = filename.find_last_of('.');
        std::string extension;
        if (pos != std::string::npos && pos + 1 < filename.length()) {
            extension = filename.substr(pos + 1);
        }
        else {
            std::cerr << "�����޷���ȡ�ļ���չ����" << std::endl;
            logger.log("�����޷���ȡ�ļ���չ����");
            continue;
        }

        // ���� CompressionFactory ����
        Choose_algorithm fac;

        // �����ļ���չ��ѡ����ʵ�ѹ���㷨
        auto algo = fac.createCompressionAlgorithm(extension);
        if (algo) {
            // ִ��ѹ�����ѹ�߼�
            int op;
            std::cout << "*******************************************��ѡ��������ͣ�******************************************  \n1. ѹ��\n2. ˫��ѹ��\n3. ��ѹ\n";
            std::cin >> op;
            std::cin.ignore(); // ���Ի��з�
            std::string inputpath, outputpath;
            switch (op) {
                //֧��txt jpg doc docx
            case 1:
                std::cout << "�������ѹ���ļ�·��: ";
                std::getline(std::cin, inputpath);
                std::cout << "�����������ļ�·�� (������Ĭ���������ļ�ͬ·��������ͬ���ļ�): "<<endl;
                std::cout << "��������ܺ���ļ�·��: ";
                std::getline(std::cin, outputpath);
                compressionStats.addOriginalSize((unsigned long)getFileSize(inputpath));
                generateOutputPath(inputpath, outputpath, ".ez ");
                if (!(algo->compress(inputpath, outputpath))) {
                    cout << "ѹ���ɹ�" << endl;
                  logger.log("ѹ���ɹ�");
                    compressionStats.addCompressedSize((unsigned long)getFileSize(outputpath));
                    compressionStats.printStats();
                    
                }
                else
                {
                    cout << "ѹ��ʧ��" << endl;
                    logger.log("��ѹʧ��");
                }
     
                break;
            case 2:
                std::cout << "�������ѹ���ļ�·��: ";
                std::getline(std::cin, inputpath);
                std::cout << "�����������ļ�·�� (������Ĭ���������ļ�ͬ·��������ͬ���ļ�)����׺��Ϊ .dhuf : " << endl;
                std::cout << "��������ܺ���ļ�·��: ";
                std::getline(std::cin, outputpath);
                generateOutputPath(inputpath, outputpath, ".dhuf ");
                compressionStats.addOriginalSize((unsigned long)getFileSize(inputpath));
                if (!(algo->compress(inputpath, outputpath))) {
                    algo->compress(inputpath, outputpath);
                    cout << "˫��ѹ���ɹ�" << endl;
                    logger.log("˫��ѹ���ɹ�");
                    compressionStats.addCompressedSize((unsigned long)getFileSize(outputpath));
                    compressionStats.printStats();
                }
                else
                {
                    cout << "ѹ��ʧ��" << endl;
                    logger.log("��ѹʧ��");
                }

                break;

            case 3:
                std::cout << "���������ѹ�ļ�·��: ";
                std::getline(std::cin, inputpath);
                std::cout << "�����������ļ�·�� (������Ĭ���������ļ�ͬ·��������ͬ���ļ�): " << endl;
                std::cout << "�������ѹ����ļ�·��: ";
                std::getline(std::cin, outputpath);
                generateOutputPath(inputpath, outputpath, ".txt ");
                if (!(algo->decompress(inputpath, outputpath))) {
                    cout << "��ѹ�ɹ�" << endl;
                    logger.log("��ѹ�ɹ�");
                }
                else
                {
                    cout << "��ѹʧ��" << endl;
                    logger.log("��ѹʧ��");
                }

                break;
            default:
                std::cerr << "������Ч�Ĳ������͡�" << std::endl;
               logger.log("������Ч�Ĳ������͡�");
                break;




            }
        }
        else {
            std::cerr << "�����޷�ʶ����ļ���ʽ��" << std::endl;
           logger.log("�����޷�ʶ����ļ���ʽ��");
            continue;
        }
    }
}