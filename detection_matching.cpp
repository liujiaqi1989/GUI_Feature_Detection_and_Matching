#include "detection_matching.h"

Detection_Matching::Detection_Matching(const char* detectorType, const char* descriptorType,
                                       const char* matcherType, cv::Mat Limage, cv::Mat Rimage)
{

    image_left=Limage.clone();
    image_right=Rimage.clone();
    detector=cv::FeatureDetector::create(detectorType);
    descriptorExtractor=cv::DescriptorExtractor::create(descriptorType);
    descriptorMatcher=cv::DescriptorMatcher::create(matcherType);
}

void Detection_Matching::Detecting()
{
    cv::initModule_nonfree();
    detector->detect(image_left, keypoints_left);
    detector->detect(image_right, keypoints_right);

    descriptorExtractor->compute(image_left, keypoints_left, descriptors_left);
    descriptorExtractor->compute(image_right, keypoints_right, descriptors_right);

    cv::drawKeypoints( image_left, keypoints_left, kimage_left, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );
    cv::drawKeypoints( image_right, keypoints_right, kimage_right, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );

}

void Detection_Matching::Matching()
{
    descriptorMatcher->match(descriptors_left,descriptors_right, matches);
    if(matches.size()>25){
        std::nth_element(matches.begin(),matches.begin()+24,matches.end());
        matches.erase(matches.begin()+25,matches.end());
    }

    cv::drawMatches(image_left,keypoints_left,image_right, keypoints_right,matches,matchResult,cv::Scalar(255,255,255));
}


cv::Mat Detection_Matching::getKimage_left()
{
    return kimage_left;
}

cv::Mat Detection_Matching::getKimage_right()
{
    return kimage_right;
}

cv::Mat Detection_Matching::getmatchResult()
{
    return matchResult;
}

cv::Mat Detection_Matching::getDescriptors_left()
{
    return descriptors_left;
}

cv::Mat Detection_Matching::getDescriptors_right()
{
    return descriptors_right;
}

