//
// Created by pardusumsu on 04.10.2024.
//

#include "tracker.h"

tracker::tracker() {
    cv::namedWindow("DaSiamRPN_tracker_cpp", cv::WINDOW_AUTOSIZE);
}

void tracker::processFrame() {
    double fps;
    cv::VideoCapture cap("../../tracker-tester-py/data/ConstantRobotics-test-video.mp4");

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera\n";
        return;
    }

    while (true) {
        int64 time_start = cv::getTickCount();
        cap >> frame_prc;
        if (frame_prc.empty()) break;
        cv::flip(frame_prc, frame_prc, 1);
        frame_prc.copyTo(frame_show);
        if (!roiSelected) {
            roi = cv::selectROI("DaSiamRPN_tracker_cpp", frame_show, false, false);
            roiSelected = true;
        }
        if (roi.empty()) {
            std::cerr << "Roi is empty." << std::endl;
            break;
        } else if (!init) {
            tracker_DaSiamRPN->init(frame_prc, roi);
            init = true;
        }

        tracker_DaSiamRPN->update(frame_prc, roi);
        fps = cv::getTickFrequency() / (cv::getTickCount() - time_start);
        cv::putText(frame_show, "FPS: " + std::to_string((int)fps), cv::Point(10, 30),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(255, 255, 0));
        cv::rectangle(frame_show, roi, cv::Scalar(0, 255, 0), 2, 1); // green
        cv::imshow("DaSiamRPN_tracker_cpp", frame_show);

        int key = cv::waitKey(1) & 0xFF;
        if (key == 27) break;
        else if (key == 'q') {
            roiSelected = false;
            init = false;
        }
        else if (key == ' ') {
            paused = !paused;
            while (paused) {
                key = cv::waitKey(1) & 0xFF;
                if (key == ' ') paused = !paused;
                else if (key == 27 || key == 'q') break;
            }
        }
    }
}

tracker::~tracker() = default;
