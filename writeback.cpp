#include <cassert>
#include "writeback.h"
#include <cstdlib>
#include <iostream>

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {
	Instruction instr;
	instr = this->ins;
	if(!instr.isNop() && !this->isStalled()){
		if(instr.isAluReg()){
			this->setReg(instr.getArg1(), instr.getAluOut());
			this->incStatistics((StatisticsType) 2);
		} else if(instr.isAluImm()){
			this->setReg(instr.getArg1(), instr.getAluOut());
			this->incStatistics((StatisticsType) 2);
		} else if(instr.isLoad()){
			this->setReg(instr.getArg1(), instr.getLoadMemData());
			this->incStatistics((StatisticsType) 2);
		} else if(instr.isHlt()){
			this->incStatistics((StatisticsType) 2);
			this->stopSimulation();
		}
	}
}

WritebackStage::~WritebackStage() {
}
