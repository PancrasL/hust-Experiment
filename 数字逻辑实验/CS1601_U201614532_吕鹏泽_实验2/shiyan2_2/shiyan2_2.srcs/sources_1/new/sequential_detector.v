`timescale 1ns / 1ps
module sequential_detector(CP,RST,X,Z,c_state);
input CP,X,RST;
output reg Z;
output reg [2:0] c_state;
parameter ST0=0,ST1=1,ST2=2,ST3=3,ST4=4,ST5=5;
reg [2:0] n_state;
always @(posedge CP) begin
    if(RST)
        c_state<=ST0;
    else
        c_state<=n_state;
end

always @(c_state, X) begin
    case(c_state)
    ST0:begin
    Z<=0;
    if(X)
        n_state<=ST1;
    else n_state<=ST0;
    end
    ST1:begin
    Z<=0;
    if(X)
        n_state<=ST1;
    else n_state<=ST2;
    end
    ST2:begin
    Z<=0;
    if(X)
        n_state<=ST3;
    else n_state<=ST0;
    end
    ST3:begin
    Z<=0;
    if(X)
        n_state<=ST4;
    else n_state<=ST2;
    end
    ST4:begin
    Z<=0;
    if(X)
        n_state<=ST1;
    else n_state<=ST5;
    end
    ST5:begin
    Z<=1;
    if(X)
        n_state<=ST1;
    else n_state<=ST0;
    end
    default:begin
    Z<=0;
    n_state<=ST0;
    end
    endcase
end
endmodule