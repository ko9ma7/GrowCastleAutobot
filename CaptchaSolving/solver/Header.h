#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <conio.h>
#include <direct.h>
#include <io.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
#include <sys/stat.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <random>
#include <cstdlib>

using namespace cv;
using namespace std;
using namespace chrono;

extern "C" __declspec(dllexport) int execute(int* arr, int size);