(* T2 *)
(* mult : int list -> int 		*)
(* REQUIRES: true		*)
(* ENSURES: mult(L) evaluates to the product of the integers in L. *)
fun mult [ ] = 1
    | mult (x ::L) = x * (mult L);


(* T3 *)
(* mult : int list list -> int 	*)
(* REQUIRES: true		*)
(* ENSURES: mult(R) evaluates to the product of all the integers in the lists of R. *)
fun Mult [ ] = mult []
    | Mult (r :: R) = mult(r) * Mult(R);

(* T4 *)
(* mult’ : int list * int -> int 			*)
(* REQUIRES: true				*)
(* ENSURES: mult’(L, a) … (* FILL IN *) 	*)
(* 求出a和int list中所有整数的乘积 *)
 fun mult' ([ ], a) = a
	  | mult' (x :: L, a) = mult' (L, x * a);

fun Mult' ( [ ], a) = mult'( [ ], a)	
    | Mult' (r::R, a) = Mult'(R, mult'(r,a));


(* T5 *)
(* double : int -> int *)
(* REQUIRES: n >= 0 *)
(* ENSURES: double n evaluates to 2 * n.*)
fun double (0 : int) : int = 0
    | double n = 2 + double (n - 1);
fun square (0 : int) : int = 0
    | square (n : int) = square (n - 1) + double(n) - 1;


(* T6 *)
(* divisibleByThree : int -> bool 	*)
(* REQUIRES: true				*)
(* ENSURES: divisibleByThree n evaluates to true if n is a multiple of 3 and to false otherwise *)
fun divisibleByThree (0) : bool = true
    | divisibleByThree (1) : bool = false
    | divisibleByThree (2) : bool = false
    | divisibleByThree (n) : bool = 
        if(n < 0) then divisibleByThree(n+3)
        else divisibleByThree(n-3);


(* T7 *)
(* oddP : int -> bool 		*)
(* REQUIRES: n >= 0 		*)
(* ENSURES: oddP n evaluates to true iff n is odd. *)
fun oddP (0 : int) : bool = false
  	| oddP 1 = true
  	| oddP n = oddP (n - 2)
