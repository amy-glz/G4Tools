#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh" 
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* detConstruction)
  : fpDetectorConstruction(detConstruction),fpWorldGeometryDirectory(nullptr),fpWorldSideLength(nullptr),fpCellGeometryDirectory(nullptr),fpCellRadius(nullptr){
  fpWorldGeometryDirectory = new G4UIdirectory("/world/");
  fpWorldGeometryDirectory->SetGuidance("Commands for word geometry params");

  fpWorldSideLength = new G4UIcmdWithADoubleAndUnit("/world/worldSize", this);
  fpWorldSideLength->SetGuidance("Side length for the world");
  fpWorldSideLength->SetParameterName("Side length", false);

  fpCellGeometryDirectory = new G4UIdirectory("/cell/");
  fpCellGeometryDirectory->SetGuidance("Commands for world geometry params");
  fpCellRadius = new G4UIcmdWith3VectorAndUnit("/cell/radiusSize", this);
  fpCellRadius->SetParameterName("xradius","yradius","zradius",false);
}

DetectorMessenger::~DetectorMessenger()
{
  delete fpCellRadius;
  delete fpWorldSideLength;
  delete fpCellGeometryDirectory;
  delete fpWorldGeometryDirectory;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fpWorldSideLength){
    fpDetectorConstruction->SetWorldSideLength(((G4UIcmdWithADoubleAndUnit*)command)->GetNewDoubleValue(newValue));
  }
  else if (command == fpCellRadius){
    fpDetectorConstruction->SetCellRadius(((G4UIcmdWith3VectorAndUnit*)command)->GetNew3VectorValue(newValue));
  }
}
