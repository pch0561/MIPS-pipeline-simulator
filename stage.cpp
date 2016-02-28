#include <cassert>
#include "stage.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memaccess.h"
#include "writeback.h"

AbstractStage::getPcPtr AbstractStage::getPc = NULL;
AbstractStage::setPcPtr AbstractStage::setPc = NULL;
AbstractStage::getInstrCountPtr AbstractStage::getInstrCount = NULL;
AbstractStage::resolveDependencePtr AbstractStage::resolveDependence = NULL;
AbstractStage::setInstrCountPtr AbstractStage::setInstrCount = NULL;
AbstractStage::getNextInsPtr AbstractStage::getNextIns = NULL;
AbstractStage::getCurrentInsPtr AbstractStage::getCurrentIns = NULL;
AbstractStage::getRegPtr AbstractStage::getReg = NULL;
AbstractStage::setRegPtr AbstractStage::setReg = NULL;
AbstractStage::getDataPtr AbstractStage::getData = NULL;
AbstractStage::setDataPtr AbstractStage::setData = NULL;
AbstractStage::setStopSimulationPtr AbstractStage::stopSimulation = NULL;
AbstractStage::getCyclePtr AbstractStage::getCycle = NULL;
AbstractStage::incStatisticsPtr AbstractStage::incStatistics = NULL;


AbstractStage::AbstractStage(StageType _type, AbstractStage *_prevStage) : stalled(false), type(_type), 
                                                                         prevStage(_prevStage) {
  if (prevStage != NULL)
    prevStage->nextStage = this;
  nextStage = NULL;
}

AbstractStage* AbstractStage::createStage(StageType _type, AbstractStage *_prevStage) {
  // Create a new stage of type _type and set the previous stage to _prevStage
  // Return the newly created stage

	AbstractStage* temp;
	switch (_type) {
	case 0:
		temp = new FetchStage(_type, _prevStage);
		break;
	case 1:
		temp = new DecodeStage(_type, _prevStage);
		break;
	case 2:
		temp = new ExecuteStage(_type, _prevStage);
		break;
	case 3:
		temp = new MemaccessStage(_type, _prevStage);
		break;
	case 4:
		temp = new WritebackStage(_type, _prevStage);
		break;
	}
	return temp;
}

void AbstractStage::setStalled() {
  stalled = true; 
  if (prevStage)
    prevStage->setStalled();
}

void AbstractStage::setUnstalled() { 
  stalled = false; 
  if (prevStage)
    prevStage->setUnstalled();
}

void AbstractStage::updateDependences(int _srcCycle) {
  // This function is used to notify (and possibly unstall) the consumer instruction that was stalled
  // due to the current instruction (i.e., producer instruction) of this stage

}

void AbstractStage::setInstruction(Instruction& _ins) {
  ins = _ins;
}

Instruction& AbstractStage::getInstruction() {
  return ins;
}

AbstractStage::~AbstractStage() {
}
