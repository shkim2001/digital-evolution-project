#include "World.h"

// TOTAL TASK COUNTS
/**
  * input: none
  * output: the data node tracking how many 'not' tasks were executed total in the
  * population
  * purpose: to track how many 'not' tasks were executed total in the population
  */
emp::DataMonitor<int>& OrgWorld::GetNotCountDataNode() {
  if (!not_count_node) {
    not_count_node.New();
    OnUpdate([this](size_t) {
      not_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 0)
            not_count_node->AddDatum(1);
        }
      }
      });
  }
  return *not_count_node;
}

/**
* input: none
* output: the data node tracking how many 'nand' tasks were executed total in the
* population
* purpose: to track how many 'nand' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetNandCountDataNode() {
  if (!nand_count_node) {
    nand_count_node.New();
    OnUpdate([this](size_t) {
      nand_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 1)
            nand_count_node->AddDatum(1);
        }
      }
      });
  }
  return *nand_count_node;
}

/**
* input: none
* output: the data node tracking how many 'and' tasks were executed total in the
* population
* purpose: to track how many 'and' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetAndCountDataNode() {
  if (!and_count_node) {
    and_count_node.New();
    OnUpdate([this](size_t) {
      and_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 2)
            and_count_node->AddDatum(1);
        }
      }
      });
  }
  return *and_count_node;
}

/**
* input: none
* output: the data node tracking how many 'orn' tasks were executed total in the
* population
* purpose: to track how many 'orn' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetOrnCountDataNode() {
  if (!orn_count_node) {
    orn_count_node.New();
    OnUpdate([this](size_t) {
      orn_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 3)
            orn_count_node->AddDatum(1);
        }
      }
      });
  }
  return *orn_count_node;
}

/**
* input: none
* output: the data node tracking how many 'or' tasks were executed total in the
* population
* purpose: to track how many 'or' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetOrCountDataNode() {
  if (!or_count_node) {
    or_count_node.New();
    OnUpdate([this](size_t) {
      or_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 4)
            or_count_node->AddDatum(1);
        }
      }
      });
  }
  return *or_count_node;
}

/**
* input: none
* output: the data node tracking how many 'andn' tasks were executed total in the
* population
* purpose: to track how many 'andn' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetAndnCountDataNode() {
  if (!andn_count_node) {
    andn_count_node.New();
    OnUpdate([this](size_t) {
      andn_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 5)
            andn_count_node->AddDatum(1);
        }
      }
      });
  }
  return *andn_count_node;
}

/**
* input: none
* output: the data node tracking how many 'nor' tasks were executed total in the
* population
* purpose: to track how many 'nor' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetNorCountDataNode() {
  if (!nor_count_node) {
    nor_count_node.New();
    OnUpdate([this](size_t) {
      nor_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 6)
            nor_count_node->AddDatum(1);
        }
      }
      });
  }
  return *nor_count_node;
}

/**
* input: none
* output: the data node tracking how many 'xor' tasks were executed total in the
* population
* purpose: to track how many 'xor' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetXorCountDataNode() {
  if (!xor_count_node) {
    xor_count_node.New();
    OnUpdate([this](size_t) {
      xor_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 7)
            xor_count_node->AddDatum(1);
        }
      }
      });
  }
  return *xor_count_node;
}

/**
* input: none
* output: the data node tracking how many 'equ' tasks were executed total in the
* population
* purpose: to track how many 'equ' tasks were executed total in the population
*/
emp::DataMonitor<int>& OrgWorld::GetEquCountDataNode() {
  if (!equ_count_node) {
    equ_count_node.New();
    OnUpdate([this](size_t) {
      equ_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          if (pop[i]->GetCPU()->state.completed_task_id == 8)
            equ_count_node->AddDatum(1);
        }
      }
      });
  }
  return *equ_count_node;
}

// HOTSPOT TASK COUNTS

