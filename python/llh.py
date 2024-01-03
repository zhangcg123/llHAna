from Gaudi.Configuration import *

from Configurables import k4DataSvc
dsvc = k4DataSvc("EventDataSvc")

from Configurables import LCIOInput
lcioinput = LCIOInput("lcioinput")
lcioinput.inputs = ["/cefs/data/FullSim/CEPC240/CEPC_v4/higgs/smart_final_states/E240.Pffh_invi.e0.p0.whizard195/ffh_inv.e0.p0.00001_1000_sim.slcio"]

lcioinput.collections = [
    "MCParticle:MCParticle",
    "SimCalorimeterHit:ECALBarrel",
]

from Configurables import llHAna
llHAna = llHAna("llHAna")

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [lcioinput, llHAna],
                EvtMax = 10,
                ExtSvc = [dsvc],
                OutputLevel=DEBUG
)

