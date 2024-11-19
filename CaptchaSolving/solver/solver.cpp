#include "Header.h"

using namespace cv;
using namespace std;

extern "C" __declspec(dllexport) int execute(int* arr, int size) {

    bool saveScreenshots;
    bool failMode;
    int testMode = 42;
    int hwnd_callback = 0;

    if (size != 4) {
        return 100;
    }

    hwnd_callback = arr[3];

    ifstream f("slpx.exe");
    if (!f.good()) {
        return 159;
    }

    if (arr[2] == 69) {
        Mat m = cv::Mat::zeros(100, 100, CV_8UC3);

        Vec3b color = m.at<Vec3b>(Point(1, 1));
        color[0] = 11;
        color[1] = 12;
        color[2] = 13;
        m.at<Vec3b>(Point(1, 1)) = color;

        return m.at<Vec3b>(Point(1, 1))[2] * 32 + 4;

    }
    if (arr[2] == 420) {
        Mat m = cv::Mat::zeros(100, 100, CV_8UC3);

        Vec3b color = m.at<Vec3b>(Point(1, 1));
        color[0] = 123;
        color[1] = 111;
        color[2] = 159;
        m.at<Vec3b>(Point(1, 1)) = color;

        return m.at<Vec3b>(Point(1, 1))[2] - m.at<Vec3b>(Point(1, 1))[1] + m.at<Vec3b>(Point(1, 1))[0] - 102;

    }


    //testMode = arr[2] == 0 ? 1 : arr[2];
    //std::string command = "slpx.exe 0 0 " + std::to_string(testMode);

    //wstring temp = wstring(command.begin(), command.end());
    //LPCWSTR wideString = temp.c_str();

    //const char* cstr = command.c_str();
        
    //return system(cstr);
    //ShellExecute(NULL, L"open", L"slpx.exe", wideString, NULL, SW_HIDE);


    if (arr[0] != 0 && arr[0] != 1) {
        return 11;
    }
    if (arr[1] != 0 && arr[1] != 1) {
        return 12;
    }


    saveScreenshots = arr[0];
    failMode = arr[1];

    bool releaseMode = true;

    if (releaseMode) {

        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        std::string exePath = "slpx.exe";
        std::wstring stemp = std::wstring(exePath.begin(), exePath.end());
        LPCWSTR sw = stemp.c_str();

        std::wstring commandLine = stemp + L" " +
            (saveScreenshots ? L"1" : L"0") + L" " +
            (failMode ? L"1" : L"0") + L" " +
            std::to_wstring(hwnd_callback) + L" bmp png";

        if (CreateProcess(sw, &commandLine[0], NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else {
            std::cerr << "Error: Unable to create process." << std::endl;
        }
    }
    else {


        const char* progName = "slpx.exe";
        char* arg0 = new char[std::strlen(progName) + 1];
        strcpy_s(arg0, std::strlen(progName) + 1, progName);


        char* arg1 = new char[2];
        char* arg2 = new char[2];
        strcpy_s(arg1, 2, saveScreenshots ? "1" : "0");
        strcpy_s(arg1, 2, failMode ? "1" : "0");

        std::string testStr = std::to_string(testMode);
        char* arg3 = new char[testStr.length() + 1];

        strcpy_s(arg3, testStr.length() + 1, testStr.c_str());

        std::string hwndStr = std::to_string(hwnd_callback);
        char* arg4 = new char[hwndStr.length() + 1];
        strcpy_s(arg4, hwndStr.length() + 1, hwndStr.c_str());

        char* argv[] = { arg0, arg1, arg2, arg3, arg4 };
            

        //main(5, argv);
    }


    return 115;
}