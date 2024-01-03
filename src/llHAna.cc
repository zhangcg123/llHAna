#include "llHAna.h"
#include "edm4hep/EventHeaderCollection.h"
#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/ReconstructedParticleCollection.h"

DECLARE_COMPONENT(llHAna)

// Constructor
llHAna::llHAna(const std::string& name, ISvcLocator* pSvcLocator)
    : GaudiAlgorithm(name, pSvcLocator) {
        declareProperty("MCParticleCollection", mcParticleCol, "Handle for the MCParticleCollection");
        declareProperty("ReconstructedParticleCollection", recoParticleCol, "Handle for the ReconstructedParticleCollection");   
    
    }

// Method to initialize your analysis
StatusCode llHAna::initialize() {
    // Initialization code goes here
    debug() << "Initializing llHAna" << endmsg;
    return GaudiAlgorithm::initialize();
}

// Method to execute your analysis
StatusCode llHAna::execute() {
    debug() << "Executing llHAna" << endmsg;
    // Get the MCParticleCollection
    const edm4hep::MCParticleCollection* mcParticles = mcParticleCol.get();
    // Get the ReconstructedParticleCollection
    const edm4hep::ReconstructedParticleCollection* recoParticles = recoParticleCol.get();

    // Print the number of MCParticles
    debug() << "Number of MCParticles: " << mcParticles->size() << endmsg;

    // Execution code goes here

    return StatusCode::SUCCESS;
}

// Method to finalize your analysis
StatusCode llHAna::finalize() {
    // Finalization code goes here
    return GaudiAlgorithm::finalize();
}
