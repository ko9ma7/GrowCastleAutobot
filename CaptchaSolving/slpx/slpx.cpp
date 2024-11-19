

#include "slpxHeader.h";

#include <filesystem>
vector<Mat> originalImages;

vector<Mat> resultImages;

string currentDirectoryBackSlashes;
string currentDirectory;

set<Vec3b, Vec3bComparator> uniqueColors;

//vector<Point2f> boxPaths;

const int TOTAL_SCREENS = 24;

std::string processingImageFormat = "bmp";
std::string saveImageFormat = "png";

PathBezierPoints pbp[8][8] = { {PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 0 => 0
                                PathBezierPoints(Point2f(236,103), Point2f(281,30), Point2f(331,121)), // 0 => 1
                                PathBezierPoints(Point2f(236,103), Point2f(308,133), Point2f(363,226)), // 0 => 2
                                PathBezierPoints(Point2f(236,103), Point2f(283,215), Point2f(331,328)), // 0 => 3
                                PathBezierPoints(Point2f(236,103), Point2f(236,232), Point2f(236,361)), // 0 => 4
                                PathBezierPoints(Point2f(236,103), Point2f(194,203), Point2f(140,327)), // 0 => 5
                                PathBezierPoints(Point2f(236,103), Point2f(172,124), Point2f(107,226)), // 0 => 6
                                PathBezierPoints(Point2f(236,103), Point2f(184,32), Point2f(139,123))}, // 0 => 7

                               {PathBezierPoints(Point2f(339,139), Point2f(292,0), Point2f(243,87)), // 1 => 0
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 1 => 1
                                PathBezierPoints(Point2f(339,139), Point2f(359,140), Point2f(370,225)), // 1 => 2
                                PathBezierPoints(Point2f(339,139), Point2f(339,234), Point2f(339,329)), // 1 => 3
                                PathBezierPoints(Point2f(339,139), Point2f(292,253), Point2f(244,362)), // 1 => 4
                                PathBezierPoints(Point2f(339,139), Point2f(234,234), Point2f(150,326)), // 1 => 5
                                PathBezierPoints(Point2f(339,139), Point2f(219,134), Point2f(118,223)), // 1 => 6
                                PathBezierPoints(Point2f(339,139), Point2f(245,29), Point2f(148,123))}, // 1 => 7

                               {PathBezierPoints(Point2f(373, 244), Point2f(308,5), Point2f(246,89)), // 2 => 0
                                PathBezierPoints(Point2f(373,244), Point2f(359,41), Point2f(343,122)), // 2 => 1
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 2 => 2
                                PathBezierPoints(Point2f(373,244), Point2f(360,228), Point2f(341,333)), // 2 => 3
                                PathBezierPoints(Point2f(373,244), Point2f(316,257), Point2f(246,365)), // 2 => 4
                                PathBezierPoints(Point2f(373,244), Point2f(260,231), Point2f(153,329)), // 2 => 5
                                PathBezierPoints(Point2f(373,244), Point2f(250,134), Point2f(118,226)), // 2 => 6
                                PathBezierPoints(Point2f(373,244), Point2f(266,38), Point2f(150,124))}, // 2 => 7

                               {PathBezierPoints(Point2f(340,347), Point2f(291,16), Point2f(244,88)), // 3 => 0
                                PathBezierPoints(Point2f(340,347), Point2f(340,48), Point2f(340,124)), // 3 => 1
                                PathBezierPoints(Point2f(340,347), Point2f(356,140), Point2f(372,228)), // 3 => 2
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 3 => 3
                                PathBezierPoints(Point2f(340,347), Point2f(288,271), Point2f(245,363)), // 3 => 4
                                PathBezierPoints(Point2f(340,347), Point2f(242,241), Point2f(151,326)), // 3 => 5
                                PathBezierPoints(Point2f(340,347), Point2f(228,144), Point2f(115,227)), // 3 => 6
                                PathBezierPoints(Point2f(340,347), Point2f(248,47), Point2f(149,123))}, // 3 => 7

                               {PathBezierPoints(Point2f(236,380), Point2f(236,21), Point2f(236,85)), // 4 => 0
                                PathBezierPoints(Point2f(236, 380), Point2f(279, 55), Point2f(332,123)), // 4 => 1
                                PathBezierPoints(Point2f(236,380), Point2f(301,141), Point2f(366,230)), // 4 => 2
                                PathBezierPoints(Point2f(236,380), Point2f(282,245), Point2f(330,327)), // 4 => 3
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 4 => 4
                                PathBezierPoints(Point2f(236,380), Point2f(186,243), Point2f(140,329)), // 4 => 5
                                PathBezierPoints(Point2f(236,380), Point2f(170,146), Point2f(108,227)), // 4 => 6
                                PathBezierPoints(Point2f(236,380), Point2f(184,52), Point2f(141,122))}, // 4 => 7

                               {PathBezierPoints(Point2f(131,346), Point2f(177,17), Point2f(227,88)), // 5 => 0
                                PathBezierPoints(Point2f(131,346), Point2f(233,47), Point2f(319,122)), // 5 => 1
                                PathBezierPoints(Point2f(131,346), Point2f(240,147), Point2f(353,223)), // 5 => 2
                                PathBezierPoints(Point2f(131,346), Point2f(222,241), Point2f(319,327)), // 5 => 3
                                PathBezierPoints(Point2f(131,346), Point2f(180,270), Point2f(227,365)), // 5 => 4
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 5 => 5
                                PathBezierPoints(Point2f(131,346), Point2f(116,146), Point2f(100,225)), // 5 => 6
                                PathBezierPoints(Point2f(131,346), Point2f(131,44), Point2f(131,124))}, // 5 => 7

                               {PathBezierPoints(Point2f(97,242), Point2f(162,3), Point2f(227,92)), // 6 => 0
                                PathBezierPoints(Point2f(97,242), Point2f(210,40), Point2f(320,122)), // 6 => 1
                                PathBezierPoints(Point2f(97,242), Point2f(228,134), Point2f(352,227)), // 6 => 2
                                PathBezierPoints(Point2f(97,242), Point2f(224,236), Point2f(322,331)), // 6 => 3
                                PathBezierPoints(Point2f(97,242), Point2f(175,274), Point2f(224,363)), // 6 => 4
                                PathBezierPoints(Point2f(97,242), Point2f(112,231), Point2f(128,328)), // 6 => 5
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1)), // 6 => 6
                                PathBezierPoints(Point2f(97,242), Point2f(114,41), Point2f(128,122))}, // 6 => 7

                               {PathBezierPoints(Point2f(131,139), Point2f(181,-5), Point2f(229,92)), // 7 => 0
                                PathBezierPoints(Point2f(131,139), Point2f(229,30), Point2f(322,121)), // 7 => 1
                                PathBezierPoints(Point2f(131,139), Point2f(253,126), Point2f(355,228)), // 7 => 2
                                PathBezierPoints(Point2f(131,139), Point2f(234,228), Point2f(321,328)), // 7 => 3
                                PathBezierPoints(Point2f(131,139), Point2f(173,238), Point2f(227,362)), // 7 => 4
                                PathBezierPoints(Point2f(131,139), Point2f(131,233), Point2f(131,328)), // 7 => 5
                                PathBezierPoints(Point2f(131,139), Point2f(116,127), Point2f(99,226)), // 7 => 6
                                PathBezierPoints(Point2f(-1,-1), Point2f(-1,-1), Point2f(-1,-1))}, }; // 7 => 7











