#include "VExprBlockingAssignment.h"
#include "Indent.h"

VExprBlockingAssignmentHandle vexpr_blocking_assignment_mk(VExprRegLvalueHandle pRegLvalue, VExprExpressionHandle pExpr) {
    return VExprBlockingAssignmentHandle(VExprBlockingAssignment(pRegLvalue, pExpr));
}

VExprBlockingAssignment::VExprBlockingAssignment(VExprRegLvalueHandle pRegLvalue, VExprExpressionHandle pExpr)
  : _pRegLvalue(pRegLvalue)
  , _pExpr(pExpr)
  { }

VExprRegLvalueHandle VExprBlockingAssignment::getRegLvalueHandle() const
  { return _pRegLvalue; }

VExprExpressionHandle VExprBlockingAssignment::getExpressionHandle() const
  { return _pExpr; }

std::string VExprBlockingAssignment::getString() const {
    return getString(0);
}

std::string VExprBlockingAssignment::getString(unsigned int indentLevel) const {
    return indent(indentLevel) + getRegLvalueHandle()->getString()
         + " = "
         + getExpressionHandle()->getString();
}