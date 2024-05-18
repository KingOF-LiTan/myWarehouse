#pragma once
#ifndef IMAGE_COMPRESSION_H
#define IMAGE_COMPRESSION_H
#include <string>
#include <opencv2/opencv.hpp>
bool compressPicture(std::string file, int presslev = 4);

#endif // IMAGE_COMPRESSION_H