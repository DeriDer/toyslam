#pragma once
#ifndef FRONTEND_H
#define FRONTEND_H
//#define _GLIBCXX_USE_CXX11_ABI 0
#include <opencv2/features2d.hpp>

#include"toyslam/common.h"
#include"toyslam/frame.h"
#include"toyslam/map.h"


namespace toyslam
{

class Backend;
class Viewer;

enum class FrontendStatus
{
  INITING, TRACKING_GOOD, TRACKING_BAD, LOST
};

class Frontend
{

  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    typedef std::shared_ptr<Frontend> Ptr;

    Frontend();

    bool AddFrame(Frame::Ptr frame);

    void SetMap(Map::Ptr map) { map_ = map; }

    void SetBackend(std::shared_ptr<Backend> backend) { backend_ = backend; }

    void SetViewer(std::shared_ptr<Viewer> viewer) { Viewer_ = viewer; }

    FrontendStatus GetStatus() const { return status_; }

    void SetCameras(Camera::Ptr left, Camera::Ptr right)
    {
      camera_left_ = left;
      camera_right_ = right;
    }


  private:

    bool Track();

    bool Reset();

    int TrackLastFrame();

    int EstimateCurrentPose();

    bool InsertKeyframe();

    bool StereoInit();

    int DetectFeatures();

    int FindFeaturesInRight();

    bool BuildInitMap();

    int TriangulateNewPoints();

    void SetObservationsForKeyFrame();

    //data
    FrontendStatus status_ = FrontendStatus::INITING;

    Frame::Ptr current_frame_ = nullptr;
    Frame::Ptr last_frame_ = nullptr;
    Camera::Ptr camera_left_ = nullptr;
    Camera::Ptr camera_right_= nullptr;

    Map::Ptr map_ = nullptr;
    std::shared_ptr<Backend> backend_ = nullptr;
    std::shared_ptr<Viewer> Viewer_ = nullptr;

    SE3 relative_motion_;

    int tracking_inliers_ = 0;

    //parameters
    int num_features_ = 200;
    int num_features_init_ = 100;
    int num_features_tracking_ = 50;
    int num_features_tracking_bad_ = 20;
    int num_features_needed_for_keyframe_ = 80;

    //utilities
    cv::Ptr<cv::GFTTDetector>gftt_;

};


}//namespace


#endif /* end of include guard:FRONTEND_H */
