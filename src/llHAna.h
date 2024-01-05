// Include necessary header files
#include "GaudiAlg/GaudiAlgorithm.h"
#include <Gaudi/Property.h>
#include "k4FWCore/DataHandle.h" 
#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/MCParticle.h"
#include "edm4hep/ReconstructedParticleCollection.h"
#include "edm4hep/ReconstructedParticle.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

namespace{
    class MCParticleCollection;
    class ReconstructedParticleCollection;
}

class llHAna : public GaudiAlgorithm {
public:
    // Constructor and destructor
    llHAna(const std::string& name, ISvcLocator* pSvcLocator);
    // GaudiAlgorithm methods
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

private:
    TFile* rootFile;
    TTree* tree;
    double lep_energy_threshold = 30.0;

    // DataHandle for the MCParticleCollection
    DataHandle<edm4hep::MCParticleCollection> mcParticleCol{"MCParticle", Gaudi::DataHandle::Reader, this};
    // DataHandel for the ReconstructedParticleCollection
    DataHandle<edm4hep::ReconstructedParticleCollection> recParticleCol{"ArborPFOs", Gaudi::DataHandle::Reader, this};
    // DataHandle for the MCTruthLinkCollection
    //DataHandle<edm4hep::MCTruthLinkCollection> mcTruthLinkCol{"RecoMCTruthLink", Gaudi::DataHandle::Reader, this};

};
