EMP_BUILD_CONFIG(MyConfigType,
    VALUE(NUM_ORGS, int, 200, "How many organisms should the world start with (too few and they may not evolve)?"), 
    VALUE(REQUIRED_POINTS, int, 20, "How many points should be required for organisms to reproduce?"),
    VALUE(MOVING_HOTSPOT_FREQ, int, 100, "Per how many updates does the hotspot move (0 for never)?"),
    VALUE(RANDOM_SEED, int, 5, "What is the random seed of this run?"),
    VALUE(NUM_POSSIBLE_TASKS, int, 9, "How many tasks are possible?"),
)
