#include "ur5e.h"

#include <RBDyn/parsers/urdf.h>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

namespace
{

// This is set by CMake, see CMakeLists.txt
static const std::string MC_UR5E_DESCRIPTION_PATH = "@MC_UR5E_DESCRIPTION_PATH@";

} // namespace

namespace mc_robots
{

UR5eRobotModule::UR5eRobotModule() : mc_rbdyn::RobotModule(MC_UR5E_DESCRIPTION_PATH, "ur5e")
{
  // True if the robot has a fixed base, false otherwise
  bool fixed = true;
  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load the convex hulls associated to each body
  std::string convexPath = path + "/convex/" + name + "/";
  bfs::path p(convexPath);
  if(bfs::exists(p) && bfs::is_directory(p))
  {
    std::vector<bfs::path> files;
    std::copy(bfs::directory_iterator(p), bfs::directory_iterator(), std::back_inserter(files));
    for(const bfs::path & file : files)
    {
      size_t off = file.filename().string().rfind("-ch.txt");
      if(off != std::string::npos)
      {
        std::string name = file.filename().string();
        name.replace(off, 7, "");
        mc_rtc::log::info("name:" + name);
        if(name == "upperarm")
        {
          _convexHull["upper_arm_link"] = std::pair<std::string, std::string>("upper_arm_link", file.string());
        }
        else if(name == "wrist1")
        {
          _convexHull["wrist_1_link"] = std::pair<std::string, std::string>("wrist_1_link", file.string());
        }
        else if(name == "wrist2")
        {
          _convexHull["wrist_2_link"] = std::pair<std::string, std::string>("wrist_2_link", file.string());
        }
        else if(name == "wrist3")
        {
          _convexHull["wrist_3_link"] = std::pair<std::string, std::string>("wrist_3_link", file.string());
        }
        else
        {
          _convexHull[name + "_link"] = std::pair<std::string, std::string>(name + "_link", file.string());
        }
      }
    }
  }

  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {
      {"base_link", "upper_arm_link", 0.01, 0.001, 0.0},
      {"base_link", "forearm_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"base_link", "wrist_3_link", 0.01, 0.001, 0.0},

      {"shoulder_link", "forearm_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"shoulder_link", "wrist_3_link", 0.01, 0.001, 0.0},

      {"upper_arm_link", "wrist_1_link", 0.01, 0.001, 0.0},
      {"upper_arm_link", "wrist_2_link", 0.01, 0.001, 0.0},
      {"upper_arm_link", "wrist_3_link", 0.01, 0.001, 0.0}};
  _commonSelfCollisions = _minimalSelfCollisions;

  //Ref joint order
  _ref_joint_order = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",
		      "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"
  };

  // Stance: joint name, angle in degrees
  std::map<std::string, double> starting
  {
    {"shoulder_pan_joint", 0.0},
    {"shoulder_lift_joint", 0.0},
    {"elbow_joint", 0.0},
    {"wrist_1_joint", 0.0},
    {"wrist_2_joint", 0.0},
    {"wrist_3_joint", 0.0}
  };

  for(const auto & j : mb.joints())
  {
    if(j.name() != "Root" && j.dof() > 0)
    {
      _stance[j.name()] = {starting.at(j.name())};
    }
  }
}

} // namespace mc_robots