/**
  * input: none
  * output: the data node tracking how many 'not' tasks were executed in the hotspot
  * purpose: to track how many 'not' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotNotCountDataNode() {
  if (!hotspot_not_count_node) {
    hotspot_not_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_not_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 0) {
            hotspot_not_count_node->AddDatum(1);
          }
        }
      }
    });
  }
  return *hotspot_not_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'nand' tasks were executed in the hotspot
  * purpose: to track how many 'nand' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotNandCountDataNode() {
  if (!hotspot_nand_count_node) {
    hotspot_nand_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_nand_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 1) {
            hotspot_nand_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_nand_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'and' tasks were executed in the hotspot
  * purpose: to track how many 'and' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotAndCountDataNode() {
  if (!hotspot_and_count_node) {
    hotspot_and_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_and_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 2) {
            hotspot_and_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_and_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'orn' tasks were executed in the hotspot
  * purpose: to track how many 'orn' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotOrnCountDataNode() {
  if (!hotspot_orn_count_node) {
    hotspot_orn_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_orn_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 3) {
            hotspot_orn_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_orn_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'or' tasks were executed in the hotspot
  * purpose: to track how many 'or' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotOrCountDataNode() {
  if (!hotspot_or_count_node) {
    hotspot_or_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_or_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 4) {
            hotspot_or_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_or_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'andn' tasks were executed in the hotspot
  * purpose: to track how many 'andn' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotAndnCountDataNode() {
  if (!hotspot_andn_count_node) {
    hotspot_andn_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_andn_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 5) {
            hotspot_andn_count_node->AddDatum(1);
          }
        }
      }
    });
  }
  return *hotspot_andn_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'nor' tasks were executed in the hotspot
  * purpose: to track how many 'nor' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotNorCountDataNode() {
  if (!hotspot_nor_count_node) {
    hotspot_nor_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_nor_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 6) {
            hotspot_nor_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_nor_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'xor' tasks were executed in the hotspot
  * purpose: to track how many 'xor' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotXorCountDataNode() {
  if (!hotspot_xor_count_node) {
    hotspot_xor_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_xor_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 7) {
            hotspot_xor_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_xor_count_node;
}

/**
  * input: none
  * output: the data node tracking how many 'equ' tasks were executed in the hotspot
  * purpose: to track how many 'equ' tasks were executed total in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotEquCountDataNode() {
  if (!hotspot_equ_count_node) {
    hotspot_equ_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_equ_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          if (pop[hotspot_indices[i]]->GetCPU()->state.completed_task_id == 8) {
            hotspot_equ_count_node->AddDatum(1);
          }
        }
      }
      });
  }
  return *hotspot_equ_count_node;
}

/**
* input: the name of the file
* output: the data file
* purpose: to track how many tasks were executed total in the population
*/
emp::DataFile& OrgWorld::SetupTaskCountFile(const std::string& filename) {
  auto& file = SetupFile(filename);

  auto& not_node = GetNotCountDataNode();
  auto& nand_node = GetNandCountDataNode();
  auto& and_node = GetAndCountDataNode();
  auto& orn_node = GetOrnCountDataNode();
  auto& or_node = GetOrCountDataNode();
  auto& andn_node = GetAndnCountDataNode();
  auto& nor_node = GetNorCountDataNode();
  auto& xor_node = GetXorCountDataNode();
  auto& equ_node = GetEquCountDataNode();

  auto& hotspot_not_node = GetHotspotNotCountDataNode();
  auto& hotspot_nand_node = GetHotspotNandCountDataNode();
  auto& hotspot_and_node = GetHotspotAndCountDataNode();
  auto& hotspot_orn_node = GetHotspotOrnCountDataNode();
  auto& hotspot_or_node = GetHotspotOrCountDataNode();
  auto& hotspot_andn_node = GetHotspotAndnCountDataNode();
  auto& hotspot_nor_node = GetHotspotNorCountDataNode();
  auto& hotspot_xor_node = GetHotspotXorCountDataNode();
  auto& hotspot_equ_node = GetHotspotEquCountDataNode();

  file.AddVar(update, "update", "Update");
  file.AddTotal(not_node, "not_count", "Total number of successful not task calls");
  file.AddTotal(nand_node, "nand_count", "Total number of successful nand task calls");
  file.AddTotal(and_node, "and_count", "Total number of successful and task calls");
  file.AddTotal(orn_node, "orn_count", "Total number of successful orn task calls");
  file.AddTotal(or_node, "or_count", "Total number of successful or task calls");
  file.AddTotal(andn_node, "andn_count", "Total number of successful andn task calls");
  file.AddTotal(nor_node, "nor_count", "Total number of successful nor task calls");
  file.AddTotal(xor_node, "xor_count", "Total number of successful xor task calls");
  file.AddTotal(equ_node, "equ_count", "Total number of successful equ task calls");

  file.AddTotal(hotspot_not_node, "hotspot_not_count", "Hotspot successful not task calls");
  file.AddTotal(hotspot_nand_node, "hotspot_nand_count", "Hotspot successful nand task calls");
  file.AddTotal(hotspot_and_node, "hotspot_and_count", "Hotspot successful and task calls");
  file.AddTotal(hotspot_orn_node, "hotspot_orn_count", "Hotspot successful orn task calls");
  file.AddTotal(hotspot_or_node, "hotspot_or_count", "Hotspot successful or task calls");
  file.AddTotal(hotspot_andn_node, "hotspot_andn_count", "Hotspot successful andn task calls");
  file.AddTotal(hotspot_nor_node, "hotspot_nor_count", "Hotspot successful nor task calls");
  file.AddTotal(hotspot_xor_node, "hotspot_xor_count", "Hotspot successful xor task calls");
  file.AddTotal(hotspot_equ_node, "hotspot_equ_count", "Hotspot successful equ task calls");

  file.PrintHeaderKeys();

  return file;
}


