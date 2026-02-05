#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VDNAMolecularGeometry.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include <map>

class DetectorMessenger;
class DNAGeometry;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  DetectorConstruction();
  ~DetectorConstruction() override;
  G4VPhysicalVolume* Construct() override;
  void ConstructSDAndField() override;
  
  private:
  G4VPhysicalVolume* fWorld = nullptr;
};

#endif
