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
  //    void ConstrucSDandField() override {};
    void SetWorldSideLength(const G4double& length) { fWorldSideLength = length; }
    void SetCellRadius(const G4ThreeVector& length) { fCellRadius = length; }
    [[maybe_unused]] auto GetWorld() const {return fWorld; };
    auto GetDNAGeometry() const {return fpDNAGeometry; };

  protected:
    G4VPhysicalVolume* ConstructDetector();
    void BuildMaterials();

  private:
    G4VPhysicalVolume* fWorld = nullptr;
    DNAGeometry* fpDNAGeometry;
    DetectorMessenger* fpDetectorMessenger;

    G4double fWorldSideLength = 6 * um;
    G4ThreeVector fCellRadius;

    G4Material* fpWorld = nullptr;
    G4Material* fpWater = nullptr;
};

#endif
