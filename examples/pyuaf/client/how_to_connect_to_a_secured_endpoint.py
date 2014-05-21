import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings, SessionSecuritySettings
from pyuaf.util             import Address, NodeId
from pyuaf.util.errors      import UafError, ConnectionError


DISCOVERY_URL = "opc.tcp://localhost:48010"
SERVER_URI   = "urn:UnifiedAutomation:UaServerCpp"




# define the ClientSettings (note that we do NOT provide a discoveryUrl!!!):
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.logToStdOutLevel = pyuaf.util.loglevels.Debug
settings.discoveryUrls.append(DISCOVERY_URL)

settings.clientCertificateAbsoluteFileName = "dsds"

# create the client
myClient = Client(settings)


sess = SessionSettings()

secu = SessionSecuritySettings()
secu.securityPolicy      = pyuaf.util.securitypolicies.UA_Basic128Rsa15
secu.messageSecurityMode = pyuaf.util.messagesecuritymodes.Mode_Sign



sess.securitySettingsList[0] = secu


id = myClient.manuallyConnect(SERVER_URI, sess)
info = myClient.sessionInformation(id)
print myClient.sessionInformation(id)

print myClient.serversFound()

assert info.sessionState == pyuaf.client.sessionstates.Connected
print myClient.sessionInformation(id).sessionState == pyuaf.client.sessionstates.Disconnected

#someAddress = Address(NodeId("Demo.SimulationSpeed",                         # NodeId identifier
#                             "http://www.unifiedautomation.com/DemoServer"), # NodeId namespace URI
#                      "urn:UnifiedAutomation:UaServerCpp")                   # server URI
#
#result = myClient.read( [someAddress] )
#
#print result