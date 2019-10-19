/*���ڻ�a��b����aΪ��β��bΪ��ͷ*/
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

#define MAX_VERTEX_NUM 200//��󶥵���
#define MAX_ARC_NUM 2000//�����
#define V_DATA "VData"//���������ļ�
#define E_DATA "EData"//�������ļ�
typedef int status;
typedef int KEY;
typedef struct VertexType
{
	int key;
	char c;
}VertexType;
typedef int InfoType;

typedef struct ArcNode {
	int adjves;//�û���ָ�����λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
	InfoType info;//����Ȩֵ
}ArcNode;

typedef struct VNode {
	VertexType data;//������Ϣ
	ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;//����������
}ALGraph;
typedef struct {
	KEY tail;//��β
	KEY head;//��ͷ
	InfoType info;//��Ȩֵ
}VertexRalation;//ͼ�Ĺ�ϵ��
				/*--------------------page 19 on textbook ----------------------------------*/
status CreateGraph(ALGraph &G, VertexType * V, VertexRalation * VR);
status DestroyGraph(ALGraph &G);
VNode * GetVex(ALGraph &G, KEY v);
status PutVex(ALGraph &G, KEY v, VertexType value);//�����v��ֵ��Ϊvalue
status LocateVex(ALGraph &G, KEY v);
int FirstAdjVex(ALGraph &G, int v);//��v������ĵ�һ�ڽӵ�
int NextAdjVex(ALGraph &G, int v, int w);//��v����������ڵ�w�������һ�ڽӵ�
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KEY v);
status InsertArc(ALGraph &G, KEY v, KEY w, InfoType i);
status DeleteArc(ALGraph &G, KEY v, KEY w);
status DFSTraverse(ALGraph G, status(*visit)(VNode v));
void DFS(ALGraph G, int v, status(*visit)(VNode v));//�ӵ�v����������ݹ��������ȱ���ͼG
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
	printf("������ ����\n");
	printf("%6d %4d\n", G.vexnum, G.arcnum);
	printf("λ�� �ؼ��� ֵ	  �ڽӱ�\n");
	printf("------------------------------------------------------------------------------------------\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%4d|%6d %2c|->", i, G.vertices[i].data.key, G.vertices[i].data.c);
		for (p = G.vertices[i].firstarc; p; p = p->nextarc)
			printf("�ڽӵ�λ��%-4dȨ%-4d-> ", p->adjves, p->info);
		printf("NULL\n");
		printf("------------------------------------------------------------------------------------------\n");
	}
}
bool visited[MAX_VERTEX_NUM];//����ѱ����ʵĽ��
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
		printf("    	  7. NextAdjVex       14. ��ӡ��ͼ���ڽӱ�\n");
		printf("    	  15. ��������        16. ��������\n");
		printf("    	  0.exit\n");
		printf("-------------------------------------------------\n");
		if (exist == 0)
			printf("���ȴ���ͼ����ļ��м�������\n");
		printf("    ��ѡ����Ĳ���[0~16]:");
		if (exist == 1 && (G.arcnum >= MAX_ARC_NUM || G.vexnum >= MAX_VERTEX_NUM))
		{
			printf("�ռ䲻��\n");
			exit(0);
		}//�ռ䲻�㣬�쳣�˳�
		scanf("%d", &op);
		if (exist == 0 && op != 1 && op != 16)//ͼ�����ڣ�����ִ�в���1
		{
			printf("ͼ�����ڣ����ȴ���ͼ\n");
			getchar(); getchar();
			continue;
		}
		else if (exist == 1 && (op == 1 || op == 16))//ͼ���ڣ�����ѡ���˲���1�����16
		{
			printf("ͼ�Ѵ���,�������ٺ��ٴ���\n");
			getchar(); getchar();
			continue;
		}
		switch (op) {
		case 1:
		{
			int i = 0;
			VertexType V[MAX_VERTEX_NUM];//ͼ����
			printf("��˳������ͼ����Ĺؼ���(int) ����(char),��0 #��������\n");
			while (1)
			{
				scanf("%d %c", &V[i].key, &V[i].c);
				if (V[i].key == 0 && V[i].c == '#')
					break;
				i++;
			}
			printf("ͼ������Ϣ¼�����\n");
			i = 0;
			VertexRalation VR[MAX_ARC_NUM];//�����ϵ
			printf("��˳������ÿ�����Ļ�β�ؼ���(int) ��ͷ�ؼ���(int) Ȩֵ(int),�Կո����,��0 0 0��������\n");
			while (1)
			{
				scanf("%d %d %d", &VR[i].tail, &VR[i].head, &VR[i].info);
				if (VR[i].tail == 0 && VR[i].head == 0 && VR[i].info == 0)
					break;
				i++;
			}
			printf("ͼ�����ϵ��Ϣ¼�����\n");
			if (CreateGraph(G, V, VR))
				printf("ͼ�����ɹ�\n");
			else printf("ͼ����ʧ��\n");
			exist = 1;
			getchar(); getchar();
			break;
		}
		case 2:
		{
			DestroyGraph(G);
			printf("ͼ���ٳɹ�\n");
			exist = 0;
			getchar(); getchar();
			break;
		}
		case 3:
		{
			KEY key;
			printf("������ͼ���Ĺؼ���(int):\n");
			scanf("%d", &key);
			VNode *pv;
			pv = GetVex(G, key);
			if (pv == NULL)
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", key);
			else
			{
				printf("�ؼ��֣�%d    ֵ��%c", pv->data.key, pv->data.c);
			}
			getchar(); getchar();
			break;
		}
		case 4:
		{
			KEY key;
			printf("������ͼ���Ĺؼ���(int):\n");
			scanf("%d", &key);
			int locate;
			locate = LocateVex(G, key);
			if (locate == -1)
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", key);
			else
			{
				printf("�ؼ���Ϊ%d�Ķ����λ��Ϊ%d\n", key, locate);
			}
			getchar(); getchar();
			break;
		}
		case 5:
		{
			KEY key;
			printf("������ͼ���Ĺؼ���(int):\n");
			scanf("%d", &key);
			VNode *pv;
			pv = GetVex(G, key);
			if (pv == NULL)
			{
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", key);
				getchar(); getchar();
				break;
			}
			VertexType value;
			printf("��������ĺ�ͼ���ؼ���(int) ֵ(char)\n");
			scanf("%d %c", &value.key, &value.c);
			printf("����ǰ��%d %c\n", pv->data.key, pv->data.c);
			PutVex(G, key, value);
			printf("���ĺ�%d %c\n", pv->data.key, pv->data.c);
			getchar(); getchar();
			break;
		}
		case 6:
		{
			KEY key;
			int locate;
			printf("������ͼ�����Ĺؼ���(int):\n");
			scanf("%d", &key);
			locate = LocateVex(G, key);//����v��λ��
			if (locate == -1)
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", key);
			else
			{
				locate = FirstAdjVex(G, locate);//����v�ĵ�һ�ڽӵ�λ��
				if (locate>-1)
					printf("�ؼ���Ϊ%d����ĵ�һ�ڽӶ���λ��%d �ؼ���%d ֵ%c\n", key, locate, G.vertices[locate].data.key, G.vertices[locate].data.c);
				else printf("�ؼ���Ϊ%d����ĵ�һ�ڽӶ��㲻����\n", key);
			}
			getchar(); getchar();
			break;
		}
		case 7:
		{
			KEY v;
			printf("������ͼ���Ĺؼ���(int):\n");
			scanf("%d", &v);
			if (GetVex(G, v) == NULL)
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", v);
			else
			{
				KEY w;
				printf("������ؼ���Ϊ%d�����ڽӽ��ؼ���:\n", v);
				scanf("%d", &w);
				int vlocate, wlocate, Adj;
				vlocate = LocateVex(G, v);
				wlocate = LocateVex(G, w);
				Adj = NextAdjVex(G, vlocate, wlocate);
				if (Adj>-1)
					printf("%d��������%d������һ���ڽӽ��λ��:%d �ؼ���:%d ֵ:%c", v, w, Adj, G.vertices[Adj].data.key, G.vertices[Adj].data.c);
				else
					printf("%d��������%d������һ���ڽӽ�㲻����\n", v, w);
				getchar(); getchar();
				break;
			}
		}
		case 8:
		{
			VertexType v;
			printf("�������½��Ĺؼ���(int) ֵ(char)\n");
			scanf("%d %c", &v.key, &v.c);
			InsertVex(G, v);
			VNode *pv;
			pv = GetVex(G, v.key);
			printf("�½ڵ�%d %c����ɹ�\n", pv->data.key, pv->data.c);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			KEY key;
			printf("������Ҫɾ����ͼ���Ĺؼ���(int):\n");
			scanf("%d", &key);
			if (GetVex(G, key) == NULL)
				printf("�ؼ���Ϊ%d�Ķ��㲻����\n", key);
			else
			{
				DeleteVex(G, key);
				printf("���%dɾ���ɹ�\n", key);
			}
			getchar(); getchar();
			break;

		}
		case 10:
		{
			KEY v, w;
			printf("��ֱ����뻡β���ͻ�ͷ���ؼ���\n");
			scanf("%d %d", &v, &w);
			if (GetVex(G, v) == NULL)
				printf("ͼ�в����ڶ���%d\n", v);
			else if (GetVex(G, w) == NULL)
				printf("ͼ�в����ڶ���%d\n", w);
			else
			{
				InfoType i;
				printf("�����뻡��Ȩֵ\n");
				scanf("%d", &i);
				InsertArc(G, v, w, i);
				printf("��(%d,%d)����ɹ�\n", v, w);
			}
			getchar(); getchar();
			break;
		}
		case 11:
		{
			KEY v, w;
			printf("��ֱ����뻡β���ͻ�ͷ���ؼ���\n");
			scanf("%d %d", &v, &w);
			if (GetVex(G, v) == NULL)
				printf("ͼ�в����ڶ���%d\n", v);
			else if (GetVex(G, w) == NULL)
				printf("ͼ�в����ڶ���%d\n", w);
			else
			{
				if (DeleteArc(G, v, w))
					printf("��(%d,%d)ɾ���ɹ�\n", v, w);
				else printf("ͼ���޻�(%d,%d)\n", v, w);
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
			printf("���ݱ���ɹ�\n");
			getchar(); getchar();
			break;
		}
		case 16:
		{
			LoadData(G);
			exist = 1;
			printf("���ݼ��سɹ�\n");
			getchar(); getchar();
			break;
		}
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


status CreateGraph(ALGraph &G, VertexType * V, VertexRalation * VR)
{
	/*��������*/
	G.arcnum = G.vexnum = 0;
	int i;
	ArcNode *pe, *temp;
	VNode *pv;//������ָ��
	for (i = 0; V[i].key != 0 || V[i].c != '#'; i++)
	{
		G.vertices[i].data = V[i];//����һ������
		G.vertices[i].firstarc = NULL;//�����ڽӱ��ÿ�
		G.vexnum++;//������+1
	}
	/*������*/
	for (i = 0; VR[i].head || VR[i].tail || VR[i].info; i++)
	{
		pv = GetVex(G, VR[i].tail);//��ȡ��β���ĵ�ַ
		temp = (ArcNode *)malloc(sizeof(ArcNode));//����һ���߽��
		temp->adjves = LocateVex(G, VR[i].head);
		temp->info = VR[i].info;//¼��߽����Ϣ
		temp->nextarc = pv->firstarc;
		pv->firstarc = temp;//���µı߽����ڱ����ĵ�һ�����
		G.arcnum++;//����+1
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
		}//�ͷű߽��
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
	pv = GetVex(G, v);//��ȡ���
	pv->data = value;//��㸳ֵ
	return OK;
}
status LocateVex(ALGraph &G, KEY v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			return i;//���ض����λ��
	return -1;//���㲻���ڷ���-1
}
int FirstAdjVex(ALGraph &G, int v)
{
	VNode *pv;
	pv = &G.vertices[v];
	if (pv->firstarc == NULL)//��v���ڽӱ�
		return -1;
	else return pv->firstarc->adjves;//����v�ĵ�һ�ڽӵ�λ��
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
			if (pe->nextarc != NULL)//��w����v�����һ���ڽӵ�
				return pe->nextarc->adjves;
			else return -1;//w��v�����һ���ڽӵ�
		}
	}
	return -1;//w����v���ڽӵ�
}
status InsertVex(ALGraph &G, VertexType v)
{
	G.vertices[G.vexnum].data = v;//��ֵ�������
	G.vertices[G.vexnum].firstarc = NULL;//�½ڵ��һ�ڽӱ��ÿ�
	G.vexnum++;
	return OK;
}
status DeleteVex(ALGraph &G, KEY v)
{
	int locate = LocateVex(G, v);//��λ����v
	int i;
	VNode *pv;
	ArcNode *temp, *pe, *pre;//pe�����ڽӱߣ�preָ��pe�߽���ǰ�����

	/*1.ɾ���붥��v�����ı�*/

	//1.1ɾ����vΪ��β�ı߽��
	pv = &G.vertices[locate];//ָ�򶥵�v
	pre = pe = pv->firstarc;
	while (pe)
	{
		pe = pe->nextarc;
		free(pre);
		pre = pe;
		G.arcnum--;
	}
	pv->firstarc = NULL;
	//1.2����G�����ж��㣬ɾ����vΪ��ͷ�ı߽��
	for (i = 0; i < G.vexnum; i++)
	{
		DeleteArc(G, G.vertices[i].data.key, v);
	}
	/*2.ɾ������v*/
	for (i = locate; i < G.vexnum - 1; i++)
	{
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;

	/*3.����G�б߽����ڽӵ��λ����Ϣ*/
	for (i = 0; i < G.vexnum; i++)
	{
		pv = &G.vertices[i];
		for (pe = pv->firstarc; pe; pe = pe->nextarc)
		{
			if (pe->adjves > locate)//v���֮��Ľ��λ�ö�ǰ��1
				pe->adjves--;
		}
	}
	return OK;
}
status InsertArc(ALGraph &G, KEY v, KEY w, InfoType i)
{
	int locate = LocateVex(G, v);
	ArcNode *pe;
	pe = (ArcNode *)malloc(sizeof(ArcNode));//����һ���߽��
											//��ʼ���߽��
	pe->adjves = LocateVex(G, w);
	pe->info = i;
	//���µı߽����뵽������ͷ��λ��
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
	if (pv->firstarc == NULL)//v���ڽӵ�
		return FALSE;
	int wlocate = LocateVex(G, w);//w��λ��
	if (pv->firstarc->adjves == wlocate)//���w��v�ĵ�һ�ڽӵ�
	{
		temp = pv->firstarc;
		pv->firstarc = pv->firstarc->nextarc;
		free(temp);
		G.arcnum--;
		return TRUE;
	}
	else//��v�ķǵ�һ�ڽӽ���в���w
	{
		for (pre = pe = pv->firstarc; pe; pre = pe, pe = pe->nextarc)
		{
			if (pe->adjves == wlocate)//�ҵ�
			{
				pre->nextarc = pe->nextarc;//�޸�ָ��
				free(pe);//�ͷŽ��
				G.arcnum--;
				return TRUE;
			}
		}
	}
	return FALSE;//��(v,w)������
}
status DFSTraverse(ALGraph G, status(*visit)(VNode v))
{
	int v;
	for (v = 0; v < MAX_VERTEX_NUM; v++)//����ÿ�
		visited[v] = 0;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v]) DFS(G, v, visit);//��δ���ʵĶ������DFS
	return OK;
}
void DFS(ALGraph G, int v, status(*visit)(VNode v))
{
	int w;
	visited[v] = TRUE;
	visit(G.vertices[v]);//���ʵ�v������
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w, visit);//��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}
status BFSTraverse(ALGraph G, status(*visit)(VNode v))
{
	int head, tail;
	int v, u, w;
	for (v = 0; v < MAX_VERTEX_NUM; v++)//����ÿ�
		visited[v] = 0;
	int queue[MAX_VERTEX_NUM];
	head = tail = 0;
	for (v = 0; v < G.vexnum; v++)//˳�����G�����ж���
	{
		if (!visited[v])//vδ������
		{
			visited[v] = TRUE; visit(G.vertices[v]);//����v
			queue[tail] = v;//v���
			tail = (tail + 1) % MAX_VERTEX_NUM;
			while (tail != head && (tail + 1) % MAX_VERTEX_NUM != head)//�ӷǿ�
			{
				u = queue[head];//����
				head = (head + 1) % MAX_VERTEX_NUM;
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))//u��δ�����ʵ��ڽӵ����ν���
					if (!visited[w])//u���ڽӵ�wδ������
					{
						visited[w] = TRUE;//����w
						visit(G.vertices[w]);
						queue[tail] = w;
						tail = (tail + 1) % MAX_VERTEX_NUM;//w����
					}
			}//end while
		}//end if
	}//end for
	return OK;
}
void SaveData(ALGraph G)
{
	FILE *fp;
	/*���涥����Ϣ*/
	fp = fopen(V_DATA, "w");
	fwrite(&G, sizeof(ALGraph), 1, fp);
	fclose(fp);
	/*���满��Ϣ*/
	fp = fopen(E_DATA, "w");
	int i = 0;
	ArcNode *pe;
	for (i = 0; i < G.vexnum; i++)
	{
		for (pe = G.vertices[i].firstarc; pe; pe = pe->nextarc)
		{
			fprintf(fp, "%d %d %d\n", i, pe->adjves, pe->info);//���ջ�βλ�� ��ͷλ�� ��Ȩֵ�ĸ�ʽ��������д�뵽�ļ���
		}
	}
	fclose(fp);
}
void LoadData(ALGraph &G)
{
	FILE *fp;
	int i;
	int tail, head, info;//��β����ͷ��Ȩֵ
	/*��ȡ������Ϣ*/
	fp = fopen(V_DATA, "r");
	fread(&G, sizeof(ALGraph), 1, fp);
	fclose(fp);
	for (i = 0; i < G.vexnum; i++)
		G.vertices[i].firstarc = NULL;//�ڽӱ��ÿ�
	/*��ȡ����Ϣ*/
	fp = fopen(E_DATA, "r");
	while (fscanf(fp, "%d %d %d", &tail, &head, &info) != EOF)
	{//ʹ���޸ĵ�InsertArc���뻡
		ArcNode *pe;
		pe = (ArcNode *)malloc(sizeof(ArcNode));//����һ���߽��
		//��ʼ���߽��
		pe->adjves = head;
		pe->info = info;
		//���µı߽����뵽������ͷ��λ��
		pe->nextarc = G.vertices[tail].firstarc;
		G.vertices[tail].firstarc = pe;
	}
	fclose(fp);
}