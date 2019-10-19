/*对于弧a→b，称a为弧尾，b为弧头*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*--------------------page 10 on textbook ----------------------------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

#define MAX_VERTEX_NUM 200//最大顶点数
#define MAX_ARC_NUM 2000//最大弧数
#define V_DATA "VData"//顶点数据文件
#define E_DATA "EData"//弧数据文件
typedef int status;
typedef int KEY;
typedef struct VertexType
{
	int key;
	char c;
}VertexType;
typedef int InfoType;

typedef struct ArcNode {
	int adjves;//该弧所指顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType info;//弧的权值
}ArcNode;

typedef struct VNode {
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;//点数、边数
}ALGraph;
typedef struct {
	KEY tail;//弧尾
	KEY head;//弧头
	InfoType info;//弧权值
}VertexRalation;//图的关系集
				/*--------------------page 19 on textbook ----------------------------------*/
status CreateGraph(ALGraph &G, VertexType * V, VertexRalation * VR);
status DestroyGraph(ALGraph &G);
VNode * GetVex(ALGraph &G, KEY v);
status PutVex(ALGraph &G, KEY v, VertexType value);//将结点v的值赋为value
status LocateVex(ALGraph &G, KEY v);
int FirstAdjVex(ALGraph &G, int v);//第v个顶点的第一邻接点
int NextAdjVex(ALGraph &G, int v, int w);//第v个顶点相对于第w顶点的下一邻接点
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KEY v);
status InsertArc(ALGraph &G, KEY v, KEY w, InfoType i);
status DeleteArc(ALGraph &G, KEY v, KEY w);
status DFSTraverse(ALGraph G, status(*visit)(VNode v));
void DFS(ALGraph G, int v, status(*visit)(VNode v));//从第v个顶点出发递归地深度优先遍历图G
status BFSTraverse(ALGraph G, status(*visit)(VNode v));
status visit(VNode v)
{
	printf("%d %c\n", v.data.key, v.data.c);
	return OK;
}
void SaveData(ALGraph G);
void LoadData(ALGraph &G);
void printG(ALGraph G)
{
	int i;
	ArcNode *p;
	printf("顶点数 边数\n");
	printf("%6d %4d\n", G.vexnum, G.arcnum);
	printf("位置 关键字 值	  邻接边\n");
	printf("------------------------------------------------------------------------------------------\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%4d|%6d %2c|->", i, G.vertices[i].data.key, G.vertices[i].data.c);
		for (p = G.vertices[i].firstarc; p; p = p->nextarc)
			printf("邻接点位置%-4d权%-4d-> ", p->adjves, p->info);
		printf("NULL\n");
		printf("------------------------------------------------------------------------------------------\n");
	}
}
bool visited[MAX_VERTEX_NUM];//标记已被访问的结点
							 /*------------------------------------------------------*/
