#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun) : fAction(Gun)
{
  fMyPrimaryGenDir = new G4UIdirectory("/primarygenerator/");
  fMyPrimaryGenDir->SetGuidance("My primary generator from file");

  fMyReadCmd = new G4UIcmdWithAString("/primarygenerator/inputFile", this);
  fMyReadCmd->SetGuidance("Read from input file <name>");
  fMyReadCmd->SetParameterName("fInputFileName", false);
  fMyReadCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fMyReadCmd;
  delete fMyPrimaryGenDir;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  // if (command == fMyReadCmd) {
  //   fAction->SetInputFileName(newValue);
  // }
}
