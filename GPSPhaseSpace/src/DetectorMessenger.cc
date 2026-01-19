#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh" 
#include "G4UIcmWith3VectorAndUnit.hh"
#include "G4UIcmWithADoubleAndUnit.hh"
#include "G4UIDirectory.hh"

DetectorMessenger::DetectorMessenger(DetecotConstruction* detConstruction)
  : fpDetectorConstruction(detConstruction),fpWorldGeometryDirectory(nullptr),fpWorldSideLength(nullptr),fpCellGeometryDirectory(nullptr),fpCellRadius(nullptr){
  fpWorldGeometryDirectory = new G4UIdirectory("/world/");
  fpWorldGeometryDirectory->SetGuidance("Commands for word geometry params");

  fpWorldSideLength = new G4UIcmWithADoubleAndUnit("/world/worldSize", this);
  fpWorldSideLength->SetGuidance("Side length for the world");
  fpWorldSideLength->SetParameterName("Side length", false);

  fpCellGeometryDirectory = new G4UIdirectory("/cell/");
  fpCellGeometryDirectory->SetGuidance("Commands for world geometry params");
  fpCellRadius = new G4UIcmWith3VectorAndUnit("/cell/radiusSize", this);
  fpCellRaduis->SetParameterName("xradius","yradius","zradius",false);
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
    fpDetectorConstruction->SetWorldSideLength(((G4UIcmWithADoubleAndUnit*)command)->GetNewDoubleValue(newValue));
  }
  else if (command == fpCellRadius){
    fpDetectorConstruction->SetCellRadius(((G4UIcmWith3VectorAndUnit*)command)->GetNew3VectorValue(newValue));
  }
}
