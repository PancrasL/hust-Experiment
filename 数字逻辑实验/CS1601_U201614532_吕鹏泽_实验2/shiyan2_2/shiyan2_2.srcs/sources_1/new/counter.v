`timescale 1ns / 1ps
module counter(CP,CLR,M,LD,D,C,B,A,QD,QC,QB,QA,Qcc);
input CP,CLR,M,LD;//CLR,LD低电平有效
input D,C,B,A;
output reg QD,QC,QB,QA;
output reg Qcc=0;
initial begin {QA,QB,QC,QD}=0;end
always @ (posedge CP) begin
    Qcc<=!(CLR&LD&((QA&QB&QC&QD&M)|(~QA&~QB&~QC&~QD&~M)));
end
always @ (posedge CP) begin
    if(LD==0)
            {QD,QC,QB,QA}<={D,C,B,A};
    else if(CLR==0)
            {QD,QC,QB,QA}<=0;
    else begin
        if(M==1)
            {QD,QC,QB,QA}= {QD,QC,QB,QA}+1;
        else if(M==0)
            {QD,QC,QB,QA}= {QD,QC,QB,QA}-1;
        else {QD,QC,QB,QA}= {QD,QC,QB,QA};
    end
end
endmodule
