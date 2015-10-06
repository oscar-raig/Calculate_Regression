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
	logger = Logger::getInstance(LOG4CPLUS_TEXT("DeletePointCommand"));
}

DeletePointCommand::~DeletePointCommand() {
	while (!pointStack.empty()){
     pointStack.pop();
  }
}


GraphXY* DeletePointCommand::execute() {
	

	if( graphXY->getSize() == 0) {
		throw std::runtime_error( "ERROR: graph is empty" );
	}
	GraphXYIterator *iterator = graphXY->createIterator(0);

	if (removeEnd) {
			iterator->end();
			iterator->previous();
	}
	PointXY *pointXY = iterator->current();
	if ( pointXY == NULL) {
		throw std::runtime_error( "ERROR: Getting point" );
	}
	//LOG4CPLUS_INFO(logger,"DeletePointCommand::execute " << pointXY->getX());
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


