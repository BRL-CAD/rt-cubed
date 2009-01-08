lib_LTLIBRARIES = libgs.la

libgs_la_SOURCES = \
	AbstractPortal.cxx \
	CommunicationsManager.cxx \
	IntraAppPortal.cxx \
	Session.cxx \
	AccessManager.cxx \
	GeometryService.cxx \
 	NetSockPortal.cxx \
	SessionManager.cxx \
	NetMsgActionDefinitions/AbstractNetMsgActionDef.cxx \
	NetMsgActionDefinitions/NetMsgActionDefManager.cxx \
	NetMsgActionDefinitions/NewSessionNMAD.cxx \
	Jobs/AbstractJob.cxx \
	Jobs/CopyCacheToSvnJob.cxx \
	Jobs/JobScheduler.cxx \
	Jobs/NewSessionJob.cxx \
	Jobs/CopyCacheToDiskJob.cxx \
	Jobs/JobManager.cxx \
	Jobs/JobWorker.cxx \
	Jobs/NetMsgActionJob.cxx \
	netMsg/GeometryManifestMsg.cxx \
	netMsg/GeometryReqMsg.cxx \
	netMsg/NetMsg.cxx \
	netMsg/RemHostNameSetFailMsg.cxx \
	netMsg/RemHostNameSetMsg.cxx


bin_PROGRAMS = netMsgSerialTest


#gsph0_SOURCES = \
#	gsph0.cxx
#
#gsph0_LDADD = \
#	../GeometryEngine/libge.la \
#	libgs.la



netMsgSerialTest_SOURCES = \
	../io/netMsgSerialTest.cxx

netMsgSerialTest_LDADD = \
	../GeometryEngine/libge.la \
	libgs.la


