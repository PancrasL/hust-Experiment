#include"head.h"
int space;//调整输出格式

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
	printf("欢迎下次使用\n");
	getchar();
	return 0;

}//end of main()

/*AVL树旋转操作*/
void L_Rotate(BSTree &p) {
	//对以*p为根的二叉排序树作左旋处理，处理之后p指向新的数根节点，即旋转处理之前的右子树的根节点
	BSTNode *rc=NULL;
	rc = p->rchild;//rc指向*p的右孩子
	p->rchild = rc->lchild;//rc的左子树挂接为*p的右子树
	rc->lchild = p; p = rc;//p指向新的根节点
}
void R_Rotate(BSTree &p) 
{//类似于L_Rotate
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
		case LH:                    //LL旋转   
			T->bf = EH;
			lc->bf = EH;
			R_Rotate(T);
			break;

		case EH:                    //deleteAVL需要，insertAVL用不着   
			T->bf = LH;
			lc->bf = RH;
			R_Rotate(T);
			break;

		case RH:                    //LR旋转   
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
			L_Rotate(T->lchild);//不能写L_Rotate(lc);采用的是引用参数   
			R_Rotate(T);
			break;
		}
	}
}
void RightBalance(BSTree &T)
{
	//对以二叉树T作右平衡处理，并使T指向新的根节点
	BSTNode* rc = NULL;
	BSTNode *ld = NULL;

	rc = T->rchild;
	switch (rc->bf)
	{
	case LH:                //RL旋转   
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

	case RH:                //RR旋转   
		T->bf = EH;
		rc->bf = EH;
		L_Rotate(T);
		break;
	}
}
/*AVL树的基本运算*/
Status InitAVL(BSTree &T)
{
	T = NULL;
	return TRUE;
}
Status InsertAVL(BSTree &T, Info e, bool &taller) 
{
	//若T不存在与e有相同关键字的节点，插入e，返回1，否则返回0
	//若插入e后二叉排序树失去平衡，作平衡化处理，taller反应T长高与否

	if (!T) {//插入新节点，树长高，taller为TRUE
		T = (BSTNode *)malloc(sizeof(BSTNode)); T->data = e;
		T->rchild = T->lchild = NULL; T->bf = EH; taller = TRUE;
	}
	else
	{
		if (e.id == T->data.id)//树中已存在和e有相同关键字的结点
		{
			taller = FALSE; return 0;//不再插入
		}
		if (e.id < T->data.id)//在T的左子树中搜索
		{
			if (!InsertAVL(T->lchild, e, taller)) return 0;//未插入
			if (taller)//已插入到*T的左子树中且左子树长高
				switch (T->bf)//检查*T的平衡度
				{
				case LH://原本左子树比右子树高，需要作左平衡处理
					LeftBalance(T); taller = FALSE; break;//
				case EH://原本左右子树等高，现因左子树增高而使树增高
					T->bf = LH; taller = TRUE; break;
				case RH://原本右子树比左子树高，现左右子树等高
					T->bf = EH; taller = FALSE; break;
				}
		}
		else//在T的右子树中搜索
		{
			if (!InsertAVL(T->rchild, e, taller)) return 0;//未插入
			if (taller)//已插入到*T的右子树中且右子树长高
				switch (T->bf)//检查*T的平衡度
				{
				case LH://原本左子树比右子树高，现左右子树等高
					T->bf = EH; taller = FALSE; break;
				case EH://原本左右子树等高，现因右子树增高而使树增高
					T->bf = RH; taller = TRUE; break;
				case RH://原本右子树比左子树高，需要作右平衡处理
					RightBalance(T); taller = FALSE; break;
				}
		}
	}
	return TRUE;
}
Status DestroyAVL(BSTree &T)
{//销毁AVL树T
	if (!T) return FALSE;//树为空
	else 
	{
		DestroyAVL(T->lchild);//销毁左子树
		DestroyAVL(T->rchild);//销毁右子树
		free(T);//释放节点
		T = NULL;//根节点指针置空
		return TRUE;
	}
}
BSTNode * SearchAVL(BSTree& T, int key)
{//在AVL树T中查找关键字为key的节点，找到返回其地址，否者返回NULL
	if ((T == NULL) || (key == T->data.id))
		return T;
	else if (key<(T->data.id))//在左子树中继续查找
		return SearchAVL(T->lchild, key);
	else
		return SearchAVL(T->rchild, key);//在右子树中继续查找
}
Status DeleteAVL(BSTree& T, int key, bool& shorter)
{
	//若在平衡的二叉排序树t中存在和e有相同关键字的结点，则删除之
	//并返回true，否则返回false。若因删除而使二叉排序树
	//失去平衡，则作平衡旋转处理，布尔变量shorter反映t变矮与否
	if (T == NULL)//不存在该元素   
	{
		return FALSE;//删除失败   
	}
	else if (key == T->data.id)//找到元素结点  
	{
		BSTNode * q = NULL;
		if (T->lchild == NULL)//左子树为空,令T指向要删除结点的右子树，然后删除该结点(包含左右子树都为空的情况)
		{
			q = T;
			T = T->rchild;
			free(q);
			shorter = TRUE;
		}
		else if (T->rchild == NULL)//右子树为空，令T指向要删除结点的左子树，然后删除该结点   
		{
			q = T;
			T = T->lchild;
			free(q);
			shorter = TRUE;
		}
		else//左右子树都存在,交换结点数据后删除结点
		{

			q = T->lchild;
			while (q->rchild)
			{
				q = q->rchild;
			}//q定位到要删除结点的左子树的最右子树根节点
			T->data = q->data;//将q的数据置换到T结点
							  //graphAVL(T, X0, X0, get_cursor_y());
			DeleteAVL(T->lchild, q->data.id, shorter);//在左子树中递归删除q结点  
			if (shorter)
			{
				switch (T->bf)
				{
				case LH://原来左高，现左变矮，故等高
					T->bf = EH;
					shorter = TRUE;
					break;
				case EH://原等高，现左变矮，故右高
					T->bf = RH;
					shorter = FALSE;
					break;
				case RH://原右高，现左矮，故右更高，不平衡，需进行右平衡调节

					if (T->rchild->bf == EH)
						shorter = FALSE;
					else
						shorter = TRUE;
					RightBalance(T);    //右平衡处理
					break;
				}
			}
		}
	}
	else if (key < T->data.id)//左子树中继续查找   
	{
		if (!DeleteAVL(T->lchild, key, shorter))//删除失败
		{
			return FALSE;
		}
		if (shorter)//左子树变矮，调节T平衡因子
		{
			switch (T->bf)
			{
			case LH://原来左高，现左变矮，故等高
				T->bf = EH;
				shorter = TRUE;
				break;
			case EH://原等高，现左变矮，故右高
				T->bf = RH;
				shorter = FALSE;
				break;
			case RH://原右高，现左矮，故右更高，不平衡，需进行右平衡调节
				
				if (T->rchild->bf == EH)
					shorter = FALSE;
				else
					shorter = TRUE;
				RightBalance(T);    //右平衡处理
				break;
			}
		}
	}
	else                                //在右子树中继续查找，操作同左子树
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
				LeftBalance(T);     //左平衡处理   
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
	if (T)//T非空
	{
		
		InOrderTraverse(T->lchild, visit);
		if (!visit(T->data)) return FALSE;
		InOrderTraverse(T->rchild, visit);
	}
	return TRUE;
}
/*集合的基本运算*/
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
{//遍历T2中所有元素，若T1中也有，则插入到T3中
	if (!T2 || !T1) return TRUE;//T1或T2为空
	if (set_member(T1, T2->data.id))
		set_insert(T3, T2->data);
	set_intersection(T1, T2->lchild, T3);//遍历T2的左子树
	set_intersection(T1, T2->rchild, T3);//遍历T2的右子树
	return TRUE;
}
Status set_union(BSTree &T1, BSTree T2)
{//将T2中的元素并到T1中
	if (!T2) return FALSE;//T2为空
	else
	{
		set_insert(T1, T2->data);
		set_union(T1, T2->lchild);//合并T2的左子树
		set_union(T1, T2->rchild);//合并T2的右子树
		return TRUE;
	}
}
Status set_difference(BSTree T1, BSTree T2, BSTree &T3)
{
	if (!T1) return FALSE;//T1为空,则T1-T2为空
	if (!set_member(T2, T1->data.id))
		set_insert(T3, T1->data);//将属于T1，不属于T2的元素插入到T中
	set_difference(T1->lchild, T2, T3);//遍历T1的左子树
	set_difference(T1->rchild, T2, T3);//遍历T1的右子树
	return TRUE;
}
int set_size(BSTree T)
{
	if (!T) return 0;//T为空
	else
	{
		return 1 + set_size(T->lchild) + set_size(T->rchild);//T元素个数=1+左子树元素个数+右子树元素个数
	}
}
BSTNode * set_member(BSTree T, int key)
{//找到返回节点地址，未找到返回NULL
	return SearchAVL(T, key);
}
Status set_subset(BSTree T1, BSTree T2)
{//判断T2是否为T1的子集，是返回TRUE，否返回FALSE
	if (T2 == NULL) return TRUE;//T2为空集
	if (set_member(T1, T2->data.id))//T2根节点是T1的元素
	{
		if (!set_subset(T1, T2->lchild))//判断T2的左子树是否为T1的子集
			return FALSE;
		if (!set_subset(T1, T2->rchild))//判断T2的右子树是否为T1的子集
			return FALSE;
		return TRUE;
	}
	else return FALSE;//T2的根结点不是T1的子集
}
Status set_equal(BSTree T1, BSTree T2)
{//集合T1=T2返回1，否则返回0
	return set_subset(T1, T2) && set_subset(T2, T1);//T1 T2互为子集则相等
}
Status set_traverse(BSTree T, Status(*visit)(Info e))
{
	space = 0;
	if (T == NULL) { printf("集合为空\n"); return FALSE; }
	else { InOrderTraverse(T, visit); return TRUE; }
}

