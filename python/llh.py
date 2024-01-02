from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc", input="input.slcio")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")
lcioinput.inputs = ["input.slcio",
                    "input2.slcio",
                    "input3.slcio"]

lcioinput.collections = [
    "MCParticle:MCParticle",
    "SimCalorimeterHit:ECALBarrel",
]

from Configurables import llHAna
llHAna = llHAna("llHAna")

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EventSelector = "NONE",
                EvtMax = 10,
                ExtSvc = [dsvc],
                OutputLevel=DEBUG
)

