#include "PhaseSpaceData.hh"

#include <TFile.h>
#include <TTree.h>

PhaseSpaceData* PhaseSpaceData::fInstance = nullptr;

PhaseSpaceData* PhaseSpaceData::Instance(){
  if (!fInstance)
    fInstance = new PhaseSpaceData();
  return fInstance;
}

void PhaseSpaceData::LoadROOT(const std::string& filename){
  TFile* file = TFile::Open(filename.c_str(), "READ");
  TTree* tree = (TTree*)file->Get("phsp");
  PhaseSpaceParticle p;
  tree->SetBranchAddress("x_mm", &p.x);
  tree->SetBranchAddress("y_mm", &p.y);
  tree->SetBranchAddress("z_mm", &p.z);
  tree->SetBranchAddress("ux", &p.ux);
  tree->SetBranchAddress("uy", &p.uy);
  tree->SetBranchAddress("uz", &p.uz);
  tree->SetBranchAddress("E_MeV", &p.E);
  tree->SetBranchAddress("t_ns", &p.t);
  tree->SetBranchAddress("w", &p.w);
  tree->SetBranchAddress("pdg", &p.pdg);

  const auto n = tree->GetEntries();
  fParticles.reserve(n);

  for(Long64_t i = 0; i < n ; ++i ){
    tree->GetEntry(i);
    fParticles.push_back(p);
  }

  file->Close();
}

const PhaseSpaceParticle&
PhaseSpaceData::GetParticle(size_t i) const {
  return fParticles[i];
}

size_t PhaseSpaceData::GetSize() const {
  return fParticles.size();
}
