#include "protocol/past/CAstParser.h"
#include "PExpr.h"
#include "ConvertCAst2PExpr.h"
#include "test/UnitTest.h"

void test_convert_constant() {
    CAstConstantParser parser;
    CAstConstantHandle pCAstConstant = parser.parseString("(constant (integer_literal 0))");

    PExprConstantHandle pConstant = ConvertCAst2PExpr::convert(pCAstConstant);
    assertEqual("(constant 0)", pConstant->toString(), "Test convert constant integer literal");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();

    pCAstConstant = parser.parseString("(constant (floating_literal 0.1))");

    pConstant = ConvertCAst2PExpr::convert(pCAstConstant);
    assertEqual("(constant 0.1)", pConstant->toString(), "Test convert constant floating literal");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();

    pCAstConstant = parser.parseString("(constant (bit_literal 2'b11))");

    pConstant = ConvertCAst2PExpr::convert(pCAstConstant);
    assertEqual("(constant 2'b11)", pConstant->toString(), "Test convert constant bit literal");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_assert_statement() {
    CAstAssertStatementParser parser;
    CAstAssertStatementHandle pCAstAssertStatement = parser.parseString("(assert_statement assert ( (integer_literal 0) ) ;)");

    PExprAssertStatementHandle pAssertStatement = ConvertCAst2PExpr::convert(pCAstAssertStatement);
    assertEqual("(assert_statement 0)", pAssertStatement->toString(), "Test convert assert statement");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_read_statement() {
    CAstReadStatementParser parser;
    CAstReadStatementHandle pCAstReadStatement = parser.parseString("(read_statement read ( (identifier yuv_in) ) ;)");

    PExprReadStatementHandle pReadStatement = ConvertCAst2PExpr::convert(pCAstReadStatement);
    assertEqual("(read_statement yuv_in)", pReadStatement->toString(), "Test convert read statement");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_write_statement() {
    CAstWriteStatementParser parser;
    CAstWriteStatementHandle pCAstWriteStatement = parser.parseString("(write_statement write ( (identifier rgb_out) ) ;)");

    PExprWriteStatementHandle pWriteStatement = ConvertCAst2PExpr::convert(pCAstWriteStatement);
    assertEqual("(write_statement rgb_out)", pWriteStatement->toString(), "Test convert write statement");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_state_label() {
    CAstStateLabelParser parser;
    CAstStateLabelHandle pCAstStateLabel = parser.parseString("(state_label (identifier s0) :)");

    PExprStateLabelHandle pStateLabel = ConvertCAst2PExpr::convert(pCAstStateLabel);
    assertEqual("(state_label s0)", pStateLabel->toString(), "Test convert state label");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_goto_statement() {
    CAstGotoStatementParser parser;
    CAstGotoStatementHandle pCAstGotoStatement = parser.parseString("(goto_statement goto  (identifier s1) ;)");

    PExprGotoStatementHandle pGotoStatement = ConvertCAst2PExpr::convert(pCAstGotoStatement);
    assertEqual("(goto_statement s1)", pGotoStatement->toString(), "Test goto statement");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_bool_expression() {
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression (identifier reset))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression reset)", pBoolExpression->toString(), "Test bool expression identifier");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression (identifier a) = (constant (integer_literal 0)))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression a == (constant 0))", pBoolExpression->toString(), "Test bool expression constant");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression ! (bool_expression (identifier a)))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression ! (bool_expression a))", pBoolExpression->toString(), "Test bool expression logical not");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression (bool_expression (identifier a)) ^ (bool_expression (identifier b)))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression (bool_expression a) ^ (bool_expression b))", pBoolExpression->toString(), "Test bool expression logical xor");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression (bool_expression (identifier a)) | | (bool_expression (identifier b)))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression (bool_expression a) || (bool_expression b))", pBoolExpression->toString(), "Test bool expression logical or");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstBoolExpressionParser parser;
        CAstBoolExpressionHandle pCAstBoolExpression = parser.parseString("(bool_expression (bool_expression (identifier a)) & & (bool_expression (identifier b)))");

        PExprBoolExpressionHandle pBoolExpression = ConvertCAst2PExpr::convert(pCAstBoolExpression);
        assertEqual("(bool_expression (bool_expression a) && (bool_expression b))", pBoolExpression->toString(), "Test bool expression logical and");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
}