void main(void) {
	ALGraph G;
	int op = 1;
	int exist = 0;
	while (op) {
		system("cls");
		printf("\n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateGraph       8. InsertVex\n");
		printf("    	  2. DestroyGraph      9. DeleteVex\n");
		printf("    	  3. GetVex           10. InsertArc\n");
		printf("    	  4. LocateVex        11. DeleteArc\n");
		printf("    	  5. PutVex           12. DfsTraverse\n");
		printf("    	  6. FirstAdjVex      13. BFSTraverse\n");
		printf("    	  7. NextAdjVex       14. 打印出图的邻接表\n");
		printf("    	  15. 保存数据        16. 加载数据\n");
		printf("    	  0.exit\n");
		printf("-------------------------------------------------\n");
		if (exist == 0)
			printf("请先创建图或从文件中加载数据\n");
		printf("    请选择你的操作[0~16]:");
		if (exist == 1 && (G.arcnum >= MAX_ARC_NUM || G.vexnum >= MAX_VERTEX_NUM))
		{
			printf("空间不足\n");
			exit(0);
		}//空间不足，异常退出
		scanf("%d", &op);
		if (exist == 0 && op != 1 && op != 16)//图不存在，需先执行操作1
		{
			printf("图不存在，请先创建图\n");
			getchar(); getchar();
			continue;
		}
		else if (exist == 1 && (op == 1 || op == 16))//图存在，并且选择了操作1或操作16
		{
			printf("图已存在,请先销毁后再创建\n");
			getchar(); getchar();
			continue;
		}
		switch (op) {
		case 1:
		{
			int i = 0;
			VertexType V[MAX_VERTEX_NUM];//图顶点
			printf("请顺序输入图顶点的关键字(int) 数据(char),以0 #结束输入\n");
			while (1)
			{
				scanf("%d %c", &V[i].key, &V[i].c);
				if (V[i].key == 0 && V[i].c == '#')
					break;
				i++;
			}
			printf("图顶点信息录入完毕\n");
			i = 0;
			VertexRalation VR[MAX_ARC_NUM];//顶点关系
			printf("请顺序输入每条弧的弧尾关键字(int) 弧头关键字(int) 权值(int),以空格隔开,以0 0 0结束输入\n");
			while (1)
			{
				scanf("%d %d %d", &VR[i].tail, &VR[i].head, &VR[i].info);
				if (VR[i].tail == 0 && VR[i].head == 0 && VR[i].info == 0)
					break;
				i++;
			}
			printf("图顶点关系信息录入完毕\n");
			if (CreateGraph(G, V, VR))
				printf("图创建成功\n");
			else printf("图创建失败\n");
			exist = 1;
			getchar(); getchar();
			break;
		}
		case 2:
		{
			DestroyGraph(G);
			printf("图销毁成功\n");
			exist = 0;
			getchar(); getchar();
			break;
		}
		case 3:
		{
			KEY key;
			printf("请输入图结点的关键字(int):\n");
			scanf("%d", &key);
			VNode *pv;
			pv = GetVex(G, key);
			if (pv == NULL)
				printf("关键字为%d的顶点不存在\n", key);
			else
			{
				printf("关键字：%d    值：%c", pv->data.key, pv->data.c);
			}
			getchar(); getchar();
			break;
		}
		case 4:
		{
			KEY key;
			printf("请输入图结点的关键字(int):\n");
			scanf("%d", &key);
			int locate;
			locate = LocateVex(G, key);
			if (locate == -1)
				printf("关键字为%d的顶点不存在\n", key);
			else
			{
				printf("关键字为%d的顶点的位置为%d\n", key, locate);
			}
			getchar(); getchar();
			break;
		}
		case 5:
		{
			KEY key;
			printf("请输入图结点的关键字(int):\n");
			scanf("%d", &key);
			VNode *pv;
			pv = GetVex(G, key);
			if (pv == NULL)
			{
				printf("关键字为%d的顶点不存在\n", key);
				getchar(); getchar();
				break;
			}
			VertexType value;
			printf("请输入更改后图结点关键字(int) 值(char)\n");
			scanf("%d %c", &value.key, &value.c);
			printf("更改前：%d %c\n", pv->data.key, pv->data.c);
			PutVex(G, key, value);
			printf("更改后：%d %c\n", pv->data.key, pv->data.c);
			getchar(); getchar();
			break;
		}
		case 6:
		{
			KEY key;
			int locate;
			printf("请输入图顶点点的关键字(int):\n");
			scanf("%d", &key);
			locate = LocateVex(G, key);//顶点v的位置
			if (locate == -1)
				printf("关键字为%d的顶点不存在\n", key);
			else
			{
				locate = FirstAdjVex(G, locate);//顶点v的第一邻接点位置
				if (locate>-1)
					printf("关键字为%d顶点的第一邻接顶点位置%d 关键字%d 值%c\n", key, locate, G.vertices[locate].data.key, G.vertices[locate].data.c);
				else printf("关键字为%d顶点的第一邻接顶点不存在\n", key);
			}
			getchar(); getchar();
			break;
		}
		case 7:
		{
			KEY v;
			printf("请输入图结点的关键字(int):\n");
			scanf("%d", &v);
			if (GetVex(G, v) == NULL)
				printf("关键字为%d的顶点不存在\n", v);
			else
			{
				KEY w;
				printf("请输入关键字为%d结点的邻接结点关键字:\n", v);
				scanf("%d", &w);
				int vlocate, wlocate, Adj;
				vlocate = LocateVex(G, v);
				wlocate = LocateVex(G, w);
				Adj = NextAdjVex(G, vlocate, wlocate);
				if (Adj>-1)
					printf("%d结点相对于%d结点的下一个邻接结点位置:%d 关键字:%d 值:%c", v, w, Adj, G.vertices[Adj].data.key, G.vertices[Adj].data.c);
				else
					printf("%d结点相对于%d结点的下一个邻接结点不存在\n", v, w);
				getchar(); getchar();
				break;
			}
		}
		case 8:
		{
			VertexType v;
			printf("请输入新结点的关键字(int) 值(char)\n");
			scanf("%d %c", &v.key, &v.c);
			InsertVex(G, v);
			VNode *pv;
			pv = GetVex(G, v.key);
			printf("新节点%d %c插入成功\n", pv->data.key, pv->data.c);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			KEY key;
			printf("请输入要删除的图结点的关键字(int):\n");
			scanf("%d", &key);
			if (GetVex(G, key) == NULL)
				printf("关键字为%d的顶点不存在\n", key);
			else
			{
				DeleteVex(G, key);
				printf("结点%d删除成功\n", key);
			}
			getchar(); getchar();
			break;

		}
		case 10:
		{
			KEY v, w;
			printf("请分别输入弧尾结点和弧头结点关键字\n");
			scanf("%d %d", &v, &w);
			if (GetVex(G, v) == NULL)
				printf("图中不存在顶点%d\n", v);
			else if (GetVex(G, w) == NULL)
				printf("图中不存在顶点%d\n", w);
			else
			{
				InfoType i;
				printf("请输入弧的权值\n");
				scanf("%d", &i);
				InsertArc(G, v, w, i);
				printf("弧(%d,%d)插入成功\n", v, w);
			}
			getchar(); getchar();
			break;
		}
		case 11:
		{
			KEY v, w;
			printf("请分别输入弧尾结点和弧头结点关键字\n");
			scanf("%d %d", &v, &w);
			if (GetVex(G, v) == NULL)
				printf("图中不存在顶点%d\n", v);
			else if (GetVex(G, w) == NULL)
				printf("图中不存在顶点%d\n", w);
			else
			{
				if (DeleteArc(G, v, w))
					printf("弧(%d,%d)删除成功\n", v, w);
				else printf("图中无弧(%d,%d)\n", v, w);
			}
			getchar(); getchar();
			break;
		}
		case 12:
		{
			DFSTraverse(G, visit);
			getchar(); getchar();
			break;
		}
		case 13:
		{
			BFSTraverse(G, visit);
			getchar(); getchar();
			break;
		}
		case 14:
		{
			printG(G);
			getchar(); getchar();
			break;
		}
		case 15:
		{
			SaveData(G);
			printf("数据保存成功\n");
			getchar(); getchar();
			break;
		}
		case 16:
		{
			LoadData(G);
			exist = 1;
			printf("数据加载成功\n");
			getchar(); getchar();
			break;
		}
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()


status CreateGraph(ALGraph &G, VertexType * V, VertexRalation * VR)
{
	/*创建顶点*/
	G.arcnum = G.vexnum = 0;
	int i;
	ArcNode *pe, *temp;
	VNode *pv;//顶点结点指针
	for (i = 0; V[i].key != 0 || V[i].c != '#'; i++)
	{
		G.vertices[i].data = V[i];//创建一个顶点
		G.vertices[i].firstarc = NULL;//顶点邻接边置空
		G.vexnum++;//顶点数+1
	}
	/*创建边*/
	for (i = 0; VR[i].head || VR[i].tail || VR[i].info; i++)
	{
		pv = GetVex(G, VR[i].tail);//获取弧尾结点的地址
		temp = (ArcNode *)malloc(sizeof(ArcNode));//创建一个边结点
		temp->adjves = LocateVex(G, VR[i].head);
		temp->info = VR[i].info;//录入边结点信息
		temp->nextarc = pv->firstarc;
		pv->firstarc = temp;//将新的边结点放在边链的第一个结点
		G.arcnum++;//边数+1
	}
	return OK;
}
status DestroyGraph(ALGraph &G)
{
	int i;
	ArcNode *pe1, *pe2;
	for (i = 0; i < G.vexnum; i++)
	{
		pe2 = pe1 = G.vertices[i].firstarc;
		while (pe1)
		{
			pe1 = pe1->nextarc;
			free(pe2);
			pe2 = pe1;
		}//释放边结点
	}
	return OK;
}
VNode * GetVex(ALGraph &G, KEY v)
{
	VNode *p;
	for (p = G.vertices; p < G.vertices + G.vexnum; p++)
	{
		if (p->data.key == v)
			return p;
	}
	return NULL;
}
status PutVex(ALGraph &G, KEY v, VertexType value)
{
	VNode *pv;
	pv = GetVex(G, v);//获取结点
	pv->data = value;//结点赋值
	return OK;
}
status LocateVex(ALGraph &G, KEY v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			return i;//返回顶点的位置
	return -1;//顶点不存在返回-1
}
int FirstAdjVex(ALGraph &G, int v)
{
	VNode *pv;
	pv = &G.vertices[v];
	if (pv->firstarc == NULL)//若v无邻接边
		return -1;
	else return pv->firstarc->adjves;//返回v的第一邻接点位置
}
int NextAdjVex(ALGraph &G, int v, int w)
{
	VNode *pv;
	pv = &G.vertices[v];
	ArcNode *pe;
	for (pe = pv->firstarc; pe; pe = pe->nextarc)
	{
		if (pe->adjves == w)
		{
			if (pe->nextarc != NULL)//若w不是v的最后一个邻接点
				return pe->nextarc->adjves;
			else return -1;//w是v的最后一个邻接点
		}
	}
	return -1;//w不是v的邻接点
}
status InsertVex(ALGraph &G, VertexType v)
{
	G.vertices[G.vexnum].data = v;//赋值结点数据
	G.vertices[G.vexnum].firstarc = NULL;//新节点第一邻接边置空
	G.vexnum++;
	return OK;
}
status DeleteVex(ALGraph &G, KEY v)
{
	int locate = LocateVex(G, v);//定位顶点v
	int i;
	VNode *pv;
	ArcNode *temp, *pe, *pre;//pe遍历邻接边，pre指向pe边结点的前驱结点

	/*1.删除与顶点v关联的边*/

	//1.1删除以v为弧尾的边结点
	pv = &G.vertices[locate];//指向顶点v
	pre = pe = pv->firstarc;
	while (pe)
	{
		pe = pe->nextarc;
		free(pre);
		pre = pe;
		G.arcnum--;
	}
	pv->firstarc = NULL;
	//1.2遍历G中所有顶点，删除以v为弧头的边结点
	for (i = 0; i < G.vexnum; i++)
	{
		DeleteArc(G, G.vertices[i].data.key, v);
	}
	/*2.删除顶点v*/
	for (i = locate; i < G.vexnum - 1; i++)
	{
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;

	/*3.更改G中边结点的邻接点的位置信息*/
	for (i = 0; i < G.vexnum; i++)
	{
		pv = &G.vertices[i];
		for (pe = pv->firstarc; pe; pe = pe->nextarc)
		{
			if (pe->adjves > locate)//v结点之后的结点位置都前移1
				pe->adjves--;
		}
	}
	return OK;
}
status InsertArc(ALGraph &G, KEY v, KEY w, InfoType i)
{
	int locate = LocateVex(G, v);
	ArcNode *pe;
	pe = (ArcNode *)malloc(sizeof(ArcNode));//分配一个边结点
											//初始化边结点
	pe->adjves = LocateVex(G, w);
	pe->info = i;
	//将新的边结点插入到边链的头部位置
	pe->nextarc = G.vertices[locate].firstarc;
	G.vertices[locate].firstarc = pe;
	G.arcnum++;
	return OK;
}
status DeleteArc(ALGraph &G, KEY v, KEY w)
{
	VNode *pv;
	ArcNode *pe, *temp, *pre;
	pv = GetVex(G, v);
	if (pv->firstarc == NULL)//v无邻接点
		return FALSE;
	int wlocate = LocateVex(G, w);//w的位置
	if (pv->firstarc->adjves == wlocate)//如果w是v的第一邻接点
	{
		temp = pv->firstarc;
		pv->firstarc = pv->firstarc->nextarc;
		free(temp);
		G.arcnum--;
		return TRUE;
	}
	else//在v的非第一邻接结点中查找w
	{
		for (pre = pe = pv->firstarc; pe; pre = pe, pe = pe->nextarc)
		{
			if (pe->adjves == wlocate)//找到
			{
				pre->nextarc = pe->nextarc;//修改指针
				free(pe);//释放结点
				G.arcnum--;
				return TRUE;
			}
		}
	}
	return FALSE;//弧(v,w)不存在
}
status DFSTraverse(ALGraph G, status(*visit)(VNode v))
{
	int v;
	for (v = 0; v < MAX_VERTEX_NUM; v++)//标记置空
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v]) DFS(G, v, visit);//对未访问的顶点调用DFS
	return OK;
}
void DFS(ALGraph G, int v, status(*visit)(VNode v))
{
	int w;
	visited[v] = TRUE;
	visit(G.vertices[v]);//访问第v个顶点
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w, visit);//对v的尚未访问的邻接顶点w递归调用DFS
}
status BFSTraverse(ALGraph G, status(*visit)(VNode v))
{
	int head, tail;
	int v, u, w;
	for (v = 0; v < MAX_VERTEX_NUM; v++)//标记置空
		visited[v] = 0;
	int queue[MAX_VERTEX_NUM];
	head = tail = 0;
	for (v = 0; v < G.vexnum; v++)//顺序遍历G中所有顶点
	{
		if (!visited[v])//v未被访问
		{
			visited[v] = TRUE; visit(G.vertices[v]);//访问v
			queue[tail] = v;//v入队
			tail = (tail + 1) % MAX_VERTEX_NUM;
			while (tail != head && (tail + 1) % MAX_VERTEX_NUM != head)//队非空
			{
				u = queue[head];//出队
				head = (head + 1) % MAX_VERTEX_NUM;
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))//u的未被访问的邻接点依次进队
					if (!visited[w])//u的邻接点w未被访问
					{
						visited[w] = TRUE;//访问w
						visit(G.vertices[w]);
						queue[tail] = w;
						tail = (tail + 1) % MAX_VERTEX_NUM;//w进队
					}
			}//end while
		}//end if
	}//end for
	return OK;
}
void SaveData(ALGraph G)
{
	FILE *fp;
	/*储存顶点信息*/
	fp = fopen(V_DATA, "w");
	fwrite(&G, sizeof(ALGraph), 1, fp);
	fclose(fp);
	/*储存弧信息*/
	fp = fopen(E_DATA, "w");
	int i = 0;
	ArcNode *pe;
	for (i = 0; i < G.vexnum; i++)
	{
		for (pe = G.vertices[i].firstarc; pe; pe = pe->nextarc)
		{
			fprintf(fp, "%d %d %d\n", i, pe->adjves, pe->info);//按照弧尾位置 弧头位置 弧权值的格式将弧数据写入到文件中
		}
	}
	fclose(fp);
}
void LoadData(ALGraph &G)
{
	FILE *fp;
	int i;
	int tail, head, info;//弧尾，弧头，权值
	/*读取顶点信息*/
	fp = fopen(V_DATA, "r");
	fread(&G, sizeof(ALGraph), 1, fp);
	fclose(fp);
	for (i = 0; i < G.vexnum; i++)
		G.vertices[i].firstarc = NULL;//邻接边置空
	/*读取弧信息*/
	fp = fopen(E_DATA, "r");
	while (fscanf(fp, "%d %d %d", &tail, &head, &info) != EOF)
	{//使用修改的InsertArc插入弧
		ArcNode *pe;
		pe = (ArcNode *)malloc(sizeof(ArcNode));//分配一个边结点
		//初始化边结点
		pe->adjves = head;
		pe->info = info;
		//将新的边结点插入到边链的头部位置
		pe->nextarc = G.vertices[tail].firstarc;
		G.vertices[tail].firstarc = pe;
	}
	fclose(fp);
}