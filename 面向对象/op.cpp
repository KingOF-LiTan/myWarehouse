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
        // 如果用户未输入输出路径，则默认在输入文件的同一目录下生成同名文件
        std::string newFilename = inputFilePath.stem().string() + newExtension;
        outputFilePath = inputFilePath.parent_path() / newFilename;
    }

    // 添加新的文件扩展名
    

    // 将生成的输出路径返回
    outputPath = outputFilePath.string();
}
long Operation::getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << "。" << std::endl;
        return -1;
    }
    long fileSize = file.tellg();
    if (fileSize == -1) {
        std::cerr << "错误：无法读取文件大小。" << std::endl;
        return -1;
    }
    return fileSize;
}
void Operation:: execute() {
    std::cout << "*********************easy 解压缩工具*********************" << endl;
    //std::cout << "****支持的格式: 基于哈夫曼编码的txt，doc，docx，jpg，jpeg文件压缩 \n                基于rle游程编码的txt文本压缩\n" << endl;
    //std::cout << "请输入拓展名以调用操作 例如 .huf .doc .rle(输入 'exit' 退出): \n";
    CompressionStats compressionStats;
    while (true) {
        // 输入文件名
        std::cout << "****支持的格式: 基于哈夫曼编码的txt，doc，docx，jpg，jpeg文件压缩 \n                基于rle游程编码的txt文本压缩\n" << endl;
        std::cout << "请输入拓展名以调用操作 例如 .huf .doc .rle(输入 'exit' 退出): \n";
        std::string filename;
        std::getline(std::cin, filename);

        if (filename == "exit") {
            break;
        }

        // 获取文件扩展名
        size_t pos = filename.find_last_of('.');
        std::string extension;
        if (pos != std::string::npos && pos + 1 < filename.length()) {
            extension = filename.substr(pos + 1);
        }
        else {
            std::cerr << "错误：无法获取文件扩展名。" << std::endl;
            logger.log("错误：无法获取文件扩展名。");
            continue;
        }

        // 创建 CompressionFactory 对象
        Choose_algorithm fac;

        // 根据文件扩展名选择合适的压缩算法
        auto algo = fac.createCompressionAlgorithm(extension);
        if (algo) {
            // 执行压缩或解压逻辑
            int op;
            std::cout << "*******************************************请选择操作类型：******************************************  \n1. 压缩\n2. 双重压缩\n3. 解压\n";
            std::cin >> op;
            std::cin.ignore(); // 忽略换行符
            std::string inputpath, outputpath;
            switch (op) {
                //支持txt jpg doc docx
            case 1:
                std::cout << "请输入待压缩文件路径: ";
                std::getline(std::cin, inputpath);
                std::cout << "请输入生成文件路径 (留空则默认在输入文件同路径下生成同名文件): "<<endl;
                std::cout << "请输入加密后的文件路径: ";
                std::getline(std::cin, outputpath);
                compressionStats.addOriginalSize((unsigned long)getFileSize(inputpath));
                generateOutputPath(inputpath, outputpath, ".ez ");
                if (!(algo->compress(inputpath, outputpath))) {
                    cout << "压缩成功" << endl;
                  logger.log("压缩成功");
                    compressionStats.addCompressedSize((unsigned long)getFileSize(outputpath));
                    compressionStats.printStats();
                    
                }
                else
                {
                    cout << "压缩失败" << endl;
                    logger.log("解压失败");
                }
     
                break;
            case 2:
                std::cout << "请输入待压缩文件路径: ";
                std::getline(std::cin, inputpath);
                std::cout << "请输入生成文件路径 (留空则默认在输入文件同路径下生成同名文件)，后缀名为 .dhuf : " << endl;
                std::cout << "请输入加密后的文件路径: ";
                std::getline(std::cin, outputpath);
                generateOutputPath(inputpath, outputpath, ".dhuf ");
                compressionStats.addOriginalSize((unsigned long)getFileSize(inputpath));
                if (!(algo->compress(inputpath, outputpath))) {
                    algo->compress(inputpath, outputpath);
                    cout << "双重压缩成功" << endl;
                    logger.log("双重压缩成功");
                    compressionStats.addCompressedSize((unsigned long)getFileSize(outputpath));
                    compressionStats.printStats();
                }
                else
                {
                    cout << "压缩失败" << endl;
                    logger.log("解压失败");
                }

                break;

            case 3:
                std::cout << "请输入待解压文件路径: ";
                std::getline(std::cin, inputpath);
                std::cout << "请输入生成文件路径 (留空则默认在输入文件同路径下生成同名文件): " << endl;
                std::cout << "请输入解压后的文件路径: ";
                std::getline(std::cin, outputpath);
                generateOutputPath(inputpath, outputpath, ".txt ");
                if (!(algo->decompress(inputpath, outputpath))) {
                    cout << "解压成功" << endl;
                    logger.log("解压成功");
                }
                else
                {
                    cout << "解压失败" << endl;
                    logger.log("解压失败");
                }

                break;
            default:
                std::cerr << "错误：无效的操作类型。" << std::endl;
               logger.log("错误：无效的操作类型。");
                break;




            }
        }
        else {
            std::cerr << "错误：无法识别的文件格式。" << std::endl;
           logger.log("错误：无法识别的文件格式。");
            continue;
        }
    }
}