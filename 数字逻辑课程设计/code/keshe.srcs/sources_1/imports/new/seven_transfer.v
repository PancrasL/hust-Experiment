`timescale 1ns / 1ps
module seven_transfer(hello_sig,charge_sig,not_buy_sig,not_pay_sig,cur_val,num,out);
input hello_sig,charge_sig,not_buy_sig,not_pay_sig;
input [7:0] cur_val;
input [2:0] num;
output reg [7:0] out;
wire[3:0] one,ten;//��λ��ʮλ
assign one=cur_val[7:1]%10;
assign ten=cur_val[7:1]/10;
wire[7:0] pat_one,pat_ten;
pattern p1(one,pat_one);//���ĸ�λ��Ӧ������ܱ���
pattern p2(ten,pat_ten);//����ʮλ��Ӧ������ܱ���
always @(hello_sig,cur_val,num,pat_one,pat_ten) begin
    if(hello_sig==1) begin
       if(charge_sig==1) begin
       case(num)
       3'b000:out=8'b11000000;//0
       3'b001:out=8'b01000000;//0
       3'b010:out=8'b11000000;//0
       default:out=8'b11111111;
       endcase        
   end
   else begin
        case(num)
        3'b000:out=8'b11000000;//O
        3'b001:out=8'b11000111;//L
        3'b010:out=8'b11000111;//L
        3'b011:out=8'b10000110;//E
        3'b100:out=8'b10001001;//H
        default:out=8'b11111111;//����ʾ
        endcase
    end
    end
    else begin//hello_sig==0
        if(not_buy_sig==1) begin
            case(num)
            3'b000:out=8'b10000011;//b
            3'b001:out=8'b11000000;//o
            3'b010:out=8'b11001000;//n
            default:out=8'b11111111;
            endcase
        end
        else if(not_pay_sig==1) begin
            case(num)
            3'b000:out=8'b10001100;//p
            3'b001:out=8'b11000000;//o
            3'b010:out=8'b11001000;//n
            default:out=8'b11111111;
            endcase        
        end

        else begin
            case(num)
            3'b000:out=cur_val[0]?8'b10010010:8'b11000000;//��С��λ���5����С��λ���0
            3'b001:out=pat_one;//out=��λ
            3'b010:out={1'b1,pat_ten[6:0]};//out=ʮλ��ȥ��С����
            default:out=8'b11111111;
            endcase
        end
    end
end
endmodule
