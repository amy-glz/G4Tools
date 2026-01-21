#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

class RunAction : public G4UserRunAction{
public:
  explicit RunAction();
  ~RunAction() override = default;

  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

};
#endif
