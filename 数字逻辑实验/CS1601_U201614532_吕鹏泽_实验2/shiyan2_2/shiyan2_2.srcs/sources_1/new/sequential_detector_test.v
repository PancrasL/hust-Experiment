`timescale 1ns / 1ps
module sequential_detector_test();
reg CP,X,RST;
wire Z;
sequential_detector test(CP,RST,X,Z);
initial begin
CP=0;
X=0;
RST=0;
#10 RST=1;
#10 RST=0;
#2
#20 X=1;//
#20 X=0;
#20 X=1;
#20 X=1;
#20 X=0;//������10110����1
#20 X=0;
#20 X=0;
#20 X=1;
#20 X=1;
#20 X=1;//
#20 X=0;
#20 X=1;
#20 X=1;
#20 X=0;//������10110����2
#20 X=1;
#20 X=1;
#20 X=0;//������10110����
end
always begin
#10 CP=!CP;
end
endmodule