tuple<int, int> pairs[105][4]{ {{0, 1}, {2, 3}, {4, 5}, {6, 7}, },
                                {{0, 1}, {2, 3}, {4, 6}, {5, 7}, },
                                {{0, 1}, {2, 3}, {4, 7}, {5, 6}, },
                                {{0, 1}, {2, 4}, {3, 5}, {6, 7}, },
                                {{0, 1}, {2, 4}, {3, 6}, {5, 7}, },
                                {{0, 1}, {2, 4}, {3, 7}, {5, 6}, },
                                {{0, 1}, {2, 5}, {3, 4}, {6, 7}, },
                                {{0, 1}, {2, 5}, {3, 6}, {4, 7}, },
                                {{0, 1}, {2, 5}, {3, 7}, {4, 6}, },
                                {{0, 1}, {2, 6}, {3, 4}, {5, 7}, },
                                {{0, 1}, {2, 6}, {3, 5}, {4, 7}, },
                                {{0, 1}, {2, 6}, {3, 7}, {4, 5}, },
                                {{0, 1}, {2, 7}, {3, 4}, {5, 6}, },
                                {{0, 1}, {2, 7}, {3, 5}, {4, 6}, },
                                {{0, 1}, {2, 7}, {3, 6}, {4, 5}, },
                                {{0, 2}, {1, 3}, {4, 5}, {6, 7}, },
                                {{0, 2}, {1, 3}, {4, 6}, {5, 7}, },
                                {{0, 2}, {1, 3}, {4, 7}, {5, 6}, },
                                {{0, 2}, {1, 4}, {3, 5}, {6, 7}, },
                                {{0, 2}, {1, 4}, {3, 6}, {5, 7}, },
                                {{0, 2}, {1, 4}, {3, 7}, {5, 6}, },
                                {{0, 2}, {1, 5}, {3, 4}, {6, 7}, },
                                {{0, 2}, {1, 5}, {3, 6}, {4, 7}, },
                                {{0, 2}, {1, 5}, {3, 7}, {4, 6}, },
                                {{0, 2}, {1, 6}, {3, 4}, {5, 7}, },
                                {{0, 2}, {1, 6}, {3, 5}, {4, 7}, },
                                {{0, 2}, {1, 6}, {3, 7}, {4, 5}, },
                                {{0, 2}, {1, 7}, {3, 4}, {5, 6}, },
                                {{0, 2}, {1, 7}, {3, 5}, {4, 6}, },
                                {{0, 2}, {1, 7}, {3, 6}, {4, 5}, },
                                {{0, 3}, {1, 2}, {4, 5}, {6, 7}, },
                                {{0, 3}, {1, 2}, {4, 6}, {5, 7}, },
                                {{0, 3}, {1, 2}, {4, 7}, {5, 6}, },
                                {{0, 3}, {1, 4}, {2, 5}, {6, 7}, },
                                {{0, 3}, {1, 4}, {2, 6}, {5, 7}, },
                                {{0, 3}, {1, 4}, {2, 7}, {5, 6}, },
                                {{0, 3}, {1, 5}, {2, 4}, {6, 7}, },
                                {{0, 3}, {1, 5}, {2, 6}, {4, 7}, },
                                {{0, 3}, {1, 5}, {2, 7}, {4, 6}, },
                                {{0, 3}, {1, 6}, {2, 4}, {5, 7}, },
                                {{0, 3}, {1, 6}, {2, 5}, {4, 7}, },
                                {{0, 3}, {1, 6}, {2, 7}, {4, 5}, },
                                {{0, 3}, {1, 7}, {2, 4}, {5, 6}, },
                                {{0, 3}, {1, 7}, {2, 5}, {4, 6}, },
                                {{0, 3}, {1, 7}, {2, 6}, {4, 5}, },
                                {{0, 4}, {1, 2}, {3, 5}, {6, 7}, },
                                {{0, 4}, {1, 2}, {3, 6}, {5, 7}, },
                                {{0, 4}, {1, 2}, {3, 7}, {5, 6}, },
                                {{0, 4}, {1, 3}, {2, 5}, {6, 7}, },
                                {{0, 4}, {1, 3}, {2, 6}, {5, 7}, },
                                {{0, 4}, {1, 3}, {2, 7}, {5, 6}, },
                                {{0, 4}, {1, 5}, {2, 3}, {6, 7}, },
                                {{0, 4}, {1, 5}, {2, 6}, {3, 7}, },
                                {{0, 4}, {1, 5}, {2, 7}, {3, 6}, },
                                {{0, 4}, {1, 6}, {2, 3}, {5, 7}, },
                                {{0, 4}, {1, 6}, {2, 5}, {3, 7}, },
                                {{0, 4}, {1, 6}, {2, 7}, {3, 5}, },
                                {{0, 4}, {1, 7}, {2, 3}, {5, 6}, },
                                {{0, 4}, {1, 7}, {2, 5}, {3, 6}, },
                                {{0, 4}, {1, 7}, {2, 6}, {3, 5}, },
                                {{0, 5}, {1, 2}, {3, 4}, {6, 7}, },
                                {{0, 5}, {1, 2}, {3, 6}, {4, 7}, },
                                {{0, 5}, {1, 2}, {3, 7}, {4, 6}, },
                                {{0, 5}, {1, 3}, {2, 4}, {6, 7}, },
                                {{0, 5}, {1, 3}, {2, 6}, {4, 7}, },
                                {{0, 5}, {1, 3}, {2, 7}, {4, 6}, },
                                {{0, 5}, {1, 4}, {2, 3}, {6, 7}, },
                                {{0, 5}, {1, 4}, {2, 6}, {3, 7}, },
                                {{0, 5}, {1, 4}, {2, 7}, {3, 6}, },
                                {{0, 5}, {1, 6}, {2, 3}, {4, 7}, },
                                {{0, 5}, {1, 6}, {2, 4}, {3, 7}, },
                                {{0, 5}, {1, 6}, {2, 7}, {3, 4}, },
                                {{0, 5}, {1, 7}, {2, 3}, {4, 6}, },
                                {{0, 5}, {1, 7}, {2, 4}, {3, 6}, },
                                {{0, 5}, {1, 7}, {2, 6}, {3, 4}, },
                                {{0, 6}, {1, 2}, {3, 4}, {5, 7}, },
                                {{0, 6}, {1, 2}, {3, 5}, {4, 7}, },
                                {{0, 6}, {1, 2}, {3, 7}, {4, 5}, },
                                {{0, 6}, {1, 3}, {2, 4}, {5, 7}, },
                                {{0, 6}, {1, 3}, {2, 5}, {4, 7}, },
                                {{0, 6}, {1, 3}, {2, 7}, {4, 5}, },
                                {{0, 6}, {1, 4}, {2, 3}, {5, 7}, },
                                {{0, 6}, {1, 4}, {2, 5}, {3, 7}, },
                                {{0, 6}, {1, 4}, {2, 7}, {3, 5}, },
                                {{0, 6}, {1, 5}, {2, 3}, {4, 7}, },
                                {{0, 6}, {1, 5}, {2, 4}, {3, 7}, },
                                {{0, 6}, {1, 5}, {2, 7}, {3, 4}, },
                                {{0, 6}, {1, 7}, {2, 3}, {4, 5}, },
                                {{0, 6}, {1, 7}, {2, 4}, {3, 5}, },
                                {{0, 6}, {1, 7}, {2, 5}, {3, 4}, },
                                {{0, 7}, {1, 2}, {3, 4}, {5, 6}, },
                                {{0, 7}, {1, 2}, {3, 5}, {4, 6}, },
                                {{0, 7}, {1, 2}, {3, 6}, {4, 5}, },
                                {{0, 7}, {1, 3}, {2, 4}, {5, 6}, },
                                {{0, 7}, {1, 3}, {2, 5}, {4, 6}, },
                                {{0, 7}, {1, 3}, {2, 6}, {4, 5}, },
                                {{0, 7}, {1, 4}, {2, 3}, {5, 6}, },
                                {{0, 7}, {1, 4}, {2, 5}, {3, 6}, },
                                {{0, 7}, {1, 4}, {2, 6}, {3, 5}, },
                                {{0, 7}, {1, 5}, {2, 3}, {4, 6}, },
                                {{0, 7}, {1, 5}, {2, 4}, {3, 6}, },
                                {{0, 7}, {1, 5}, {2, 6}, {3, 4}, },
                                {{0, 7}, {1, 6}, {2, 3}, {4, 5}, },
                                {{0, 7}, {1, 6}, {2, 4}, {3, 5}, },
                                {{0, 7}, {1, 6}, {2, 5}, {3, 4}, }, };

