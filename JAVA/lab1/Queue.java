import java.util.Stack;
import java.util.NoSuchElementException;
public class Queue<E> extends Stack<E> {
    public final int dump = 10;
    private  Stack<E> stk;
    public Queue() {
        stk = new Stack<E>();
    }

    public boolean add(E e) throws IllegalStateException, ClassCastException, NullPointerException, IllegalArgumentException {
        if(e == null)//null元素入队
            throw new NullPointerException();
        if (stk.size() >= dump){//当stk的元素个数超过dump时，将元素导入另一个栈中
            if(!this.isEmpty())//另一个栈不为空，不可导入元素
                throw new IllegalStateException();
            else {
                while(!stk.isEmpty())
                    this.push(stk.pop());
                stk.push(e);
            }
        } 
        else {//当元素个数少于dump时，直接入队
            stk.push(e);
        }
        return true;
    }

    public boolean offer(E e) throws ClassCastException, NullPointerException, IllegalArgumentException {
        if(e == null)//null元素入队
            throw new NullPointerException();
        if (stk.size() >= dump){//当stk的元素个数超过dump时，将元素导入另一个栈中
            if(!this.isEmpty())//另一个栈不为空，不可导入元素
                return false;
            else {
                while(!stk.isEmpty())
                    this.push(stk.pop());
                stk.push(e);
            }
        } 
        else {//当元素个数少于dump时，直接入队
            stk.push(e);
        }
        return true;
    }
    public E remove() throws NoSuchElementException {
        if(!this.isEmpty()){//出队栈不为空，直接出队
            return this.pop();
        } 
        else if(!stk.isEmpty()){//出队栈为空，入队栈不为空，导入元素后出队
            while(!stk.isEmpty())
                this.push(stk.pop());
            return this.pop();
        } 
        else {//队列为空
            throw new NoSuchElementException();
        }
    }

    public E poll() {
        if(!this.isEmpty()){//出队栈不为空，直接出队
            return this.pop();
        } 
        else if(!stk.isEmpty()){//出队栈为空，入队栈不为空，导入元素后出队
            while(!stk.isEmpty())
                this.push(stk.pop());
            return this.pop();
        } 
        else {//队列为空
            return null;
        }
    }

    public E element() throws NoSuchElementException {
        if(!this.isEmpty()){//出队栈不为空
            return super.peek();
        } 
        else if(!stk.isEmpty()){//出队栈为空，入队栈不为空，导入元素
            while(!stk.isEmpty())
                this.push(stk.pop());
            return super.peek();
        } 
        else {//队列为空
            throw new NoSuchElementException();
        }
    }

    public E peek1() {
        if(!this.isEmpty()){//出队栈不为空
            return super.peek();
        } 
        else if(!stk.isEmpty()){//出队栈为空，入队栈不为空，导入元素
            while(!stk.isEmpty())
                this.push(stk.pop());
            return super.peek();
        } 
        else {//队列为空
            return null;
        }
    }
    public boolean queueEmpty() {
    	return this.isEmpty()&&stk.isEmpty();
    }
}
