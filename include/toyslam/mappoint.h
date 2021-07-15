#pragma once

#ifndef MAP_POINT_H
#define MAP_POINT_H

#include "toyslam/common.h"

namespace toyslam
{
  struct Feature;
  struct Frame;

  struct MapPoint
  {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    typedef std::shared_ptr<MapPoint> Ptr;
    unsigned long id_ = 0;
    bool is_outlier_ = false;
    Vec3 pos_ = Vec3::Zero();
    std::mutex data_mutex_;
    int observed_times_ = 0;
    std::list<std::weak_ptr<Feature>> observations_;

  MapPoint() {}

  MapPoint(long id, Vec3 position);

  Vec3 Pos()
  {
    std::unique_lock<std::mutex> lck(data_mutex_);
    return pos_;
  }

  void SetPos(const Vec3 &pos)
  {
    std::unique_lock<std::mutex> lck(data_mutex_);
    pos_ = pos;
  }

  void AddObservation(std::shared_ptr<Feature> feature)
  {
    std::unique_lock<std::mutex> lck(data_mutex_);
    observations_.push_back(feature);
    observed_times_++;
  }


  std::list<std::weak_ptr<Feature>> GetObs()
  {
    std::unique_lock<std::mutex> lck(data_mutex_);
    return observations_;
  }

  // factory function
  static MapPoint::Ptr CreateNewMappoint();
  void RemoveObservation(std::shared_ptr<Feature> feat);



};


} //namespace toyslam

#endif
