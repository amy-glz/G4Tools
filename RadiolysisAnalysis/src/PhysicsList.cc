#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmDNAChemistry.hh"
 #include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"

 PhysicsList::PhysicsList()
{
   SetDefaultCutValue(1.0 * micrometer);
   SetVerboseLevel(1);

   UseCoupledTransportation();

  //=========================================================
  // 1.  PHYSICS GEANT4-DNA
  //=========================================================
   RegisterPhysics(new G4EmDNAPhysics());

  //=========================================================
  // 2.  CHEMISTRY GEANT4-DNA
  //=========================================================
   RegisterPhysics(new G4EmDNAChemistry());
   
  //=========================================================
  // 3.  DESINTEGRATION
  //=========================================================
   RegisterPhysics(new G4DecayPhysics());
   RegisterPhysics(new G4RadioactiveDecayPhysics());

   G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100 * eV, 1 * GeV);
}
