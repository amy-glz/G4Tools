#include "DetectorConstruction.hh"

#include <fstream>



//#include "DNAGeometry.hh"
//#include "DetectorMessenger.hh"
//#include "OctreeNode.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#inlcude "G4MultiFunciontalDetector.hh"
#inlcude "G4PhysicalConstants.hh"
#include "G4Box.hh"
#include "G4Color.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //=========================================================
  // 1.  MaATERIALS
  //=========================================================
  
  G4NistManager * nist = G4NistManager::Instance();
  auto Water=nist->FindOrBuildMaterial("G4_WATER");

  //=========================================================
  // 2. WORLD VOLUME
  //=========================================================
  
  //G4double fWorldSideLength = 10 * um;
  G4double wsize = 1.0 * cm / 2.;
  auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
  auto worldLogical  = new G4LogicalVolume(worldPhysical, Water, "world");
  auto fWorld = new G4PVPlacement(nullptr, G4ThreeVector(0), worldLogical, "world", nullptr,false, 0);

  G4cout << "World Creado" << G4endl;

  //=========================================================
  // 3. CELL VOLUME
  //=========================================================
  
  G4double csize = 15.0 * um / 2.;
  auto cellPhysical = new G4Box("CellPhysical",csize,csize,csize);
  auto cellLogical  = new G4LogicalVolume(cellPhysical, Water, "Cell");
  auto fCell = new G4PVPlacement(nullptr, G4ThreeVector(0), cellLogical, "cell", worldLogical, false, 0);

  G4cout << "Cell Creado" << G4endl;

  //=========================================================
  // 4. VISUALIZATION
  //=========================================================
  G4VisAttributes* WorldAttr = new G4VisAttributes();
  WorldAttr->SetVisibility(true);
  WorldAttr->SetForceSolid(false);
  WorldAttr->SetForceWireframe(true);
  worldLogical->SetVisAttributes(WorldAttr);

  G4VisAttributes* CellAttr = new G4VisAttributes();
  CellAttr->SetVisibility(true);
  CellAttr->SetForceSolid(true);
  cellLogical->SetVisAttributes(CellAttr);
  
  return fWorld;
}

voide DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SerVerboseLevel(1);

  //=========================================================
  // 1. DETECTOR MULTIFUNCIONAL
  //=========================================================

  G4MultiFunctionalDetector* mfDetector = new G4MultiFunctionalDetector("mfDetector");
  
  //=========================================================
  // 2. PRIMARY KILLER
  //=========================================================

  //=========================================================
  // 3. LET SCORER
  //=========================================================

  scoreLET* LET = new scorerLET("LET");
  mfDetector->RegisterPrimitive(LET);
  
  //=========================================================
  // 4. SPECIES SCORER
  //=========================================================

  G4VPrimitiveScorer * PrimitiveSpecies = new scoreSpecies("Species");
  mfDetector->RegisterPrimitive(PrimitiveSpecies);

  G4SDManager::GetSDMpointer()->AddNewDetectir(fDetector);
  SetSensitiveDetector("World",mfDetector)
}
