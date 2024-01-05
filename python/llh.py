#!/usr/bin/env python

from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")
lcioinput.inputs = ["/cefs/data/DstData/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00048_001000_dst.slcio"
			#"/cefs/higgs/yudan/CEPC240/Reco_tpc_1800/qqh/Reco_qqh__00003.slcio",
			#"/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00002_000000_sim.slcio",
			#"/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00003_001000_sim.slcio",
			#"/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00004_000000_sim.slcio",
			#"/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00004_001000_sim.slcio",
		]
lcioinput.collections = [ 
    "MCParticle:MCParticle",
    "ReconstructedParticle:ArborPFOs",
]


from Configurables import llHAna
llHAna = llHAna("llHAna")

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EvtSel = 'NONE',
                EvtMax = -1,
                ExtSvc = [dsvc],
                OutputLevel=INFO #DEBUG
)

