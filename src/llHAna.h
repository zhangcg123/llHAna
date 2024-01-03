// Include necessary header files
#include "GaudiAlg/GaudiAlgorithm.h"
#include "k4FWCore/DataHandle.h" 
#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/ReconstructedParticleCollection.h"
#include "TFile.h"
#include "TTree.h"

class llHAna : public GaudiAlgorithm {
public:
    // Constructor and destructor
    llHAna(const std::string& name, ISvcLocator* pSvcLocator);
    virtual ~llHAna();

    // GaudiAlgorithm methods
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

private:
    TFile* rootFile;
    TTree* tree;
    double energy;

    // DataHandle for the MCParticleCollection
    DataHandle<edm4hep::MCParticleCollection> mcParticleCol{"MCParticles", Gaudi::DataHandle::Reader, this};
    // DataHandle for the ReconstructedParticleCollection
    DataHandle<edm4hep::ReconstructedParticleCollection> recoParticleCol{"ReconstructedParticles", Gaudi::DataHandle::Reader, this};
};