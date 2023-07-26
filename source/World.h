#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "Task.h"
#include "Org.h"

class OrgWorld : public emp::World<Organism> {
  emp::Random &random;
  std::vector<emp::WorldPosition> reproduce_queue;
  int move_freq = 0;
  std::vector<Task*> tasks; 
  emp::vector<int> hotspot_indices; 

  //NOT NAND AND ORN OR ANDN NOR XOR EQU
  emp::Ptr<emp::DataMonitor<int>> not_count_node;
  emp::Ptr<emp::DataMonitor<int>> nand_count_node;
  emp::Ptr<emp::DataMonitor<int>> and_count_node;
  emp::Ptr<emp::DataMonitor<int>> orn_count_node;
  emp::Ptr<emp::DataMonitor<int>> or_count_node;
  emp::Ptr<emp::DataMonitor<int>> andn_count_node;
  emp::Ptr<emp::DataMonitor<int>> nor_count_node;
  emp::Ptr<emp::DataMonitor<int>> xor_count_node;
  emp::Ptr<emp::DataMonitor<int>> equ_count_node;

  emp::Ptr<emp::DataMonitor<int>> hotspot_not_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_nand_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_and_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_orn_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_or_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_andn_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_nor_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_xor_count_node;
  emp::Ptr<emp::DataMonitor<int>> hotspot_equ_count_node;

