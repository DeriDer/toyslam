#pragma once
#ifndef VO_H
#define VO_H

#include"toyslam/frontend.h"
#include"toyslam/backend.h"
#include"toyslam/common.h"
#include"toyslam/dataset.h"
#include"toyslam/viewer.h"

namespace toyslam
{
  class VisualOdometry
  {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
      typedef std::shared_ptr<VisualOdometry> Ptr;

      VisualOdometry(std::string &config_path);

      bool Init();

      void Run();

      bool Step();

      FrontendStatus GetFrontendStatus() const { return frontend_->GetStatus();}

    private:
      bool inited_ = false;
      std::string config_file_path_;

      Frontend::Ptr frontend_ = nullptr;
      Backend::Ptr backend_ = nullptr;
      Map::Ptr map_ = nullptr;
      Viewer::Ptr Viewer_ = nullptr;

      Dataset::Ptr dataset_ = nullptr;
  };

}// namespace

#endif
