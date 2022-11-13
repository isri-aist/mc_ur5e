#pragma once

#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_rtc/logging.h>
#include <mc_rbdyn/RobotModule.h>
#include <mc_robots/api.h>

namespace mc_robots
{

struct MC_ROBOTS_DLLAPI UR5eRobotModule : public mc_rbdyn::RobotModule
{
  UR5eRobotModule();
};

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names)
  {
    names = {"UR5e"};
  }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr;
  }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("UR5e")
    if(n == "UR5e")
    {
      return new mc_robots::UR5eRobotModule();
    }
    else
    {
      mc_rtc::log::error("Aliengo module Cannot create an object of type {}", n);
      return nullptr;
    }
  }
}
