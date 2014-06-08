module CAL_Threshold(clk, CAL_reset, s_in, s_reset, o_out, o_threshold);
input        clk;
input        CAL_reset;
input  [7:0] s_in;
input        s_reset;
output       o_out;
output [7:0] o_threshold;

reg    [7:0] tmp_max;
reg    [7:0] tmp_min;
reg    [7:0] o_threshold;
reg          n_reset;
reg    [7:0] aA0,  aA1,  aA2,  aA3,  aA4,  aA5,  aA6,  aA7,  aA8,  aA9;
reg    [7:0] aA10, aA11, aA12, aA13, aA14, aA15, aA16, aA17, aA18, aA19;
reg    [7:0] aA20, aA21, aA22, aA23, aA24, aA25, aA26, aA27, aA28, aA29;
reg    [7:0] aA30, aA31, aA32, aA33, aA34, aA35, aA36, aA37, aA38, aA39;
reg    [7:0] aA40, aA41, aA42, aA43, aA44, aA45, aA46, aA47, aA48, aA49;
reg    [7:0] aA50, aA51, aA52, aA53, aA54, aA55, aA56, aA57, aA58, aA59;
reg    [7:0] aA60, aA61, aA62, aA63;
reg          o_out;
reg          o_reset;
reg    [7:0] next_o_threshold;
reg          next_o_reset;
reg    [7:0] next_tmp_max;
reg    [7:0] next_tmp_min;
reg    [7:0] next_threshold;
reg    [7:0] next_aA0,  next_aA1,  next_aA2,  next_aA3,  next_aA4,  next_aA5,  next_aA6,  next_aA7,  next_aA8,  next_aA9;
reg    [7:0] next_aA10, next_aA11, next_aA12, next_aA13, next_aA14, next_aA15, next_aA16, next_aA17, next_aA18, next_aA19;
reg    [7:0] next_aA20, next_aA21, next_aA22, next_aA23, next_aA24, next_aA25, next_aA26, next_aA27, next_aA28, next_aA29;
reg    [7:0] next_aA30, next_aA31, next_aA32, next_aA33, next_aA34, next_aA35, next_aA36, next_aA37, next_aA38, next_aA39;
reg    [7:0] next_aA40, next_aA41, next_aA42, next_aA43, next_aA44, next_aA45, next_aA46, next_aA47, next_aA48, next_aA49;
reg    [7:0] next_aA50, next_aA51, next_aA52, next_aA53, next_aA54, next_aA55, next_aA56, next_aA57, next_aA58, next_aA59;
reg    [7:0] next_aA60, next_aA61, next_aA62, next_aA63;
wire   [8:0] o_diff;
wire   [8:0] o_sum;
wire   [7:0] o_avg;

