#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
  // process for this step
  if(getPc()/4 < getInstrCount()){
	  Instruction instr;
	  instr = this->getNextIns();
	  this->nextStage->setInstruction(instr);
	  this->incStatistics((StatisticsType) 1);
	  setPc(this->getPc()+4);
  } else {
	  Instruction instr;
	  instr = this->ins;
	  this->nextStage->setInstruction(instr);
  }
}

FetchStage::~FetchStage() {
}