  emp::Ptr<emp::DataMonitor<int>> hotspot_org_count_node;
  emp::Ptr<emp::DataMonitor<double>> hotspot_point_count_node;
  emp::Ptr<emp::DataMonitor<double>> total_point_count_node;

 
public:
  /*Constructor*/
  OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) { }

  /*Deconstructor*/
  ~OrgWorld() {
    if (not_count_node) not_count_node.Delete();
    if (nand_count_node) nand_count_node.Delete();
    if (and_count_node) and_count_node.Delete();
    if (orn_count_node) orn_count_node.Delete();
    if (or_count_node) or_count_node.Delete();
    if (andn_count_node) andn_count_node.Delete();
    if (nor_count_node) nor_count_node.Delete();
    if (xor_count_node) xor_count_node.Delete();
    if (equ_count_node) equ_count_node.Delete();

    if (hotspot_not_count_node) hotspot_not_count_node.Delete();
    if (hotspot_nand_count_node) hotspot_nand_count_node.Delete();
    if (hotspot_and_count_node) hotspot_and_count_node.Delete();
    if (hotspot_orn_count_node) hotspot_orn_count_node.Delete();
    if (hotspot_or_count_node) hotspot_or_count_node.Delete();
    if (hotspot_andn_count_node) hotspot_andn_count_node.Delete();
    if (hotspot_nor_count_node) hotspot_nor_count_node.Delete();
    if (hotspot_xor_count_node) hotspot_xor_count_node.Delete();
    if (hotspot_equ_count_node) hotspot_equ_count_node.Delete();

    if (hotspot_org_count_node) hotspot_org_count_node.Delete();
    if (hotspot_point_count_node) hotspot_point_count_node.Delete();
    if (total_point_count_node) total_point_count_node.Delete();

    Clear();
    for (Task* task : tasks) {
      delete task;
    }
  }

  /**
  * input: none
  * output: the population
  * purpose: gets the population
  */
  const pop_t &GetPopulation() { return pop;}

  /**
  * input: per how many updates the hotspot should move
  * output: none
  * purpose: sets the hotspot moving frequency
  */
  void SetHospotMoveFreq(int _in) { move_freq = _in; }

  /**
  * input: none
  * output: none
  * purpose: updates the world
  */
  void Update() {
    emp::World<Organism>::Update();
    //move the hotspot
    if (move_freq > 0 && update % move_freq == 0) {
      int old_center = hotspot_indices[4];
      hotspot_indices.clear();
      int new_center = GetRandomNeighborPos(old_center).GetIndex();
      SetupHotspot(new_center);
    }
    //Process each organism
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    for(int i : schedule) {
      if(!IsOccupied(i)) {continue;}
      if (IsHotspot(i)) {
        pop[i]->Process(i, 4);
      } else {
        pop[i]->Process(i, 1);
      }
    }

    //Time to allow reproduction for any organisms that ran the reproduce instruction
    for (emp::WorldPosition location : reproduce_queue) {
      if (!IsOccupied(location)) {
        return;
      }
      std::optional<Organism> offspring =
          pop[location.GetIndex()]->CheckReproduction();
      if (offspring.has_value()) {
        DoBirth(offspring.value(), location.GetIndex());
      }
    }
    reproduce_queue.clear();
  }

  /**
  * input: the output and a state
  * output: none
  * purpose: randomly iterates over tasks and stops when it completes one or fails all tasks
  */
  void CheckOutput(float output, OrgState& state) {
    //only let it complete one task, but randomize task list order
    emp::vector<size_t> schedule = emp::GetPermutation(random, tasks.size());
    state.completed_task_id = -1;
    for (int i : schedule) {
      double points = state.points;
      state.points += tasks[i]->CheckOutput(output, state.last_inputs);
      if (state.points > points) { // gained points
        state.completed_task_id = tasks[i]->id();
        return; // only complete 1 task
      }
    }
  }

  

  /**
  * input: the position of an organism
  * output: none
  * purpose: to handle an organism's reproduction
  */
  void ReproduceOrg(emp::WorldPosition location) {
    // Wait until after all organisms have been processed to perform
    // reproduction. If reproduction happened immediately then the child could
    // ovewrite the parent, and then we would be running the code of a deleted
    // organism
    reproduce_queue.push_back(location);

  }

  /**
  * input: the position of an organism
  * output: the index of the organism's color
  * purpose: to determine what color an organism should be in the web gui
  */
  int GetColorI(int i) {
    int color_i = 1;
    if (IsOccupied(i)) {
      color_i = pop[i]->GetCPU()->state.completed_task_id;
      if (color_i == -1) {
        color_i = 0;
      }
      else color_i += 2;
    }
    return color_i;
  }

  /**
  * input: the index of the central hotspot cell
  * output: none
  * purpose: populate the hotspot indices vector
  */
  void SetupHotspot(int center) {
    int side = GetWidth();
    int x = center % side; 
    int y = center / side; 
    int x_vals[3] = { x - 1, x, x + 1 };
    if (x - 1 < 0) x_vals[0] = side - 1;
    else if (x + 1 >= side) x_vals[2] = 0;
    int y_vals[3] = { y - 1, y, y + 1 };
    if (y - 1 < 0) y_vals[0] = side - 1;
    else if (y + 1 >= side) y_vals[2] = 0;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        hotspot_indices.push_back((y_vals[j] * side) + x_vals[i]);

      }
    }
  }

  /**
   * input: the index of the tasks to permit (up to 9)
   * output: none
   * purpose: populate the determine how many tasks can be completed
   */
  void SetupTasks(int num_tasks) {
    std::vector<Task*> possible_tasks{ new AND(),  new EQU(),  new XOR(),  new NOR(),
                            new ANDN(), new OR(),   new ORN(),
                              new NAND(), new NOT() };
    for (int i = 0; i < possible_tasks.size(); i++) {
      if (i < num_tasks) {
        tasks.push_back(possible_tasks[i]);
      }
      else {
        delete possible_tasks[i];
      }
    }
  }
  /**
  * input: the index to check
  * output: whether the index is in the hotspot
  * purpose: to determine whether an organism is in a hotspot
  */
  bool IsHotspot(int pos) {
    for (int i = 0; i < hotspot_indices.size(); i++) {
      if (pos == hotspot_indices[i]) {
        return true;
      }
    }
    return false;
  }

  // DATA NODES - expanded in DataMethods.cpp
  emp::DataMonitor<int>& GetNotCountDataNode();
  emp::DataMonitor<int>& GetNandCountDataNode();
  emp::DataMonitor<int>& GetAndCountDataNode();
  emp::DataMonitor<int>& GetOrnCountDataNode();
  emp::DataMonitor<int>& GetOrCountDataNode();
  emp::DataMonitor<int>& GetAndnCountDataNode();
  emp::DataMonitor<int>& GetNorCountDataNode();
  emp::DataMonitor<int>& GetXorCountDataNode();
  emp::DataMonitor<int>& GetEquCountDataNode();

  emp::DataMonitor<int>& GetHotspotNotCountDataNode();
  emp::DataMonitor<int>& GetHotspotNandCountDataNode();
  emp::DataMonitor<int>& GetHotspotAndCountDataNode();
  emp::DataMonitor<int>& GetHotspotOrnCountDataNode();
  emp::DataMonitor<int>& GetHotspotOrCountDataNode();
  emp::DataMonitor<int>& GetHotspotAndnCountDataNode();
  emp::DataMonitor<int>& GetHotspotNorCountDataNode();
  emp::DataMonitor<int>& GetHotspotXorCountDataNode();
  emp::DataMonitor<int>& GetHotspotEquCountDataNode();

  emp::DataMonitor<int>& GetHotspotOrgCount();
  emp::DataMonitor<double>& GetHotspotPointGain();
  emp::DataMonitor<double>& GetPointGain();

  emp::DataFile& SetupTaskCountFile(const std::string& filename);
  emp::DataFile& SetupOrgPointsFile(const std::string& filename);
};

#endif
