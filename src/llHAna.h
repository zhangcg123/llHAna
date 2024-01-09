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
#include "TH1D.h"
#include "TLorentzVector.h"
#include <cmath>

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
    TH1D* cutFlow; 
    TH1D* Eventcounter;

    TLorentzVector S;

    double Z_mass = 91.1876;

    // DataHandle for the MCParticleCollection
    DataHandle<edm4hep::MCParticleCollection> mcParticleCol{"MCParticle", Gaudi::DataHandle::Reader, this};
    // DataHandel for the ReconstructedParticleCollection
    DataHandle<edm4hep::ReconstructedParticleCollection> recParticleCol{"ArborPFOs", Gaudi::DataHandle::Reader, this};
    // DataHandle for the MCTruthLinkCollection
    //DataHandle<edm4hep::MCTruthLinkCollection> mcTruthLinkCol{"RecoMCTruthLink", Gaudi::DataHandle::Reader, this};

    double pos_energy, neg_energy, pos_px, pos_py, pos_pz, neg_px, neg_py, neg_pz, pos_pt, neg_pt, pos_p, neg_p, pos_eta, neg_eta, pos_phi, neg_phi;
    double ll_energy, ll_mass, ll_px, ll_py, ll_pz, ll_pt, ll_p, ll_eta, ll_phi, recoil_mass;

    std::string filename;

};
