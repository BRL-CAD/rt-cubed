lib_LTLIBRARIES = libgs.la

libgs_la_SOURCES = \
	AbstractPortal.cxx \
	CommunicationsManager.cxx \
	IntraAppPortal.cxx \
	NetMsg.cxx \
	RemHostNameSetMsg.cxx \
	RemHostNameSetFailMsg.cxx \
	GeometryReqMsg.cxx \
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


