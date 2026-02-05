#ifndef PHYSICS_LIST_HH
#define PHYSICS_LIST_HH

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsList : public G4VModularPhysicsList
{
public:
  explicit PhysicsList();
  ~PhysicsList() override = default;
};

#endif
