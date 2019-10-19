import java.util.Stack;
import java.util.NoSuchElementException;
public class Queue<E> extends Stack<E> {
    public final int dump = 10;
    private  Stack<E> stk;
    public Queue() {
        stk = new Stack<E>();
    }

    public boolean add(E e) throws IllegalStateException, ClassCastException, NullPointerException, IllegalArgumentException {
        if(e == null)//nullԪ�����
            throw new NullPointerException();
        if (stk.size() >= dump){//��stk��Ԫ�ظ�������dumpʱ����Ԫ�ص�����һ��ջ��
            if(!this.isEmpty())//��һ��ջ��Ϊ�գ����ɵ���Ԫ��
                throw new IllegalStateException();
            else {
                while(!stk.isEmpty())
                    this.push(stk.pop());
                stk.push(e);
            }
        } 
        else {//��Ԫ�ظ�������dumpʱ��ֱ�����
            stk.push(e);
        }
        return true;
    }

    public boolean offer(E e) throws ClassCastException, NullPointerException, IllegalArgumentException {
        if(e == null)//nullԪ�����
            throw new NullPointerException();
        if (stk.size() >= dump){//��stk��Ԫ�ظ�������dumpʱ����Ԫ�ص�����һ��ջ��
            if(!this.isEmpty())//��һ��ջ��Ϊ�գ����ɵ���Ԫ��
                return false;
            else {
                while(!stk.isEmpty())
                    this.push(stk.pop());
                stk.push(e);
            }
        } 
        else {//��Ԫ�ظ�������dumpʱ��ֱ�����
            stk.push(e);
        }
        return true;
    }
    public E remove() throws NoSuchElementException {
        if(!this.isEmpty()){//����ջ��Ϊ�գ�ֱ�ӳ���
            return this.pop();
        } 
        else if(!stk.isEmpty()){//����ջΪ�գ����ջ��Ϊ�գ�����Ԫ�غ����
            while(!stk.isEmpty())
                this.push(stk.pop());
            return this.pop();
        } 
        else {//����Ϊ��
            throw new NoSuchElementException();
        }
    }

    public E poll() {
        if(!this.isEmpty()){//����ջ��Ϊ�գ�ֱ�ӳ���
            return this.pop();
        } 
        else if(!stk.isEmpty()){//����ջΪ�գ����ջ��Ϊ�գ�����Ԫ�غ����
            while(!stk.isEmpty())
                this.push(stk.pop());
            return this.pop();
        } 
        else {//����Ϊ��
            return null;
        }
    }

    public E element() throws NoSuchElementException {
        if(!this.isEmpty()){//����ջ��Ϊ��
            return super.peek();
        } 
        else if(!stk.isEmpty()){//����ջΪ�գ����ջ��Ϊ�գ�����Ԫ��
            while(!stk.isEmpty())
                this.push(stk.pop());
            return super.peek();
        } 
        else {//����Ϊ��
            throw new NoSuchElementException();
        }
    }

    public E peek1() {
        if(!this.isEmpty()){//����ջ��Ϊ��
            return super.peek();
        } 
        else if(!stk.isEmpty()){//����ջΪ�գ����ջ��Ϊ�գ�����Ԫ��
            while(!stk.isEmpty())
                this.push(stk.pop());
            return super.peek();
        } 
        else {//����Ϊ��
            return null;
        }
    }
    public boolean queueEmpty() {
    	return this.isEmpty()&&stk.isEmpty();
    }
}
