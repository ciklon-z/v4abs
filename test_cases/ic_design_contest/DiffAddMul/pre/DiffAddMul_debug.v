
// SUB MODULE ===============================
module sub(pclP, pclN1, pclN2, selN);

input [24:0] pclP; // [24:17] is i, [16:9] is j, [8:1] is k, [0] is operation.

output [16:0] pclN1; // [16:9] is i, [8:1] is j, [0] is operation.
output [15:0] pclN2; // [15:8] is i, [7:0] is j
output  [2:0] selN;

wire [16:0] pclN1;
wire [15:0] pclN2;
wire  [8:0] diff;
wire  [2:0] selN;

assign diff  = {1'b0, pclP[24:17]} - {1'b0, pclP[16:9]};
assign pclN1 = {diff[7:0], pclP[8:0]};
assign pclN2 = {diff[7:0], pclP[8:1]};
assign selN  = (diff[8])? 3'b001 : ((pclP[0])? 3'b010 : 3'b100);

endmodule

// NEG MODULE ===============================
module neg(pclP, pclN, selN);

input [16:0] pclP;  // [16:9] is i, [8:1] is j, [0] is operation.

output [15:0] pclN; // [15:8] is i, [7:0] is j
output  [1:0] selN;

wire [15:0] pclN;
wire  [1:0] selN;
wire  [7:0] abs;

assign abs = 8'b0 - pclP[16:9];
assign pclN = {abs, pclP[8:1]};
assign selN = (pclP[16])? ((pclP[0])? 2'b01 : 2'b10) : 2'b0;

endmodule

// MUL MODULE ===============================
module mul(pclP1, pclP2, stateIn, stateOut, pclN1, pclN2, done);

input [15:0] pclP1;
input  [7:0] pclP2;
input  [2:0] stateIn;

output [2:0] stateOut;
output [7:0] pclN1;
output [7:0] pclN2;
output       done;

reg  [2:0] stateOut;
reg  [7:0] pclN1;
reg  [7:0] pclN2;
reg        done;

wire [3:0] a;
wire [3:0] b;
wire [3:0] c;
wire [3:0] d;
wire [7:0] a_mult_d;
wire [7:0] a_mult_c;
wire [7:0] b_mult_c;
wire [7:0] a_mult_d_high;
wire [7:0] b_mult_c_high;

assign a = pclP1[11: 8];
assign b = pclP1[15:12];
assign c = pclP1[ 3: 0];
assign d = pclP1[ 7: 4];

assign a_mult_d = a * d; // error, should extend
assign a_mult_c = a * c; // error, should extend
assign b_mult_c = b * c; // error, should extend
assign a_mult_d_high = {a_mult_d[3:0], 4'b0};
assign b_mult_c_high = {b_mult_c[3:0], 4'b0};

always @ (*) begin
    case (stateIn) 
        3'b000 : stateOut = (a == 4'h0) ? 3'b001 : 3'b010;
        3'b001 : stateOut = (b == 4'h0) ? 3'b111 : 3'b111;
        3'b010 : stateOut = (b == 4'h0) ? 3'b011 : 3'b100;
        3'b011 : stateOut = 3'b111;
        3'b100 : stateOut = (d == 4'h0) ? 3'b111 : 3'b110;
        3'b110 : stateOut = 3'b111;
        3'b111 : stateOut = 3'b000;
        default: stateOut = 3'b111;
    endcase
end

always @ (*) begin
    case (stateIn) 
        3'b111 : pclN1 = pclP2;
        default: pclN1 = 8'h0;
    endcase
end

always @ (*) begin
    case (stateIn)
        3'b000 : pclN2 = (a == 4'h0) ? b_mult_c      : a_mult_c;
        3'b001 : pclN2 = (b == 4'h0) ? 8'h0          : pclP2;
        3'b010 : pclN2 =((b == 4'h0) ? a_mult_d_high : b_mult_c_high) + pclP2;
        3'b011 : pclN2 = pclP2;
        3'b100 : pclN2 =((d == 4'h0) ? 8'h0          : a_mult_d_high) + pclP2;
        3'b110 : pclN2 = pclP2;
        default: pclN2 = 8'h0;
    endcase
end

always @ (*) begin
    case (stateIn) 
        3'b111 : done = 1'b1;
        default: done = 1'b0;
    endcase
end

endmodule

// ADD MODULE ===============================
module add(pclP, pclN);

input [15:0] pclP; // [15:8] is i, [7:0] is j
output [7:0] pclN;

wire [7:0] pclN;
assign pclN = pclP[15:8] + pclP[7:0];

endmodule

// TOP MODULE ===============================
module top(clk, rst, i, j, k, operation, vo, in_valid, out_valid);

input        clk;
input        rst;
input  [7:0] i;
input  [7:0] j;
input  [7:0] k;
input        operation;
output [7:0] vo;
output       in_valid;  // Control the input 
output       out_valid; // Control the output