Point2f squareToDetectCrystal[8] = { Point2f(229, 161),
                                    Point2f(290,187),
                                    Point2f(311,230),
                                    Point2f(293, 281),
                                    Point2f(231,309),
                                    Point2f(173,285),
                                    Point2f(144,234),
                                    Point2f(177,184) };


enum Color {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    HOTPINK,
    DEEPPINK,
    MEDIUM_SLATE_BLUE,
    GOLD,
    CHOCOLATE,
    DEEP_SKY_BLUE,
    WHITE,
    BLACK
};

cv::Scalar getColor(Color color) {

    switch (color) {
    case RED:
        return cv::Scalar(0, 0, 255);
    case ORANGE:
        return cv::Scalar(0, 165, 255);
    case YELLOW:
        return cv::Scalar(0, 255, 255);
    case GREEN:
        return cv::Scalar(0, 255, 0);
    case CYAN:
        return cv::Scalar(255, 255, 0);
    case BLUE:
        return cv::Scalar(255, 105, 105);
    case MAGENTA:
        return cv::Scalar(255, 0, 255);
    case HOTPINK:
        return cv::Scalar(180, 105, 255);
    case DEEPPINK:
        return cv::Scalar(147, 20, 255);
    case MEDIUM_SLATE_BLUE:
        return cv::Scalar(238, 104, 123);
    case GOLD:
        return cv::Scalar(0, 215, 255);
    case CHOCOLATE:
        return cv::Scalar(30, 105, 210);
    case DEEP_SKY_BLUE:
        return cv::Scalar(255, 191, 0);
    case WHITE:
        return cv::Scalar(255, 255, 255);
    case BLACK:
        return cv::Scalar(0, 0, 0);
    default:
        return cv::Scalar(0, 0, 0);
    }
}

