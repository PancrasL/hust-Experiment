`timescale 1ns / 1ns
module romN(addr,data);
//16个N位存储器
parameter N=8;
parameter M=4;
parameter T=M*M;
input [M-1:0] addr;//地址
output [N-1:0] data;
reg [N-1:0] mem [T-1:0];//16个N位的存储器
initial   begin             // 初始化存储器
    $readmemh("E:/shiyan4/ram_init.txt",mem);
//        mem[0]=32'h00000003;
//        mem[1]=32'h00000002;
//        mem[2]=32'h00000000;
//        mem[3]=32'h00000007;
        
//        mem[4]=32'h00000004;
//        mem[5]=32'h00000000;
//        mem[6]=32'h00000000;
//        mem[7]=32'h0000000b;
        
//        mem[8]=32'h00000006;
//        mem[9]=32'h00000000;
//        mem[10]=32'h00000000;
//        mem[11]=32'h00000000;
        
//        mem[12]=32'h00000008;
//        mem[13]=32'h00000000;
//        mem[14]=32'h00000000;
//        mem[15]=32'h00000000;    
end 
assign data=mem[addr];
endmodule
