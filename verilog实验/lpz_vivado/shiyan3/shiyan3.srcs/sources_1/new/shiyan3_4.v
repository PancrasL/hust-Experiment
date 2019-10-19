`timescale 1ns / 1ps

//module main(sw,led);
//input [2:0]sw;
//output [3:0]led;
//rom8x4(sw,led);
//endmodule

module rom8x4(addr, data);
input [2:0] addr;           // 地址
output [3:0] data;          // 地址addr处存储的数据 

reg [3: 0] mem [7: 0];      //  8个4位的存储器

initial   begin             // 初始化存储器
    mem[0]=0;
    mem[1]=2;
    mem[2]=4;
    mem[3]=6;
    mem[4]=8;
    mem[5]=10;
    mem[6]=12;
    mem[7]=14;
    
end     
assign data=mem[addr];                 // 读取addr单元的值输出                      
endmodule