int main(int argc, char* argv[]) {

    bool gotCWD = false;
    char cwd[_MAX_PATH];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        currentDirectoryBackSlashes = string(cwd);
        currentDirectory = string(cwd);
        std::replace(currentDirectory.begin(), currentDirectory.end(), '\\', '/');
        gotCWD = true;
    }
    else {
        gotCWD = false;
    }

    if (argc != 6) {

        if(true){
            cout << "TEST MODE. IF YOU ARE READING THIS MESSAGE, THEN I FORGOT TO TURN OFF TEST MODE. MESSAGE ME ABOUT IT!." << endl;
        }
        else {
            cout << "Usage: pass 5 parameters:" << endl;
            cout << " - [1] saveScreenshots (0 or 1) - will save original and result images to /Captchas/Captcha_N" << endl <<
                " - [2] failMode (0 or 1) - same as previous, but will save to /Failed captchas/Captcha_N" << endl <<
                " - [3] hwnd_callback - integer value of window, to which answer of captcha will be passed" << endl <<
                " - [4] processing image format (string) - will search for CaptchaImage_N.bmp, if you pass \"bmp\".\nIt must be in current folder " << endl <<
                " - [5] save image format (string) - will save results in given format to /Captchas/Captcha_N,\nor /Failed captchas/Captcha_N" << endl << endl;

            cout << "Example: " << endl;

            if (gotCWD) {
                cout << currentDirectoryBackSlashes << "\\slpx.exe 0 0 0 bmp png" << endl << endl;
            }
            else {
                cout << "slpx.exe 0 0 0 bmp jpg" << endl << endl;
            }

            cout << "Press enter to finish" << endl;

            getchar();

            return 0;
        }


    }

    bool saveScreenshots = false;
    bool failMode = false;
    int hwnd_callback = 0;

    if (argc == 6) {
        saveScreenshots = std::string(argv[1]) == "1";
        failMode = std::string(argv[2]) == "1";
        hwnd_callback = std::stoi(argv[3]);
        processingImageFormat = argv[4];
        saveImageFormat = argv[5];
    }

    if (!gotCWD) {
        cout << "Couldn't get cwd" << endl;
        return 20;
    }



    auto start = high_resolution_clock::now();
    //logP("Start", 0);

    /*vector<Point2f> obj;
    obj.push_back(Point2f(1, 1));
    obj.push_back(Point2f(2, 2));
    obj.push_back(Point2f(4, 4));
    obj.push_back(Point2f(3, 3));
    vector<Point2f> scene;
    scene.push_back(Point2f(1, 2));
    scene.push_back(Point2f(2, 3));
    scene.push_back(Point2f(300, 4));
    scene.push_back(Point2f(4, 5));

    try {
        Mat H = findHomography(obj, scene, RANSAC);
        cout << "Homography matrix:" << endl;
        if (H.empty()) {
            cout << "Homography computation failed, resulting in an empty matrix." << endl;
            return 111;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << H.at<double>(i, j) << " ";
            }
            cout << endl;
        }
    }
    catch (Exception e) {

        cout << "E. what: " << e.what() << endl;
        return 222;
    }*/




    /*
    if (logOutput) {
        logFile.open("giftLog.log", std::ios::app);
        if (logFile) {
            logFile << fixed << setprecision(6);
            logFile << "[" << getCurrentDateTime() << "]" << endl;
            logFileOpened = true;
        }
        //else {
            //cout << "File is not open!" << endl;
        //}
    }
    */

    cv::Mat part1ToFind(101, 75, CV_8UC3, imageArray);

    for (int i = 1; i <= TOTAL_SCREENS; ++i) {

        string filename = format("%s/CaptchaImage_%d.%s", currentDirectory.c_str(), i, processingImageFormat.c_str());

        Mat imgOriginal = imread(filename, IMREAD_COLOR);
        if (imgOriginal.empty()) {
            return i + 50;
        }

        originalImages.push_back(imgOriginal);

    }

    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 8; j++) {
    //         if (i != j) {
    //             drawQuadraticBezier(originalImages[0], pbp[i][j].PS, pbp[i][j].PC, pbp[i][j].PE, getColor(RED), 1);
    //         }
    //     }
    // }

    // cv::imshow("RESULT", originalImages[0]);
    // cv::waitKey(0);


    int thingToTrack = -1;
    int squareSize = 16;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 8; j++) {
            if (pxlCount(originalImages[i], Scalar(73, 87, 98), squareToDetectCrystal[j].x, squareToDetectCrystal[j].y, squareToDetectCrystal[j].x + squareSize, squareToDetectCrystal[j].y + squareSize) < squareSize * squareSize) {
                thingToTrack = j;
                break;
            }
        }
        if (thingToTrack != -1) {
            break;
        }
    }

    //cout << "Tracking " << thingToTrack << endl;

    //Mat firstCopy = originalImages[0].clone();

    for (int i = 0; i < TOTAL_SCREENS; i++) {
        resultImages.push_back(originalImages[i].clone());
    }

    tuple<int, double> totalError[105];

    vector<Point2f> allPoints[TOTAL_SCREENS];

    for (int j = 7; j < TOTAL_SCREENS; j++) {


        //cout << "Image " << j + 1 << endl;
        vector<Point2f> pointsOnFrame = findRotatedPart(part1ToFind, originalImages[j], resultImages[j]);


        for (int i = 0; i < pointsOnFrame.size(); i++) {
            //circle(resultImages[j], pointsOnFrame[i], 3, interpolateScalar(getColor(GREEN), getColor(CYAN), (j - 7) / (TOTAL_SCREENS - 1 - 7)), 2);
            allPoints[j].push_back(pointsOnFrame[i]);
            for (int k = 0; k < 105; k++) {
                std::get<0>(totalError[k]) = k;
                double dst = getMinDist(pointsOnFrame[i], k, (double)(j - 7) / (TOTAL_SCREENS - 1 - 7));
                std::get<1>(totalError[k]) += dst * dst;
            }

        }

        //double threshold = 1;

        //TemplateMatching(originalImages[j], part1ToFind, threshold);

        //cv::imshow("Detected Lines", resultImage);
        //cv::waitKey(0);
    }

    sortValues(totalError, 105);

    //for (int i = 0; i < 105; i++) {
    //    cout << "Captcha " << std::get<0>(totalError[i]) << ": " << std::get<1>(totalError[i]) << endl;
    //}

    int captchaInd = std::get<0>(totalError[0]);
    int answer = -1;

    for (int i = 0; i < 4; i++) {
        int p1 = std::get<0>(pairs[captchaInd][i]);
        int p2 = std::get<1>(pairs[captchaInd][i]);

        if (p1 == thingToTrack) {
            answer = p2;
            break;
        }
        if (p2 == thingToTrack) {
            answer = p1;
            break;
        }
    }

    Point2f redraw_ps;
    Point2f redraw_pc;
    Point2f redraw_pe;

    for (int i = 0; i < 4; i++) {


        int p1 = std::get<0>(pairs[captchaInd][i]);
        int p2 = std::get<1>(pairs[captchaInd][i]);

        Point2f ps = pbp[p1][p2].PS;
        Point2f pc = pbp[p1][p2].PC;
        Point2f pe = pbp[p1][p2].PE;


        Scalar c = getColor(DEEP_SKY_BLUE);

        if (thingToTrack == p1) {
            c = getColor(GREEN);
            redraw_ps = ps;
            redraw_pc = pc;
            redraw_pe = pe;
        }

        for (int i = 7; i < TOTAL_SCREENS; i++) {
            drawQuadraticBezierWithArrow(resultImages[i], ps, pc, pe, c, 4);

            //double progress = (double)(i - 15) / (47 - 15);
            //double negProgress = 1 - progress;
            //circle(resultImages[i], getQuadraticBezierPoint(ps,pc,pe, 1 - (negProgress * negProgress)), 2, getColor(CYAN), 3);

        }

        ps = pbp[p2][p1].PS;
        pc = pbp[p2][p1].PC;
        pe = pbp[p2][p1].PE;


        c = getColor(DEEP_SKY_BLUE);

        if (thingToTrack == p2) {
            c = getColor(GREEN);
            redraw_ps = ps;
            redraw_pc = pc;
            redraw_pe = pe;
        }

        for (int i = 7; i < TOTAL_SCREENS; i++) {
            drawQuadraticBezierWithArrow(resultImages[i], ps, pc, pe, c, 4);


            //double progress = (double)(i - 15) / (47 - 15);
            //double negProgress = 1 - progress;
            //circle(resultImages[i], getQuadraticBezierPoint(ps, pc, pe, 1 - (negProgress * negProgress)), 2, getColor(CYAN), 3);
        }
    }

    for (int i = 7; i < TOTAL_SCREENS; i++) {
        drawQuadraticBezierWithArrow(resultImages[i], redraw_ps, redraw_pc, redraw_pe, getColor(GREEN), 4);
    }

    for (int i = 7; i < TOTAL_SCREENS; i++) {
        for (int j = 0; j < allPoints[i].size(); j++) {
            circle(resultImages[i], allPoints[i][j], 5, getColor(RED), -1);
        }
    }

    //for (int i = 0; i < 24; i++) {
    //    for (int j = 0; j < allPoints[i].size(); j++) {
    //        circle(resultImages[TOTAL_SCREENS - 1], allPoints[i][j], 5, getColor(RED), -1);
    //    }
    //}

    //std::ofstream outputFile("example.txt");

    //if (outputFile.is_open()) {
        // Write data to the file
    //    for (int i = 0; i < boxPaths.size(); i++) {
    //        outputFile << boxPaths[i].x << "\t" << boxPaths[i].y << endl;
    //    }
        // Close the file
    //    outputFile.close();
    //}
    //else {
    //    std::cerr << "Failed to open the file." << std::endl;
    //}

    //imshow("Paths", firstCopy);
    //waitKey(0);
    int rightCaptchaIndex = std::get<0>(totalError[0]);

    for (int i = 104; i >=0; i--) {

        //logP("C ", std::get<0>(totalError[i]));
        //logP("C       ", std::get<1>(totalError[i]));

        int captchaIndex = std::get<0>(totalError[i]);

        


        cout << "Captcha " << captchaIndex << ": "
            << "(" << std::get<0>(pairs[captchaIndex][0]) << " => " << std::get<1>(pairs[captchaIndex][0]) << ") "
            << "(" << std::get<0>(pairs[captchaIndex][1]) << " => " << std::get<1>(pairs[captchaIndex][1]) << ") "
            << "(" << std::get<0>(pairs[captchaIndex][2]) << " => " << std::get<1>(pairs[captchaIndex][2]) << ") "
            << "(" << std::get<0>(pairs[captchaIndex][3]) << " => " << std::get<1>(pairs[captchaIndex][3]) << ") "
            
            << (int)std::get<1>(totalError[i]) << " total error";


        if (i != 104) {
            cout << " (" << std::get<1>(totalError[i]) / std::get<1>(totalError[i + 1]) * 100 << "% comparing to next)" << endl;
            if (i == 0) {
                cout << endl;
            }
        }
        else {
            cout << endl;
        }

    }

    cout << "Most likely captcha: " << rightCaptchaIndex << " "

        << "(" << getPositionStr(std::get<0>(pairs[rightCaptchaIndex][0])) << " => " << getPositionStr(std::get<1>(pairs[rightCaptchaIndex][0])) << ") "
        << "(" << getPositionStr(std::get<0>(pairs[rightCaptchaIndex][1])) << " => " << getPositionStr(std::get<1>(pairs[rightCaptchaIndex][1])) << ") "
        << "(" << getPositionStr(std::get<0>(pairs[rightCaptchaIndex][2])) << " => " << getPositionStr(std::get<1>(pairs[rightCaptchaIndex][2])) << ") "
        << "(" << getPositionStr(std::get<0>(pairs[rightCaptchaIndex][3])) << " => " << getPositionStr(std::get<1>(pairs[rightCaptchaIndex][3])) << ") " << endl << endl;


    cout << "Tracking: " << getPositionStr(thingToTrack) << endl;
    cout << "Result: " << getPositionStr(answer) << endl << endl;


    double ratio = std::get<1>(totalError[0]) / std::get<1>(totalError[1]);

    int resemblance = (int)(ratio * 1000);

    if (failMode == 1) {
        saveImagesToFolder("Failed captchas");
    }
    else if (saveScreenshots == 1) {
        saveImagesToFolder("Captchas");
    }
    else {
        cout << "No saving screenshoots" << endl << endl;
    }
    //logP("saved images  ", 0);

    //cv::imshow("Detected Lines", result);
    //cv::waitKey(0);

    //logP("last steps  ", 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    int durationMS = duration.count();

    cout << "Time solving: " << durationMS << "ms" << endl;

    durationMS &= 0xFFF; // to cut out most significant bits so result is not < 0

    durationMS /= 4;

    int returningValue = answer + (resemblance << 8) + (durationMS << 18);

    cout <<"Returning " << returningValue << endl;

    HWND hwnd = reinterpret_cast<HWND>(hwnd_callback);
    UINT WM_USER_CUSTOM = WM_USER;

    WPARAM wParam = returningValue;
    LPARAM lParam = returningValue;

    if (hwnd_callback != 0 && hwnd != nullptr)
    {
        PostMessage(hwnd, 1024, wParam, lParam);
    }


    return returningValue;
}


