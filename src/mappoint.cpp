#include "toyslam/mappoint.h"
#include "toyslam/feature.h"

namespace toyslam
{

  MapPoint::MapPoint(long id, Vec3 position)
  : id_(id), pos_(position) {}

  MapPoint::Ptr MapPoint::CreateNewMappoint()
  {
    static long factory_id = 0;
    MapPoint::Ptr new_mappoint(new MapPoint);
    new_mappoint->id_ =factory_id++;
    return new_mappoint;
  }

  void MapPoint::RemoveObservation(std::shared_ptr<Feature> feat)
  {
    std::unique_lock<std::mutex> lck(data_mutex_);

    for(auto iter = observations_.begin(); iter != observations_.end(); iter++)
    {
      //find feat to delete
      if(iter->lock() == feat)
      {
        observations_.erase(iter);
        feat->map_point_.reset();
        observed_times_--;
        break;
      }
    }
  }


}// namespace toyslame