// register
reg  [24:0] next_rSub;
reg  [16:0] next_rNeg;
reg  [15:0] next_rAdd;
reg  [15:0] next_rMul1;
reg   [7:0] next_rMul2;
reg   [2:0] next_stateIn;

// This is for SUB
reg  [24:0] rSub;
wire [16:0] sub_out1; // [16:9] is i, [8:1] is j, [0] is operation.
wire [15:0] sub_out2; // [15:8] is i, [7:0] is j
wire  [2:0] sub_sel;

// This is for NEG
reg  [16:0] rNeg;     // [16:9] is i, [8:1] is j, [0] is operation.
wire [15:0] neg_out;  // [15:8] is i, [7:0] is j
wire  [1:0] neg_sel;

// This is for ADD
reg  [15:0] rAdd;     // [15:8] is i, [7:0] is j
wire  [7:0] out_Add;

// This is for MULT
reg  [15:0] rMul1;    // [15:8] is i, [7:0] is j
reg   [7:0] rMul2;
reg   [2:0] stateIn;
wire  [2:0] stateOut;
wire  [7:0] out_Mul;
wire  [7:0] mul_out2;
wire        done;

// This is for top design
reg         op_Add;
reg         op_Mul;
reg         next_op_Add;
reg         next_op_Mul;
wire        stall_Add;
wire        stall_Mul;
reg         in_valid;
wire        out_valid;

reg         c_done;
reg         next_c_done;

reg   [7:0] vo;

assign stall_Mul = (sub_sel == 3'b100 && neg_sel != 2'b0);
assign stall_Add = (sub_sel == 3'b010 && neg_sel != 2'b0);
assign out_valid = (op_Add && done && !c_done) || c_done;

// This is for modulo
sub sub_inst0(.pclP(rSub), .pclN1(sub_out1), .pclN2(sub_out2), .selN(sub_sel));
neg neg_inst1(.pclP(rNeg), .pclN(neg_out), .selN(neg_sel));
add add_inst2(.pclP(rAdd), .pclN(out_Add));
mul mul_inst2(.pclP1(rMul1), .pclP2(rMul2), .stateIn(stateIn), 
              .stateOut(stateOut), .pclN1(out_Mul), .pclN2(mul_out2), .done(done));

always @ (*) begin
    if (rst) begin
        next_op_Add  =  1'b0;
        next_op_Mul  =  1'b0;
        in_valid     =  1'b1;
        next_rSub    = 25'b1;
        next_rNeg    = 17'b0;
        next_rAdd    = 16'b0;
        next_rMul1   = 16'b0;
        next_rMul2   =  8'b0;
        next_stateIn =  3'b111;
        vo           =  8'h0;
        next_c_done  =  1'b0;
    end
    else begin
        next_op_Add  = (stall_Add)? neg_sel[0] : (sub_sel[1] || neg_sel[0]);
        next_op_Mul  = (stall_Mul)? neg_sel[1] : (sub_sel[2] || neg_sel[1]);
        in_valid     = (!done)?          1'b0  : (!stall_Mul && !stall_Add);

        next_rSub    = (!in_valid)?      rSub  : {i, j, k, operation};
        next_rNeg    = (!done)?          rNeg  : sub_out1;
        next_rAdd    = (!done)?          rAdd  :
                       (!next_op_Add)?   16'h0 : (neg_sel == 2'b0)? sub_out2 : neg_out;
        next_rMul1   = (!done)?          rMul1 : 
                       (!next_op_Mul)?   16'h0 : (neg_sel == 2'b0)? sub_out2 : neg_out;
        next_rMul2   = (done)?           rMul2 : mul_out2;
        next_stateIn = (done && !op_Mul && !next_op_Mul)? 3'b111 : stateOut;

        vo           = (c_done)?       out_Mul : ((op_Add && done && !c_done)? out_Add : 8'h0);
        next_c_done  = (stateOut == 3'b111)? 1'b1 : 1'b0;
    end
end

always @ (posedge clk) begin
    if (rst) begin
        rSub    <= 25'b1;
        rNeg    <= 17'b0;
        rAdd    <= 16'b0;
        rMul1   <= 16'b0;
        rMul2   <=  8'b0;
        stateIn <=  3'b111;
        op_Add  <=  1'b0;
        op_Mul  <=  1'b0;
        c_done  <=  1'b0;
    end
    else begin
        rSub    <= next_rSub;
        rNeg    <= next_rNeg;
        rAdd    <= next_rAdd;
        rMul1   <= next_rMul1;
        rMul2   <= next_rMul2;
        stateIn <= next_stateIn;
        op_Add  <= next_op_Add;
        op_Mul  <= next_op_Mul;
        c_done  <= next_c_done;
    end
end

endmodule