double getMinDist(Point2f& p, int captchaNum, double progress) {

    double spread = 0.25;

    double progressMin = progress - spread < 0 ? 0 : progress - spread;
    double progressMax = progress + spread > 1 ? 1 : progress + spread;

    int splitPatrs = 1000;

    double stepSize = 1.0 / splitPatrs;


    double minDist = 999999;

    for (int i = 0; i < 4; i++) {

        int ps = std::get<0>(pairs[captchaNum][i]);
        int pf = std::get<1>(pairs[captchaNum][i]);

        for (double j = progressMin; j <= progressMax; j += stepSize) {

            double dst = distance(p, getQuadraticBezierPoint(pbp[ps][pf].PS, pbp[ps][pf].PC, pbp[ps][pf].PE, j));
            double dst2 = distance(p, getQuadraticBezierPoint(pbp[pf][ps].PS, pbp[pf][ps].PC, pbp[pf][ps].PE, j));

            if (dst < minDist) {
                minDist = dst;
            }
            if (dst2 < minDist) {
                minDist = dst2;
            }

        }


    }

    return minDist;

}

string getPositionStr(int p) {
    switch (p) {
    case(0): return "Up";
    case(1): return "Right up";
    case(2): return "Right";
    case(3): return "Right down";
    case(4): return "Down";
    case(5): return "Left down";
    case(6): return "Left";
    case(7): return "Left up";
    default: return ".";
    }
}


void sortValues(std::tuple<int, double> arr[], int size) {
    std::sort(arr, arr + size, [](const std::tuple<int, double>& a, const std::tuple<int, double>& b) {
        return std::get<1>(a) < std::get<1>(b);
        });
}


