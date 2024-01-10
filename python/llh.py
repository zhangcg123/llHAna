#!/usr/bin/env python

import os
#ithpart = os.environ['ITHPART']
processname = '/cms/user/zhangcg/cepc/CEPCSW/Analysis/llHAna/E240.Pe2e2h_X.e0.p0.whizard195'#_'+str(ithpart)


from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")

import json
inputs = json.load(open(processname+".json")) 

import math
chuck_size = math.ceil( len(inputs)/10 )
groups = [inputs[i:i+chuck_size] for i in range(0, len(inputs), chuck_size)]

ith = os.environ['ITH']
ith = int(ith)

lcioinput.inputs = groups[ith]
lcioinput.collections = [ 
    "MCParticle:MCParticle",
    "ReconstructedParticle:ArborPFOs",
]


from Configurables import llHAna
llHAna = llHAna("llHAna")
llHAna.OutputFileName = processname + "_" + str(ith) + ".root"

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EvtSel = 'NONE',
                EvtMax = -1,
                ExtSvc = [dsvc],
                OutputLevel=INFO #DEBUG
)
