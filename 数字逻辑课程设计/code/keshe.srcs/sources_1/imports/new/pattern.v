`timescale 1ns / 1ps
module pattern(code, patt);
input [3: 0] code;       // 16进制数字的4位二进制编码
output reg [7:0] patt;       // 7段数码管驱动，低电平有效
always @(code[3:0])  begin
       case(code[3:0])
        4'b0000:patt=8'b01000000;//0
        4'b0001:patt=8'b01111001;//1
        4'b0010:patt=8'b00100100;//2
        4'b0011:patt=8'b00110000;//3
        
        4'b0100:patt=8'b00011001;//4
        4'b0101:patt=8'b00010010;//5
        4'b0110:patt=8'b00000010;//6
        4'b0111:patt=8'b01111000;//7
        
        4'b1000:patt=8'b00000000;//8
        4'b1001:patt=8'b00011000;//9
        default:patt=8'b11111111;       
        endcase
     end
endmodule