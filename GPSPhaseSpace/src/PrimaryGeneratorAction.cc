#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "TFile.h"
#include "TROOT.h"
#include <iostream>
#include <cmath> 
// #include "CLHEP/Units/SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(){
  // fGun = new G4ParticleGun(1);
  // G4ParticleDefinition * electron = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  // fGun->SetParticleDefinition(electron);
  // fGun->SetParticleEnergy(6. * eV);
  // fGun->SetParticlePosition(G4ThreeVector(0));
  file=TFile::Open("PhaseSpace.root");
  tree= (TTree*)file->Get("PhSp");
  tree->SetBranchesAddress("x", &x);
  tree->SetBranchesAddress("y", &y);
  tree->SetBranchesAddress("z", &z);
  tree->SetBranchesAddress("px", &px);
  tree->SetBranchesAddress("py", &py);
  tree->SetBranchesAddress("pz", &px);
  tree->SetBranchesAddress("E", &E);
  tree->SetBranchesAddress("t", &t);
  tree->SetBranchesAddress("w", &w);
  tree->SetBranchesAddress("pdg", &pdg);

  nEntries = tree->GetEntries();
  currentEntry = 0;
  
}


PrimaryGeneratorAction::~PrimaryGeneratorAction(){ delete fGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
  // G4double cosTheta = 2.0 * G4UniformRand() - 1.0;
  // G4double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);
  // G4double phi      = 2.0 * CLHEP::pi * G4UniformRand();

  // G4ThreeVector direction(sinTheta * std::cos(phi),
  // 			  sinTheta * std::sin(phi),
  // 			  cosTheta);

  // fGun->SetParticleMomentumDirection(direction);
  // fGun->GeneratePrimaryVertex(event);
  // G4cout << "Generating primary particle" << G4endl;


  if(currendEntry >= nEntries) {
    G4Exeption("PrimaryGeneratorAction",
	       "EndOfPhaseSpace",
	       FatalExeption,
	       "Phase space file exhausted");
  }

  tree->GetEntry(currentEntry++);
  auto ParticleDef = G4ParticleTable::GetParticleTable()->FindParticle(pdg);
  G4ThreeVector Pos = G4ThreeVector(x * mm,y * mm,z * mm);
  G4ThreeVector P = G4ThreeVector(px,py,pz);

  fGun->SetParticleDefinition(ParticleDef);
  fGun->SetParticlePosition(Pos);
  fGun->SetParticleMomentumDirection(P.unit);
  fGun->SetParticleEnergy(E*MeV);

  fGun->GetPrimaryVertex(event);
  event->GetPrimaryVertex()->SetWeight(w);

  G4cout << "Generating primary particle" << G4endl;
}
