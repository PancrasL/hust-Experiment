`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 11:02:44
// Design Name: 
// Module Name: shiyan2_4_1
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module shiyan2_4(sw[3:0],key,seg);
	input  [3:0] sw;                          // 输入数
	input key;                                 //输出控制
	output [7:0]  seg;                         // 7段数码管驱动，低电平有效
	
    always @(sw[3:0],key) begin
        if (key==0) begin
               case(sw[3:0])
               4'b0000:seg=8'b11000000;
               4'b0001:seg=8'b11111001;
               4'b0010:seg=8'b10100100;
               4'b0011:seg=8'b10110000;
               
               4'b0100:seg=8'b10011001;
               4'b0101:seg=8'b10010010;
               4'b0110:seg=8'b10000010;
               4'b0111:seg=8'b11111000;
               
               4'b1000:seg=8'b10000000;
               4'b1001:seg=8'b10011000;
               4'b1010:seg=8'b11000000;
               4'b1011:seg=8'b11000000;
                
               4'b1100:seg=8'b11000000;
               4'b1101:seg=8'b11000000;
               4'b1110:seg=8'b11000000;
               4'b1111:seg=8'b11000000;          
               endcase            
         
        end
        else  begin
            if(sw<10) begin
              seg=8'b11000000;
            end
            else begin
              seg=8'b11111001;
            end
        end
    end

endmodule