vector<Point2f> findRotatedPart(const Mat& objectPart, const Mat& image, Mat& imageToDraw) {

    //logP("findRotatedPart", 0);
    //cout << "New image" << endl;

    Mat imageCopy = image.clone();

    Mat grayObjectPart, grayImage;

    cvtColor(objectPart, grayObjectPart, COLOR_BGR2GRAY);
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    Ptr<SIFT> sift = SIFT::create();
    std::vector<KeyPoint> keypointsObject;
    Mat descriptorsObject;
    sift->detectAndCompute(grayObjectPart, noArray(), keypointsObject, descriptorsObject);

    int h = 105;
    int w = 105;
    int step = 50;

    vector<Point2f> foundRectangles;

    //logP("findRotatedPart", 1);
    for (int y = 0; y <= image.rows - h; y += step) {
        //logP("Y: ", y);
        for (int x = 0; x <= image.cols - w; x += step) {


            //logP("X: ", x);
            cv::Rect roi(x, y, w, h);

            Mat subImage = image(roi);

            if (pxlCount(subImage, Scalar(73, 87, 98), 0, 0, w - 1, h - 1) > w * h / 3) {
                continue;
            }


            Mat graySubImage;
            cvtColor(subImage, graySubImage, COLOR_BGR2GRAY);

            std::vector<KeyPoint> keypointsROI;
            Mat descriptorsROI;
            sift->detectAndCompute(graySubImage, noArray(), keypointsROI, descriptorsROI);

            if (!descriptorsObject.empty() && !descriptorsROI.empty() &&
                descriptorsObject.type() == descriptorsROI.type() &&
                descriptorsObject.cols == descriptorsROI.cols) {

                BFMatcher matcher(NORM_L2, true);
                vector<DMatch> matches;
                matcher.match(descriptorsObject, descriptorsROI, matches);

                vector<DMatch> goodMatches = matches;

                std::vector<Point2f> obj;
                std::vector<Point2f> scene;

                for (size_t i = 0; i < goodMatches.size(); i++) {

                    //logP("OBJ    X:        ", keypointsObject[goodMatches[i].queryIdx].pt.x);
                    //logP("OBJ    Y:        ", keypointsObject[goodMatches[i].queryIdx].pt.y);
                    obj.push_back(keypointsObject[goodMatches[i].queryIdx].pt);

                    //logP("SCENE X:             ", (keypointsROI[goodMatches[i].trainIdx].pt + Point2f(x, y)).x);
                    //logP("SCENE Y:             ", (keypointsROI[goodMatches[i].trainIdx].pt + Point2f(x, y)).y);
                    scene.push_back(keypointsROI[goodMatches[i].trainIdx].pt + Point2f(x, y));


                    //obj.push_back(Point2f((int)keypointsObject[goodMatches[i].queryIdx].pt.x, (int)keypointsObject[goodMatches[i].queryIdx].pt.y));
                    //scene.push_back(Point2f((int)(keypointsROI[goodMatches[i].trainIdx].pt + Point2f(x, y)).x, (int)(keypointsROI[goodMatches[i].trainIdx].pt + Point2f(x, y)).y));
                }
                removeDuplicatePoints(obj, scene);


                //logP("OBJ: ", x);
                //for (int i = 0; i < obj.size(); i++) {
                //    logP(to_string(obj[i].x) + "\t" + to_string(obj[i].y), 0);
                //}
                //logP("SCENE: ", x);
                //for (int i = 0; i < scene.size(); i++) {
                //    logP(to_string(scene[i].x) +"\t" + to_string(scene[i].y), 0);
                //}

                //logP("111        ", x);

                if (obj.size() >= 4 && scene.size() >= 4) {
                    //logP("Try find homography        ", x);
                    //logP("obj size:        ", obj.size());
                    //logP("scene size:        ", scene.size());

                    Mat H = findHomography(obj, scene, RANSAC);

                    //logP("Homography found        ", x);

                    std::vector<Point2f> objCorners(4);
                    objCorners[0] = Point2f(0, 0);
                    objCorners[1] = Point2f(objectPart.cols, 0);
                    objCorners[2] = Point2f(objectPart.cols, objectPart.rows);
                    objCorners[3] = Point2f(0, objectPart.rows);

                    if (!H.empty()) {

                        //logP("perspective transform        ", x);
                        std::vector<Point2f> sceneCorners(4);
                        perspectiveTransform(objCorners, sceneCorners, H);
                        //logP("transformed        ", x);

                        //drawMatches(objectPart, keypointsObject, image, keypointsImage, goodMatches, img_matches);

                        if (isApproxRectangle(sceneCorners[0], sceneCorners[1], sceneCorners[2], sceneCorners[3], 75, 101, 0.1)) {

                            //rectangle(imageCopy, roi, getColor(RED));
                            line(imageToDraw, sceneCorners[0], sceneCorners[1], Scalar(0, 255, 0), 1);
                            line(imageToDraw, sceneCorners[1], sceneCorners[2], Scalar(0, 255, 0), 1);
                            line(imageToDraw, sceneCorners[2], sceneCorners[3], Scalar(0, 255, 0), 1);
                            line(imageToDraw, sceneCorners[3], sceneCorners[0], Scalar(0, 255, 0), 1);

                            int centerX = (sceneCorners[0].x + sceneCorners[1].x + sceneCorners[2].x + sceneCorners[3].x) / 4;
                            int centerY = (sceneCorners[0].y + sceneCorners[1].y + sceneCorners[2].y + sceneCorners[3].y) / 4;

                            foundRectangles.push_back(Point2f(centerX, centerY));
                        }

                        //rectangle(img_matches, roi, getColor(RED), 2);

                    }
                }
                //logP("222        ", x);
            }
        }
    }

    clusterPoints(foundRectangles, 10);

    vector<Point2f> points;

    //cout << "Found "<< foundRectangles.size() << " points" << endl;
    for (int i = 0; i < foundRectangles.size(); i++) {
        circle(imageCopy, foundRectangles[i], 2, getColor(CYAN), 2);
        //boxPaths.push_back(foundRectangles[i]);
        points.push_back(foundRectangles[i]);
    }


    //cout << "Done" << endl;
    //imshow("Detected Part", imageToDraw);
    //waitKey(0);

    return points;

}

cv::Mat calculateHomography(const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints) {
    cv::Mat A(8, 9, CV_64F);

    for (int i = 0; i < 4; i++) {
        double x1 = srcPoints[i].x;
        double y1 = srcPoints[i].y;
        double x2 = dstPoints[i].x;
        double y2 = dstPoints[i].y;

        A.at<double>(2 * i, 0) = x1;
        A.at<double>(2 * i, 1) = y1;
        A.at<double>(2 * i, 2) = 1.0;
        A.at<double>(2 * i, 3) = 0.0;
        A.at<double>(2 * i, 4) = 0.0;
        A.at<double>(2 * i, 5) = 0.0;
        A.at<double>(2 * i, 6) = -x2 * x1;
        A.at<double>(2 * i, 7) = -x2 * y1;
        A.at<double>(2 * i, 8) = -x2;

        A.at<double>(2 * i + 1, 0) = 0.0;
        A.at<double>(2 * i + 1, 1) = 0.0;
        A.at<double>(2 * i + 1, 2) = 0.0;
        A.at<double>(2 * i + 1, 3) = x1;
        A.at<double>(2 * i + 1, 4) = y1;
        A.at<double>(2 * i + 1, 5) = 1.0;
        A.at<double>(2 * i + 1, 6) = -y2 * x1;
        A.at<double>(2 * i + 1, 7) = -y2 * y1;
        A.at<double>(2 * i + 1, 8) = -y2;
    }


    cv::Mat h;
    cv::SVD::solveZ(A, h);


    cv::Mat H = h.reshape(1, 3);
    return H;
}


