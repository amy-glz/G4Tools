//Radiolysis Analysis
//Amy González

#include "ActionInitialization.hh" 
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4DNAChemistryManager.hh"
#include "G4Scheduler.hh"

//#include <ctime>

int main(int argc, char** argv){
  //--- Run Manager
  auto* runManager = G4RunManagerFactory::CreateRunManager();

  //--- Geometry
  runManager->SetUserInitialization(new DetectorConstruction());

  //--- Physics
  runManager->SetUserInitialization(new PhysicsList());

  //--- User Actions
  runManager->SetUserInitialization(new ActionInitialization());

  //==== QUIMICA =====
  G4DNAChemistryManager::Instance()->Initialize();
  G4Scheduler::Instance()->SetVerbose(1);

  //--- Visualization
  auto* visManager = new G4VisExecutive();
  visManager->Initialize();

  //--- UI
  auto* UImanager = G4UImanager::GetUIpointer();
  if (argc ==1){
    auto* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("control/execute macros/vis.mac");

    ui->SessionStart();
    delete ui;
  }
  else {
    G4String macro = argv[1];
    UImanager->ApplyCommand("/control/execute " + macro);
  }

  delete visManager;
  delete runManager;
  return 0;
}
