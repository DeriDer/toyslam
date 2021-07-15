#pragma once

#ifndef MAP_H
#define MAP_H

#include"toyslam/common.h"
#include"toyslam/frame.h"
#include "toyslam/mappoint.h"

namespace toyslam
{
  class Map
  {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    typedef std::shared_ptr<Map> Ptr;
    typedef std::unordered_map<unsigned long, MapPoint::Ptr> LandmarksType;
    typedef std::unordered_map<unsigned long, Frame::Ptr> KeyframesType;

    Map(){}

    //insert keyframe
    void InsertKeyFrame(Frame::Ptr frame);

    //insert a mappoint
    void InsertMapPoint(MapPoint::Ptr map_point);

    //gets all map points
    LandmarksType GetAllPoints()
    {
      std::unique_lock<std::mutex> lck(data_mutex_);
      return landmarks_;
    }
    //gets all key points
    KeyframesType GetAllKeyFrames()
    {
      std::unique_lock<std::mutex> lck(data_mutex_);
      return keyframes_;
    }
    //get active mappoints
    LandmarksType GetActivePoints()
    {
      std::unique_lock<std::mutex> lck(data_mutex_);
      return active_landmarks_;
    }
    //get active keyframes
    KeyframesType GetActiveKeyFrames()
    {
      return active_keyframes_;
    }

    void CleanMap();

  private:
    void RemoveOldKeyframe();

    std::mutex data_mutex_;
    LandmarksType landmarks_;
    LandmarksType active_landmarks_;
    KeyframesType active_keyframes_;
    KeyframesType keyframes_;

    Frame::Ptr current_frame_= nullptr;

    int num_active_keyframes_ = 7;

  };
} //namespace toyslam

#endif //MAP_H