/*集合演示函数*/
void menu1(void)
{
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("      集合操作演示 \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. set_init        7. set_difference        13.set_intersection \n");
	printf("    	  2. set_destroy     8. set_subset            14.set_equal\n");
	printf("    	  3. set_insert      9. set_traverse          \n");
	printf("    	  4. set_remove      10.SaveSet\n"   );
	printf("    	  5. set_size        11.LoadSet\n");
	printf("    	  6. set_member      12.set_union\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    请选择你的操作[0~9]:");
}
void set_display(void)
{
	SqList L;
	L.pT = (SetData *)malloc(LIST_INIT_SIZE * sizeof(SetData));//线性表最多可管理LIST_INIT_SIZE棵树
	L.listsize = LIST_INIT_SIZE;
	L.listlenth = 0;

	int myop = 1, key;
	while (myop) {
		system("cls");
		menu1();
		scanf("%d", &myop);
		if (L.listlenth == 0 && (myop != 1 && myop != 11))
		{
			printf("集合不存在，请先初始化集合\n");
			getchar(); getchar();
			continue;
		}
		switch (myop) {
		case 1:
		{

			if (L.listlenth >= L.listsize)
			{
				printf("空间不足，无法创建新集合\n");
				break;
			}

			set_init(L.pT[L.listlenth].pRoot);//在线性表表尾创建集合
			printf("输入集合的名称:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("集合%s创建成功！\n", L.pT[L.listlenth].name);
			L.listlenth++;//线性表同步创建一集合

			getchar(); getchar();
			break;
		}
		case 2:
		{
			printf("请选择销毁的集合\n");
			int op = SelectSet(L);
			set_destroy(L.pT[op].pRoot);
			printf("集合T销毁成功\n");
			printf("集合%s销毁成功！\n", L.pT[op].name);

			for (int i = op; i < L.listlenth - 1; i++)
			{
				L.pT[i] = L.pT[i + 1];
			}
			L.listlenth--;//线性表同步删除一棵树
			getchar(); getchar();
			break;
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 3:
		{
			printf("请选择要初始化的集合\n");
			int op = SelectSet(L);
			int N;
			Info a;
			printf("请输入数据的组数\n");
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
			printf("请选择需要删除元素的集合\n");
			int op = SelectSet(L);
			printf("输入要删除元素的关键字\n");
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			putchar('\n');
			putchar('\n');
			scanf("%d", &key);
			putchar('\n'); putchar('\n');
			if (set_remove(L.pT[op].pRoot, key)) printf("删除成功\n");
			else printf("元素不存在\n");
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 5:
		{
			printf("请选择需要显示大小的集合\n");
			int op = SelectSet(L);
			printf("集合%s大小%d\n", L.pT[op].name, set_size(L.pT[op].pRoot));
			getchar(); getchar();
			break;
		}
		case 6:
		{
			printf("请选择需要查询元素的集合\n");
			int op = SelectSet(L);
			printf("输入关键字\n");
			int key;
			scanf("%d", &key);
			if (set_member(L.pT[op].pRoot, key)) printf("%d在集合%s中\n", key, L.pT[op].name);
			else
			{
				printf("%d不在集合%s中\n", key, L.pT[op].name);
			}
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 7:
		{
			printf("请选择第一个集合（运算结果为第一个集合 - 第二个集合）\n");
			int op1 = SelectSet(L);
			printf("请选择第二个集合");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//在线性表表尾创建集合
			printf("输入保存运算结果的集合的名称:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("集合%s创建成功！\n", L.pT[L.listlenth].name);

			printf("集合%s：", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//重新定位光标在新的一行

			printf("集合%s：", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_difference(L.pT[op1].pRoot, L.pT[op2].pRoot, L.pT[L.listlenth].pRoot);//T1-T2
			printf("集合%s-集合%s：", L.pT[op1].name, L.pT[op2].name); 
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("是否保存运算结果数据？1.是 0.否\n");
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
			printf("请选择原集合（判断子集合是否为原集合的子集）\n");
			int op1 = SelectSet(L);
			printf("请选择子集合\n");
			int op2 = SelectSet(L);

			printf("集合%s：", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//重新定位光标在新的一行

			printf("集合%s：", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			if (set_subset(L.pT[op1].pRoot, L.pT[op2].pRoot))
			{
				printf("集合%s是集合%s的子集合\n", L.pT[op2].name, L.pT[op1].name);
			}
			else printf("集合%s不是集合%s的子集合\n", L.pT[op2].name, L.pT[op1].name);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			printf("请选择需要遍历的集合\n");
			int op = SelectSet(L);
			set_traverse(L.pT[op].pRoot, visit);
			graphAVL(L.pT[op].pRoot, X0, X0, get_cursor_y() + 1);
			getchar(); getchar();
			break;
		}
		case 10:
		{
			SaveSetData(L);
			printf("数据保存成功\n");
			getchar(); getchar();
			break;
		}
		case 11:
		{
			int c=1;
			if (L.listlenth)
			{
				printf("重新加载数据会丢失当前数据，是否继续？\n");
				printf("1.是 0.否\n");
				scanf("%d", &c);
				if (c == 0)
				{
					printf("未加载数据\n");
					getchar(); getchar();
					break;
				}
				else
				{
					for (int i = 0; i < L.listlenth; i++)
						set_destroy(L.pT[i].pRoot);//销毁所有集合，重新加载
					L.listlenth = 0;
				}
			}
			if (c == 0)
			{
				printf("未加载数据\n");
				getchar(); getchar();
				break;
			}
			if (LoadSetData(L))
				printf("数据加载成功\n");
			else printf("数据加载失败\n");
			getchar(); getchar();
			break;
		}
		case 12:
		{
			printf("请选择第一个集合（运算结果为第一个集合 ∪ 第二个集合）\n");
			int op1 = SelectSet(L);
			printf("请选择第二个集合");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//在线性表表尾创建集合
			printf("输入保存运算结果的集合的名称:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("集合%s创建成功！\n", L.pT[L.listlenth].name);

			printf("集合%s：", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//重新定位光标在新的一行

			printf("集合%s：", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_union(L.pT[L.listlenth].pRoot, L.pT[op1].pRoot);
			set_union(L.pT[L.listlenth].pRoot, L.pT[op2].pRoot);//并集
			printf("集合%s并集合%s：", L.pT[op1].name, L.pT[op2].name);
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("是否保存运算结果数据？1.是 0.否\n");
			int c;
			scanf("%d", &c);
			if (c == 0)//不保存
			{
				set_destroy(L.pT[L.listlenth].pRoot);
			}
			else L.listlenth++;
			getchar(); getchar();
			break;
		}
		case 13:
		{
			printf("请选择第一个集合（运算结果为第一个集合 ∩ 第二个集合）\n");
			int op1 = SelectSet(L);
			printf("请选择第二个集合");
			int op2 = SelectSet(L);

			set_init(L.pT[L.listlenth].pRoot);//在线性表表尾创建集合
			printf("输入保存运算结果的集合的名称:\n");
			scanf_s("%s", L.pT[L.listlenth].name, 20);
			printf("集合%s创建成功！\n", L.pT[L.listlenth].name);

			printf("集合%s：", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//重新定位光标在新的一行

			printf("集合%s：", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			set_intersection(L.pT[op1].pRoot, L.pT[op2].pRoot, L.pT[L.listlenth].pRoot);//T1∩T2
			printf("集合%s∩集合%s：", L.pT[op1].name, L.pT[op2].name);
			set_traverse(L.pT[L.listlenth].pRoot, visit);
			putchar('\n');
			graphAVL(L.pT[L.listlenth].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);
			printf("是否保存运算结果数据？1.是 0.否\n");
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
			printf("请选择第一个集合(判断第一个集合是否和第二个集合相等)\n");
			int op1 = SelectSet(L);
			printf("请选择第二个集合\n");
			int op2 = SelectSet(L);

			printf("集合%s：", L.pT[op1].name); set_traverse(L.pT[op1].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op1].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);//重新定位光标在新的一行

			printf("集合%s：", L.pT[op2].name); set_traverse(L.pT[op2].pRoot, visit); putchar('\n');
			graphAVL(L.pT[op2].pRoot, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 4);

			if (set_equal(L.pT[op1].pRoot, L.pT[op2].pRoot))
			{
				printf("集合%s = 集合%s\n", L.pT[op1].name, L.pT[op2].name);
			}
			else printf("集合%s != 集合%s\n", L.pT[op1].name, L.pT[op2].name);
			getchar(); getchar();
			break;
		}
		case 0:
		{
			for (int i = 0; i < L.listlenth; i++)
				set_destroy(L.pT[i].pRoot);//销毁所有集合，重新加载
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
	if (!T)  return; //T为空
	printKey(T, x, y);//输出根
	if (T->lchild || T->rchild) { setxy(x, ++y); putchar('|'); }//如果根有孩子，在根正下方输出大括号箭头
	if (T->lchild)
	{//有左孩子，输出大括号左半部分
		setxy(x - l / 2 + 1, y);
		int i;
		for (i = 0; i < l / 2 - 1; i++)
			putchar('_');
	}
	if (T->rchild)
	{//有右孩子，输出大括号右半部分
		setxy(x + 1, y);
		int i;
		for (i = 0; i < l / 2 - 1; i++)
			putchar('_');
	}
	graphAVL(T->lchild, x - l / 2, l / 2, y + 1);//输出左子树
	graphAVL(T->rchild, x + l / 2, l / 2, y + 1);//输出右子树
}
int get_cursor_x(void)
{
	HANDLE     gh_std_out;
	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	return bInfo.dwCursorPosition.X;//返回当前光标的横坐标
}
int get_cursor_y(void)
{
	HANDLE     gh_std_out;
	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    bInfo;
	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	return bInfo.dwCursorPosition.Y;//返回当前光标的纵坐标
}
void setxy(short x, short y)
{//将光标定位到(x,y)处
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
	printf("请选择集合(1-%d)\n", L.listlenth);
	for (i = 1; i <= L.listlenth; i++)
	{
		printf("    	 %d. %s\n", i, L.pT[i - 1].name);
	}
	scanf("%d", &op);
	while (op < 1 || op > L.listlenth)
	{
		printf("输入错误，请重新输入\n");
		getchar(); getchar();
		scanf("%d", &op);
	}
	return op - 1;
}
Status SaveSetData(SqList L)
{
	FILE *fp;
	/*保存线性表信息*/
	if ((fp = fopen(L_DATA_NAME, "w")) == NULL)//打开文件失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	fwrite(L.pT, sizeof(SetData), L.listlenth, fp);//线性表数据一次性写入到文件中
	fclose(fp);
	/*保存树结点信息*/
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
	/*写入线性表数据*/
	FILE *fp;
	if ((fp = fopen(L_DATA_NAME, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}

	while (fread(&L.pT[L.listlenth], sizeof(SetData), 1, fp))
	{
		L.pT[L.listlenth].pRoot = NULL;
		L.listlenth++;//准备写入下一个数据
	}
	fclose(fp);

	/*写入二叉树数据*/
	if ((fp = fopen(T_DATA_NAME, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		LoadSet(L.pT[i].pRoot, fp);
	}
	return TRUE;//写入完毕
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
/*人际关系模拟函数*/
Status vis(Info e)
{
	printf("%-4d %-8s|", e.id, e.name); space++;//space调整输出格式，一行输出8个信息
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
	printf("      人际关系模拟演示 \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. 添加用户              2. 维护用户信息 \n");
	printf("    	  3. 查询用户信息          4. 显示共同关注\n");
	printf("    	  5. 显示共同爱好          6. 显示共同好友\n");
	printf("    	  7. 加载数据              8. 保存数据\n");
	printf("    	  9. 显示所有用户          10. 显示二度好友\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    请选择你的操作[0~9]:");
}
void apply_display(void)
{
	BSTree Account, Hobby;//总用户集，总兴趣集
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
			if (data_input(Account, in)) { set_insert(Account, in); printf("新用户添加成功\n"); }
			else printf("新用户添加失败\n");
	
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
			printf("用户：\n");
			set_traverse(Account, vis);
			putchar('\n');
			/*printf("爱好：\n");
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
	printf("请分别输入两位用户id：\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("用户不存在\n");
	else {
		BSTree common_follows;
		set_init(common_follows);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//定位两位用户
		set_intersection(p1->data.follows, p2->data.follows, common_follows);//两位用户关注人集的交集
		printf("\"%s\"和\"%s\"的共同关注:\n", p1->data.name, p2->data.name);
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Account, common_follows);
		set_destroy(common_follows);
		
		{
			printf("\n\n\n");
			system("pause");
			printf("\"%s\"关注人:\n", p1->data.name);
			space = 0;
			print_account_data(Account, p1->data.follows);
			printf("\n\n\"%s\"关注人:\n", p2->data.name);
			space = 0;
			print_account_data(Account, p2->data.follows);
		}
	}
}
void common_friend(BSTree Account)
{
	int id1, id2;
	printf("请分别输入两位用户id：\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("用户不存在\n");
	else 
	{
		BSTree common_friend;
		set_init(common_friend);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//定位两位用户
		set_intersection(p1->data.friends, p2->data.friends, common_friend);//两位用户朋友集的交集
		//set_traverse(common_friend, visit);
		printf("\"%s\"和\"%s\"的共同好友:\n", p1->data.name, p2->data.name);
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Account, common_friend);
		set_destroy(common_friend);
		{
			printf("\n\n\n"); system("pause");
			printf("\n\n\n");
			printf("\"%s\"好友:\n", p1->data.name);
			space = 0;
			print_account_data(Account, p1->data.friends);
			
			printf("\n\n\"%s\"好友:\n", p2->data.name);
			space = 0;
			print_account_data(Account, p2->data.friends);
		}
	}
}
void common_hobby(BSTree Account,BSTree Hobby)
{
	int id1, id2;
	printf("请分别输入两位用户id：\n");
	scanf("%d %d", &id1, &id2);
	if (!set_member(Account, id1) || !set_member(Account, id2))
		printf("用户不存在\n");
	else
	{
		BSTree common_hobby;
		set_init(common_hobby);
		BSTree p1, p2;
		p1 = set_member(Account, id1); p2 = set_member(Account, id2);//定位两位用户
		set_intersection(p1->data.hobby, p2->data.hobby, common_hobby);
		printf("\"%s\"和\"%s\"的共同爱好:\n", p1->data.name, p2->data.name);//两位用户爱好集的交集
		printf("------------------------------------------------------\n");
		space = 0;
		print_account_data(Hobby, common_hobby);
		set_destroy(common_hobby);
		{
			printf("\n\n\n"); system("pause");
			printf("\"%s\"爱好:\n", p1->data.name);
			space = 0;
			print_account_data(Hobby, p1->data.hobby);
			printf("\n\n\"%s\"爱好:\n", p2->data.name);
			space = 0;
			print_account_data(Hobby, p2->data.hobby);
		}
	}
}
void second_friend(BSTree Account)
{
	int id;
	printf("请输入用户id\n");
	scanf("%d", &id);
	BSTree p; BSTree T = NULL;
	p = set_member(Account, id);
	if (!p)
	{
		printf("用户不存在\n"); return;
	}
	
	int op = 1;
	while (op)
	{
		system("cls");
		printf("%s\n", p->data.name);
		printf("1. 查询\"%s\"关于某个好友的二度好友		2.查询\"%s\"所有二度好友\n", p->data.name, p->data.name);
		printf("0. 退出\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
		{
			int friend_id;
			printf("\"%s\"的好友:\n", p->data.name);
			space = 0;
			print_account_data(Account, p->data.friends);
			printf("\n请输入用户好友id\n");
			scanf("%d", &friend_id);
			while(!set_member(p->data.friends, friend_id))
			{
				printf("好友不存在，请重新输入\n");
				scanf("%d", &friend_id);
			}
			BSTree pfriend; BSTree T = NULL;
			pfriend = set_member(Account, friend_id);
			set_difference(pfriend->data.friends, p->data.friends, T);//求二度好友
			set_remove(T, id);//二度好友除去自己
			space = 0;
			print_account_data(Account, T);
			set_destroy(T);//销毁集合
			getchar(); getchar(); break;

		}
		case 2:
		{
			S_friend(Account, p->data.friends, T);//获得好友的好友
			BSTree T1 = NULL;
			set_difference(T, p->data.friends, T1);//二度好友中除去自己的好友
			set_remove(T1, p->data.id);//二度好友中除去自己
			space = 0;
			printf("\"%s\"的二度好友:（%d位）\n", p->data.name, set_size(T1));//两位用户爱好集的交集

			print_account_data(Account, T1);//输出二度好友
			set_destroy(T); set_destroy(T1);//销毁集合
			getchar(); getchar(); break;
		}
		default: break;
		}
	}
}
void S_friend(BSTree Account,BSTree p,BSTree &T)
{//p为某个用户的好友集，求该用户好友的好友的并集于T中
	if (p)
	{
		BSTree p_friend = set_member(Account, p->data.id);//定位好友节点
		set_union(T, p_friend->data.friends);//添加该好友的好友于T中
		S_friend(Account, p->lchild, T);//在左子树中查找并添加二度好友
		S_friend(Account, p->rchild, T);//在右子树中查找并添加二度好友
	}
	
}
Status destroy_accountset(BSTree &T)
{
	if (T)
	{
		destroy_accountset(T->lchild);
		destroy_accountset(T->rchild);
		set_destroy(T->data.fans); set_destroy(T->data.follows); set_destroy(T->data.friends); set_destroy(T->data.hobby);//销毁个人关系集
		free(T);//释放节点
		T = NULL;
	}
	return TRUE;
}
Status data_input(BSTree T, Info &in)
{
	Info temp;
	printf("请输入新用户id:\n");
	scanf("%d", &temp.id);
	while (set_member(T, temp.id)) { printf("用户%d已存在，请重新输入(输入0退出)\n", temp.id); scanf("%d", &temp.id); if (temp.id== 0 )return FALSE; }
	printf("请输入用户姓名:\n");
	scanf("%s", &temp.name);
	temp.follows = temp.friends = temp.fans = temp.hobby = NULL;//新用户无粉丝好友等信息
	if (confirm_save()) { in = temp; return TRUE; }
	else return FALSE;
}
int confirm_save(void)
{
	printf("是否保存?\n");
	printf("1.是  0.否\n");
	int c;
	scanf("%d", &c);
	while (c != 0 && c != 1)
	{
		printf("输入错误，请重新输入\n");
		scanf("%d", &c);
	}
	return c;
}
int select_display(void)
{
	printf("请选择演示功能：\n");
	printf("1.集合操作演示  2.人际关系模拟演示\n");
	printf("3.AVL树演示		0.退出系统\n");
	int c;
	scanf("%d", &c);
	getchar();
	while (c != 1 && c != 2 && c != 0&&c!=3)
	{
		printf("输入错误，请重新输入\n");
		scanf("%d", &c);
		getchar();
	}
	return c;
}
void maintain_data(BSTree &Account,BSTree Hobby)
{
	int id;
	printf("请输入用户id\n");
	scanf("%d", &id);
	BSTNode *pt;
	pt = set_member(Account, id);
	if (!pt)
	{
		printf("用户不存在\n");
	}
	else
	{
		int op = 1;
		while (op)
		{
			system("cls");
			printf("请选择维护用户\"%s\"的内容\n", pt->data.name);
			printf("    	  1. 维护用户朋友集              2. 维护用户关注人集 \n");
			printf("    	  3. 维护用户爱好集              4. 移除用户粉丝\n");
			printf("    	  5. 修改用户姓名\n");
			printf("    	  0. 退出维护\n");

			scanf("%d", &op);
			switch (op)
			{
			case 1:
			{
				int o;
				printf("用户\"%s\"的朋友\n", pt->data.name);
				space = 0; print_account_data(Account, pt->data.friends);
				printf("\n请选择操作:\n");
				printf("    	  1. 添加朋友              2. 删除朋友 \n");
				printf("    	  0. 退出 \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_friend;
					printf("请输入新朋友id\n");
					scanf("%d", &new_friend.id);
					if (!set_member(Account, new_friend.id)) printf("用户%d不存在\n", new_friend.id);
					else
					{
						if (set_insert(pt->data.friends, new_friend))//插入到用户*pt的朋友集中
						{
							BSTNode *p = set_member(Account, new_friend.id);
							set_insert(p->data.friends, pt->data);//朋友是相互的
							
							printf("添加成功\n");
						}
						else printf("用户%d已经是%s的朋友", new_friend.id, pt->data.name);//元素插入失败
					}
				}
				else if (o == 2)
				{
					int friend_id;
					printf("请输入要删除的朋友id\n");
					scanf("%d", &friend_id);
					if (set_member(pt->data.friends, friend_id)) 
					{ 
						set_remove(pt->data.friends, friend_id);
						BSTNode *p = set_member(Account, friend_id);
						set_remove(p->data.friends, id);//移除朋友是相互的
						printf("删除成功\n"); 
					}
					else printf("%d不是\"%s\"的朋友\n", friend_id, pt->data.name);
				}
				getchar(); getchar();
				break;
			}
			case 2:
			{
				int o;
				printf("\"%s\"的关注人:\n", pt->data.name); 
				space = 0; print_account_data(Account, pt->data.follows);
				printf("\n请选择操作:\n");
				printf("    	  1. 添加关注人              2. 移除关注人 \n");
				printf("    	  0. 退出 \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_follow;
					printf("请输入新关注人id\n");
					scanf("%d", &new_follow.id);
					if (!set_member(Account, new_follow.id)) printf("用户%d不存在\n", new_follow.id);
					else
					{
						if (set_insert(pt->data.follows, new_follow))
						{//为关注人添加粉丝
							printf("添加成功\n");
							BSTNode *p;
							Info new_fan;
							new_fan.id = id;
							p = set_member(Account, new_follow.id);//p指向新关注人
							set_insert(p->data.fans, new_fan);//添加粉丝
						}
						else printf("用户%d已经是\"%s\"的关注人\n", new_follow.id, pt->data.name);
					}
				}
				else if (o == 2)
				{
					int follow_id;
					printf("请输入要删除的关注人id\n");
					scanf("%d", &follow_id);
					if (set_member(pt->data.follows, follow_id))
					{
						set_remove(pt->data.follows, follow_id); //移除关注人
						set_remove(set_member(Account, follow_id)->data.fans, id); //移除被关注人的粉丝
						printf("删除成功\n");
					}
					else printf("关注人%d不存在\n", follow_id);
				}
				getchar(); getchar();
				break;
			}
			case 3:
			{
				int o;
				printf("\"%s\"的爱好:\n", pt->data.name);
				space = 0; print_account_data(Hobby, pt->data.hobby);
				printf("\n请选择操作:\n");
				printf("    	  1. 添加爱好              2. 移除爱好 \n");
				printf("    	  0. 退出 \n");
				scanf("%d", &o);
				if (o == 1)
				{
					Info new_hobby;
					printf("请输入新爱好id\n");
					space = 0; set_traverse(Hobby, vis); putchar('\n');
					scanf("%d", &new_hobby.id);
					if (!set_member(Hobby, new_hobby.id)) printf("爱好%d不存在\n", new_hobby.id);
					else
					{
						if (set_insert(pt->data.hobby, new_hobby))//插入到用户*pt的爱好集中
							printf("添加成功\n");
						else printf("爱好%d已存在\n", new_hobby.id);
					}
				}
				else if (o == 2)
				{
					int hobby_id;
					printf("请输入要删除的爱好id\n");
					scanf("%d", &hobby_id);
					if (set_member(pt->data.hobby, hobby_id)) { set_remove(pt->data.hobby, hobby_id); printf("爱好移除成功\n"); }
					else printf("%d不是\"%s\"的爱好\n", hobby_id, pt->data.name);
				}
				getchar(); getchar();
				break;
			}
			case 4:
			{
				printf("\"%s\"的粉丝:\n", pt->data.name);
				space = 0; print_account_data(Account, pt->data.fans);
				putchar('\n');
				int fan_id;
				printf("请输入要删除的粉丝id\n");
				scanf("%d", &fan_id);
				if (set_member(pt->data.fans, fan_id)) { set_remove(pt->data.fans, fan_id); printf("粉丝移除成功\n"); }
				else printf("%d不是\"%s\"的粉丝\n", fan_id, pt->data.name);
				getchar(); getchar();
				break;
			}
			case 5:
			{
				printf("请输入新的姓名\n");
				char new_name[20];
				scanf("%s", new_name);
				strcpy(pt->data.name, new_name);
				printf("姓名修改成功.\n");
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
	if (T)//T非空
	{
		
		save_account(T->lchild, fp);
		fprintf(fp, "%d %s\n", T->data.id, T->data.name);
		save_account(T->rchild, fp);
	}
	return TRUE;
}
Status save_hobby(BSTree T, FILE *fp)
{
	if (T)//T非空
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
		save_relation(T->lchild, fp);//保存左子树信息
		fprintf(fp, "%d\n", T->data.id);//保存节点id
		save_rela(T->data.fans, fp); fprintf(fp, " 0\n");
		save_rela(T->data.follows, fp); fprintf(fp, " 0\n");
		save_rela(T->data.friends, fp); fprintf(fp, " 0\n");
		save_rela(T->data.hobby, fp); fprintf(fp, " 0\n\n");//存储节点的关系信息,以0作为结束标记
		save_relation(T->rchild, fp);//保存右子树信息
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
	while (fscanf(fp, " %d", &id1)!=EOF)//读取一个用户
	{
		pt = set_member(T, id1);
		fscanf(fp,"%d", &id2);
		while (id2 != 0)//加载用户粉丝集
		{
			temp.id = id2;
			set_insert(pt->data.fans, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp, "%d", &id2);
		while (id2 != 0)//加载用户关注人集
		{
			temp.id = id2;
			set_insert(pt->data.follows, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp, "%d", &id2);
		while (id2 != 0)//加载用户朋友集
		{
			temp.id = id2;

			set_insert(pt->data.friends, temp);
			fscanf(fp, "%d", &id2);
		}
		
		fscanf(fp,"%d", &id2);
		while (id2 != 0)//加载用户兴趣集
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
	if (!fp) { printf("账户数据加载失败\n"); }//文件打开失败
	else {
		destroy_accountset(Account);//销毁已存在的集合，重新加载
		load_account(Account, fp);
		printf("账户数据加载成功\n");
		fclose(fp);

		fp = fopen(RELATIONDATA, "r");
		if (!fp) { printf("关系数据加载失败\n"); }
		else {
			
			load_relation(Account, fp);
			fclose(fp);
			printf("关系数据加载成功\n");
		}
	}
	
	fp = fopen(HOBBYDATA, "r");
	if (!fp) { printf("兴趣数据加载失败\n"); }//文件打开失败
	else {
		set_destroy(Hobby);
		load_hobby(Hobby, fp);
		printf("兴趣数据加载成功\n");
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
	printf("数据保存成功\n");

	return TRUE;
}
void account_data(BSTree Account, BSTree Hobby)
{
	system("cls");
	int id;
	printf("请输入查询的用户id（输入0退出查询）\n");
	scanf("%d", &id);
	while (id)
	{
		BSTNode *T = set_member(Account, id);//定位用户
		if (!T) printf("用户%d不存在\n", id);
		else
		{
			int op = 1;
			while (op!=5)
			{
				system("cls");
				printf("---------------------%d %s--------------------\n", T->data.id, T->data.name);
				printf("1. 好友集			2.关注人集\n"); 
				printf("3. 粉丝集			4.爱好集\n");
				printf("5. 重新选择查询用户		0.退出查询\n");

				scanf("%d", &op);
				if (op == 0)return;
				switch (op)
				{
				case 1:
				{
					printf("%d \"%s\"的朋友：（%d位）\n", T->data.id,T->data.name, set_size(T->data.friends)); space = 0;
					print_account_data(Account, T->data.friends); space = 0; putchar('\n');//调整输入格式

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;

				}
				case 2:
				{
					printf("%d \"%s\"的关注人：（%d位）\n", T->data.id, T->data.name, set_size(T->data.follows));
					print_account_data(Account, T->data.follows); space = 0; putchar('\n');

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;
				}
				case 3:
				{
					printf("%d \"%s\"的粉丝：（%d位）\n", T->data.id, T->data.name, set_size(T->data.fans));
					print_account_data(Account, T->data.fans); space = 0; putchar('\n');

					putchar('\n');	putchar('\n');
					getchar(); getchar();
					break;
				}

				case 4:
				{
					printf("%d \"%s\"的爱好：（%d个）\n", T->data.id, T->data.name, set_size(T->data.hobby));
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
		printf("请重新输入用户id:(输入0退出查询)");
		scanf("%d", &id);
		printf("切换成功\n");
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
		fflush(stdout);//刷新缓冲区  
		Sleep(5);
		i++;
	}

	printf("\n");
}

void menu3(void)
{
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("      AVL树操作演示 \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. InitAVL         5. SearchAVL\n");
	printf("    	  2. InsertAVL       6. TraverseAVL\n");
	printf("    	  3. DestroyAVL    \n");
	printf("    	  4. DeleteAVL\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	printf("    请选择你的操作[0~6]:");
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
			printf("AVL树T初始化成功\n");
			
			getchar(); getchar();
			break;
		}
		case 2:
		{
			int N;
			Info a;
			bool taller;
			printf("请输入数据的组数\n");
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
			printf("AVL树销毁成功\n");
			getchar(); getchar();
			break;
		}
		case 4:
		{
			bool shorter;
			graphAVL(T, X0, X0, get_cursor_y());
			setxy(0, get_cursor_y() + 2);
			printf("输入要删除的节点\n");
			scanf("%d", &key);
			if (DeleteAVL(T, key,shorter)) printf("删除成功\n");
			else printf("节点不存在\n");
			graphAVL(T, X0, X0, get_cursor_y());
			getchar(); getchar();
			break;
		}
		case 5:
		{
			printf("请输入节点\n");
			int key;
			scanf("%d", &key);
			if (SearchAVL(T, key)) printf("%d节点在树中", key);
			else printf("节点不存在\n");
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
			set_destroy(T);//退出前销毁集合T
			break;
		}//end of switch
	}//end of while
}