#ifndef PHASE_SPACE_HH
#define PHASE_SPACE_HH

#include <vector>
#include <string>

struct PhaseSpaceParticle {
  double x, y ,z;
  double ux, uy, uz;
  double E;
  double t;
  double w;
  int pdg;
};

class PhaseSpaceData{
public:
  static PhaseSpaceData* Instance();
  void LoadROOT(const std::string& filename);
  const PhaseSpaceParticle& GetParticle(size_t i ) const;
  size_t GetSize() const;
  
private:
  PhaseSpaceData() = default;
  static PhaseSpaceData* fInstance;
  std::vector<PhaseSpaceParticle> fParticles;
  
};


#endif
