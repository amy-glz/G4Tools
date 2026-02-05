#include "PrimaryGeneratorAction.hh"
#include "PhaseSpaceData.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <iostream>
#include <cmath> 
#include "CLHEP/Units/SystemOfUnits.h"

PrimaryGeneratorAction::PrimaryGeneratorAction(bool isMaster)
  : fGun(new G4ParticleGun(1)), fIndex(0) {}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){ delete fGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {

  auto data = PhaseSpaceData::Instance();
  const auto n = data->GetSize();

  if(fIndex >= n) {
    G4Exception("PrimaryGeneratorAction",
	       "EndOfPhaseSpace",
	       FatalException,
	       "Phase space file exhausted");
  }

  const auto& p = data->GetParticle(fIndex++);
  auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle(p.pdg);

  fGun->SetParticleDefinition(particleDef);
  fGun->SetParticlePosition(G4ThreeVector(p.x*mm, p.y*mm, p.z*mm));
  fGun->SetParticleMomentumDirection(G4ThreeVector(p.ux, p.uy, p.uz).unit());
  fGun->SetParticleEnergy(p.E * MeV);
  fGun->GeneratePrimaryVertex(event);
  event->GetPrimaryVertex()->SetWeight(p.w);
    
  G4cout << "Generating primary particle" << G4endl;
}
