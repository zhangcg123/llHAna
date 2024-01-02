#include "llHAna.h"

// Constructor
llHAna::llHAna(const std::string& name, ISvcLocator* pSvcLocator)
    : GaudiAlgorithm(name, pSvcLocator) {}

// Destructor
llHAna::~llHAna() {}

// Method to initialize your analysis
StatusCode llHAna::initialize() {
    // Initialization code goes here
    return StatusCode::SUCCESS;
}

// Method to execute your analysis
StatusCode llHAna::execute() {
    // Get the MCParticleCollection
    const edm4hep::MCParticleCollection* mcParticles = mcParticleCol.get();

    // Execution code goes here

    return StatusCode::SUCCESS;
}

// Method to finalize your analysis
StatusCode llHAna::finalize() {
    // Finalization code goes here
    return StatusCode::SUCCESS;
}