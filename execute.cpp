#include <cassert>
#include "execute.h"
#include <cstdlib>
#include <iostream>

ExecuteStage::ExecuteStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == ID);
}

void ExecuteStage::process() {
	Instruction instr;
	instr = this->ins;
	if(!instr.isNop() && !this->isStalled()){
		switch (instr.getType()){
		case 1: // ADD
			instr.setAluOut((instr.getA() + instr.getB()));
			break;
		case 2: // SUB
			instr.setAluOut((instr.getA() - instr.getB()));
			break;
		case 3: // MUL
			instr.setAluOut((instr.getA() * instr.getB()));
			break;
		case 4: // DIV
			if(instr.getB() != 0)
				instr.setAluOut((instr.getA() / instr.getB()));
			break;
		case 5: // XOR
			instr.setAluOut((instr.getA() ^ instr.getB()));
			break;
		case 6: // AND
			instr.setAluOut((instr.getA() & instr.getB()));
			break;
		case 7: // OR
			instr.setAluOut((instr.getA() | instr.getB()));
			break;
		case 8: // ADDI
			instr.setAluOut((instr.getA() + instr.getImmidiate()));
			break;
		case 9: // SUBI
			instr.setAluOut((instr.getA() - instr.getImmidiate()));
			break;
		case 10: // LD
			instr.setAluOut((instr.getA() + instr.getImmidiate()));
			break;
		case 11: // ST
			instr.setAluOut((instr.getA() + instr.getImmidiate()));
			break;
		case 12: // BEQZ
			instr.setAluOut((this->getPc() + (instr.getImmidiate()<<2)));
			instr.setCond(instr.getA() == 0);
			break;
		case 13: // BNEQZ
			instr.setAluOut((this->getPc() + (instr.getImmidiate()<<2)));
			instr.setCond(instr.getA() != 0);
			break;
		default:
			break;
		}
	}
	this->nextStage->setInstruction(instr);
}

ExecuteStage::~ExecuteStage() {
}
