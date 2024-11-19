#ifndef HERDER_H
#define HEADER_H

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

#include <windows.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt> // For wstring_convert

#include "ImageData.h"

using namespace cv;
using namespace std;
using namespace chrono;

struct Vec3bComparator {
    bool operator() (const Vec3b& lhs, const Vec3b& rhs) const {
        if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
        if (lhs[1] != rhs[1]) return lhs[1] < rhs[1];
        return lhs[2] < rhs[2];
    }
};
struct PointPairComparator {
    bool operator()(const pair<Point2f, Point2f>& a, const pair<Point2f, Point2f>& b) const {
        if (a.first.x != b.first.x) return a.first.x < b.first.x;
        if (a.first.y != b.first.y) return a.first.y < b.first.y;
        if (a.second.x != b.second.x) return a.second.x < b.second.x;
        return a.second.y < b.second.y;
    }
};
struct PathBezierPoints {
    Point2f PS;
    Point2f PC;
    Point2f PE;
    PathBezierPoints(Point2f S, Point2f R, Point2f E) : PS(S), PC(R), PE(E){}
};

int main(int argc, char* argv[]);

void COLORMODE(int mode, Mat& src);
void getDistinctColors(const Mat& image);
void replaceColorsWithBlack(Mat& image, const set<Vec3b, Vec3bComparator>& colorsToReplace);
int pxlCount(const Mat& image, const set<Vec3b, Vec3bComparator>& distinctColors, int sx, int sy, int fx, int fy);
int pxlCount(const Mat& image, Scalar s, int sx, int sy, int fx, int fy);
bool directoryExists(const std::string& dirName);
int saveImagesToFolder(string folderName);
void SetConsoleColor(int color);
string getCurrentDateTime();
bool fileExists(const std::string& filename);
void linearRegression(const std::vector<Point2f>& points, double& m, double& c);
string getPositionStr(int p);

vector<Point2f> findRotatedPart(const Mat& objectPart, const Mat& image, Mat& imageToDraw);
double getMinDist(Point2f& p, int captchaNum, double progress);
void sortValues(std::tuple<int, double> arr[], int size);
void drawQuadraticBezier(Mat& image, Point2f start, Point2f control, Point2f end, Scalar color, int thickness);
Point2f quadraticBezierDerivative(Point2f start, Point2f control, Point2f end, float t);
void drawQuadraticBezierWithArrow(Mat& image, Point2f start, Point2f control, Point2f end, Scalar color, int thickness);


Point2f getQuadraticBezierPoint(const Point2f& ps, const Point2f& pc, const Point2f pe, double t);
void clusterPoints(std::vector<cv::Point2f>& points, double threshold);
void TemplateMatching(const Mat& img, const Mat& templ, double threshold);
std::vector<std::tuple<cv::Mat, cv::Point>> getSubImages(const cv::Mat& image, int subImageWidth, int subImageHeight, int step);
double distance(cv::Point2f p1, cv::Point2f p2);
bool isApproxRectangle(cv::Point2f A, cv::Point2f B, cv::Point2f C, cv::Point2f D, double expectedWidth, double expectedHeight, double tolerance);
cv::Scalar interpolateScalar(const cv::Scalar& start, const cv::Scalar& end, double t);
void removeDuplicatePoints(vector<Point2f>& obj, vector<Point2f>& scene);


//void logP(const std::string& message, int value);
void drawLineThroughPoint(cv::Mat& image, cv::Point point, double angle);

cv::Mat calculateHomography(const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints);
cv::Mat customFindHomography(const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints, int maxIterations = 2000, double reprojectionThreshold = 3.0);

#endif
