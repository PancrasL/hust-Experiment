#include"head.h"
int space;//���������ʽ

int main(void) {
	//system("mode con cols=200 lines=40  ");
	system("color F0\n");
	while (1)
	{
		system("cls");
		int op = select_display();
		if (op == 1) { set_display(); }
		else if (op == 2) { apply_display(); }
		else if (op == 3) { AVL_display(); }
		else break;
	}
	printf("��ӭ�´�ʹ��\n");
	getchar();
	return 0;

}//end of main()

/*AVL����ת����*/
void L_Rotate(BSTree &p) {
	//����*pΪ���Ķ�����������������������֮��pָ���µ������ڵ㣬����ת����֮ǰ���������ĸ��ڵ�
	BSTNode *rc=NULL;
	rc = p->rchild;//rcָ��*p���Һ���
	p->rchild = rc->lchild;//rc���������ҽ�Ϊ*p��������
	rc->lchild = p; p = rc;//pָ���µĸ��ڵ�
}
void R_Rotate(BSTree &p) 
{//������L_Rotate
	BSTNode *lc=NULL;
	lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p; p = lc;
}
void LeftBalance(BSTree &T)
{
	{
		BSTNode* lc = NULL;
		BSTNode* rd = NULL;
		lc = T->lchild;
		switch (lc->bf)
		{
		case LH:                    //LL��ת   
			T->bf = EH;
			lc->bf = EH;
			R_Rotate(T);
			break;

		case EH:                    //deleteAVL��Ҫ��insertAVL�ò���   
			T->bf = LH;
			lc->bf = RH;
			R_Rotate(T);
			break;

		case RH:                    //LR��ת   
			rd = lc->rchild;
			switch (rd->bf)
			{
			case LH:
				T->bf = RH;
				lc->bf = EH;
				break;
			case EH:
				T->bf = EH;
				lc->bf = EH;
				break;
			case RH:
				T->bf = EH;
				lc->bf = LH;
				break;
			}
			rd->bf = EH;
			L_Rotate(T->lchild);//����дL_Rotate(lc);���õ������ò���   
			R_Rotate(T);
			break;
		}
	}
}
void RightBalance(BSTree &T)
{
	//���Զ�����T����ƽ�⴦����ʹTָ���µĸ��ڵ�
	BSTNode* rc = NULL;
	BSTNode *ld = NULL;

	rc = T->rchild;
	switch (rc->bf)
	{
	case LH:                //RL��ת   
		ld = rc->lchild;
		switch (ld->bf)
		{
		case LH:
			T->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			T->bf = EH;
			rc->bf = EH;
			break;
		case RH:
			T->bf = LH;
			rc->bf = EH;
			break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
		break;

	case EH:               
		T->bf = RH;
		rc->bf = LH;
		L_Rotate(T);
		break;

	case RH:                //RR��ת   
		T->bf = EH;
		rc->bf = EH;
		L_Rotate(T);
		break;
	}
}
/*AVL���Ļ�������*/
Status InitAVL(BSTree &T)
{
	T = NULL;
	return TRUE;
}
Status InsertAVL(BSTree &T, Info e, bool &taller) 
{
	//��T��������e����ͬ�ؼ��ֵĽڵ㣬����e������1�����򷵻�0
	//������e�����������ʧȥƽ�⣬��ƽ�⻯����taller��ӦT�������

	if (!T) {//�����½ڵ㣬�����ߣ�tallerΪTRUE
		T = (BSTNode *)malloc(sizeof(BSTNode)); T->data = e;
		T->rchild = T->lchild = NULL; T->bf = EH; taller = TRUE;
	}
	else
	{
		if (e.id == T->data.id)//�����Ѵ��ں�e����ͬ�ؼ��ֵĽ��
		{
			taller = FALSE; return 0;//���ٲ���
		}
		if (e.id < T->data.id)//��T��������������
		{
			if (!InsertAVL(T->lchild, e, taller)) return 0;//δ����
			if (taller)//�Ѳ��뵽*T����������������������
				switch (T->bf)//���*T��ƽ���
				{
				case LH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					LeftBalance(T); taller = FALSE; break;//
				case EH://ԭ�����������ȸߣ��������������߶�ʹ������
					T->bf = LH; taller = TRUE; break;
				case RH://ԭ�����������������ߣ������������ȸ�
					T->bf = EH; taller = FALSE; break;
				}
		}
		else//��T��������������
		{
			if (!InsertAVL(T->rchild, e, taller)) return 0;//δ����
			if (taller)//�Ѳ��뵽*T����������������������
				switch (T->bf)//���*T��ƽ���
				{
				case LH://ԭ�����������������ߣ������������ȸ�
					T->bf = EH; taller = FALSE; break;
				case EH://ԭ�����������ȸߣ��������������߶�ʹ������
					T->bf = RH; taller = TRUE; break;
				case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					RightBalance(T); taller = FALSE; break;
				}
		}
	}
	return TRUE;
}
Status DestroyAVL(BSTree &T)
{//����AVL��T
	if (!T) return FALSE;//��Ϊ��
	else 
	{
		DestroyAVL(T->lchild);//����������
		DestroyAVL(T->rchild);//����������
		free(T);//�ͷŽڵ�
		T = NULL;//���ڵ�ָ���ÿ�
		return TRUE;
	}
}
BSTNode * SearchAVL(BSTree& T, int key)
{//��AVL��T�в��ҹؼ���Ϊkey�Ľڵ㣬�ҵ��������ַ�����߷���NULL
	if ((T == NULL) || (key == T->data.id))
		return T;
	else if (key<(T->data.id))//���������м�������
		return SearchAVL(T->lchild, key);
	else
		return SearchAVL(T->rchild, key);//���������м�������
}
Status DeleteAVL(BSTree& T, int key, bool& shorter)
{
	//����ƽ��Ķ���������t�д��ں�e����ͬ�ؼ��ֵĽ�㣬��ɾ��֮
	//������true�����򷵻�false������ɾ����ʹ����������
	//ʧȥƽ�⣬����ƽ����ת������������shorter��ӳt�䰫���
	if (T == NULL)//�����ڸ�Ԫ��   
	{
		return FALSE;//ɾ��ʧ��   
	}
	else if (key == T->data.id)//�ҵ�Ԫ�ؽ��  
	{
		BSTNode * q = NULL;
		if (T->lchild == NULL)//������Ϊ��,��Tָ��Ҫɾ��������������Ȼ��ɾ���ý��(��������������Ϊ�յ����)
		{
			q = T;
			T = T->rchild;
			free(q);
			shorter = TRUE;
		}
		else if (T->rchild == NULL)//������Ϊ�գ���Tָ��Ҫɾ��������������Ȼ��ɾ���ý��   
		{
			q = T;
			T = T->lchild;
			free(q);
			shorter = TRUE;
		}
		else//��������������,����������ݺ�ɾ�����
		{

			q = T->lchild;
			while (q->rchild)
			{
				q = q->rchild;
			}//q��λ��Ҫɾ�������������������������ڵ�
			T->data = q->data;//��q�������û���T���
							  //graphAVL(T, X0, X0, get_cursor_y());
			DeleteAVL(T->lchild, q->data.id, shorter);//���������еݹ�ɾ��q���  
			if (shorter)
			{
				switch (T->bf)
				{
				case LH://ԭ����ߣ�����䰫���ʵȸ�
					T->bf = EH;
					shorter = TRUE;
					break;
				case EH://ԭ�ȸߣ�����䰫�����Ҹ�
					T->bf = RH;
					shorter = FALSE;
					break;
				case RH://ԭ�Ҹߣ����󰫣����Ҹ��ߣ���ƽ�⣬�������ƽ�����

					if (T->rchild->bf == EH)
						shorter = FALSE;
					else
						shorter = TRUE;
					RightBalance(T);    //��ƽ�⴦��
					break;
				}
			}
		}
	}
	else if (key < T->data.id)//�������м�������   
	{
		if (!DeleteAVL(T->lchild, key, shorter))//ɾ��ʧ��
		{
			return FALSE;
		}
		if (shorter)//�������䰫������Tƽ������
		{
			switch (T->bf)
			{
			case LH://ԭ����ߣ�����䰫���ʵȸ�
				T->bf = EH;
				shorter = TRUE;
				break;
			case EH://ԭ�ȸߣ�����䰫�����Ҹ�
				T->bf = RH;
				shorter = FALSE;
				break;
			case RH://ԭ�Ҹߣ����󰫣����Ҹ��ߣ���ƽ�⣬�������ƽ�����
				
				if (T->rchild->bf == EH)
					shorter = FALSE;
				else
					shorter = TRUE;
				RightBalance(T);    //��ƽ�⴦��
				break;
			}
		}
	}
	else                                //���������м������ң�����ͬ������
	{
		if (!DeleteAVL(T->rchild, key, shorter))
		{
			return FALSE;
		}
		if (shorter)
		{
			switch (T->bf)
			{
			case LH:
				
				if (T->lchild->bf == EH)
					shorter = FALSE;
				else
					shorter = TRUE;
				LeftBalance(T);     //��ƽ�⴦��   
				break;
			case EH:
				T->bf = LH;
				shorter = FALSE;
				break;
			case RH:
				T->bf = EH;
				shorter = TRUE;
				break;
			}
		}
	}
	return true;

}
Status InOrderTraverse(BSTree T, Status(*visit)(Info e))
{
	if (T)//T�ǿ�
	{
		
		InOrderTraverse(T->lchild, visit);
		if (!visit(T->data)) return FALSE;
		InOrderTraverse(T->rchild, visit);
	}
	return TRUE;
}
/*���ϵĻ�������*/
Status set_init(BSTree &T)
{
	return InitAVL(T);
}
Status set_destroy(BSTree &T)
{
	return DestroyAVL(T);
}
Status set_insert(BSTree &T, Info e)
{
	bool taller;
	return InsertAVL(T, e, taller);
}
Status set_remove(BSTree &T, int key)
{
	bool shorter;
	return DeleteAVL(T, key, shorter);
}
Status set_intersection(BSTree T1, BSTree T2, BSTree &T3)
{//����T2������Ԫ�أ���T1��Ҳ�У�����뵽T3��
	if (!T2 || !T1) return TRUE;//T1��T2Ϊ��
	if (set_member(T1, T2->data.id))
		set_insert(T3, T2->data);
	set_intersection(T1, T2->lchild, T3);//����T2��������
	set_intersection(T1, T2->rchild, T3);//����T2��������
	return TRUE;
}
Status set_union(BSTree &T1, BSTree T2)
{//��T2�е�Ԫ�ز���T1��
	if (!T2) return FALSE;//T2Ϊ��
	else
	{
		set_insert(T1, T2->data);
		set_union(T1, T2->lchild);//�ϲ�T2��������
		set_union(T1, T2->rchild);//�ϲ�T2��������
		return TRUE;
	}
}
Status set_difference(BSTree T1, BSTree T2, BSTree &T3)
{
	if (!T1) return FALSE;//T1Ϊ��,��T1-T2Ϊ��
	if (!set_member(T2, T1->data.id))
		set_insert(T3, T1->data);//������T1��������T2��Ԫ�ز��뵽T��
	set_difference(T1->lchild, T2, T3);//����T1��������
	set_difference(T1->rchild, T2, T3);//����T1��������
	return TRUE;
}
int set_size(BSTree T)
{
	if (!T) return 0;//TΪ��
	else
	{
		return 1 + set_size(T->lchild) + set_size(T->rchild);//TԪ�ظ���=1+������Ԫ�ظ���+������Ԫ�ظ���
	}
}
BSTNode * set_member(BSTree T, int key)
{//�ҵ����ؽڵ��ַ��δ�ҵ�����NULL
	return SearchAVL(T, key);
}
Status set_subset(BSTree T1, BSTree T2)
{//�ж�T2�Ƿ�ΪT1���Ӽ����Ƿ���TRUE���񷵻�FALSE
	if (T2 == NULL) return TRUE;//T2Ϊ�ռ�
	if (set_member(T1, T2->data.id))//T2���ڵ���T1��Ԫ��
	{
		if (!set_subset(T1, T2->lchild))//�ж�T2���������Ƿ�ΪT1���Ӽ�
			return FALSE;
		if (!set_subset(T1, T2->rchild))//�ж�T2���������Ƿ�ΪT1���Ӽ�
			return FALSE;
		return TRUE;
	}
	else return FALSE;//T2�ĸ���㲻��T1���Ӽ�
}
Status set_equal(BSTree T1, BSTree T2)
{//����T1=T2����1�����򷵻�0
	return set_subset(T1, T2) && set_subset(T2, T1);//T1 T2��Ϊ�Ӽ������
}
Status set_traverse(BSTree T, Status(*visit)(Info e))
{
	space = 0;
	if (T == NULL) { printf("����Ϊ��\n"); return FALSE; }
	else { InOrderTraverse(T, visit); return TRUE; }
}

/*������ʾ����*/
void menu1(void)
{
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("      ���ϲ�����ʾ \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. set_init        7. set_difference        13.set_intersection \n");
	printf("    	  2. set_destroy     8. set_subset            14.set_equal\n");
	printf("    	  3. set_insert      9. set_traverse          \n");
	printf("    	  4. set_remove      10.SaveSet\n"   );
	printf("    	  5. set_size        11.LoadSet\n");
	printf("    	  6. set_member      12.set_union\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~9]:");
}
void set_display(void)
{
	SqList L;
	L.pT = (SetData *)malloc(LIST_INIT_SIZE * sizeof(SetData));//���Ա����ɹ���LIST_INIT_SIZE����
	L.listsize = LIST_INIT_SIZE;
	L.listlenth = 0;

	int myop = 1, key;
	while (myop) {
		system("cls");
		menu1();
		scanf("%d", &myop);
		if (L.listlenth == 0 && (myop != 1 && myop != 11))
		{
			printf("���ϲ����ڣ����ȳ�ʼ������\n");
			getchar(); getchar();
			continue;
		}
		switch (myop) {
		case 1:
		{

			if (L.listlenth >= L.listsize)
			{
				printf("�ռ䲻�㣬�޷������¼���\n");
				break;
			}

			set_init(L.pT[L.listlenth].pRoot);//�����Ա��β��������
			printf("���뼯�ϵ�����:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("����%s�����ɹ���\n", L.pT[L.listlenth].name);
			L.listlenth++;//���Ա�ͬ������һ����

			getchar(); getchar();
			break;
		}
		case 2:
		{
			printf("��ѡ�����ٵļ���\n");
			int op = SelectSet(L);
			set_destroy(L.pT[op].pRoot);
			printf("����T���ٳɹ�\n");
			printf("����%s���ٳɹ���\n", L.pT[op].name);

			for (int i = op; i < L.listlenth - 1; i++)
			{
				L.pT[i] = L.pT[i + 1];
			}
			L.listlenth--;//���Ա�ͬ��ɾ��һ����
			getchar(); getchar();
			break;
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 3:
		{
			printf("��ѡ��Ҫ��ʼ���ļ���\n");
			int op = SelectSet(L);
			int N;
			Info a;
			printf("���������ݵ�����\n");
			scanf("%d", &N);
			while (N--)
			{
				scanf("%d", &a.id);
				set_insert(L.pT[op].pRoot, a);
			}
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 4:
		{
			printf("��ѡ����Ҫɾ��Ԫ�صļ���\n");
			int op = SelectSet(L);
			printf("����Ҫɾ��Ԫ�صĹؼ���\n");
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			putchar('\n');
			putchar('\n');
			scanf("%d", &key);
			putchar('\n'); putchar('\n');
			if (set_remove(L.pT[op].pRoot, key)) printf("ɾ���ɹ�\n");
			else printf("Ԫ�ز�����\n");
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 5:
		{
			printf("��ѡ����Ҫ��ʾ��С�ļ���\n");
			int op = SelectSet(L);
			printf("����%s��С%d\n", L.pT[op].name, set_size(L.pT[op].pRoot));
			getchar(); getchar();
			break;
		}
		case 6:
		{
			printf("��ѡ����Ҫ��ѯԪ�صļ���\n");
			int op = SelectSet(L);
			printf("����ؼ���\n");
			int key;
			scanf("%d", &key);
			if (set_member(L.pT[op].pRoot, key)) printf("%d�ڼ���%s��\n", key, L.pT[op].name);
			else
			{
				printf("%d���ڼ���%s��\n", key, L.pT[op].name);
			}
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 7:
		{
			printf("��ѡ���һ�����ϣ�������Ϊ��һ������ - �ڶ������ϣ�\n");
			int op1 = SelectSet(L);
			printf("��ѡ��ڶ�������");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//�����Ա��β��������
			printf("���뱣���������ļ��ϵ�����:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("����%s�����ɹ���\n", L.pT[L.listlenth].name);

			printf("����%s��", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//���¶�λ������µ�һ��

			printf("����%s��", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_difference(L.pT[op1].pRoot, L.pT[op2].pRoot, L.pT[L.listlenth].pRoot);//T1-T2
			printf("����%s-����%s��", L.pT[op1].name, L.pT[op2].name); 
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("�Ƿ񱣴����������ݣ�1.�� 0.��\n");
			int c;
			scanf("%d", &c);
			if (c == 0)
			{
				set_destroy(L.pT[L.listlenth].pRoot);
			}
			else L.listlenth++;
			getchar(); getchar();
			break;
		}
		case 8:
		{
			printf("��ѡ��ԭ���ϣ��ж��Ӽ����Ƿ�Ϊԭ���ϵ��Ӽ���\n");
			int op1 = SelectSet(L);
			printf("��ѡ���Ӽ���\n");
			int op2 = SelectSet(L);

			printf("����%s��", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//���¶�λ������µ�һ��

			printf("����%s��", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			if (set_subset(L.pT[op1].pRoot, L.pT[op2].pRoot))
			{
				printf("����%s�Ǽ���%s���Ӽ���\n", L.pT[op2].name, L.pT[op1].name);
			}
			else printf("����%s���Ǽ���%s���Ӽ���\n", L.pT[op2].name, L.pT[op1].name);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			printf("��ѡ����Ҫ�����ļ���\n");
			int op = SelectSet(L);
			set_traverse(L.pT[op].pRoot, visit);
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y() + 1);
			getchar(); getchar();
			break;
		}
		case 10:
		{
			SaveSetData(L);
			printf("���ݱ���ɹ�\n");
			getchar(); getchar();
			break;
		}
		case 11:
		{
			int c=1;
			if (L.listlenth)
			{
				printf("���¼������ݻᶪʧ��ǰ���ݣ��Ƿ������\n");
				printf("1.�� 0.��\n");
				scanf("%d", &c);
				if (c == 0)
				{
					printf("δ��������\n");
					getchar(); getchar();
					break;
				}
				else
				{
					for (int i = 0; i < L.listlenth; i++)
						set_destroy(L.pT[i].pRoot);//�������м��ϣ����¼���
					L.listlenth = 0;
				}
			}
			if (c == 0)
			{
				printf("δ��������\n");
				getchar(); getchar();
				break;
			}
			if (LoadSetData(L))
				printf("���ݼ��سɹ�\n");
			else printf("���ݼ���ʧ��\n");
			getchar(); getchar();
			break;
		}
		case 12:
		{
			printf("��ѡ���һ�����ϣ�������Ϊ��һ������ �� �ڶ������ϣ�\n");
			int op1 = SelectSet(L);
			printf("��ѡ��ڶ�������");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//�����Ա��β��������
			printf("���뱣���������ļ��ϵ�����:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("����%s�����ɹ���\n", L.pT[L.listlenth].name);

			printf("����%s��", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//���¶�λ������µ�һ��

			printf("����%s��", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_union(L.pT[L.listlenth].pRoot, L.pT[op1].pRoot);
			set_union(L.pT[L.listlenth].pRoot, L.pT[op2].pRoot);//����
			printf("����%s������%s��", L.pT[op1].name, L.pT[op2].name);
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("�Ƿ񱣴����������ݣ�1.�� 0.��\n");
			int c;
			scanf("%d", &c);
			if (c == 0)//������
			{
				set_destroy(L.pT[L.listlenth].pRoot);
			}
			else L.listlenth++;
			getchar(); getchar();
			break;
		}
		case 13:
		{
			printf("��ѡ���һ�����ϣ�������Ϊ��һ������ �� �ڶ������ϣ�\n");
			int op1 = SelectSet(L);
			printf("��ѡ��ڶ�������");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//�����Ա��β��������
			printf("���뱣���������ļ��ϵ�����:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("����%s�����ɹ���\n", L.pT[L.listlenth].name);

			printf("����%s��", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//���¶�λ������µ�һ��

			printf("����%s��", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_intersection(L.pT[op1].pRoot, L.pT[op2].pRoot, L.pT[L.listlenth].pRoot);//T1��T2
			printf("����%s�ɼ���%s��", L.pT[op1].name, L.pT[op2].name);
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("�Ƿ񱣴����������ݣ�1.�� 0.��\n");
			int c;
			scanf("%d", &c);
			if (c == 0)
			{
				set_destroy(L.pT[L.listlenth].pRoot);
			}
			else L.listlenth++;
			getchar(); getchar();
			break;
		}
		case 14:
		{
			printf("��ѡ���һ������(�жϵ�һ�������Ƿ�͵ڶ����������)\n");
			int op1 = SelectSet(L);
			printf("��ѡ��ڶ�������\n");
			int op2 = SelectSet(L);

			printf("����%s��", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//���¶�λ������µ�һ��

			printf("����%s��", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			if (set_equal(L.pT[op1].pRoot, L.pT[op2].pRoot))
			{
				printf("����%s = ����%s\n", L.pT[op1].name, L.pT[op2].name);
			}
			else printf("����%s != ����%s\n", L.pT[op1].name, L.pT[op2].name);
			getchar(); getchar();
			break;
		}
		case 0:
		{
			for (int i = 0; i < L.listlenth; i++)
				set_destroy(L.pT[i].pRoot);//�������м��ϣ����¼���
			free(L.pT);
			break;
		}
		}//end of switch
	}//end of while
}
void printKey(BSTree p, int x, int y)
{
	setxy(x, y);
	visit(p->data); //printf("(%d)", p->bf);
}
void graphAVL(BSTree T, int x, int l, int y)
{
	if (!T)  return; //TΪ��
	printKey(T, x, y);//�����
	if (T->lchild || T->rchild) { setxy(x, ++y); putchar('|'); }//������к��ӣ��ڸ����·���������ż�ͷ
	if (T->lchild)
	{//�����ӣ������������벿��
		setxy(x - l / 2 + 1, y);
		int i;
		for (i = 0; i < l / 2 - 1; i++)
			putchar('_');
	}
	if (T->rchild)
	{//���Һ��ӣ�����������Ұ벿��
		setxy(x + 1, y);
		int i;
		for (i = 0; i < l / 2 - 1; i++)
			putchar('_');
	}
	graphAVL(T->lchild, x - l / 2, l / 2, y + 1);//���������
	graphAVL(T->rchild, x + l / 2, l / 2, y + 1);//���������
}
int get_cursor_x(void)
{
	HANDLE     gh_std_out;
	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	return bInfo.dwCursorPosition.X;//���ص�ǰ���ĺ�����
}
int get_cursor_y(void)
{
	HANDLE     gh_std_out;
	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	return bInfo.dwCursorPosition.Y;//���ص�ǰ����������
}
void setxy(short x, short y)
{//����궨λ��(x,y)��
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
Status visit(Info e)
{
	printf("%d ", e.id);
	return TRUE;
}
int SelectSet(SqList L)
{
	int i, op;
	printf("��ѡ�񼯺�(1-%d)\n", L.listlenth);
	for (i = 1; i <= L.listlenth; i++)
	{
		printf("    	 %d. %s\n", i, L.pT[i - 1].name);
	}
	scanf("%d", &op);
	while (op < 1 || op > L.listlenth)
	{
		printf("�����������������\n");
		getchar(); getchar();
		scanf("%d", &op);
	}
	return op - 1;
}
Status SaveSetData(SqList L)
{
	FILE *fp;
	/*�������Ա���Ϣ*/
	if ((fp = fopen(L_DATA_NAME, "w")) == NULL)//���ļ�ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	fwrite(L.pT, sizeof(SetData), L.listlenth, fp);//���Ա�����һ����д�뵽�ļ���
	fclose(fp);
	/*�����������Ϣ*/
	fp = fopen(T_DATA_NAME, "w");
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		SaveSet(L.pT[i].pRoot, fp);
		fprintf(fp, " %d", FLAT);
		fputc('\n', fp);
	}
	fclose(fp);

	return TRUE;
}
Status SaveSet(BSTree T, FILE *fp)
{
	if (T)
	{
		SaveSet(T->lchild, fp);
		fprintf(fp, "%d ", T->data.id);
		SaveSet(T->rchild, fp);
	}
	return OK;
}
Status LoadSetData(SqList &L)
{
	/*д�����Ա�����*/
	FILE *fp;
	if ((fp = fopen(L_DATA_NAME, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}

	while (fread(&L.pT[L.listlenth], sizeof(SetData), 1, fp))
	{
		L.pT[L.listlenth].pRoot = NULL;
		L.listlenth++;//׼��д����һ������
	}
	fclose(fp);

	/*д�����������*/
	if ((fp = fopen(T_DATA_NAME, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		LoadSet(L.pT[i].pRoot, fp);
	}
	return TRUE;//д�����
}
Status LoadSet(BSTree &T, FILE *fp)
{
	Info temp;
	while (fscanf(fp, "%d", &temp.id) != EOF)
	{
		if (temp.id == FLAT) return TRUE;
		temp.fans = temp.follows = temp.friends = temp.hobby = NULL;
		set_insert(T, temp);
	}
	return TRUE;
}
/*�˼ʹ�ϵģ�⺯��*/
Status vis(Info e)
{
	printf("%-4d %-8s|", e.id, e.name); space++;//space���������ʽ��һ�����8����Ϣ
	if (space % 8 == 0) 
	{ 
		int x = get_cursor_x(); 
		putchar('\n'); 
		for (int i = 0; i < x; i++) putchar('-'); 
		putchar('\n'); 
	}
	return TRUE;
}
void menu2(void)
{
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("      �˼ʹ�ϵģ����ʾ \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. ����û�              2. ά���û���Ϣ \n");
	printf("    	  3. ��ѯ�û���Ϣ          4. ��ʾ��ͬ��ע\n");
	printf("    	  5. ��ʾ��ͬ����          6. ��ʾ��ͬ����\n");
	printf("    	  7. ��������              8. ��������\n");
	printf("    	  9. ��ʾ�����û�          10. ��ʾ���Ⱥ���\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~9]:");
}
void apply_display(void)
{
	BSTree Account, Hobby;//���û���������Ȥ��
	set_init(Account);
	set_init(Hobby);

	load_data(Account, Hobby);
	system("pause");
	int op = 1;
	

	while (op) {
		system("cls");
		menu2();
		scanf("%d", &op);
		switch (op) {
		case 1:
		{
			Info in;
			if (data_input(Account, in)) { set_insert(Account, in); printf("���û���ӳɹ�\n"); }
			else printf("���û����ʧ��\n");
	
			getchar(); getchar();
			break;
		}
		case 2:
		{
			maintain_data(Account,Hobby);
			getchar(); getchar();
			break;
		}
		case 3:
		{
			account_data(Account, Hobby);
			getchar(); getchar();
			break;
		}
		case 4:
		{
			common_follow(Account);
			getchar(); getchar();
			break;
		}
		case 5:
		{
			common_hobby(Account,Hobby);
			getchar(); getchar();
			break;
		}
		case 6:
		{
			common_friend(Account);
			getchar(); getchar();
			break;
		}
		case 7:
		{
			load_data(Account,Hobby);
			getchar(); getchar();
			break;
		}
		case 8:
		{
			save_data(Account,Hobby);
			proc();
			getchar(); getchar();
			break;
		}
		case 9:
		{
			printf("�û���\n");
			set_traverse(Account, vis);
			putchar('\n');
			/*printf("���ã�\n");
			set_traverse(Hobby, vis);*/
			getchar(); getchar();
			break;
		}
		case 10:
		{
			second_friend(Account);
			getchar(); getchar();
			break;
		}
		case 0:
			if (confirm_save()) { save_data(Account, Hobby); proc(); }
			destroy_accountset(Account);
			set_destroy(Hobby);
			getchar(); getchar();
			break;
		}//end of switch
	}//end of while
}
void common_follow(BSTree Account)
{
	int id1, id2;
	printf("��ֱ�������λ�û�id��\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("�û�������\n");
	else {
		BSTree common_follows;
		set_init(common_follows);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//��λ��λ�û�
		set_intersection(p1->data.follows, p2->data.follows, common_follows);//��λ�û���ע�˼��Ľ���
		printf("\"%s\"��\"%s\"�Ĺ�ͬ��ע:\n", p1->data.name, p2->data.name);
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Account, common_follows);
		set_destroy(common_follows);
		
		{
			printf("\n\n\n");
			system("pause");
			printf("\"%s\"��ע��:\n", p1->data.name);
			space = 0;
			print_account_data(Account, p1->data.follows);
			printf("\n\n\"%s\"��ע��:\n", p2->data.name);
			space = 0;
			print_account_data(Account, p2->data.follows);
		}
	}
}
void common_friend(BSTree Account)
{
	int id1, id2;
	printf("��ֱ�������λ�û�id��\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("�û�������\n");
	else 
	{
		BSTree common_friend;
		set_init(common_friend);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//��λ��λ�û�
		set_intersection(p1->data.friends, p2->data.friends, common_friend);//��λ�û����Ѽ��Ľ���
		//set_traverse(common_friend, visit);
		printf("\"%s\"��\"%s\"�Ĺ�ͬ����:\n", p1->data.name, p2->data.name);
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Account, common_friend);
		set_destroy(common_friend);
		{
			printf("\n\n\n"); system("pause");
			printf("\n\n\n");
			printf("\"%s\"����:\n", p1->data.name);
			space = 0;
			print_account_data(Account, p1->data.friends);
			
			printf("\n\n\"%s\"����:\n", p2->data.name);
			space = 0;
			print_account_data(Account, p2->data.friends);
		}
	}
}
void common_hobby(BSTree Account,BSTree Hobby)
{
	int id1, id2;
	printf("��ֱ�������λ�û�id��\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("�û�������\n");
	else
	{
		BSTree common_hobby;
		set_init(common_hobby);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//��λ��λ�û�
		set_intersection(p1->data.hobby, p2->data.hobby, common_hobby);
		printf("\"%s\"��\"%s\"�Ĺ�ͬ����:\n", p1->data.name, p2->data.name);//��λ�û����ü��Ľ���
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Hobby, common_hobby);
		set_destroy(common_hobby);
		{
			printf("\n\n\n"); system("pause");
			printf("\"%s\"����:\n", p1->data.name);
			space = 0;
			print_account_data(Hobby, p1->data.hobby);
			printf("\n\n\"%s\"����:\n", p2->data.name);
			space = 0;
			print_account_data(Hobby, p2->data.hobby);
		}
	}
}
void second_friend(BSTree Account)
{
	int id;
	printf("�������û�id\n");
	scanf("%d", &id);
	BSTree p; BSTree T = NULL;
	p = set_member(Account, id);
	if (!p)
	{
		printf("�û�������\n"); return;
	}
	
	int op = 1;
	while (op)
	{
		system("cls");
		printf("%s\n", p->data.name);
		printf("1. ��ѯ\"%s\"����ĳ�����ѵĶ��Ⱥ���		2.��ѯ\"%s\"���ж��Ⱥ���\n", p->data.name, p->data.name);
		printf("0. �˳�\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
		{
			int friend_id;
			printf("\"%s\"�ĺ���:\n", p->data.name);
			space = 0;
			print_account_data(Account, p->data.friends);
			printf("\n�������û�����id\n");
			scanf("%d", &friend_id);
			while(!set_member(p->data.friends, friend_id))
			{
				printf("���Ѳ����ڣ�����������\n");
				scanf("%d", &friend_id);
			}
			BSTree pfriend; BSTree T = NULL;
			pfriend = set_member(Account, friend_id);
			set_difference(pfriend->data.friends, p->data.friends, T);//����Ⱥ���
			set_remove(T, id);//���Ⱥ��ѳ�ȥ�Լ�
			space = 0;
			print_account_data(Account, T);
			set_destroy(T);//���ټ���
			getchar(); getchar(); break;

		}
		case 2:
		{
			S_friend(Account, p->data.friends, T);//��ú��ѵĺ���
			BSTree T1 = NULL;
			set_difference(T, p->data.friends, T1);//���Ⱥ����г�ȥ�Լ��ĺ���
			set_remove(T1, p->data.id);//���Ⱥ����г�ȥ�Լ�
			space = 0;
			printf("\"%s\"�Ķ��Ⱥ���:��%dλ��\n", p->data.name, set_size(T1));//��λ�û����ü��Ľ���

			print_account_data(Account, T1);//������Ⱥ���
			set_destroy(T); set_destroy(T1);//���ټ���
			getchar(); getchar(); break;
		}
		default: break;
		}
	}
}
void S_friend(BSTree Account,BSTree p,BSTree &T)
{//pΪĳ���û��ĺ��Ѽ�������û����ѵĺ��ѵĲ�����T��
	if (p)
	{
		BSTree p_friend = set_member(Account, p->data.id);//��λ���ѽڵ�
		set_union(T, p_friend->data.friends);//��Ӹú��ѵĺ�����T��
		S_friend(Account, p->lchild, T);//���������в��Ҳ���Ӷ��Ⱥ���
		S_friend(Account, p->rchild, T);//���������в��Ҳ���Ӷ��Ⱥ���
	}
	
}
Status destroy_accountset(BSTree &T)
{
	if (T)
	{
		destroy_accountset(T->lchild);
		destroy_accountset(T->rchild);
		set_destroy(T->data.fans); set_destroy(T->data.follows); set_destroy(T->data.friends); set_destroy(T->data.hobby);//���ٸ��˹�ϵ��
		free(T);//�ͷŽڵ�
		T = NULL;
	}
	return TRUE;
}
Status data_input(BSTree T, Info &in)
{
	Info temp;
	printf("���������û�id:\n");
	scanf("%d", &temp.id);
	while (set_member(T, temp.id)) { printf("�û�%d�Ѵ��ڣ�����������(����0�˳�)\n", temp.id); scanf("%d", &temp.id); if (temp.id== 0 )return FALSE; }
	printf("�������û�����:\n");
	scanf("%s", &temp.name);
	temp.follows = temp.friends = temp.fans = temp.hobby = NULL;//���û��޷�˿���ѵ���Ϣ
	if (confirm_save()) { in = temp; return TRUE; }
	else return FALSE;
}
int confirm_save(void)
{
	printf("�Ƿ񱣴�?\n");
	printf("1.��  0.��\n");
	int c;
	scanf("%d", &c);
	while (c != 0 && c != 1)
	{
		printf("�����������������\n");
		scanf("%d", &c);
	}
	return c;
}
int select_display(void)
{
	printf("��ѡ����ʾ���ܣ�\n");
	printf("1.���ϲ�����ʾ  2.�˼ʹ�ϵģ����ʾ\n");
	printf("3.AVL����ʾ		0.�˳�ϵͳ\n");
	int c;
	scanf("%d", &c);
	getchar();
	while (c != 1 && c != 2 && c != 0&&c!=3)
	{
		printf("�����������������\n");
		scanf("%d", &c);
		getchar();
	}
	return c;
}
void maintain_data(BSTree &Account,BSTree Hobby)
{
	int id;
	printf("�������û�id\n");
	scanf("%d", &id);
	BSTNode *pt;
	pt = set_member(Account, id);
	if (!pt)
	{
		printf("�û�������\n");
	}
	else
	{
		int op = 1;
		while (op)
		{
			system("cls");
			printf("��ѡ��ά���û�\"%s\"������\n", pt->data.name);
			printf("    	  1. ά���û����Ѽ�              2. ά���û���ע�˼� \n");
			printf("    	  3. ά���û����ü�              4. �Ƴ��û���˿\n");
			printf("    	  5. �޸��û�����\n");
			printf("    	  0. �˳�ά��\n");

			scanf("%d", &op);
			switch (op)
			{
			case 1:
			{
				int o;
				printf("�û�\"%s\"������\n", pt->data.name);
				space = 0; print_account_data(Account, pt->data.friends);
				printf("\n��ѡ�����:\n");
				printf("    	  1. �������              2. ɾ������ \n");
				printf("    	  0. �˳� \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_friend;
					printf("������������id\n");
					scanf("%d", &new_friend.id);
					if (!set_member(Account, new_friend.id)) printf("�û�%d������\n", new_friend.id);
					else
					{
						if (set_insert(pt->data.friends, new_friend))//���뵽�û�*pt�����Ѽ���
						{
							BSTNode *p = set_member(Account, new_friend.id);
							set_insert(p->data.friends, pt->data);//�������໥��
							
							printf("��ӳɹ�\n");
						}
						else printf("�û�%d�Ѿ���%s������", new_friend.id, pt->data.name);//Ԫ�ز���ʧ��
					}
				}
				else if (o == 2)
				{
					int friend_id;
					printf("������Ҫɾ��������id\n");
					scanf("%d", &friend_id);
					if (set_member(pt->data.friends, friend_id)) 
					{ 
						set_remove(pt->data.friends, friend_id);
						BSTNode *p = set_member(Account, friend_id);
						set_remove(p->data.friends, id);//�Ƴ��������໥��
						printf("ɾ���ɹ�\n"); 
					}
					else printf("%d����\"%s\"������\n", friend_id, pt->data.name);
				}
				getchar(); getchar();
				break;
			}
			case 2:
			{
				int o;
				printf("\"%s\"�Ĺ�ע��:\n", pt->data.name); 
				space = 0; print_account_data(Account, pt->data.follows);
				printf("\n��ѡ�����:\n");
				printf("    	  1. ��ӹ�ע��              2. �Ƴ���ע�� \n");
				printf("    	  0. �˳� \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_follow;
					printf("�������¹�ע��id\n");
					scanf("%d", &new_follow.id);
					if (!set_member(Account, new_follow.id)) printf("�û�%d������\n", new_follow.id);
					else
					{
						if (set_insert(pt->data.follows, new_follow))
						{//Ϊ��ע����ӷ�˿
							printf("��ӳɹ�\n");
							BSTNode *p;
							Info new_fan;
							new_fan.id = id;
							p = set_member(Account, new_follow.id);//pָ���¹�ע��
							set_insert(p->data.fans, new_fan);//��ӷ�˿
						}
						else printf("�û�%d�Ѿ���\"%s\"�Ĺ�ע��\n", new_follow.id, pt->data.name);
					}
				}
				else if (o == 2)
				{
					int follow_id;
					printf("������Ҫɾ���Ĺ�ע��id\n");
					scanf("%d", &follow_id);
					if (set_member(pt->data.follows, follow_id))
					{
						set_remove(pt->data.follows, follow_id); //�Ƴ���ע��
						set_remove(set_member(Account, follow_id)->data.fans, id); //�Ƴ�����ע�˵ķ�˿
						printf("ɾ���ɹ�\n");
					}
					else printf("��ע��%d������\n", follow_id);
				}
				getchar(); getchar();
				break;
			}
			case 3:
			{
				int o;
				printf("\"%s\"�İ���:\n", pt->data.name);
				space = 0; print_account_data(Hobby, pt->data.hobby);
				printf("\n��ѡ�����:\n");
				printf("    	  1. ��Ӱ���              2. �Ƴ����� \n");
				printf("    	  0. �˳� \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_hobby;
					printf("�������°���id\n");
					space = 0; set_traverse(Hobby, vis); putchar('\n');
					scanf("%d", &new_hobby.id);
					if (!set_member(Hobby, new_hobby.id)) printf("����%d������\n", new_hobby.id);
					else
					{
						if (set_insert(pt->data.hobby, new_hobby))//���뵽�û�*pt�İ��ü���
							printf("��ӳɹ�\n");
						else printf("����%d�Ѵ���\n", new_hobby.id);
					}
				}
				else if (o == 2)
				{
					int hobby_id;
					printf("������Ҫɾ���İ���id\n");
					scanf("%d", &hobby_id);
					if (set_member(pt->data.hobby, hobby_id)) { set_remove(pt->data.hobby, hobby_id); printf("�����Ƴ��ɹ�\n"); }
					else printf("%d����\"%s\"�İ���\n", hobby_id, pt->data.name);
				}
				getchar(); getchar();
				break;
			}
			case 4:
			{
				printf("\"%s\"�ķ�˿:\n", pt->data.name);
				space = 0; print_account_data(Account, pt->data.fans);
				putchar('\n');
				int fan_id;
				printf("������Ҫɾ���ķ�˿id\n");
				scanf("%d", &fan_id);
				if (set_member(pt->data.fans, fan_id)) { set_remove(pt->data.fans, fan_id); printf("��˿�Ƴ��ɹ�\n"); }
				else printf("%d����\"%s\"�ķ�˿\n", fan_id, pt->data.name);
				getchar(); getchar();
				break;
			}
			case 5:
			{
				printf("�������µ�����\n");
				char new_name[20];
				scanf("%s", new_name);
				strcpy(pt->data.name, new_name);
				printf("�����޸ĳɹ�.\n");
				getchar(); getchar();
				break;
			}
			default:
				break;
			}
		}
	}

}
Status save_account(BSTree T, FILE *fp)
{
	if (T)//T�ǿ�
	{
		
		save_account(T->lchild, fp);
		fprintf(fp, "%d %s\n", T->data.id, T->data.name);
		save_account(T->rchild, fp);
	}
	return TRUE;
}
Status save_hobby(BSTree T, FILE *fp)
{
	if (T)//T�ǿ�
	{
		
		save_hobby(T->lchild, fp);
		fprintf(fp, "%d %s\n", T->data.id, T->data.name);
		save_hobby(T->rchild, fp);
	}
	return TRUE;
}
Status save_relation(BSTree T, FILE *fp)
{
	if (T)
	{
		save_relation(T->lchild, fp);//������������Ϣ
		fprintf(fp, "%d\n", T->data.id);//����ڵ�id
		save_rela(T->data.fans, fp); fprintf(fp, " 0\n");
		save_rela(T->data.follows, fp); fprintf(fp, " 0\n");
		save_rela(T->data.friends, fp); fprintf(fp, " 0\n");
		save_rela(T->data.hobby, fp); fprintf(fp, " 0\n\n");//�洢�ڵ�Ĺ�ϵ��Ϣ,��0��Ϊ�������
		save_relation(T->rchild, fp);//������������Ϣ
	}
	return TRUE;
}
Status save_rela(BSTree T, FILE *fp)
{
	if (T)
	{
		
		save_rela(T->lchild, fp);
		fprintf(fp, "%d ", T->data.id);
		save_rela(T->rchild, fp);
	}
	return TRUE;
}
Status load_account(BSTree &T, FILE *fp)
{
	Info temp;
	while (fscanf(fp, "%d %s", &temp.id, temp.name) != EOF)
	{
		temp.fans = temp.follows = temp.friends = temp.hobby = NULL;
		set_insert(T, temp);
	}
	return TRUE;
}
Status load_hobby(BSTree &Hobby, FILE *fp)
{
	Info temp;
	while (fscanf(fp,"%d %s",&temp.id,temp.name)!=EOF)
	{
		set_insert(Hobby, temp);
	}
	return TRUE;
}
Status load_relation(BSTree &T, FILE *fp)
{
	Info temp;
	BSTNode *pt;
	int id1,id2;
	while (fscanf(fp, " %d", &id1)!=EOF)//��ȡһ���û�
	{
		pt = set_member(T, id1);
		fscanf(fp,"%d", &id2);
		while (id2 != 0)//�����û���˿��
		{
			temp.id = id2;
			set_insert(pt->data.fans, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp, "%d", &id2);
		while (id2 != 0)//�����û���ע�˼�
		{
			temp.id = id2;
			set_insert(pt->data.follows, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp, "%d", &id2);
		while (id2 != 0)//�����û����Ѽ�
		{
			temp.id = id2;

			set_insert(pt->data.friends, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp,"%d", &id2);
		while (id2 != 0)//�����û���Ȥ��
		{
			temp.id = id2;
			set_insert(pt->data.hobby, temp);
			fscanf(fp, "%d", &id2);
		}
		
	}
	return TRUE;
}
Status load_data(BSTree &Account,BSTree &Hobby)
{
	
	FILE *fp;
	fp = fopen(ACCOUNTDATA, "rb");
	if (!fp) { printf("�˻����ݼ���ʧ��\n"); }//�ļ���ʧ��
	else {
		destroy_accountset(Account);//�����Ѵ��ڵļ��ϣ����¼���
		load_account(Account, fp);
		printf("�˻����ݼ��سɹ�\n");
		fclose(fp);

		fp = fopen(RELATIONDATA, "r");
		if (!fp) { printf("��ϵ���ݼ���ʧ��\n"); }
		else {
			
			load_relation(Account, fp);
			fclose(fp);
			printf("��ϵ���ݼ��سɹ�\n");
		}
	}
	
	fp = fopen(HOBBYDATA, "r");
	if (!fp) { printf("��Ȥ���ݼ���ʧ��\n"); }//�ļ���ʧ��
	else {
		set_destroy(Hobby);
		load_hobby(Hobby, fp);
		printf("��Ȥ���ݼ��سɹ�\n");
		fclose(fp);
	}
	proc();
	return TRUE;
}
Status save_data(BSTree Account,BSTree Hobby)
{
	FILE *fp;
	fp = fopen(ACCOUNTDATA, "wb");
	save_account(Account, fp);
	fclose(fp);

	fp = fopen(HOBBYDATA, "w");
	save_hobby(Hobby,fp);
	fclose(fp);

	fp = fopen(RELATIONDATA, "w");
	save_relation(Account, fp);
	fclose(fp);
	printf("���ݱ���ɹ�\n");

	return TRUE;
}
void account_data(BSTree Account, BSTree Hobby)
{
	system("cls");
	int id;
	printf("�������ѯ���û�id������0�˳���ѯ��\n");
	scanf("%d", &id);
	while (id)
	{
		BSTNode *T = set_member(Account, id);//��λ�û�
		if (!T) printf("�û�%d������\n", id);
		else
		{
			int op = 1;
			while (op!=5)
			{
				system("cls");
				printf("---------------------%d %s--------------------\n", T->data.id, T->data.name);
				printf("1. ���Ѽ�			2.��ע�˼�\n"); 
				printf("3. ��˿��			4.���ü�\n");
				printf("5. ����ѡ���ѯ�û�		0.�˳���ѯ\n");

				scanf("%d", &op);
				if (op == 0)return;
				switch (op)
				{
				case 1:
				{
					printf("%d \"%s\"�����ѣ���%dλ��\n", T->data.id,T->data.name, set_size(T->data.friends)); space = 0;
					print_account_data(Account, T->data.friends); space = 0; putchar('\n');//���������ʽ

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;

				}
				case 2:
				{
					printf("%d \"%s\"�Ĺ�ע�ˣ���%dλ��\n", T->data.id, T->data.name, set_size(T->data.follows));
					print_account_data(Account, T->data.follows); space = 0; putchar('\n');

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;
				}
				case 3:
				{
					printf("%d \"%s\"�ķ�˿����%dλ��\n", T->data.id, T->data.name, set_size(T->data.fans));
					print_account_data(Account, T->data.fans); space = 0; putchar('\n');

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;
				}

				case 4:
				{
					printf("%d \"%s\"�İ��ã���%d����\n", T->data.id, T->data.name, set_size(T->data.hobby));
					print_account_data(Hobby, T->data.hobby); space = 0; putchar('\n');
					putchar('\n'); putchar('\n');
					getchar(); getchar();
					break;
				}
				default:
					break;
				}

			}
		}
		printf("�����������û�id:(����0�˳���ѯ)");
		scanf("%d", &id);
		printf("�л��ɹ�\n");
	}
}
void print_account_data(BSTree Account,BSTree T)
{
	if (T)
	{
		print_account_data(Account, T->lchild);
		BSTree p = set_member(Account, T->data.id);
		if(p)
			vis(p->data);
		print_account_data(Account, T->rchild);
	}
}
void proc(void)
{
	char buf[103];
	memset(buf, ' ', sizeof(buf));
	buf[0] = '[';
	buf[101] = ']';
	buf[102] = '\0';
	int i = 0;
	char index[6] = "-\\|/\0";
	while (i <= 100)
	{
		buf[i] = '=';
		printf("%s [%d%%][%c]\r", buf, i, index[i % 4]);
		fflush(stdout);//ˢ�»�����  
		Sleep(5);
		i++;
	}

	printf("\n");
}

void menu3(void)
{
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("      AVL��������ʾ \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. InitAVL         5. SearchAVL\n");
	printf("    	  2. InsertAVL       6. TraverseAVL\n");
	printf("    	  3. DestroyAVL    \n");
	printf("    	  4. DeleteAVL\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~6]:");
}
void AVL_display(void)
{
	BSTree T;
	InitAVL(T);
	int op = 1, key;
	while (op) {
		system("cls");
		menu3();
		scanf("%d", &op);
		switch (op) {
		case 1:
		{
			set_init(T);
			printf("AVL��T��ʼ���ɹ�\n");
			
			getchar(); getchar();
			break;
		}
		case 2:
		{
			int N;
			Info a;
			bool taller;
			printf("���������ݵ�����\n");
			scanf("%d", &N);
			while (N--)
			{
				scanf("%d", &a.id);
				InsertAVL(T, a,taller);
			}
			graphAVL(T, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 3:
		{
			DestroyAVL(T);
			printf("AVL�����ٳɹ�\n");
			getchar(); getchar();
			break;
		}
		case 4:
		{
			bool shorter;
			graphAVL(T, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 2);
			printf("����Ҫɾ���Ľڵ�\n");
			scanf("%d", &key);
			if (DeleteAVL(T, key,shorter)) printf("ɾ���ɹ�\n");
			else printf("�ڵ㲻����\n");
			graphAVL(T, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 5:
		{
			printf("������ڵ�\n");
			int key;
			scanf("%d", &key);
			if (SearchAVL(T, key)) printf("%d�ڵ�������", key);
			else printf("�ڵ㲻����\n");
			graphAVL(T, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 6:
		{
			InOrderTraverse(T, visit);
			graphAVL(T, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}

		case 0:
			set_destroy(T);//�˳�ǰ���ټ���T
			break;
		}//end of switch
	}//end of while
}