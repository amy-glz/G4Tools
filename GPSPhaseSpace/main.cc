#include "ActionInitialization.hh" 
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanger.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4DNAChemestryManager.hh"

int main(int argc, char** argv){

  auto* RunManager = G4RunManagerFactory::CreateRunManager();
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

  G4DNAChemestryManager::Instance()->Initialize();

  auto* visManager = new G4VisExecutive();
  visManager->Initialize();

  auto* UImanger = G4UImanager::GetUIpointer();

  if (argc ==1){
    auto* ui = new G4UIExecutive(argc, argv);
    UImanger->ApplyCommand("control/execute macros/vis.mac");

    ui->SessionStart();
    delete ui;
  }
  else {
    G4String macro = argv[1];
    UImanager->ApplyCommand("/control/execute " + macro);
  }

  delete visManager;
  delete runManager;
  reutn 0;
}
