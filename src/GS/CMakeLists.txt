MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring GeometryService         ##")
MESSAGE(STATUS "################################################\n")

set(GS_SOURCES
	AbstractDbObjectSource.cxx
	AbstractPortal.cxx
	DbObjectCache.cxx
	SourceDiskLink.cxx
	SourceSvnLink.cxx
	DbObjectManager.cxx
	DbObjectManifest.cxx
	CommunicationsManager.cxx
	IntraAppPortal.cxx
	Session.cxx
	AccessManager.cxx
	GeometryService.cxx
	NetSockPortal.cxx
	SessionManager.cxx
	NetMsgActionDefinitions/AbstractNetMsgActionDef.cxx
	NetMsgActionDefinitions/NetMsgActionDefManager.cxx
	NetMsgActionDefinitions/NewSessionNMAD.cxx
	Jobs/AbstractJob.cxx
	Jobs/CopyCacheToSvnJob.cxx
	Jobs/JobScheduler.cxx
	Jobs/NewSessionJob.cxx
	Jobs/CopyCacheToDiskJob.cxx
	Jobs/JobManager.cxx
	Jobs/JobWorker.cxx
	Jobs/NetMsgActionJob.cxx
	netMsg/GeometryManifestMsg.cxx
	netMsg/GeometryChunkMsg.cxx
	netMsg/GeometryReqMsg.cxx
	netMsg/NetMsg.cxx
	netMsg/RemHostNameSetFailMsg.cxx
	netMsg/RemHostNameSetMsg.cxx
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_LIBRARY (gs SHARED ${GS_SOURCES})
