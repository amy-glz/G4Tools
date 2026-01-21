#include "PhysicsList.hh"
// #include "ChemistryList.hh"
// #include "ParallelWorldPhysics.hh"

 #include "G4DecayPhysics.hh"
 #include "G4EmDNAPhysics.hh"
// #include "G4EmDNAPhysics_option2.hh"
// #include "G4EmDNAPhysics_option4.hh"
// #include "G4EmDNAPhysics_option6.hh"
// #include "G4EmParameters.hh"
 #include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"

 PhysicsList::PhysicsList()
{
   SetDefaultCutValue(1.0 * micrometer);
   SetVerboseLevel(1);

   UseCoupledTransportation();

//   if (phylist == 0){
//     RegisterPhysics(new G4EmDNAPhysics());
//   }
//   else if (phylist == 2){
//     RegisterPhysics(new G4EmDNAPhysics_option2());
//   }
//   else if (phylist == 4){
//     RegisterPhysics(new G4EmDNAPhysics_option4());
//   }
//   else if (phylist == 6){
//     RegisterPhysics(new G4EmDNAPhysics_option6());
//   }
 
   RegisterPhysics(new G4EmDNAPhysics());
   RegisterPhysics(new G4DecayPhysics());
   RegisterPhysics(new G4RadioactiveDecayPhysics());

//   G4bool useParallelPhysicsWorld = false;
//   if(useParallelPhysicsWorld){
//     RegisterPhysics(new ParallelWorldPhysics("DNAWorld",true));
//   }

//   RegisterPhysics(new ChemestryList());

   G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100 * eV, 1 * GeV);
}
