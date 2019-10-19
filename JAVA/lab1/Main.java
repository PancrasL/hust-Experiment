
public class Main {
	public static void main(String[] argvs) {
		Queue<Integer> q = new Queue<Integer>();
		for (int i = 1; i <= 10; i++)
			q.add(i);
		System.out.print(q.peek1());
//		System.out.println("³ö¶Ó£º");
//		while (!q.queueEmpty()) {
//			System.out.print(q.remove() + " ");
//		}
//		System.out.print(q.element()+"\n");
//		for (int i = 1; i <= 10; i++)
//			q.offer(i);
//		while (!q.queueEmpty()) {
//			System.out.print(q.poll() + " ");
//		}

		// q.add(null);
		// q.remove();
	}
}