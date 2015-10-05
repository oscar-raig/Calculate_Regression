#include "DeletePointCommand.hpp"
#include <cstddef>
#include <stdexcept> 



void DeletePointCommand::setParameters(GraphXY* graphXY,bool removeEnd){
	this->graphXY = graphXY;
	this->removeEnd = removeEnd;
}

DeletePointCommand::DeletePointCommand(GraphXY* graphXY,bool removeEnd ) {
	this->graphXY = graphXY;
	this->removeEnd = removeEnd;
	logger = Logger::getInstance(LOG4CPLUS_TEXT("UtilVector"));
}


GraphXY* DeletePointCommand::execute() {

	if( graphXY->getSize() == 0) {
		throw std::runtime_error( "ERROR: graph is empty" );
	}
	GraphXYIterator *iterator = graphXY->createIterator(0);

	if (removeEnd) {
			LOG4CPLUS_DEBUG(logger,"DeletePointCommand::execute going to end");
			iterator->end();
	}
	PointXY *pointXY = iterator->current();
	if ( pointXY == NULL) {
		throw std::runtime_error( "ERROR: Getting point" );
	}
	LOG4CPLUS_DEBUG(logger,"DeletePointCommand::execute " << pointXY->getX());
	pointStack.push(*pointXY);
	graphXY->erase(iterator);
	delete iterator;
	return graphXY;
}

GraphXY* DeletePointCommand::undo(int numberElementsToRecover) {

	if( pointStack.empty()) {
		throw std::runtime_error( "ERROR: trying to undo an empty stack" );
	}

	int cnt = 0;
	while( !pointStack.empty() && cnt < numberElementsToRecover) {
		PointXY pointXY = pointStack.top();
		pointStack.pop();
		if (removeEnd) {
			graphXY->addPoint(&pointXY);
		} else {
			graphXY->addPoint(&pointXY,0);
		}	
		cnt++;
	}	
	return graphXY;
}


