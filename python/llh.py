#!/usr/bin/env python

processname = '/cms/user/zhangcg/cepc/CEPCSW/Analysis/llHAna/E240.Pe2e2h_X.e0.p0.whizard195'


from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")

import json
inputs = json.load(open(processname+".json")) 
lcioinput.inputs = inputs
lcioinput.collections = [ 
    "MCParticle:MCParticle",
    "ReconstructedParticle:ArborPFOs",
]


from Configurables import llHAna
llHAna = llHAna("llHAna")
llHAna.OutputFileName = processname + ".root"

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EvtSel = 'NONE',
                EvtMax = 10,
                ExtSvc = [dsvc],
                OutputLevel=INFO #DEBUG
)

