#ifndef PHYSICS_LIST_HH
#define pHYSICS_LIST_HH

#include "G4VModularrPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsList : public G4VModularPhysicsList
{
public:
  explicit PhysicsList(G4int list);
  ~PhysicsList() override = default;
};

#endif