cv::Mat customFindHomography(const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints, int maxIterations, double reprojectionThreshold) {
    const int numPoints = srcPoints.size();
    std::vector<int> bestInliers;
    cv::Mat bestHomography;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, numPoints - 1);

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        try {
            std::vector<cv::Point2f> selectedSrcPoints(4), selectedDstPoints(4);
            for (int i = 0; i < 4; i++) {
                int idx = dist(rng);
                selectedSrcPoints[i] = srcPoints[idx];
                selectedDstPoints[i] = dstPoints[idx];
            }

            cv::Mat H = findHomography(selectedSrcPoints, selectedDstPoints, RANSAC, 3.0, noArray(), 50);
            if (H.empty() || H.rows != 3 || H.cols != 3) {
                continue;
            }

            std::vector<int> inliers;
            for (int i = 0; i < numPoints; i++) {
                cv::Point2f p1 = srcPoints[i];
                cv::Point2f p2 = dstPoints[i];

                cv::Mat pt1 = (cv::Mat_<double>(3, 1) << p1.x, p1.y, 1.0);
                cv::Mat pt2 = H * pt1;
                if (pt2.at<double>(2) == 0) {
                    continue;
                }
                pt2 /= pt2.at<double>(2);

                double error = cv::norm(p2 - cv::Point2f(pt2.at<double>(0), pt2.at<double>(1)));

                if (error < reprojectionThreshold) {
                    inliers.push_back(i);
                }
            }

            if (inliers.size() > bestInliers.size()) {
                bestInliers = inliers;
                bestHomography = H.clone();
            }
        }
        catch (const cv::Exception& e) {
            std::cerr << "Exception during RANSAC iteration: " << e.what() << std::endl;
            continue;
        }
    }

    if (!bestInliers.empty()) {
        std::vector<cv::Point2f> finalSrcPoints, finalDstPoints;
        for (int idx : bestInliers) {
            finalSrcPoints.push_back(srcPoints[idx]);
            finalDstPoints.push_back(dstPoints[idx]);
        }
        bestHomography = calculateHomography(finalSrcPoints, finalDstPoints);
    }

    return bestHomography;
}

void drawQuadraticBezier(Mat& image, Point2f start, Point2f control, Point2f end, Scalar color, int thickness) {
    Point2f prevPoint = start;

    for (float t = 0; t <= 1.0; t += 0.01) {
        Point2f currentPoint = getQuadraticBezierPoint(start, control, end, t);
        line(image, prevPoint, currentPoint, color, thickness);
        prevPoint = currentPoint;
    }
}

cv::Scalar interpolateScalar(const cv::Scalar& start, const cv::Scalar& end, double t) {
    if (t < 0)t = 0;
    if (t > 1) t = 1;

    cv::Scalar result;
    for (int i = 0; i < 4; ++i) {
        result[i] = start[i] + t * (end[i] - start[i]);
    }

    return result;
}




void clusterPoints(std::vector<cv::Point2f>& points, double threshold) {
    std::vector<bool> visited(points.size(), false);
    std::vector<cv::Point2f> newPoints;

    for (size_t i = 0; i < points.size(); ++i) {
        if (visited[i]) continue;

        std::vector<cv::Point> cluster;
        cluster.push_back(points[i]);
        visited[i] = true;

        for (size_t j = i + 1; j < points.size(); ++j) {
            if (!visited[j] && distance(points[i], points[j]) < threshold) {
                cluster.push_back(points[j]);
                visited[j] = true;
            }
        }

        cv::Point avgPoint(0, 0);
        for (const auto& pt : cluster) {
            avgPoint += pt;
        }
        avgPoint.x /= cluster.size();
        avgPoint.y /= cluster.size();

        newPoints.push_back(avgPoint);
    }

    points = newPoints;
}









Point2f getQuadraticBezierPoint(const Point2f& ps, const Point2f& pc, const Point2f pe, double t) {

    double x = (1 - t) * (1 - t) * ps.x + 2 * t * (1 - t) * pc.x + t * t * pe.x;
    double y = (1 - t) * (1 - t) * ps.y + 2 * t * (1 - t) * pc.y + t * t * pe.y;

    return Point2f(x, y);

}
//
//
//void logP(const std::string& message, int value) {
//    std::ostringstream logEntry;
//    logEntry << message << " " << value;
//
//    std::ofstream progressFile("progress.txt", std::ios::out | std::ios::app);
//    if (progressFile.is_open()) {
//        progressFile << logEntry.str() << "\n";
//        progressFile.close();
//    }
//    else {
//        std::cerr << "Unable to open file";
//    }
//}
//

Point2f quadraticBezierDerivative(Point2f start, Point2f control, Point2f end, float t) {
    return 2 * (1 - t) * (control - start) + 2 * t * (end - control);
}

void drawQuadraticBezierWithArrow(Mat& image, Point2f start, Point2f control, Point2f end, Scalar color, int thickness) {
    Point2f prevPoint = start;
    Point2f currentPoint;

    for (float t = 0; t <= 1.0; t += 0.01) {
        currentPoint = getQuadraticBezierPoint(start, control, end, t);
        line(image, prevPoint, currentPoint, color, thickness);
        prevPoint = currentPoint;
    }

    Point2f tangent = quadraticBezierDerivative(start, control, end, 1.0);
    float arrowLength = 20.0;
    float arrowAngle = CV_PI / 5;

    Point2f arrowPoint1 = currentPoint - arrowLength * Point2f(cos(atan2(tangent.y, tangent.x) + arrowAngle), sin(atan2(tangent.y, tangent.x) + arrowAngle));
    Point2f arrowPoint2 = currentPoint - arrowLength * Point2f(cos(atan2(tangent.y, tangent.x) - arrowAngle), sin(atan2(tangent.y, tangent.x) - arrowAngle));

    line(image, currentPoint, arrowPoint1, color, thickness);
    line(image, currentPoint, arrowPoint2, color, thickness);
}




void TemplateMatching(const Mat& img, const Mat& templ, double threshold)
{
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    Mat result(result_rows, result_cols, CV_32FC1);

    matchTemplate(img, templ, result, TM_CCOEFF_NORMED);

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    while (true)
    {
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

        if (maxVal < threshold)
            break;

        Point matchLoc = maxLoc;
        rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(255), 2, 8, 0);

        rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), FILLED);
    }

    imshow("Detected Matches", img);
    waitKey(0);
}






