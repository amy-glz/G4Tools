#include "DetectorConstruction.hh"

#include <fstream>

#include "DNAGeometry.hh"
#include "DetectorMessenger.hh"
#include "OctreeNode.hh"

#include "G4Box.hh"
#include "G4Color.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#incldue "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
  : fpDNAGeometry(new DNAGeometry()), fpDetectorMessenger(new DetectrorMessenger(this))
{
  G4bool useParallelPhysicsWorld = false;
  if(useParallelPhysicsWorld){
    RegisterParallelWorld(fpDNAGeometry->GetDNAWorld());
  }
}

DetectorConstruction::~DetectorConstruction()
{
  delete fpDetectorMessenger;
}

G4PhysicalVolume* DetectorConstruction::Construct()
{
  BuildMaterials();
  return ConstructDetector();
}

void DetectorConstruction::BuildMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  fpWorld = man->FindOrBuildMaterial("G4_Galactic");
  fpWater = man->FindOrBuildMaterial("G4_WATER");
}

G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{
  G4LogicalVolume* pDnaRegionLocal;

  G4double dnasx = fCellRadius.getX();
  G4double dnasy = fCellRadius.getY();
  G4double dnasz = fCellRadius.getZ();

  if ((dnasx <=0) || (dnasy <=0) || (dnasz <=0)){
    // Sin Volumen de ADN
    G4double wsize = 1.01 * fWorldSideLength / 2.;
    auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
    auto worldLogical  = new G4LogicalVolume(worldPhysical, fpWater, "world");
    fWorld = new G4PVPlacement(nullptr, G4TrheeVector(0), worldLogical, "world", nullptr,false, 0);
    pDnaRegionLogical = worldLogical
  }
  else{
    //Con ADN
    G4double wsize = 1.01 * fWorldSideLength / 2.;
    auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
    auto worldLogical  = new G4LogicalVolume(worldPhysical. fpWater, "world");
    fWorld = new G4PVPlacement(nullptr, G4ThreeVector(0), worldLogical, "world", nullptr, false, 0);

    //ADN
    auto dnaPhysical = new G4Ellipsoid("CellPhysical",dnasx,dnasy,dnasz);
    auto dnaLogical  = new G4LogicalVolume(dnaPhysical,fpWater, "CellLogical");
    new G4PVPlacement(nullptr, G4ThreeVector(0), "CellVolume", dnaLogical, fWorld, false, 0, false);
    pDnaRegionLogical = dnaLogical;
  }
  this->GetDNAGeometry()->BuildDNA(pDnaRegionLogical);
  return fWorld;
}
