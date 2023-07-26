#ifndef ORG_H
#define ORG_H

#include "CPU.h"
#include "OrgState.h"
#include "emp/Evolve/World_structure.hpp"

class Organism {
  CPU cpu;
  size_t num_cycles;
  double required_points;
  double points_gained = 0;

public:
  /*Constructor*/
  Organism(OrgWorld* world, double points = 0.0, double r_points = 20, size_t n_cycles = 4) : cpu(world), required_points(r_points), num_cycles(n_cycles) {
    SetPoints(points);
    cpu.state.completed_task_id = -1;
  }

  /*Deconstructor*/
  ~Organism() {  }


  /**
  * input: a double amount of points to be set
  * output: none
  * purpose: to set the points available to the organism
  */
  void SetPoints(double _in) { cpu.state.points = _in; }

  /**
  * input: a double amount of points to be added
  * output: none
  * purpose: to add to the point total available to the host
  */
  void AddPoints(double _in) { cpu.state.points += _in; }

  /**
  * input: none
  * output: a double representation of the organism's points
  * purpose: to get the points availble to the organism
  */
  double GetPoints() {return cpu.state.points;}

  /**
  * input: none
  * output: none
  * purpose: to reset the organisms's cpu
  */
  void Reset() {
    cpu.Reset();
    cpu.state.completed_task_id = -1;
  }

  /**
  * input: none
  * output: none
  * purpose: to mutate the organism's 'genetic' information
  */
  void Mutate() {
    cpu.Mutate();
  }

  /**
  * input: none
  * output: a pointer to the organism's cpu
  * purpose: to get the organism's cpu
  */
  emp::Ptr<CPU> GetCPU() {
    return &cpu;
  }

  /**
  * input: none
  * output: the double number of points gained
  * purpose: to retrieve the number of points gained the previous process
  */
  double GetPointsGained() {
    return points_gained;
  }

  /**
  * input: none
  * output: potentially, a pointer to the child of this organism
  * purpose: to undergo reproduction if it is possible
  */
  std::optional<Organism> CheckReproduction() {
    if (GetPoints() > required_points) {
      Organism offspring = *this;
      offspring.Reset();
      offspring.Mutate();
      AddPoints(-required_points);
      return offspring;
    }
    return {};
  }

  /**
  * input: the current position of the object in the world
  * output: none
  * purpose: to run the organism's processes
  */
  void Process(emp::WorldPosition current_location, int cycles_factor) {
    num_cycles = 4;
    points_gained = 0;
    double orig_points = cpu.state.points;
    cpu.state.completed_task_id = -1;
    cpu.state.current_location = current_location;
    cpu.RunCPUStep(num_cycles * cycles_factor);

    points_gained = cpu.state.points - orig_points;
  }

  /**
  * input: none
  * output: none
  * purpose: prints the genome of the organism
  */
  void PrintGenome() {
    std::cout << "program ------------" << std::endl;
    cpu.PrintGenome();
    std::cout << "end ---------------" << std::endl;
  }
};

#endif