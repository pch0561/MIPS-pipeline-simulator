#include <cassert>
#include "memaccess.h"
#include <cstdlib>
#include <iostream>

MemaccessStage::MemaccessStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == EX);
}

void MemaccessStage::process() {
	Instruction instr;
	instr = this->ins;
	if(!instr.isNop() && !this->isStalled()){
		if(instr.isMemory()){
			if(instr.isLoad()){
				instr.setLoadMemData(this->getData(instr.getAluOut()));
			} else if(instr.isStore()){
				this->setData(instr.getAluOut(), instr.getB());
				this->incStatistics((StatisticsType) 2);
			}
		} else if(instr.isBranch()){
			if(instr.getCond()){
				this->setPc(instr.getAluOut());
			}
			this->incStatistics((StatisticsType) 2);
		}

	}
	this->nextStage->setInstruction(instr);
}

MemaccessStage::~MemaccessStage() {
}
