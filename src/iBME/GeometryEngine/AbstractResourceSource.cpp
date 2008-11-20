///////////////////////////////////////////////////////////
//  AbstractResourceSource.cpp
//  Implementation of the Class AbstractResourceSource
//  Created on:      20-Nov-2008 12:36:09 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "AbstractResourceSource.h"


AbstractResourceSource::AbstractResourceSource(){

}



AbstractResourceSource::~AbstractResourceSource(){

}





AbstractResource& AbstractResourceSource::getResourceByURL(URL url){

	return  NULL;
}


bool AbstractResourceSource::putResource(AbstractResource& res){

	return false;
}