#ifndef DETECTOR_MESSENGER_HH
#define DETECTOR_MESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;
class G4UIcommand;
class DetectorMessenger : public G4UImessenger
{
public:
  explicit DetectorMessenger(DetectorConstruction*);
  ~DetectorMessenger() override;
  void SetNewValue(G4UIcommand*, G4String) override;
private:
  DetectorConstruction* fpDetectorConstruction;
  G4UIdirectory* fpWorldGeometryDirectory;
  G4UIcmdWithADoubleAndUnit* fpWorldSideLength;

  G4UIdirectory* fpCellGeometryDirectory;
  G4UIcmdWith3VectorAndUnit* fpCellRadius;
};

#endif
