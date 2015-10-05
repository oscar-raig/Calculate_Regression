#include <stack>
#include "PointXY.hpp"
#include "GraphXY.hpp"
class DeletePointCommand {

private:
	std::stack<PointXY> pointStack;
	bool removeEnd;
	GraphXY* graphXY;

public:
	DeletePointCommand(){};
	void setParameters(GraphXY* graphXY,bool removeEnd);
	DeletePointCommand(GraphXY* graphXY,bool removeEnd);
	GraphXY* execute();
	GraphXY* undo(int numberElementsToRecover);

};