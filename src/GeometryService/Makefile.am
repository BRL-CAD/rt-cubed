bin_PROGRAMS = geoservice netMsgSerialTest

geoservice_SOURCES = \
	AbstractPortal.cxx \
	CommunicationsManager.cxx \
	IntraAppPortal.cxx \
	NetMsg.cxx \
	Session.cxx \
	AccessManager.cxx \
	GeometryService.cxx \
 	NetSockPortal.cxx \
	SessionManager.cxx \
	NetMsgActionDefinitions/AbstractNetMsgActionDef.cxx \
	NetMsgActionDefinitions/NetMsgActionDefManager.cxx \
	NetMsgActionDefinitions/NewSessionNMAD.cxx \
	Jobs/AbstractJob.cxx  \
	Jobs/CopyCacheToSvnJob.cxx  \
	Jobs/JobScheduler.cxx  \
	Jobs/NewSessionJob.cxx \
	Jobs/CopyCacheToDiskJob.cxx \
	Jobs/JobManager.cxx \
	Jobs/JobWorker.cxx \
	Jobs/NetMsgActionJob.cxx

geoservice_LDADD = \
	../GeometryEngine/libge.la


netMsgSerialTest_SOURCES = \
	NetMsg.cxx \
	../io/netMsgSerialTest.cxx

netMsgSerialTest_LDADD = \
	../GeometryEngine/libge.la