void test_convert_check_statement(){
    CAstCheckStatementParser parser;
    CAstCheckStatementHandle pCAstCheckStatement = parser.parseString("(check_statement check  ( (bool_expression ! (bool_expression (identifier in_en))) ) ;)");

    PExprCheckStatementHandle pCheckStatement = ConvertCAst2PExpr::convert(pCAstCheckStatement);
    assertEqual("(check_statement (bool_expression ! (bool_expression in_en)))", pCheckStatement->toString(), "Test convert check statement");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_read_or_write_or_check_statement(){
    {
        CAstReadOrWriteOrCheckStatementParser parser;
        CAstReadOrWriteOrCheckStatementHandle pCAstReadOrWriteOrCheckStatement = parser.parseString("(read_or_write_or_check_statement (read_statement read  ( (identifier Din) ) ;))");

        PExprReadOrWriteOrCheckStatementHandle pReadOrWriteOrCheckStatement = ConvertCAst2PExpr::convert(pCAstReadOrWriteOrCheckStatement);
        assertEqual("(read_or_write_or_check_statement (read_statement Din))", pReadOrWriteOrCheckStatement->toString(), "Test convert read or write or chck statement");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstReadOrWriteOrCheckStatementParser parser;
        CAstReadOrWriteOrCheckStatementHandle pCAstReadOrWriteOrCheckStatement = parser.parseString("(read_or_write_or_check_statement (write_statement write  ( (identifier Dout) ) ;))");

        PExprReadOrWriteOrCheckStatementHandle pReadOrWriteOrCheckStatement = ConvertCAst2PExpr::convert(pCAstReadOrWriteOrCheckStatement);
        assertEqual("(read_or_write_or_check_statement (write_statement Dout))", pReadOrWriteOrCheckStatement->toString(), "Test convert read or write or chck statement");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
    {
        CAstReadOrWriteOrCheckStatementParser parser;
        CAstReadOrWriteOrCheckStatementHandle pCAstReadOrWriteOrCheckStatement = parser.parseString("(read_or_write_or_check_statement (check_statement check  ( (bool_expression ! (bool_expression (identifier in_en))) ) ;))");

        PExprReadOrWriteOrCheckStatementHandle pReadOrWriteOrCheckStatement = ConvertCAst2PExpr::convert(pCAstReadOrWriteOrCheckStatement);
        assertEqual("(read_or_write_or_check_statement (check_statement (bool_expression ! (bool_expression in_en))))", pReadOrWriteOrCheckStatement->toString(), "Test convert read or write or chck statement");
        UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
    }
}

void test_convert_if_statement_prefix(){
    CAstIfStatementPrefixParser parser;
    CAstIfStatementPrefixHandle pCAstIfStatementPrefix = parser.parseString("(if_statement_prefix if ( (bool_expression (identifier reset)) ))");

    PExprIfStatementPrefixHandle pIfStatementPrefix = ConvertCAst2PExpr::convert(pCAstIfStatementPrefix);
    assertEqual("(if_statement_prefix (bool_expression reset))", pIfStatementPrefix->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_end_statement(){
    CAstEndStatementParser parser;
    CAstEndStatementHandle pCAstEndStatement = parser.parseString("(end_statement (goto_statement goto  (identifier s1) ;))");

    PExprEndStatementHandle pEndStatement = ConvertCAst2PExpr::convert(pCAstEndStatement);
    assertEqual("(end_statement (goto_statement s1))", pEndStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_if_statement_without_goto(){
    CAstIfStatementWithoutGotoParser parser;
    CAstIfStatementWithoutGotoHandle pCAstIfStatementWithoutGoto = parser.parseString("(if_statement_without_goto (if_statement_prefix if ( (bool_expression (identifier y_valid)) )) (read_or_write_or_check_statement (write_statement write ( (identifier y) ) ;)))");

    PExprIfStatementWithoutGotoHandle pIfStatementWithoutGoto = ConvertCAst2PExpr::convert(pCAstIfStatementWithoutGoto);
    assertEqual("(if_statement_without_goto (if_statement_prefix (bool_expression y_valid)) (read_or_write_or_check_statement (write_statement y)))", pIfStatementWithoutGoto->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_if_statement_with_goto(){
    CAstIfStatementWithGotoParser parser;
    CAstIfStatementWithGotoHandle pCAstIfStatementWithGoto = parser.parseString("(if_statement_with_goto (if_statement_prefix if  ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))");

    PExprIfStatementWithGotoHandle pIfStatementWithGoto = ConvertCAst2PExpr::convert(pCAstIfStatementWithGoto);
    assertEqual("(if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))", pIfStatementWithGoto->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_specific(){
    CAstSpecificUpdateStatementParser parser;
    CAstSpecificUpdateStatementHandle pCAstSpecific = parser.parseString("(specific_update_statement (if_statement_without_goto (if_statement_prefix if ( (bool_expression (identifier y_valid)) )) (read_or_write_or_check_statement (write_statement write ( (identifier y) ) ;))))");

    PExprSpecificUpdateStatementHandle pSpecificUpdateStatement = ConvertCAst2PExpr::convert(pCAstSpecific);
    assertEqual("(specific_update_statement (if_statement_without_goto (if_statement_prefix (bool_expression y_valid)) (read_or_write_or_check_statement (write_statement y))))", pSpecificUpdateStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_all(){
    CAstAllUpdateStatementParser parser;
    CAstAllUpdateStatementHandle pCAstAll = parser.parseString("(all_update_statement (if_statement_without_goto (if_statement_prefix if ( (bool_expression (identifier y_valid)) )) (read_or_write_or_check_statement (write_statement write ( (identifier y) ) ;))))");

    PExprAllUpdateStatementHandle pAllUpdateStatement = ConvertCAst2PExpr::convert(pCAstAll);
    assertEqual("(all_update_statement (if_statement_without_goto (if_statement_prefix (bool_expression y_valid)) (read_or_write_or_check_statement (write_statement y))))", pAllUpdateStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_edge_statement(){
    CAstEdgeStatementParser parser;
    CAstEdgeStatementHandle pCAstEdgeStatement = parser.parseString("(edge_statement (if_statement_with_goto (if_statement_prefix if  ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;))))");

    PExprEdgeStatementHandle pEdgeStatement = ConvertCAst2PExpr::convert(pCAstEdgeStatement);
    assertEqual("(edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1))))", pEdgeStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_transition_statement(){
    CAstTransitionStatementParser parser;
    CAstTransitionStatementHandle pCAstTransitionStatement = parser.parseString("(transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix if ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))) (edge_statement (end_statement (goto_statement goto  (identifier s2) ;))))");

    PExprTransitionStatementHandle pTransitionStatement = ConvertCAst2PExpr::convert(pCAstTransitionStatement);
    assertEqual("(transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))) (edge_statement (end_statement (goto_statement s2))))", pTransitionStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_state_statement(){
    CAstStateStatementParser parser;
    CAstStateStatementHandle pCAstStateStatement = parser.parseString("(state_statement (state_label (identifier s1) :) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix if ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))) (edge_statement (end_statement (goto_statement goto  (identifier s2) ;)))))");

    PExprStateStatementHandle pStateStatement = ConvertCAst2PExpr::convert(pCAstStateStatement);
    assertEqual("(state_statement (state_label s1) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))) (edge_statement (end_statement (goto_statement s2)))))", pStateStatement->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

void test_convert_source_text(){
    CAstSourceTextParser parser;
    CAstSourceTextHandle pCAstSourceText = parser.parseString("(source_text (state_statement (state_label (identifier s0) :) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix if  ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))) (edge_statement (end_statement (goto_statement goto  (identifier s0) ;))))) (state_statement (state_label (identifier s1) :) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix if ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))) (edge_statement (end_statement (goto_statement goto  (identifier s2) ;))))) (state_statement (state_label (identifier s2) :) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix if ( (bool_expression (identifier reset)) )) (end_statement (goto_statement goto  (identifier s1) ;)))) (edge_statement (specific_update_statement (if_statement_without_goto (if_statement_prefix if ( (bool_expression (identifier y_valid)) )) (read_or_write_or_check_statement (write_statement write ( (identifier y) ) ;)))) (specific_update_statement (if_statement_without_goto (if_statement_prefix if ( (bool_expression (identifier z_valid)) )) (read_or_write_or_check_statement (write_statement write ( (identifier z) ) ;)))) (end_statement (goto_statement goto  (identifier s2) ;))))))");

    PExprSourceTextHandle pSourceText = ConvertCAst2PExpr::convert(pCAstSourceText);
    assertEqual("(source_text (state_statement (state_label s0) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))) (edge_statement (end_statement (goto_statement s0))))) (state_statement (state_label s1) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))) (edge_statement (end_statement (goto_statement s2))))) (state_statement (state_label s2) (transition_statement (edge_statement (if_statement_with_goto (if_statement_prefix (bool_expression reset)) (end_statement (goto_statement s1)))) (edge_statement (specific_update_statement (if_statement_without_goto (if_statement_prefix (bool_expression y_valid)) (read_or_write_or_check_statement (write_statement y)))) (specific_update_statement (if_statement_without_goto (if_statement_prefix (bool_expression z_valid)) (read_or_write_or_check_statement (write_statement z)))) (end_statement (goto_statement s2))))))", pSourceText->toString(), "test");
    UNIT_TEST_FUNCTION_END_FUNCTION_TEST();
}

int main() {
    test_convert_constant();
    test_convert_assert_statement();
    test_convert_read_statement();
    test_convert_write_statement();
    test_convert_state_label();
    test_convert_goto_statement();
    test_convert_bool_expression();
    test_convert_check_statement();
    test_convert_read_or_write_or_check_statement();
    test_convert_if_statement_prefix();
    test_convert_end_statement();
    test_convert_if_statement_without_goto();
    test_convert_if_statement_with_goto();
    test_convert_specific();
    test_convert_all();
    test_convert_edge_statement();
    test_convert_transition_statement();
    test_convert_state_statement();
    test_convert_source_text();

    return 0;
}
