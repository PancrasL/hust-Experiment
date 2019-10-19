(* T1 *)
fun square x = x*x;
fun thenAddOne (transFunc, x : int) = transFunc x + 1;

(* T2 *)
fun mapList(transFunc, []) = []
    | mapList(transFunc, x::L) = transFunc(x)::mapList(transFunc,L);

(* T3 *)
fun transList(transFunc, []) = []
    | transList(transFunc, x::L) = transFunc(x)::transList(transFunc,L);
fun mapList'(transFunc) = fn L => transList(transFunc, L);

(* T4 *)
fun findOdd [] = NONE
    | findOdd(x::L) = if (x mod 2) = 1 then SOME x 
                     else NONE;

(* T5 *)
(* 将函数f作用于表中的每一个元素 *)
fun map f [] = []
  | map f (x::R) = (f x) :: (map f R);

(* 求出表中所有的元素之和 *)
fun   sum [] = 0
	| sum (x :: L) = x + (sum L)

(* 求出表的所有子集构成的集和 *)
fun   subList [] = [[]]
	| subList (x :: R) = let val S = subList R in S @ map (fn A => x :: A) S end

(* 判断表元素之和是否等于a *)
fun   subsetHelper ([], a) = NONE
	| subsetHelper (x :: L, a) = if sum x = a then SOME x else subsetHelper (L, a)

fun subsetSumOption (L, a) = let val sublists = subList L in subsetHelper (sublists, a) end 

(* T6 *)
fun exists p [] = false
    | exists p (x::L) = (p x) orelse (exists p L);
fun forall p [] = true
    | forall p (x::L) = (p x) andalso (forall p L);
(* T7 *)
datatype 'a tree =
	  Empty
	| Node of 'a tree * 'a * 'a tree;
fun treeFilter p Empty = Empty
    | treeFilter p (Node(L, x, R)) = if (p x) then Node((treeFilter p L), SOME x, (treeFilter p R))
                                    else Node((treeFilter p L), NONE, (treeFilter p R));



fun toInt(a:int) = fn L => 
        case L of
        [] => 0
        | x::L1 => x + a* toInt a(L1);

fun toBase (a:int) = fn n => 
        if n < a then [n]
        else (n mod a)::(toBase a (n div a));

fun convert (a:int,b:int) = fn L =>
        case L of
        [] => []
        | L1 => toBase b (toInt a L1);