double distance(cv::Point2f p1, cv::Point2f p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool isApproxRectangle(cv::Point2f A, cv::Point2f B, cv::Point2f C, cv::Point2f D, double expectedWidth, double expectedHeight, double tolerance) {
    double AB = distance(A, B);
    double BC = distance(B, C);
    double CD = distance(C, D);
    double DA = distance(D, A);

    double AC = distance(A, C);
    double BD = distance(B, D);

    double lowerBoundWidth = expectedWidth * (1.0 - tolerance);
    double upperBoundWidth = expectedWidth * (1.0 + tolerance);
    double lowerBoundHeight = expectedHeight * (1.0 - tolerance);
    double upperBoundHeight = expectedHeight * (1.0 + tolerance);

    bool config1 =
        (AB > lowerBoundWidth && AB < upperBoundWidth && CD > lowerBoundWidth && CD < upperBoundWidth) &&
        (BC > lowerBoundHeight && BC < upperBoundHeight && DA > lowerBoundHeight && DA < upperBoundHeight);

    bool config2 =
        (AB > lowerBoundHeight && AB < upperBoundHeight && CD > lowerBoundHeight && CD < upperBoundHeight) &&
        (BC > lowerBoundWidth && BC < upperBoundWidth && DA > lowerBoundWidth && DA < upperBoundWidth);

    bool diagonalsCondition = std::abs(AC - BD) < AC * tolerance;

    return (config1 || config2) && diagonalsCondition;
}











void drawLineThroughPoint(cv::Mat& image, cv::Point point, double angle) {
    double angleRad = angle * CV_PI / 180.0;

    double dx = std::cos(angleRad);
    double dy = std::sin(angleRad);

    int width = image.cols;
    int height = image.rows;

    cv::Point pt1, pt2;

    if (dy != 0) {
        pt1.x = point.x + (0 - point.y) / dy * dx;
        pt1.y = 0;

        pt2.x = point.x + (height - point.y) / dy * dx;
        pt2.y = height;
    }
    else {
        pt1.x = 0;
        pt1.y = point.y;
        pt2.x = width;
        pt2.y = point.y;
    }

    if (pt1.x < 0) {
        pt1.x = 0;
        pt1.y = point.y + (0 - point.x) / dx * dy;
    }
    if (pt1.x > width) {
        pt1.x = width;
        pt1.y = point.y + (width - point.x) / dx * dy;
    }
    if (pt2.x < 0) {
        pt2.x = 0;
        pt2.y = point.y + (0 - point.x) / dx * dy;
    }
    if (pt2.x > width) {
        pt2.x = width;
        pt2.y = point.y + (width - point.x) / dx * dy;
    }

    cv::line(image, pt1, pt2, getColor(WHITE), 1);
}


std::vector<std::tuple<cv::Mat, cv::Point>> getSubImages(const cv::Mat& image, int subImageWidth, int subImageHeight, int step) {
    std::vector<std::tuple<cv::Mat, cv::Point>> subImages;

    for (int y = 0; y <= image.rows - subImageHeight; y += step) {
        for (int x = 0; x <= image.cols - subImageWidth; x += step) {
            cv::Rect roi(x, y, subImageWidth, subImageHeight);
            cv::Mat subImage = image(roi);
            cv::Point origin(x, y);
            subImages.push_back(std::make_tuple(subImage, origin));
        }
    }

    return subImages;
}


void linearRegression(const std::vector<Point2f>& points, double& m, double& c) {
    int n = points.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (const auto& p : points) {
        sumX += p.x;
        sumY += p.y;
        sumXY += p.x * p.y;
        sumX2 += p.x * p.x;
    }

    m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    c = (sumY - m * sumX) / n;
}




int pxlCount(const Mat& image, const set<Vec3b, Vec3bComparator>& distinctColors, int sx, int sy, int fx, int fy) {

    int pxlcount = 0;

    for (int y = sy; y <= fy; ++y) {
        for (int x = sx; x < fx; ++x) {
            Vec3b color = image.at<Vec3b>(y, x);
            if (distinctColors.find(color) != distinctColors.end()) {
                ++pxlcount;
            }
        }
    }

    return pxlcount;

}


int pxlCount(const Mat& image, Scalar s, int sx, int sy, int fx, int fy) {

    int pxlcount = 0;

    for (int y = sy; y <= fy; ++y) {
        for (int x = sx; x < fx; ++x) {
            Vec3b color = image.at<Vec3b>(y, x);
            if (s[0] == color[0] && s[1] == color[1] && s[2] == color[2]) {
                ++pxlcount;
            }
        }
    }

    return pxlcount;

}

void COLORMODE(int mode, Mat& src) {

    unsigned char colorShift = 1 << mode;
    unsigned char mask = 255 << mode;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            Vec3b color = src.at<Vec3b>(Point(x, y));
            color[0] = ((color[0] + colorShift) & mask) - 1;
            color[1] = ((color[1] + colorShift) & mask) - 1;
            color[2] = ((color[2] + colorShift) & mask) - 1;
            src.at<Vec3b>(Point(x, y)) = color;
        }
    }
}

void getDistinctColors(const Mat& image) {
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            uniqueColors.insert(image.at<Vec3b>(y, x));
        }
    }
}

void replaceColorsWithBlack(Mat& image, const set<Vec3b, Vec3bComparator>& colorsToReplace) {
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            Vec3b color = image.at<Vec3b>(Point(x, y));
            if (colorsToReplace.find(color) != colorsToReplace.end()) {
                color = Vec3b(0, 0, 0);
                image.at<Vec3b>(Point(x, y)) = color;
            }
        }
    }
}

string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);

    std::tm localTime;

    localtime_s(&localTime, &now);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d.%m.%Y %H:%M:%S");

    return oss.str();
}
void removeDuplicatePoints(vector<Point2f>& obj, vector<Point2f>& scene) {
    if (obj.size() != scene.size()) {
        return;
    }

    set<pair<Point2f, Point2f>, PointPairComparator> uniquePairs;

    vector<Point2f> filteredObj, filteredScene;

    for (size_t i = 0; i < obj.size(); ++i) {
        pair<Point2f, Point2f> currentPair = make_pair(obj[i], scene[i]);

        if (uniquePairs.find(currentPair) == uniquePairs.end()) {
            uniquePairs.insert(currentPair);
            filteredObj.push_back(obj[i]);
            filteredScene.push_back(scene[i]);
        }
    }

    obj = filteredObj;
    scene = filteredScene;
}
bool directoryExists(const std::string& dirName) {
    return _access(dirName.c_str(), 0) == 0;
}
bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}
int saveImagesToFolder(string folderName) {

    int folderIndex = 1;
    std::string folderPath;

    folderPath = currentDirectoryBackSlashes + "\\" + folderName;
    if (!directoryExists(folderPath)) {
        if (_mkdir(folderPath.c_str()) != 0) {
            return 1;
        }
    }

    do {
        folderPath = currentDirectoryBackSlashes + "\\" + folderName + "\\Captcha_" + std::to_string(folderIndex);
        folderIndex++;
    } while (directoryExists(folderPath));

    if (_mkdir(folderPath.c_str()) != 0) {
        return 2;
    }

    for (size_t i = 0; i < originalImages.size(); ++i) {
        std::string filePath = folderPath + "\\CaptchaImage_" + std::to_string(i + 1) + "." + saveImageFormat;
        cv::imwrite(filePath, originalImages[i]);
    }

    for (size_t i = 0; i < resultImages.size(); ++i) {
        std::string filePath = folderPath + "\\ResultImage_" + std::to_string(i) + "." + saveImageFormat;
        cv::imwrite(filePath, resultImages[i]);
    }

    cout << "Saved images to:\n" << folderPath << endl << endl;

    return 0;
}


void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}