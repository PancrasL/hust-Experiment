datatype tree = Empty | Node of tree * int * tree;
(* T1 *)
fun reverse([ ]) = [ ]
    | reverse(a::L)=reverse(L) @ [a];

fun help ([],a) = a
    | help(b::L, a) = help(L, b::a);
fun reverse'(L) = help(L,[]);

(* T2 *)
fun interleave([], []) = []
    | interleave([] , L) = L
    | interleave(L , []) = L
    | interleave(a::L, b::T) = a::b::interleave(L, T);

(* T3 *)
(* split = fn : 'a list -> 'a list * 'a * 'a list *)
(* listToTree = fn : int list -> tree *)
datatype tree = Empty | Node of tree * int * tree;
fun split(L) = 
    case List.length L
    of  1 => let val x::T = L in ([],x,[]) end
    |   2 => let val x::y::T = L in ([x],y,[]) end
    |   n => let val mid = length L div 2               (* 获取中间元素序号 *)
                 val a::right = List.drop(L,mid)        (* 获取右部list *)
                 in (List.take(L,mid), a, right) end;   (* 分离list *)

fun listToTree([]) = Empty
    | listToTree(L) = let val (Left, root, Right) = split(L)  
                          in Node(listToTree(Left), root, listToTree(Right)) end;
(* T4 *)
(* revT: tree -> tree *)
fun revT(Empty) = Empty
    | revT (Node (left,root,right)) = Node (revT(right), root, revT(left));

(* T5 *)
fun binarySearch(Empty, x) = false
    | binarySearch(Node(left, root, right), x) = 
        case Int.compare(x, root) of
	    GREATER => binarySearch(right, x)
        | EQUAL => true
        | LESS => binarySearch(left, x);

