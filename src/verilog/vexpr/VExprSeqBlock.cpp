#include "VExprSeqBlock.h"
#include "Indent.h"
#include "nstl/for_each/ForEach.h"

VExprSeqBlockHandle vexpr_seq_block_mk() {
    return VExprSeqBlockHandle(VExprSeqBlock());
}

VExprSeqBlockHandle vexpr_seq_block_mk(VExprStatementHandle pStatement) {
    return VExprSeqBlockHandle(VExprSeqBlock(pStatement));
}

VExprSeqBlock::VExprSeqBlock() { }
    
VExprSeqBlock::VExprSeqBlock(const std::vector<VExprStatementHandle> vecStatement)
  : _vecStatement(vecStatement)
  { }

VExprSeqBlock::VExprSeqBlock(VExprStatementHandle pStatement) {
    push_back(pStatement);
}
    
void VExprSeqBlock::push_back(VExprStatementHandle pStatement) {
    _vecStatement.push_back(pStatement);
}

unsigned int VExprSeqBlock::getStatementHandleSize() const
  { return _vecStatement.size(); }
    
VExprStatementHandle VExprSeqBlock::getStatementHandle(unsigned int pos) const
  { return _vecStatement[pos]; }
    
std::vector<VExprStatementHandle>& VExprSeqBlock::getStatementContainer()
  { return _vecStatement; }

const std::vector<VExprStatementHandle>& VExprSeqBlock::getStatementContainer() const
  { return _vecStatement; }

std::string VExprSeqBlock::getString() const
  { return getString(0); }
    
std::string VExprSeqBlock::getString(unsigned int indentLevel) const {
    std::string s = indent(indentLevel) + "begin\n";
    for (unsigned int i = 0; i < getStatementHandleSize(); ++i)
        s = s + getStatementHandle(i)->getString(indentLevel+1);
    s = s + indent(indentLevel) + "end\n";
    return s;
}
    
VExprSeqBlockHandle VExprSeqBlock::flatten(VExprIdentifierHandle pInstName) const {
    std::vector<VExprStatementHandle> vecFlatStatement;

    CONST_FOR_EACH(pStatement, getStatementContainer()) {
        vecFlatStatement.push_back(pStatement->flatten(pInstName));
    }

    return VExprSeqBlockHandle(VExprSeqBlock(vecFlatStatement));
}
    
VExprSeqBlockHandle VExprSeqBlock::substitute(VExprExpressionHandle pDst, const HashTable<VExprExpressionHandle> & hashSrc) const {
    std::vector<VExprStatementHandle> vecNewStatement;

    CONST_FOR_EACH(pStatement, getStatementContainer()) {
        vecNewStatement.push_back(pStatement->substitute(pDst, hashSrc));
    }

    return VExprSeqBlockHandle(VExprSeqBlock(vecNewStatement));
}
