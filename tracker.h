//
// Created by pardusumsu on 04.10.2024.
//

#ifndef DASIAMRPN_TRACKER_CPP_TRACKER_H
#define DASIAMRPN_TRACKER_CPP_TRACKER_H

#include "iostream"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class tracker {
public:
    tracker();
    ~tracker();
    void processFrame();
private:
    cv::Mat frame_show;
    cv::Mat frame_prc;
    cv::Rect roi;
    cv::Ptr<cv::TrackerDaSiamRPN> tracker_DaSiamRPN = cv::TrackerDaSiamRPN::create();

    bool init = false;
    bool paused = false;
    bool roiSelected = false;
};


#endif //DASIAMRPN_TRACKER_CPP_TRACKER_H
