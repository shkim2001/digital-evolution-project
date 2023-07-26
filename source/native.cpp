#include <iostream>

#include "World.h"
#include "emp/config/ArgManager.hpp"
#include "ConfigSetup.h"
#include "DataMethods.cpp"

// This is the main function for the NATIVE version of this project.

int main(int argc, char *argv[]) {
  MyConfigType config;
  config.Read("MySettings.cfg");
  bool success = config.Read("MySettings.cfg");
  if (!success) config.Write("MySettings.cfg");

  auto args = emp::cl::ArgManager(argc, argv);
  if (args.ProcessConfigOptions(config, std::cout, "MySettings.cfg") == false) {
    std::cerr << "There was a problem in processing the options file." << std::endl;
    exit(1);
  }
  if (args.TestUnknown() == false) {
    std::cerr << "Leftover args no good." << std::endl;
    exit(1);
  }

  emp::Random random(config.RANDOM_SEED());
  OrgWorld world(random);

  size_t width = 20;
  size_t height = 20;
  
  // apply config settings
  int interval = height * width / config.NUM_ORGS();
  int org_count = config.NUM_ORGS();
  if (org_count > height * width) org_count = height * width;
  else if (org_count < 1) org_count = 0;
  if (interval == 0) interval = 1;

  // set up the world size / structure
  world.Resize(width, height);
  world.SetPopStruct_Grid(width, height);

  int timing_repeat = 100;
  std::string file_ending = "_Seed"+std::to_string(config.RANDOM_SEED())+ "_ReqPoint" + std::to_string(config.REQUIRED_POINTS()) + "_MHFreq" + std::to_string(config.MOVING_HOTSPOT_FREQ()) + ".data";
  std::cout << "file ending: " << file_ending << std::endl;

  world.SetupTaskCountFile("TaskCounts"+ file_ending).SetTimingRepeat(timing_repeat);
  world.SetupOrgPointsFile("OrgPoints" + file_ending).SetTimingRepeat(timing_repeat);

  world.SetupHotspot(0);
  world.SetHospotMoveFreq(config.MOVING_HOTSPOT_FREQ());
  world.SetupTasks(config.NUM_POSSIBLE_TASKS());

  // populate the world with organisms
  for (int i = interval - 1; i < org_count * interval; i += interval) {
	world.AddOrgAt(new Organism(&world, 10, config.REQUIRED_POINTS()), i);
  }
  
  // run the experiment
  for(int update=0; update<100001; update++){
    if (update % 500 == 0) std::cout << "update: " << update << std::endl;
    world.Update();
  }
}
