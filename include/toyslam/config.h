#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "toyslam/common.h"

namespace toyslam
{

class Config
{
  private:
    static std::shared_ptr<Config> config_;
    cv::FileStorage file_;

    Config(){}
  public:
    ~Config();

    static bool SetParameterFile(const std::string &filename);

    //access the parameter values
    template <typename T>
    static T Get(const std::string &key)
    {
      return T(Config::config_->file_[key]);
    }
};




}
#endif // toyslam_config
