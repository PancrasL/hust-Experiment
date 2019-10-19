`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 10:09:14
// Design Name: 
// Module Name: shiyan2_3
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

module _7Seg_Driver_Choice(sw, an);

input [2:0] sw;       // 16位拨动开关
output reg [7:0] an;       // 7段数码管片选信号，低电平有效

 always @(sw[2:0])  begin
      case(sw[2:0])
      3'b000:an=~8'b00000001;
      3'b001:an=~8'b00000010;
      3'b010:an=~8'b00000100;
      3'b011:an=~8'b00001000;
      
      3'b100:an=~8'b00010000;
      3'b101:an=~8'b00100000;
      3'b110:an=~8'b01000000;
      3'b111:an=~8'b10000000;
      endcase
     end                                                                                                                                                                                          
endmodule