assign o_diff   = {1'b0, o_threshold} - {1'b0, aA63};
assign o_sum    = {1'b0, tmp_max} + {1'b0, tmp_min};
assign o_avg    = o_sum[8:1] + {7'b0, o_sum[0]};

always @ (*) begin
    if (CAL_reset) begin
        o_out        = 1'h0;
        o_threshold  = 8'h0;
        next_o_reset = 1'b0;
        next_tmp_max = 8'b0;
        next_tmp_min = 8'hff;
        next_aA0     = 8'b0;
        next_aA1     = 8'b0;
        next_aA2     = 8'b0;
        next_aA3     = 8'b0;
        next_aA4     = 8'b0;
        next_aA5     = 8'b0;
        next_aA6     = 8'b0;
        next_aA7     = 8'b0;
        next_aA8     = 8'b0;
        next_aA9     = 8'b0;
        next_aA10    = 8'b0;
        next_aA11    = 8'b0;
        next_aA12    = 8'b0;
        next_aA13    = 8'b0;
        next_aA14    = 8'b0;
        next_aA15    = 8'b0;
        next_aA16    = 8'b0;
        next_aA17    = 8'b0;
        next_aA18    = 8'b0;
        next_aA19    = 8'b0;
        next_aA20    = 8'b0;
        next_aA21    = 8'b0;
        next_aA22    = 8'b0;
        next_aA23    = 8'b0;
        next_aA24    = 8'b0;
        next_aA25    = 8'b0;
        next_aA26    = 8'b0;
        next_aA27    = 8'b0;
        next_aA28    = 8'b0;
        next_aA29    = 8'b0;
        next_aA30    = 8'b0;
        next_aA31    = 8'b0;
        next_aA32    = 8'b0;
        next_aA33    = 8'b0;
        next_aA34    = 8'b0;
        next_aA35    = 8'b0;
        next_aA36    = 8'b0;
        next_aA37    = 8'b0;
        next_aA38    = 8'b0;
        next_aA39    = 8'b0;
        next_aA40    = 8'b0;
        next_aA41    = 8'b0;
        next_aA42    = 8'b0;
        next_aA43    = 8'b0;
        next_aA44    = 8'b0;
        next_aA45    = 8'b0;
        next_aA46    = 8'b0;
        next_aA47    = 8'b0;
        next_aA48    = 8'b0;
        next_aA49    = 8'b0;
        next_aA50    = 8'b0;
        next_aA51    = 8'b0;
        next_aA52    = 8'b0;
        next_aA53    = 8'b0;
        next_aA54    = 8'b0;
        next_aA55    = 8'b0;
        next_aA56    = 8'b0;
        next_aA57    = 8'b0;
        next_aA58    = 8'b0;
        next_aA59    = 8'b0;
        next_aA60    = 8'b0;
        next_aA61    = 8'b0;
        next_aA62    = 8'b0;
        next_aA63    = 8'b0;
    end
    else begin
        o_out        = (o_diff == 8'b0 && o_threshold != 8'b0) || o_diff[8];
        o_threshold  = (n_reset)? o_avg : next_o_threshold;
        next_o_reset = o_reset || n_reset;
        next_tmp_max = (n_reset)? s_in : ((tmp_max > s_in)? tmp_max : s_in);
        next_tmp_min = (n_reset)? s_in : ((tmp_min < s_in)? tmp_min : s_in);
        next_aA0     = s_in;
        next_aA1     = aA0;
        next_aA2     = aA1;
        next_aA3     = aA2;
        next_aA4     = aA3;
        next_aA5     = aA4;
        next_aA6     = aA5;
        next_aA7     = aA6;
        next_aA8     = aA7;
        next_aA9     = aA8;
        next_aA10    = aA9;
        next_aA11    = aA10;
        next_aA12    = aA11;
        next_aA13    = aA12;
        next_aA14    = aA13;
        next_aA15    = aA14;
        next_aA16    = aA15;
        next_aA17    = aA16;
        next_aA18    = aA17;
        next_aA19    = aA18;
        next_aA20    = aA19;
        next_aA21    = aA20;
        next_aA22    = aA21;
        next_aA23    = aA22;
        next_aA24    = aA23;
        next_aA25    = aA24;
        next_aA26    = aA25;
        next_aA27    = aA26;
        next_aA28    = aA27;
        next_aA29    = aA28;
        next_aA30    = aA29;
        next_aA31    = aA30;
        next_aA32    = aA31;
        next_aA33    = aA32;
        next_aA34    = aA33;
        next_aA35    = aA34;
        next_aA36    = aA35;
        next_aA37    = aA36;
        next_aA38    = aA37;
        next_aA39    = aA38;
        next_aA40    = aA39;
        next_aA41    = aA40;
        next_aA42    = aA41;
        next_aA43    = aA42;
        next_aA44    = aA43;
        next_aA45    = aA44;
        next_aA46    = aA45;
        next_aA47    = aA46;
        next_aA48    = aA47;
        next_aA49    = aA48;
        next_aA50    = aA49;
        next_aA51    = aA50;
        next_aA52    = aA51;
        next_aA53    = aA52;
        next_aA54    = aA53;
        next_aA55    = aA54;
        next_aA56    = aA55;
        next_aA57    = aA56;
        next_aA58    = aA57;
        next_aA59    = aA58;
        next_aA60    = aA59;
        next_aA61    = aA60;
        next_aA62    = aA61;
        next_aA63    = aA62;
    end
end

always @ (posedge clk or negedge CAL_reset) begin
    if (CAL_reset) begin
        tmp_max <= 8'b0;
        tmp_min <= 8'hff;
        n_reset <= 1'b0;
        o_reset <= 1'b0;
        next_o_threshold <= 8'b0;
        aA0     <= 8'b0;
        aA1     <= 8'b0;
        aA2     <= 8'b0;
        aA3     <= 8'b0;
        aA4     <= 8'b0;
        aA5     <= 8'b0;
        aA6     <= 8'b0;
        aA7     <= 8'b0;
        aA8     <= 8'b0;
        aA9     <= 8'b0;
        aA10    <= 8'b0;
        aA11    <= 8'b0;
        aA12    <= 8'b0;
        aA13    <= 8'b0;
        aA14    <= 8'b0;
        aA15    <= 8'b0;
        aA16    <= 8'b0;
        aA17    <= 8'b0;
        aA18    <= 8'b0;
        aA19    <= 8'b0;
        aA20    <= 8'b0;
        aA21    <= 8'b0;
        aA22    <= 8'b0;
        aA23    <= 8'b0;
        aA24    <= 8'b0;
        aA25    <= 8'b0;
        aA26    <= 8'b0;
        aA27    <= 8'b0;
        aA28    <= 8'b0;
        aA29    <= 8'b0;
        aA30    <= 8'b0;
        aA31    <= 8'b0;
        aA32    <= 8'b0;
        aA33    <= 8'b0;
        aA34    <= 8'b0;
        aA35    <= 8'b0;
        aA36    <= 8'b0;
        aA37    <= 8'b0;
        aA38    <= 8'b0;
        aA39    <= 8'b0;
        aA40    <= 8'b0;
        aA41    <= 8'b0;
        aA42    <= 8'b0;
        aA43    <= 8'b0;
        aA44    <= 8'b0;
        aA45    <= 8'b0;
        aA46    <= 8'b0;
        aA47    <= 8'b0;
        aA48    <= 8'b0;
        aA49    <= 8'b0;
        aA50    <= 8'b0;
        aA51    <= 8'b0;
        aA52    <= 8'b0;
        aA53    <= 8'b0;
        aA54    <= 8'b0;
        aA55    <= 8'b0;
        aA56    <= 8'b0;
        aA57    <= 8'b0;
        aA58    <= 8'b0;
        aA59    <= 8'b0;
        aA60    <= 8'b0;
        aA61    <= 8'b0;
        aA62    <= 8'b0;
        aA63    <= 8'b0;
    end
    else begin
        tmp_max <= next_tmp_max;
        tmp_min <= next_tmp_min;
        n_reset <= s_reset;
        o_reset <= next_o_reset;
        next_o_threshold <= o_threshold;
        aA0     <= next_aA0;
        aA1     <= next_aA1;
        aA2     <= next_aA2;
        aA3     <= next_aA3;
        aA4     <= next_aA4;
        aA5     <= next_aA5;
        aA6     <= next_aA6;
        aA7     <= next_aA7;
        aA8     <= next_aA8;
        aA9     <= next_aA9;
        aA10    <= next_aA10;
        aA11    <= next_aA11;
        aA12    <= next_aA12;
        aA13    <= next_aA13;
        aA14    <= next_aA14;
        aA15    <= next_aA15;
        aA16    <= next_aA16;
        aA17    <= next_aA17;
        aA18    <= next_aA18;
        aA19    <= next_aA19;
        aA20    <= next_aA20;
        aA21    <= next_aA21;
        aA22    <= next_aA22;
        aA23    <= next_aA23;
        aA24    <= next_aA24;
        aA25    <= next_aA25;
        aA26    <= next_aA26;
        aA27    <= next_aA27;
        aA28    <= next_aA28;
        aA29    <= next_aA29;
        aA30    <= next_aA30;
        aA31    <= next_aA31;
        aA32    <= next_aA32;
        aA33    <= next_aA33;
        aA34    <= next_aA34;
        aA35    <= next_aA35;
        aA36    <= next_aA36;
        aA37    <= next_aA37;
        aA38    <= next_aA38;
        aA39    <= next_aA39;
        aA40    <= next_aA40;
        aA41    <= next_aA41;
        aA42    <= next_aA42;
        aA43    <= next_aA43;
        aA44    <= next_aA44;
        aA45    <= next_aA45;
        aA46    <= next_aA46;
        aA47    <= next_aA47;
        aA48    <= next_aA48;
        aA49    <= next_aA49;
        aA50    <= next_aA50;
        aA51    <= next_aA51;
        aA52    <= next_aA52;
        aA53    <= next_aA53;
        aA54    <= next_aA54;
        aA55    <= next_aA55;
        aA56    <= next_aA56;
        aA57    <= next_aA57;
        aA58    <= next_aA58;
        aA59    <= next_aA59;
        aA60    <= next_aA60;
        aA61    <= next_aA61;
        aA62    <= next_aA62;
        aA63    <= next_aA63;
    end
end

endmodule

module ATE(clk, reset, pix_data, type, bin, threshold);
input        clk;
input        reset;
input  [7:0] pix_data;
input        type;
output       bin;
output [7:0] threshold;

reg    [7:0] in_data;
reg    [6:0] out_valid;
reg    [5:0] count;
reg          one_round;
reg    [7:0] next_in_data;
reg    [6:0] next_out_valid;
reg    [5:0] next_count;
reg          next_one_round;
wire         at_first;
wire         at_second;
wire         boundary;
wire   [6:0] boundary1;
wire         bin;
wire   [7:0] threshold;
integer      i;

assign at_first  = count == 6'h01 && one_round;
assign at_second = count == 6'h00 && one_round;
assign boundary  = out_valid == 7'b0 || out_valid == boundary1;
assign boundary1 = (type)? 7'd65 : 7'd5;

CAL_Threshold cal_top(.clk(clk), .CAL_reset(reset), .s_in(in_data), .s_reset(at_first), .o_out(bin), .o_threshold(threshold));

always @ (*) begin
    if (reset) begin
        next_one_round = 1'b0;
        next_in_data   = 8'b0;
        next_out_valid = 7'b0;
        next_count     = 6'b0;
    end
    else begin
        next_one_round = one_round || count == 6'h3f;
        next_in_data   = (boundary)? 8'b0 : pix_data;
        next_out_valid = (at_second)? ((out_valid == boundary1)? 7'b0 : out_valid+7'b1) : out_valid;
        next_count     = count + 6'b1;
    end
end

always @ (posedge clk or negedge reset) begin
    if (reset) begin
        in_data   <= 8'b0;
        out_valid <= 7'b0;
        count     <= 6'h0;
        one_round <= 1'b0;
    end
    else begin
        in_data   <= next_in_data;
        out_valid <= next_out_valid;
        count     <= next_count;
        one_round <= next_one_round;
    end
end

endmodule