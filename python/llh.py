#!/usr/bin/env python

from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")
lcioinput.inputs = ["/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/E240.Pe2e2h_X.e0.p0.whizard195/e2e2h_X.e0.p0.00002_000000_sim.slcio"]
lcioinput.collections = [ 
    "MCParticle:MCParticle",
]


from Configurables import llHAna
llHAna = llHAna("llHAna")

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EvtSel = 'NONE',
                EvtMax = 10,
                ExtSvc = [dsvc],
                OutputLevel=DEBUG
)

