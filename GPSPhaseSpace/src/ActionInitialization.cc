#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh" 
#include "PhaseSpaceData.hh"
//#include "SteppingAction.hh"

void ActionInitialization::BuildForMaster() const{
  SetUserAction(new RunAction());
  PhaseSpaceData::Instance()->LoadROOT("PhaseSpace.root");
}

void ActionInitialization::Build() const{
  auto runAction = new RunAction();
  SetUserAction(new PrimaryGeneratorAction(false));
  SetUserAction(runAction);
  //  SetUserAction(new SteppingAction());
}
