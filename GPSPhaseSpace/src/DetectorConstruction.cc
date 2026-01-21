#include "DetectorConstruction.hh"

#include <fstream>

//#include "DNAGeometry.hh"
//#include "DetectorMessenger.hh"
//#include "OctreeNode.hh"

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

DetectorConstruction::DetectorConstruction()
//  : fpDNAGeometry(new DNAGeometry()), fpDetectorMessenger(new DetectrorMessenger(this))
{
//   G4bool useParallelPhysicsWorld = false;
//   if(useParallelPhysicsWorld){
//     RegisterParallelWorld(fpDNAGeometry->GetDNAWorld());
//   }
}

DetectorConstruction::~DetectorConstruction()
{
//   delete fpDetectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  BuildMaterials();
  //return ConstructDetector();
  G4NistManager * nist = G4NistManager::Instance();
  auto Water=nist->FindOrBuildMaterial("G4_WATER");
  
  //G4double fWorldSideLength = 10 * um;
  G4double wsize = 1.0 * cm / 2.;
  auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
  auto worldLogical  = new G4LogicalVolume(worldPhysical, Water, "world");
  auto fWorld = new G4PVPlacement(nullptr, G4ThreeVector(0), worldLogical, "world", nullptr,false, 0);

  G4cout << "World Creado" << G4endl;

  G4double csize = 15.0 * um / 2.;
  auto cellPhysical = new G4Box("CellPhysical",csize,csize,csize);
  auto cellLogical  = new G4LogicalVolume(cellPhysical, Water, "Cell");
  auto fCell = new G4PVPlacement(nullptr, G4ThreeVector(0), cellLogical, "cell", worldLogical, false, 0);

  G4cout << "Cell Creado" << G4endl;

  return fWorld;
}

void DetectorConstruction::BuildMaterials()
{
//   G4NistManager* man = G4NistManager::Instance();
//   //fpWorld = man->FindOrBuildMaterial("G4_Galactic");
//   auto World=man->FindOrBuildMaterial("G4_Galactic");
//   //fpWater = man->FindOrBuildMaterial("G4_WATER");
//   //auto Water=man->FindOrBuildMaterial("G4_WATER");

//   return World;
//   //return Water;
}

//G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
// {
//   G4LogicalVolume* pDnaRegionLocal;

//   G4double dnasx = fCellRadius.getX();
//   G4double dnasy = fCellRadius.getY();
//   G4double dnasz = fCellRadius.getZ();

//   if ((dnasx <=0) || (dnasy <=0) || (dnasz <=0)){
//     // Sin Volumen de ADN
//     G4double wsize = 1.01 * fWorldSideLength / 2.;
//     auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
//     auto worldLogical  = new G4LogicalVolume(worldPhysical, fpWater, "world");
//     fWorld = new G4PVPlacement(nullptr, G4TrheeVector(0), worldLogical, "world", nullptr,false, 0);
//     pDnaRegionLogical = worldLogical
//   }
//   else{
//     //Con ADN
//     G4double wsize = 1.01 * fWorldSideLength / 2.;
//     auto worldPhysical = new G4Box("WorldPhysical",wsize,wsize,wsize);
//     auto worldLogical  = new G4LogicalVolume(worldPhysical. fpWater, "world");
//     fWorld = new G4PVPlacement(nullptr, G4ThreeVector(0), worldLogical, "world", nullptr, false, 0);

//     //ADN
//     auto dnaPhysical = new G4Ellipsoid("CellPhysical",dnasx,dnasy,dnasz);
//     auto dnaLogical  = new G4LogicalVolume(dnaPhysical,fpWater, "CellLogical");
//     new G4PVPlacement(nullptr, G4ThreeVector(0), "CellVolume", dnaLogical, fWorld, false, 0, false);
//     pDnaRegionLogical = dnaLogical;
//   }
//   this->GetDNAGeometry()->BuildDNA(pDnaRegionLogical);
//   return fWorld;
// }