// POINT GAIN
/**
  * input: none
  * output: the data node tracking organisms are in the hotspot
  * purpose: to track how many organisms are in the hotspot
  */
emp::DataMonitor<int>& OrgWorld::GetHotspotOrgCount() {
  if (!hotspot_org_count_node) {
    hotspot_org_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_org_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          hotspot_org_count_node->AddDatum(1);
        }
      }
    });
  }
  return *hotspot_org_count_node;
}

/**
  * input: none
  * output: the data node tracking how points have been gained by hotspot organisms over the past turn
  * purpose: to track how points have been gained by hotspot organisms over the past turn
  */
emp::DataMonitor<double>& OrgWorld::GetHotspotPointGain() {
  if (!hotspot_point_count_node) {
    hotspot_point_count_node.New();
    OnUpdate([this](size_t) {
      hotspot_point_count_node->Reset();
      for (size_t i = 0; i < hotspot_indices.size(); i++) {
        if (IsOccupied(hotspot_indices[i])) {
          hotspot_point_count_node->AddDatum(pop[hotspot_indices[i]]->GetPointsGained());
        }
      }
    });
  }
  return *hotspot_point_count_node;
}

/**
  * input: none
  * output: the data node tracking how points have been gained by all organisms over the past turn
  * purpose: to track how points have been gained by all organisms over the past turn
  */
emp::DataMonitor<double>& OrgWorld::GetPointGain() {
  if (!total_point_count_node) {
    total_point_count_node.New();
    OnUpdate([this](size_t) {
      total_point_count_node->Reset();
      for (size_t i = 0; i < pop.size(); i++) {
        if (IsOccupied(i)) {
          total_point_count_node->AddDatum(pop[i]->GetPointsGained());
        }
      }
    });
  }
  return *total_point_count_node;
}



/**
* input: the name of the file
* output: the data file
* purpose: to track how many points were gained by organisms over the past turn
*/
emp::DataFile& OrgWorld::SetupOrgPointsFile(const std::string& filename) {
  auto& file = SetupFile(filename);
  auto& hotspot_org_count = GetHotspotOrgCount();
  auto& hotspot_point_count = GetHotspotPointGain();
  auto& total_point_count = GetPointGain();

  file.AddVar(update, "update", "Update");
  file.AddVar(num_orgs, "total_orgs", "The total number of organisms in the world");
  file.AddTotal(hotspot_org_count, "hotspot_orgs", "The number of organisms in the hotspot");
  file.AddTotal(total_point_count, "total_point_gain", "Total number of points gained over the last turn");
  file.AddTotal(hotspot_point_count, "hotspot_point_gain", "Hotspot number of points gained over the last turn");

  file.PrintHeaderKeys();

  return file;
}