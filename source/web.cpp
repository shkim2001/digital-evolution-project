#define UIT_VENDORIZE_EMP
#define UIT_SUPPRESS_MACRO_INSEEP_WARNINGS

#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/web/UrlParams.hpp"
#include "World.h"
#include "ConfigSetup.h"

emp::web::Document doc{ "target" };
emp::web::Document settings("settings");
emp::web::Document buttons("buttons");
MyConfigType config;

class Animator : public emp::web::Animate {
private:
  // arena width and height
  const int num_h_boxes = 20;
  const int num_w_boxes = 20;
  const double RECT_SIDE = 20;
  const double width{ num_w_boxes * RECT_SIDE };
  const double height{ num_h_boxes * RECT_SIDE };
  emp::Random random{ 5 };
  OrgWorld world{ random };
  std::string colors[11] = { "black","white",
							 "red","blue","yellow",
							 "#009900","#66ffff", "#006699", 
							 "#3366ff", "#ccffcc", "green"};
  Organism *org;

  emp::web::Canvas canvas{ width, height, "canvas" };

public:
  /**
  * Constructor
  * input: none
  * Adds the framework of the world representation to the doc, adds the text, and injects some organisms into the world. 
  */
  Animator() {
	// shove canvas into the div
	// along with a control button
	doc << canvas;
	buttons << GetToggleButton("Toggle");
	buttons << GetStepButton("Step");

	// apply configuration query params and config files to config
	auto specs = emp::ArgManager::make_builtin_specs(&config);
	emp::ArgManager am(emp::web::GetUrlParams(), specs);
	am.UseCallbacks();
	if (am.HasUnused()) std::exit(EXIT_FAILURE);

	// setup configuration panel
	emp::prefab::ConfigPanel config_panel(config);
	settings << config_panel;
	random.ResetSeed(config.RANDOM_SEED());

	// apply config settings
	int interval = num_h_boxes * num_w_boxes / config.NUM_ORGS();
	int org_count = config.NUM_ORGS();
	if (org_count > num_h_boxes * num_w_boxes) org_count = num_h_boxes * num_w_boxes;
	else if (org_count < 1) org_count = 0;
	if (interval == 0) interval = 1;

	
	// set up the world size / structure
	world.Resize(width, height);
	world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

	world.SetupHotspot(25);
	world.SetupTasks(config.NUM_POSSIBLE_TASKS());
	world.SetHospotMoveFreq(config.MOVING_HOTSPOT_FREQ());

	// populate the world with organisms
	for (int i = interval - 1; i < org_count * interval; i += interval) {
	  world.AddOrgAt(new Organism(&world, 10, config.REQUIRED_POINTS()), i);
	}
  }
  

  /**
  * 
  * input: none
  * output: none
  * purpose: redraws a frame and updates the world once.
  */
  void DoFrame() override {
	canvas.Clear();
	int pop_i = 0;
	for (int x = 0; x < num_w_boxes; x++) {
	  for (int y = 0; y < num_h_boxes; y++) {
		if (world.IsHotspot(pop_i)) {
		  std::cout << " hello!" << std::endl;
		  canvas.Circle(x * RECT_SIDE + RECT_SIDE/2, y * RECT_SIDE + RECT_SIDE / 2, RECT_SIDE/2, colors[world.GetColorI(pop_i)], "black");
		}
		else {
		  canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, colors[world.GetColorI(pop_i)], "black");
		}
		pop_i++;
	  }
	}

	//update AFTER drawing the world (or else the starting condition would not be  displayed)
	world.Update();
  }

};

Animator animator;

int main() { animator.Step(); }