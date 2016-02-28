#include <cassert>
#include "decode.h"
#include <cstdlib>
#include <iostream>

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {
	if(resolveDependence(this->ins)){
		this->setStalled();
	} else {
		this->setUnstalled();
	}
	if(this->isStalled()){
		this->incStatistics((StatisticsType) 0);
	}

	Instruction instr;
	instr = this->ins;
	if(!instr.isNop() && !this->isStalled()){
		if(instr.isAluReg()){
			instr.setA(this->getReg(instr.getArg2()));
			instr.setB(this->getReg(instr.getArg3()));
		} else if(instr.isAluImm()){
			instr.setA(this->getReg(instr.getArg2()));
			instr.setB(this->getReg(instr.getArg1()));
		} else if(instr.isMemory()){
			instr.setA(this->getReg(instr.getArg2()));
			instr.setB(this->getReg(instr.getArg1()));
		} else if(instr.isBranch()){
			instr.setA(this->getReg(instr.getArg1()));
		} else if(instr.isHlt()){
		}
	}
	this->nextStage->setInstruction(instr);
}

DecodeStage::~DecodeStage() {
}
