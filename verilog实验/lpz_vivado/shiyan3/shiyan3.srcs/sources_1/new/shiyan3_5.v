`timescale 1ns / 1ps
module decoder3_8(num, sel);
input [2: 0] num;       // 数码管编号：0~7
output reg [7:0] sel;       // 7段数码管片选信号，低电平有效
 always @(num[2:0])  begin
     case(num[2:0])
     3'b000:sel=~8'b00000001;
     3'b001:sel=~8'b00000010;
     3'b010:sel=~8'b00000100;
     3'b011:sel=~8'b00001000;
     
     3'b100:sel=~8'b00010000;
     3'b101:sel=~8'b00100000;
     3'b110:sel=~8'b01000000;
     3'b111:sel=~8'b10000000;
     endcase
    end  
endmodule

module pattern(code, patt);
input [3: 0] code;       // 16进制数字的4位二进制编码
output reg [7:0] patt;       // 7段数码管驱动，低电平有效
always @(code[3:0])  begin
       case(code[3:0])
        4'b0000:patt=8'b11000000;
        4'b0001:patt=8'b11111001;
        4'b0010:patt=8'b10100100;
        4'b0011:patt=8'b10110000;
        
        4'b0100:patt=8'b10011001;
        4'b0101:patt=8'b10010010;
        4'b0110:patt=8'b10000010;
        4'b0111:patt=8'b11111000;
        
        4'b1000:patt=8'b10000000;
        4'b1001:patt=8'b10011000;
        4'b1010:patt=8'b10001000;
        4'b1011:patt=8'b10000011;
        
        4'b1100:patt=8'b11000110;
        4'b1101:patt=8'b10100001;
        4'b1110:patt=8'b10000110;
        4'b1111:patt=8'b10001110;            
        endcase
     end
endmodule
