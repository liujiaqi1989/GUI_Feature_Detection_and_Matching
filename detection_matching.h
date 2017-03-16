#ifndef DETECTION_MATCHING_H
#define DETECTION_MATCHING_H
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>

class Detection_Matching
{
public:
    Detection_Matching(const char* detectorType, const char* descriptorType, const char* matcherType,
                       cv::Mat Limage, cv::Mat Rimage);
    void Detecting();
    void Matching();

    cv::Mat getKimage_left();
    cv::Mat getKimage_right();
    cv::Mat getmatchResult();
    cv::Mat getDescriptors_left();
    cv::Mat getDescriptors_right();
private:
    cv::Mat image_left;
    cv::Mat image_right;

    cv::Mat kimage_left;
    cv::Mat kimage_right;
    cv::Mat matchResult;

    std::vector<cv::KeyPoint> keypoints_left;
    std::vector<cv::KeyPoint> keypoints_right;
    std::vector<cv::DMatch> matches;

    cv::Mat descriptors_left;
    cv::Mat descriptors_right;

    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> descriptorExtractor;
    cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;
};

#endif // DETECTION_MATCHING_H
