#include "dorm.h"

unsigned long ul;

int main()
{
    COORD size = {SCR_COL, SCR_ROW};              /*���ڻ�������С*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/

    SetConsoleTitle(gp_sys_name);                 /*���ô��ڱ���*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С80*25*/

    LoadData();                   /*���ݼ���*/
    InitInterface();          /*�����ʼ��*/
    RunSys(&gp_head);             /*ϵͳ����ģ���ѡ������*/
    CloseSys(gp_head);            /*�˳�ϵͳ*/

    return 0;
}


/**
 * ��������: LoadData
 * ��������: ������������������ݴ������ļ����뵽�ڴ滺������ʮ��������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ���ܺ����г��˺���ExitSys�ķ���ֵ����ΪFALSE��,
 *           ���������ķ���ֵ����ΪTRUE.
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    /*�������ݲ���������*/
    CreatList(&gp_head);
    getchar();
    return TRUE;

}


/**
 * ��������: CreatList
 * ��������: �������ļ���ȡ��������, ����ŵ���������ʮ��������.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ, ����������������ʮ����.
 * �� �� ֵ: int����ֵ, ��ʾ�����������.
 *
 * ����˵��:
 */
int CreatList(CLASS_NODE **phead)
{
    CLASS_NODE *hd = NULL, *pclass, tmp1;
    ROOM_NODE *proom, tmp2;
    RENTER_NODE *prenter, tmp3;
    FILE *pFile;
    int find;
    int re = 0;

    if ((pFile = fopen(gp_class_info_filename, "rb")) == NULL)
    {
        printf("�ͷ�������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�ͷ�������Ϣ�����ļ��򿪳ɹ�!\n");

    /*�������ļ��ж��ͷ�������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
    while (fread(&tmp1, sizeof(CLASS_NODE), 1, pFile) == 1)
    {
        pclass = (CLASS_NODE *)malloc(sizeof(CLASS_NODE));
        *pclass = tmp1;
        pclass->rnext = NULL;
        pclass->next = hd;
        hd = pclass;
    }
    fclose(pFile);
    if (hd == NULL)
    {
        printf("�ͷ�������Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("�ͷ�������Ϣ�����ļ����سɹ�!\n");
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_room_info_filename, "rb")) == NULL)
    {
        printf("�ͷ�������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�ͷ�������Ϣ�����ļ��򿪳ɹ�!\n");
    re += 8;

    /*�������ļ��ж�ȡѧ��������Ϣ���ݣ�����������Ӧ����ѧ��������Ϣ֧����*/
    while (fread(&tmp2, sizeof(ROOM_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж�����ѧ��������Ϣ*/
        proom = (ROOM_NODE *)malloc(sizeof(ROOM_NODE));
        *proom = tmp2;
        proom->rnext = NULL;

        /*�������ϲ��Ҹ�ѧ����ס����¥��Ӧ���������*/
        pclass = hd;
        while (pclass != NULL
               && pclass->type!=proom->type)
        {
            pclass = pclass->next;
        }
        if (pclass != NULL) /*����ҵ����򽫽���Ժ���ȳ���ʽ����ѧ����Ϣ֧��*/
        {
            proom->next = pclass->rnext;
            pclass->rnext = proom;
        }
        else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(proom);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_renter_info_filename, "rb")) == NULL)
    {
        printf("�����Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�����Ϣ�����ļ��򿪳ɹ�!\n");
    re += 16;

    /*�������ļ��ж�ȡѧ���ɷ���Ϣ���ݣ�����ѧ��������Ϣ֧����Ӧ���Ľɷ�֧����*/
    while (fread(&tmp3, sizeof(RENTER_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж�����ѧ���ɷ���Ϣ*/
        prenter = (RENTER_NODE *)malloc(sizeof(RENTER_NODE));
        *prenter = tmp3;

        /*����ѧ����Ϣ֧���϶�Ӧѧ����Ϣ���*/
        pclass = hd;
        find = 0;
        while (pclass != NULL && find == 0)
        {
            proom = pclass->rnext;
            while (proom != NULL && find == 0)
            {
                if (strcmp(proom->room_id, prenter->room_id) == 0)
                {
                    find = 1;
                    break;
                }
                proom = proom->next;
            }
            pclass = pclass->next;
        }
        if (find)  /*����ҵ����򽫽���Ժ���ȳ���ʽ����ѧ���ɷ���Ϣ֧����*/
        {
            prenter->next = proom->rnext;
            proom->rnext = prenter;
        }
        else /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(prenter);
        }
    }
    fclose(pFile);


    return re;
}

/**
 * ��������: InitInterface
 * ��������: ��ʼ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               ;  /*��ɫǰ������ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

    ClearScreen();  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*��ʾ�˵���*/
    ShowState();    /*��ʾ״̬��*/

    return;
}

/**
 * ��������: ClearScreen
 * ��������: �����Ļ��Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*ȡ��Ļ��������Ϣ*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    fflush(stdin);

    return;
}

/**
 * ��������: ShowMenu
 * ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

    return;
}

/**
 * ��������: ShowState
 * ��������: ��ʾ״̬��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
 */
void ShowState()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int i;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SMALL_RECT rcMenu ={0, bInfo.dwSize.Y-1, size.X-1, bInfo.dwSize.Y-1};

    if (gp_buff_stateBar_info == NULL)
    {
        gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
        ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
    }

    for (i=0; i<size.X; i++)
    {
        (gp_buff_stateBar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                                | BACKGROUND_RED;
/*
        ch = (char)((gp_buff_stateBar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_stateBar_info+i)->Attributes |= FOREGROUND_RED;
        }
*/
    }

    WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: TagMainMenu
 * ��������: ��ָ�����˵�������ѡ�б�־.
 * �������: num ѡ�е����˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: CloseSys
 * ��������: �ر�ϵͳ.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CloseSys(CLASS_NODE *hd)
{
    CLASS_NODE *pDormNode1 = hd, *pDormNode2;
    ROOM_NODE *pStuNode1, *pStuNode2;
    RENTER_NODE *pChargeNode1, *pChargeNode2;

    while (pDormNode1 != NULL) /*�ͷ�ʮ�ֽ�������Ķ�̬�洢��*/
    {
        pDormNode2 = pDormNode1->next;
        pStuNode1 = pDormNode1->rnext;
        while (pStuNode1 != NULL) /*�ͷ�ѧ��������Ϣ֧���Ķ�̬�洢��*/
        {
            pStuNode2 = pStuNode1->next;
            pChargeNode1 = pStuNode1->rnext;
            while (pChargeNode1 != NULL) /*�ͷŽɷ���Ϣ֧���Ķ�̬�洢��*/
            {
                pChargeNode2 = pChargeNode1->next;
                free(pChargeNode1);
                pChargeNode1 = pChargeNode2;
            }
            free(pStuNode1);
            pStuNode1 = pStuNode2;
        }
        free(pDormNode1);  /*�ͷ��������Ķ�̬�洢��*/
        pDormNode1 = pDormNode2;
    }

    ClearScreen();        /*����*/

    /*�ͷŴ�Ų˵�����״̬�����Ա�����ѧ�����������Ϣ��̬�洢��*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);

    /*�رձ�׼���������豸���*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*�����ڱ�������Ϊ���н���*/
    SetConsoleTitle("���н���");

    return;
}

/**
 * ��������: RunSys
 * ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void RunSys(CLASS_NODE **phead)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
    char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                 * cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                 * gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff(); /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112) /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*������������Alt��*/
                switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:  /*Alt+X �˳�*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:  /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77: /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81: /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83: /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72: /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0) /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
                {
                    switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else  /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70: /*f��F*/
                            PopMenu(1);
                            break;
                        case 77: /*m��M*/
                            PopMenu(2);
                            break;
                        case 81: /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s��S*/
                            PopMenu(4);
                            break;
                        case 72: /*h��H*/
                            PopMenu(5);
                            break;
                        case 13: /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27) /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*���ƥ��ɹ�*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * ��������: PopMenu
 * ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
 * �������: num ָ�������˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh;
    int i, j, loc = 0;

    if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/
    TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/
    LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
    COORD aLoc[labels.num];/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    for (i=0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*���������ڻ��߿�*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*����Ϊ0������Ϊ�մ�*/
        {   /*���Ȼ�����*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*ȡ���������ַ���Ԫ����������*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*��λ��Ľ�������˵���λ*/
            }
        }

    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*�����մ�*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * ��������: PopUp
 * ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
 * �������: pRc ��������λ�����ݴ�ŵĵ�ַ
 *           att �������������ַ�����
 *           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
             pHotArea ����������������Ϣ��ŵĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/**
 * ��������: PopOff
 * ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * ��������: DrawBox
 * ��������: ��ָ�����򻭱߿�.
 * �������: pRc �������λ����Ϣ�ĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};  /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*��ѭ�����߿�����ߺ��ұ���*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*���±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/**
 * ��������: TagSubMenu
 * ��������: ��ָ���Ӳ˵�������ѡ�б��.
 * �������: num ѡ�е��Ӳ˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
    return;
}

/**
 * ��������: LocSubMenu
 * ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
 * �������: num ѡ�е����˵����
 * �������: rc �������λ����Ϣ�ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * ��������: DealInput
 * ��������: �ڵ�������������������, �ȴ�����Ӧ�û�����.
 * �������: pHotArea
 *           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
 * �������: piHot ����굥�������س���ո�ʱ���ص�ǰ�������
 * �� �� ֵ:
 *
 * ����˵��:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC��*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*�س�����ո��ʾ���µ�ǰ��ť*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {  /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * ��������: ExeFunction
 * ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
 * �������: m ���˵����
 *           s �Ӳ˵����
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
    pFunction[0] = SaveData;
    pFunction[1] = ExitSys;
    /*=========================================*/
    pFunction[2] = Insertclass;
    pFunction[3] = Maintainclass;
    pFunction[4] = Delclass;

    pFunction[5] = Insertroom;
    pFunction[6] = Maintainroom;
    pFunction[7] = Delroom;

    pFunction[8] = Insertrenter;
    pFunction[9] = Maintainrenter;
    pFunction[10] = Delrenter;
    /*=========================================*/
    pFunction[11] = Queryclass;
    pFunction[12] = Queryroom;
    pFunction[13] = Queryrenter;

    pFunction[14] = Query;
    pFunction[15] = QueryTypeInfo;
    /*=========================================*/
    pFunction[16] = Staclass;
    pFunction[17] = Staincome;
    pFunction[18] = Staroom_info;
    pFunction[19] = Starenter_info;
    pFunction[20] = Sta_in;
    /*=========================================*/
    pFunction[21] = HelpTopic;
    pFunction[22] = AboutDorm;
    pFunction[23] = Clear;

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}
/*=========================================*/
/**����ͷ�������Ϣ*/
BOOL Insertclass()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵������ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    CLASS_NODE *pclass;
    CLASS_NODE *pc;
    pclass=(CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    /*¼ȡ�ͷ�������Ϣ*/
    printf("               ***************������ͷ����S,D,T��  ***************");
    printf("                    \n               ***************    ");
    pclass->type=toupper(getchar());
    getchar();
    printf("               ***************�����������ס�������������֣�  ***************");
    printf("                    \n               ***************    ");
    scanf("%d",&pclass->pnum);
    getchar();
    printf("               ***************������ͷ�����������һλ���֣�  ***************");
    printf("                    \n               ***************    ");
    scanf("%d",&pclass->rnum);
    getchar();
    printf("               ***************������δס����������һλ���֣�  ***************");
    printf("                    \n               ***************    ");
    scanf("%d",&pclass->emptyr);
    getchar();
    printclass(pclass);
    printf("               ***************�Ƿ񱣴棿(y��n��  ***************");
    printf("                    \n               ***************    ");
    /*�Ƿ񱣴�*/
    char c=getchar();
    getchar();
    if(c=='y'||c=='Y')
    {
        /*�жϿͷ�����Ƿ���ڣ������򸲸ǣ������ڴ����½ڵ�*/
        for(pc=gp_head;pc!=NULL;pc=pc->next)
            if(pc->type==pclass->type)
        {
            //����ִ����һ��
            printf("�ͷ�����Ѵ��ڣ��޸ĳɹ���\n");
            /*�޸�������*/
            pclass->next=pc->next;
            pclass->rnext=pc->rnext;
            *pc=*pclass;
            free(pclass);
            return TRUE;
        }
        //������ִ����һ��
        pclass->next=gp_head;
        pclass->rnext=NULL;
        gp_head=pclass;
        printf("����ɹ���\n");
        return TRUE;
    }
    //������
    printf("����ʧ�ܣ�\n");
    free(pclass);
    putchar('\n');
    putchar('\n');

    return TRUE;
}
/**��ѯ�ͷ�������Ϣ*/
BOOL Queryclass()
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵����ѯ�ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    Maintain_in();
    printf("               ***************������ͷ����S,D,T��  ***************");
    printf("                    \n               ***************    ");
    /*��ȡ�û�����*/
    char c=getchar();
    c=toupper(c);
    getchar();
    CLASS_NODE *pclass;
    pclass=gp_head;
    //�����ͷ���������������Ŀ��ڵ�*/
    while(pclass!=NULL&&pclass->type!=c)
    {
        pclass=pclass->next;
    }
    if(pclass==NULL)//û���ҵ�
        printf("�޲�ѯ�����\n");
    else printclass(pclass);//�ҵ�
    putchar('\n');
    return TRUE;
}
/**�޸Ŀͷ�������Ϣ*/
BOOL Maintainclass()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���޸Ŀͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    printf("               ***************������Ҫ�޸ĵĿͷ����S,D,T��  ***************");
    printf("                    \n               ***************    ");
    char type=getchar();
    getchar();
    type=toupper(type);
    CLASS_NODE *pclass;
    CLASS_NODE *pclass1;
    pclass=(CLASS_NODE *)malloc(sizeof(CLASS_NODE));
    for(pclass1=gp_head;pclass1!=NULL&&pclass1->type!=type;pclass1=pclass1->next);
    if(pclass1==NULL)
    {//�ͷ���𲻴��ڣ���������
        printf("�ͷ���𲻴��ڣ�");
        return TRUE;
    }
    *pclass=*pclass1;
    printf("               ===============�޸������ס�����밴��1��       ===============\n");
    printf("               ===============�޸Ŀͷ������밴��2��           ===============\n");
    printf("               ***************     ");
    char key=getchar();
    while(key!='1'&&key!='2')
    {
        printf("�������\n");
        key=getchar();
    }
    getchar();
    /*�޸Ŀͷ������Ϣ*/
    switch(key)
    {
        case '1':
            {
                printf("               ===============���������������ס����,��ǰΪ%d      ===============\n",pclass->pnum);
                printf("               ===============");
                scanf("%d",&pclass->pnum);
                getchar();
                break;

            }
        case '2':
            {
                printf("               ===============����������ͷ�����,��ǰΪ%d     ===============\n",pclass->rnum);
                printf("               ===============");
                scanf("%d",&pclass->rnum);
                getchar();
                break;
            }
        default:
            {
                printf("�������\n");
                break;
            }

    }
    printf("�޸ĺ�Ľ��Ϊ��\n");
    printclass(pclass);
    printf("�Ƿ�ȷ��?��y����n��\n");
    char ch=getchar();
    ch=toupper(ch);
    getchar();
    if(ch=='Y')//���б���
    {
        *pclass1=*pclass;
        printf("�޸ĳɹ���\n");
        printclass(pclass1);
    }
    //������
    free(pclass);
    return TRUE;
}
/**ɾ���ͷ�������Ϣ*/
BOOL Delclass()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ɾ���ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
   printf("\n\n               ***************���棡ɾ���ͷ�������Ϣ��ɾ��������µĿͷ�������Ϣ�������Ϣ�������������");
   printf("                    \n               ***************    ");
   printf("�˳�������'n',��������������");
   char c;
   printf("                    \n               ***************    ");
   c=getchar();
   if(c=='n')
    return TRUE;
   fflush(stdin);
   printf("                    \n               ***************    ");
   printf("������Ҫɾ���Ŀͷ����(S,D,T)��");
   printf("                    \n               ***************    ");
   char type=getchar();
   type=toupper(type);
   getchar();
   CLASS_NODE *pclass;
   CLASS_NODE *pb;
   ROOM_NODE *proom;
    RENTER_NODE *prenter;
   pclass=gp_head;
   for(pclass=gp_head;(pclass!=NULL)&&(pclass->type!=type);pb=pclass,pclass=pclass->next);
   if(pclass==gp_head)//����ڵ�λ����ͷ
    gp_head=pclass->next;
   else pb->next=pclass->next;//����ڵ�λ������
   if(pclass==NULL)//����ڵ㲻����
   {
       printf("�ͷ���𲻴��ڣ�");
       return TRUE;
   }
   /*�ͷſͷ�������Ϣ�µ�֧��*/
   proom=pclass->rnext;
   while(proom!=NULL)
   {
       prenter=proom->rnext;
       while(prenter!=NULL)
       {
           free(prenter);
           prenter=prenter->next;
       }
       free(proom);
       proom=proom->next;
   }
   free(pclass);//�ͷ����
   printf("               ***************    ");
   printf("ɾ���ɹ���\n");
   return TRUE;
}
/*=========================================*/
/*=========================================*/
/**����ͷ�������Ϣ*/
BOOL Insertroom()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵������ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    CLASS_NODE *pclass;
    CLASS_NODE *hd;
    hd=gp_head;
    /*¼��ͷ�������Ϣ*/
    ROOM_NODE *proom,*pr;
    proom=(ROOM_NODE *)malloc(sizeof(ROOM_NODE));
    printf("               ***************������ͷ����                 ***************");
    printf("                    \n               ***************    ");
    gets(proom->room_id);
    printf("               ***************������绰����                 ***************");
    printf("                    \n               ***************    ");
    gets(proom->tel);
    printf("               ***************������ͷ����                 ***************");
    printf("                    \n               ***************    ");
    scanf("%c",&proom->type);
    proom->type=toupper(proom->type);
    getchar();
    printf("               ***************������ͷ����                 ***************");
    printf("                    \n               ***************    ");
    scanf("%f",&proom->area);
    getchar();
    printf("               ***************������ÿ�����                 ***************");
    printf("                    \n               ***************    ");
    scanf("%f",&proom->deposit);
    getchar();
    printf("               ***************�������Ƿ�����̨(1�У�0��)     ***************");
    printf("                    \n               ***************    ");
    scanf("%c",&proom->balcony);
    getchar();
    printf("               ***************�������Ƿ��п�����ס(y�У�n��) ***************");
    printf("                    \n               ***************    ");
    scanf("%c",&proom->in);
    getchar();
    printroom(proom);
    proom->rnext=NULL;
    /*�Ƿ񱣴�*/
    printf("               ***************�Ƿ񱣴棿(y��n��              ***************");
    printf("                    \n               ***************    ");
    char c=getchar();
    getchar();
    if(c=='y'||c=='Y')
    {//����
        for(pclass=hd;pclass!=NULL&&proom->type!=pclass->type;pclass=pclass->next);
        if(pclass==NULL)
        {
            printf("�ͷ���𲻴��ڣ�");
            return TRUE;
        }
        /*���ҿͷ�����Ƿ����*/
        pr=seekroom(gp_head,proom->room_id);
        if(pr!=NULL)
        {//�����޸�ԭ���Ŀͷ���Ϣ��Ȼ���˳�*/
            /*�޸�������*/
            proom->next=pr->next;
            proom->rnext=pr->rnext;
            *pr=*proom;
            free(proom);
            printf("�ͷ�����Ѵ��ڣ��޸ĳɹ���");
            return TRUE;
        }
        proom->next=pclass->rnext;
        pclass->rnext=proom;

        printf("����ɹ���\n");
        return TRUE;
    }
    //������
    printf("����ʧ�ܣ�\n");
    free(proom);
    putchar('\n');
    putchar('\n');

}
/**�޸Ŀͷ�������Ϣ*/
BOOL Maintainroom()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���޸Ŀͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    printf("               ***************������Ҫ�޸ĵĿͷ����  ***************");
    printf("                    \n               ***************    ");
    char roomid[8];
    gets(roomid);

    ROOM_NODE *proom;
    ROOM_NODE *temp;
    temp=(ROOM_NODE *)malloc(sizeof(ROOM_NODE));
    proom=seekroom(gp_head,roomid);

    *temp=*proom;
    printroom(proom);
    printf("               ===============�޸Ŀͷ�����밴��1��       ===============\n");
    printf("               ===============�޸Ŀͷ��绰�밴��2��       ===============\n");
    printf("               ===============�޸Ŀͷ�����밴��3��       ===============\n");
    printf("               ===============�޸Ŀͷ�����밴��4��       ===============\n");
    printf("               ===============�޸�ÿ������밴��5��       ===============\n");
    printf("               ===============�޸Ŀͷ���̨�밴��6��       ===============\n");
    printf("               ***************     ");
    char key=getchar();
    while(key<'1'||key>'6')
    {
        printf("�����������������\n");
        key=getchar();
    }
    getchar();
    switch(key)
    {
        case '1':
            {
                printf("               ===============����������ͷ����      ===============\n");
                printf("               ===============");
                gets(temp->room_id);
                break;

            }
        case '2':
            {
                printf("               ===============����������ͷ��绰     ===============\n");
                printf("               ===============");
                gets(temp->tel);
                break;
            }
        case '3':
            {
                printf("               ===============����������ͷ����     ===============\n");
                printf("               ===============");
                temp->type=getchar();
                getchar();
                break;
            }
        case '4':
            {
                printf("               ===============����������ͷ����      ===============\n");
                printf("               ===============");
                scanf("%f",&temp->area);
                getchar();
                break;

            }
        case '5':
            {
                printf("               ===============����������ÿ�����      ===============\n");
                printf("               ===============");
                scanf("%f",&temp->deposit);
                getchar();
                break;

            }
        case '6':
            {
                printf("               ===============�����������Ƿ�����̨(������1��������0)     ===============\n");
                printf("               ===============");
                temp->balcony=getchar();
                getchar();
                break;

            }
        default:
            {
                printf("�������\n");
                break;
            }

    }
    printf("�޸ĺ�Ľ��Ϊ��\n");
    printroom(temp);
    printf("�Ƿ�ȷ��?��y����n��\n");
    char ch=getchar();
    ch=toupper(ch);
    getchar();
    if(ch=='Y')
    {
        *proom=*temp;
        printf("�޸ĳɹ���\n");
        printroom(proom);
    }
    free(temp);
    return TRUE;
}
/**��ѯ�ͷ�������Ϣ*/
BOOL Queryroom()
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵����ѯ�ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    Maintain_in();
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    printf("               ===============���ݿͷ���Ų�ѯ�밴��1��       ===============\n");
    printf("               ===============���ݿͷ�����Ѻ���ѯ�밴��2�� ===============\n");
    printf("               ***************     ");
    char key=getchar();
    while(key!='1'&&key!='2')
    {
        printf("�����������������\n");
        key=getchar();
    }
    getchar();
    switch(key)
    {
        case '1':
            {
                printf("               ***************     ������ͷ����\n");
                printf("               ***************     ");
                char r_id[10];
                gets(r_id);
                for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
                {
                    proom=pclass->rnext;
                    while(proom!=NULL)
                    {
                        if(strcmp(proom->room_id,r_id)==0)
                            {
                                printroom(proom);
                                printf("\n\n");
                                return TRUE;
                            }
                        proom=proom->next;
                    }
                }
                printf("�޽��!\n");
                printf("\n\n");

                return TRUE;

            }
        case '2':
            {
                printf("               ***************     ������ͷ����\n");
                printf("               ***************     ");
                char type=getchar();
                type=toupper(type);
                getchar();
                for(pclass=gp_head;pclass!=NULL&&pclass->type!=type;pclass=pclass->next);
                if(pclass==NULL)
                {
                   printf("               ***************     ");
                   printf("�޽��!\n\n");
                   return TRUE;
                }
                printf("               ***************     ������ͷ����\n");
                float money;
                int find=0;
                printf("               ***************     ");
                scanf("%f",&money);
                getchar();
                proom=pclass->rnext;
                while(proom!=NULL)
                {
                    if(fabs(money-proom->deposit)<1)
                        {
                            printroom(proom);
                            find=1;
                        }
                    proom=proom->next;
                }
                if(find==0)
                {
                    printf("               ***************     ");
                    printf("û���ҵ�\n");
                }
                printf("\n\n");
                return TRUE;


            }
        default:
            {
                printf("�������\n");
                break;
            }

    }

}
/**ɾ���ͷ�������Ϣ*/
BOOL Delroom()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ɾ���ͷ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
   printf("\n\n               ***************���棡ɾ���ͷ�������Ϣ��ɾ��������������Ϣ�������������");
   printf("                    \n               ***************    ");
   printf("�˳�������'n',��������������");
   char c;
   c=getchar();
   if(c=='n')
    return TRUE;
   fflush(stdin);
   printf("                    \n               ***************    ");
   printf("������Ҫɾ���Ŀͷ���ţ�");
   printf("                    \n               ***************    ");
   char room_id[4];
   gets(room_id);
   CLASS_NODE *pclass;
   ROOM_NODE *proom;
   ROOM_NODE *pr;//��¼proomָ��ڵ��ǰһ���ڵ�
   RENTER_NODE *prenter;
   for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
   {
       proom=pclass->rnext;
       while(proom!=NULL)
       {
           if(strcmp(proom->room_id,room_id)==0)//����ҵ�,�ı�����ָ���ϵ
            {
                if(proom==pclass->rnext)//����ڵ�λ��ͷ��
                {
                    pclass->rnext=proom->next;
                }
                else //����ڵ�λ������
                {
                    pr->next=proom->next;
                }
                /*ɾ���ڵ�*/
                prenter=proom->rnext;
                while(prenter!=NULL)
                {
                    free(prenter);
                    prenter=prenter->next;
                }
                printroom(proom);
                free(proom);
                printf("ɾ���ɹ���");
                return TRUE;
            }
           pr=proom;
           proom=proom->next;
       }

   }
   printf("δ�ҵ�!\n");
    return TRUE;

}
/*=========================================*/
/*=========================================*/
/**���������Ϣ*/
BOOL Insertrenter()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵�����������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    ROOM_NODE *proom;
    RENTER_NODE *prenter,*pr;
    prenter=(RENTER_NODE *)malloc(sizeof(RENTER_NODE));
    /*¼�������Ϣ*/
    printf("               ***************���������֤�ţ�18λ��  ***************");
    printf("                    \n               ***************    ");
    gets(prenter->id_card);
    while(strlen(prenter->id_card)!=18)
    {
        printf("                    \n               ***************    ");
        printf("���֤�Ŵ������������룡\n");
        printf("                    \n               ***************    ");
        gets(prenter->id_card);
    }
    printf("               ***************�������������  ***************");
    printf("                    \n               ***************    ");
    gets(prenter->name);
    printf("               ***************��������ס�ͷ����  ***************");
    printf("                    \n               ***************    ");
    gets(prenter->room_id);
    printf("               ***************��������סʱ��(��2015/03/05-13:00)  ***************");
    printf("                    \n               ***************    ");
    gets(prenter->date_in);
    printf("               ***************�������˷�ʱ��(��ס����س�)  ***************");
    printf("                    \n               ***************    ");
    gets(prenter->date_out);
    prenter->months=Maintain_month(prenter->date_in,prenter->date_out);
    proom=seekroom(gp_head,prenter->room_id);
    if(proom==NULL)
        return TRUE;
    prenter->deposit=proom->deposit;
    if(prenter->date_out[0]!='\0')//��������Ѿ��˷�
        {
            prenter->shouldpay=proom->deposit*prenter->months;
            printf("                    \n               ***************    ");
            printf("��ס����Ϊ%.1f\n",prenter->months);
            printf("                    \n               ***************    ");
            printf("Ӧ�ɷ���Ϊ%.1f\n",prenter->shouldpay);
            printf("                    \n               ***************    ");
            printf("������ʵ�ɷ���\n");
            printf("                    \n               ***************    ");
            scanf("%f",&prenter->realpay);
            getchar();
        }
    else {
        prenter->months=prenter->shouldpay=prenter->realpay=0;
    }
    printrenter(prenter);
    printf("               ***************�Ƿ񱣴棿(y��n��  ***************");
    printf("                    \n               ***************    ");
    char c=getchar();
    getchar();
    if(c=='y'||c=='Y')
    {
        proom=seekroom(gp_head,prenter->room_id);
        if(proom==NULL)
        {
            printf("δ�ҵ��ͷ���");
            return TRUE;
        }
        pr=seekrenter(gp_head,prenter->date_in,prenter->id_card);
        /*�ж������Ϣ�Ƿ��Ѿ�����*/
        if(pr!=NULL&&strcmp(pr->room_id,prenter->room_id)==0)
        {//����͸�����Ϣ����ס���ڣ���ס�ͷ������ͬ�������Ϣ����
            /*�޸�������*/
            prenter->next=pr->next;
            *pr=*prenter;
            free(prenter);
            printf("������Ϣ�Ѵ���,�޸ĳɹ���");
            return TRUE;
        }
        prenter->next=proom->rnext;
        proom->rnext=prenter;
        printf("����ɹ���\n");
        proom->in='y';
        fflush(stdin);
        return TRUE;
    }
    printf("����ʧ�ܣ�\n");
    free(prenter);
    putchar('\n');
    putchar('\n');
    putchar('\n');

    return TRUE;
}
/**��ѯ�����Ϣ*/
BOOL Queryrenter()
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵����ѯ�����Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    /*��ȡ�û�����*/
    printf("               ===============����������֤�Ų�ѯ�밴��1��       ===============\n");
    printf("               ===============���ݿ��˵��պ���סʱ���ѯ�밴��2�� ===============\n");
    printf("               ===============���ݿ��˵����ֺ���סʱ���ѯ�밴��3�� ===============\n");
    printf("               ***************     ");
    char key=getchar();
    while(key!='1'&&key!='2'&&key!='3')
    {
        printf("�����������������\n");
        key=getchar();
    }
    getchar();
    int find=0;
    switch(key)
    {
        case '1':
            {
                printf("               ***************     ������������֤��\n");
                printf("               ***************     ");
                char id_card[20];
                gets(id_card);
                while(strlen(id_card)!=18)
                {
                    printf("                    \n               ***************    ");
                    printf("���֤�Ŵ������������룡\n");
                    printf("                    \n               ***************    ");
                    gets(id_card);
                }
                for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
                {
                    proom=pclass->rnext;
                    while(proom!=NULL)
                    {
                        prenter=proom->rnext;
                        while(prenter!=NULL)
                        {
                            if(strcmp(prenter->id_card,id_card)==0)//����ҵ������֤��
                            {
                                printrenter(prenter);//��������Ϣ
                            }
                            prenter=prenter->next;
                        }
                        proom=proom->next;
                    }
                }


                return TRUE;

            }
        case '2':
            {
                /*��ȡ������Ϣ*/
                printf("               ***************     ��������˵���\n");
                printf("               ***************     ");
                char firstname[3];
                gets(firstname);
                printf("               ***************     ��������ס��ʼʱ��(ʱ���ʽΪ2015/05/07)\n");
                printf("               ***************     ");
                char date1[18];
                gets(date1);
                printf("               ***************     ��������ס����ʱ��(ʱ���ʽΪ2015/05/07)\n");
                printf("               ***************     ");
                char date2[18];
                gets(date2);
                for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
                {

                    for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
                    {

                        for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
                        {

                            if(strncmp(prenter->name,firstname,2)==0&&Judgedate(date1,date2,prenter->date_in)==1)//������˵��շ��ϲ��������ڸ�����Χ֮��
                                printrenter(prenter);//��������Ϣ
                        }
                    }
                }

                return TRUE;

            }
        case '3':
            {
                int find=0;
                printf("               ***************     ��������˵�����\n");
                printf("               ***************     ");
                char name[3];
                gets(name);
                printf("               ***************     ��������ס��ʼʱ��(ʱ���ʽΪ2015/05/07)\n");
                printf("               ***************     ");
                char date1[18];
                gets(date1);
                printf("               ***************     ��������ס����ʱ��(ʱ���ʽΪ2015/05/07)\n");
                printf("               ***************     ");
                char date2[18];
                gets(date2);
                for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
                {

                    for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
                    {

                        for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
                        {

                            if(strcmp(prenter->name,name)==0&&Judgedate(date1,date2,prenter->date_in)==1)//������˵��������ϲ��������ڸ�����Χ֮��
                                {printrenter(prenter);find=1;}
                        }
                    }
                }
                if(find==0)
                    printf("δ�ҵ������\n");
                return TRUE;
            }
        default:
            {
                printf("�������\n");
                break;
            }

    }

}
/**�޸������Ϣ*/
BOOL Maintainrenter()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���޸������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    printf("               ***************������������֤��  ***************");
    printf("                    \n               ***************    ");
    char id_card[20];
    gets(id_card);
    while(strlen(id_card)!=18)
    {
        printf("                    \n               ***************    ");
        printf("���֤�Ŵ������������룡\n");
        printf("                    \n               ***************    ");
        gets(id_card);
    }
    printf("               ***************�����������ס���ڣ���ȷ���գ���2015/05/06,�޸���ס������س���  ***************");
    printf("                    \n               ***************    ");
    char date[18];
    gets(date);
    while(strlen(date)!=10)
    {
        printf("                    \n               ***************    ");
        printf("��������������������룡\n");
        printf("                    \n               ***************    ");
        gets(date);
    }
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    RENTER_NODE *temp;
    temp=(RENTER_NODE *)malloc(sizeof(RENTER_NODE));

    prenter=seekrenter(gp_head,date,id_card);
    if(prenter==NULL)
    {
        return TRUE;
    }
    printrenter(prenter);
    *temp=*prenter;
    printf("               ===============�޸����֤���밴��1��           ===============\n");
    printf("               ===============�޸Ŀ��������밴��2��           ===============\n");
    printf("               ===============�޸���ס�ͷ�����밴��3��       ===============\n");
    printf("               ===============�޸���סʱ���밴��4��           ===============\n");
    printf("               ===============�޸��˷�ʱ���밴��5��           ===============\n");
    printf("               ===============�޸�Ѻ���밴��6��               ===============\n");
    printf("               ===============�޸�Ӧ�ɷ����밴��7��           ===============\n");
    printf("               ===============�޸�ʵ�ɷ����밴��8��           ===============\n");
    printf("               ***************     ");
    char key=getchar();
    while(key<'1'||key>'9')
    {
        printf("�����������������\n");
        key=getchar();
    }
    getchar();
    switch(key)
    {
        case '1':
            {
                printf("               ===============�������������֤��      ===============\n");
                printf("               ===============");
                gets(temp->id_card);
                break;

            }
        case '2':
            {
                printf("               ===============�����������������     ===============\n");
                printf("               ===============");
                gets(temp->name);
                break;
            }
        case '3':
            {
                printf("               ===============����������ͷ����     ===============\n");
                printf("               ===============");
                gets(temp->room_id);
                break;
            }
        case '4':
            {
                printf("               ===============������������סʱ��      ===============\n");
                printf("               ===============");
                gets(temp->date_in);
                break;

            }
        case '5':
            {
                printf("               ===============�������˷�ʱ��      ===============\n");
                printf("               ===============");
                gets(temp->date_out);
                temp->months=Maintain_month(temp->date_in,temp->date_out);
                temp->months=Maintain_month(temp->date_in,temp->date_out);
                break;
            }
        case '6':
            {
                printf("               ===============����������Ѻ��      ===============\n");
                printf("               ===============");
                scanf("%f",&temp->deposit);
                getchar();
                break;
            }
        case '7':
            {
                printf("               ===============����������Ӧ�ɷ���      ===============\n");
                printf("               ===============");
                scanf("%f",&temp->shouldpay);
                getchar();

            }
        case '8':
            {
                printf("               ===============����������ʵ�ɷ���      ===============\n");
                printf("               ===============");
                scanf("%f",&temp->realpay);
                getchar();
                break;
            }

        default:
            {
                printf("�������\n");
                break;
            }

    }
    printf("�޸ĺ�Ľ��Ϊ��\n");
    printrenter(temp);
    printf("�Ƿ�ȷ��?��y����n��\n");
    char ch=getchar();
    ch=toupper(ch);
    getchar();
    if(ch=='Y')
    {
        if(key=='3')
        {
            proom=seekroom(gp_head,prenter->room_id);
            proom->in='n';
            proom=seekroom(gp_head,temp->room_id);
            proom->in='y';
        }
        if(key=='5'&&prenter->date_out[0]=='\0')
        {
            proom=seekroom(gp_head,prenter->room_id);
            proom->in='n';
        }
        *prenter=*temp;
        printf("�޸ĳɹ���\n");
        printrenter(prenter);
        return TRUE;
    }
    free(temp);
    printf("����ʧ��\n");
    return TRUE;
}
/**ɾ�������Ϣ*/
BOOL Delrenter()
{
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ɾ�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    printf("                    \n               ***************    ");
    printf("������Ҫɾ����������֤�ţ�");
    printf("                    \n               ***************    ");
    char id_card[20];
    gets(id_card);
    while(strlen(id_card)!=18)
    {
        printf("                    \n               ***************    ");
        printf("���֤�Ŵ������������룡\n");
        printf("                    \n               ***************    ");
        gets(id_card);
    }
    printf("                    \n               ***************    ");
    printf("�����������ס����(��2015/06/05)");
    printf("                    \n               ***************    ");
    char date[18];
    gets(date);
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    RENTER_NODE *pb;
    prenter=seekrenter(gp_head,date,id_card);
    proom=seekroom(gp_head,prenter->room_id);
    if(prenter==proom->rnext)
    {//����ڵ�λ��֧��ͷ��
        proom->rnext=prenter->next;
        free(prenter);
        return TRUE;
    }
    /*�ڵ�λ��֧���ڲ�*/
    prenter=proom->rnext;
    pb=proom->rnext;
    while(prenter!=NULL)
    {

        if(strncmp(prenter->date_in,date,10)==0&&strcmp(prenter->id_card,id_card)==0)
        {//�ͷ��ڴ�ռ�
            pb->next=prenter->next;
            free(prenter);
            printf("ɾ���ɹ���\n");
            return TRUE;
        }
        pb=prenter;
        prenter=prenter->next;
    }
    printf("δ�ҵ�");
    return TRUE;
}
/*=========================================*/
/*=========================================*/
/**ͳ��ͳ��ÿ�����Ŀͷ���������ס����δס��*/
BOOL Staclass()
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ͳ��ͳ��ÿ�����Ŀͷ���������ס����δס��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    Maintain_in();//���¿ͷ���ס���
    int allroom,inroom,emptyroom;//�ֱ�Ϊ�ͷ�����������ס����δ��ס��
    int totalroom,totalinroom,totalemptyroom;//�ϼƵĿͷ��ͷ�����������ס����δ��ס��
    totalroom=totalinroom=totalemptyroom=0;
    CLASS_NODE *pclass;

    for(pclass=gp_head;pclass!=NULL&&pclass->type!='S';pclass=pclass->next);//����������pclassָ���˼�ͷ����
    allroom=pclass->rnum;
    emptyroom=pclass->emptyr;
    inroom=allroom-emptyroom;
    totalroom+=allroom;
    totalinroom+=inroom;
    totalemptyroom+=emptyroom;
    printf("+------------------------------------------------------------------+\n");
    printf("+        �ͷ����        �ͷ�����        ����ס��        δ��ס��  +\n");
    printf("+------------------------------------------------------------------+\n");
    printf("+        ���˼�  %16d%16d%16d  +\n",allroom,inroom,emptyroom);

    for(pclass=gp_head;pclass!=NULL&&pclass->type!='D';pclass=pclass->next);//����������pclassָ��˫�˼�ͷ����
    allroom=pclass->rnum;
    emptyroom=pclass->emptyr;
    inroom=allroom-emptyroom;
    totalroom+=allroom;
    totalinroom+=inroom;
    totalemptyroom+=emptyroom;
    printf("+------------------------------------------------------------------+\n");
    printf("+        ˫�˼�  %16d%16d%16d  +\n",allroom,inroom,emptyroom);
    printf("+------------------------------------------------------------------+\n");

    for(pclass=gp_head;pclass!=NULL&&pclass->type!='T';pclass=pclass->next);//����������pclassָ�����˼�ͷ����
    allroom=pclass->rnum;
    emptyroom=pclass->emptyr;
    inroom=allroom-emptyroom;
    totalroom+=allroom;
    totalinroom+=inroom;
    totalemptyroom+=emptyroom;
    printf("+        ���˼�  %16d%16d%16d  +\n",allroom,inroom,emptyroom);
    printf("+------------------------------------------------------------------+\n");
    printf("+        �ϼ�    %16d%16d%16d  +\n",totalroom,totalinroom,totalemptyroom);
    printf("+------------------------------------------------------------------+\n");

    return TRUE;
}
/**����ͳ�Ʊ���ȸ���ͷ���Ӫҵ��*/
BOOL Staincome()
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵������ͳ�Ʊ���ȸ���ͷ���Ӫҵ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    INCOME_NODE *sroom,*droom,*troom;//���˼䣬˫�˼䣬���˼�
    /*��̬����洢�ռ�*/
    sroom=(INCOME_NODE *)malloc(sizeof(INCOME_NODE));
    droom=(INCOME_NODE *)malloc(sizeof(INCOME_NODE));
    troom=(INCOME_NODE *)malloc(sizeof(INCOME_NODE));
    /*������ṹ�и�sale������Ϊ0*/
    int i;
    for(i=0;i<12;i++)
    {
        sroom->sale[i]=0;
        droom->sale[i]=0;
        troom->sale[i]=0;
    }
    sroom->next=droom;
    droom->next=troom;
    troom->next=NULL;

    /*�����û�����*/
    printf("�����뽫Ҫͳ�Ƶ����");
    char year[18];
    gets(year);

    /*��ʼͳ������*/
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    /*ͳ�Ƶ��˼�*/
    for(pclass=gp_head;pclass!=NULL&&pclass->type!='S';pclass=pclass->next);//pclass��λ���˼����
    if(pclass!=NULL)//����ҵ����˼����
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
            for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
        {
            /**��������ͬ������ͳ�ƣ�����˷�ʱ��ȡ���ã�Ѻ�𲻼�������*/
            if(strncmp(year,prenter->date_out,4)==0)
                {
                    /*��ȡ�����е�����*/
                    char months[3];
                    months[0]=prenter->date_out[5];
                    months[1]=prenter->date_out[6];
                    months[2]='\0';
                    int month=atoi(months);//���·ݴ��ַ�ת��Ϊ����
                    sroom->sale[month-1]+=prenter->realpay;//������ӵ���Ӧ������
                }
        }
    }
    /*ͳ��˫�˼�*/
    for(pclass=gp_head;pclass!=NULL&&pclass->type!='D';pclass=pclass->next);//pclass��λ˫�˼����
    if(pclass!=NULL)//����ҵ�˫�˼����
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
            for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
        {
            /**��������ͬ������ͳ�ƣ�����˷�ʱ��ȡ���ã�Ѻ�𲻼�������*/
            if(strncmp(year,prenter->date_out,4)==0)
                {
                    /*��ȡ�����е�����*/
                    char months[3];
                    months[0]=prenter->date_out[5];
                    months[1]=prenter->date_out[6];
                    months[2]='\0';
                    int month=atoi(months);//���·ݴ��ַ�ת��Ϊ����
                    droom->sale[month-1]+=prenter->realpay;//������ӵ���Ӧ������
                }
        }
    }
    /*ͳ�����˼�*/
    for(pclass=gp_head;pclass!=NULL&&pclass->type!='T';pclass=pclass->next);//pclass��Ϊ���˼����
    if(pclass!=NULL)//����ҵ����˼����
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
            for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
        {
            /**��������ͬ������ͳ�ƣ�����˷�ʱ��ȡ���ã�Ѻ�𲻼�������*/
            if(strncmp(year,prenter->date_out,4)==0)
                {
                    /*��ȡ�����е�����*/
                    char months[3];
                    months[0]=prenter->date_out[5];
                    months[1]=prenter->date_out[6];
                    months[2]='\0';
                    int month=atoi(months);//���·ݴ��ַ�ת��Ϊ����
                    sroom->sale[month-1]+=prenter->realpay;//������ӵ���Ӧ������
                }
        }
    }
    /*������*/
    char *p[4];
    p[0]="�·�";
    p[1]="���˼�";
    p[2]="˫�˼�";
    p[3]="���˼�";
    printf("    %10s    %10s    %10s    %10s    \n",p[0],p[1],p[2],p[3]);
    for(i=0;i<12;i++)
    {
        printf("    %10.1d    %10.1f    %10.1f    %10.1f    \n",i+1,sroom->sale[i],droom->sale[i],troom->sale[i]);
    }
    /*�ͷ��ڴ�*/
    free(sroom);
    free(droom);
    free(troom);
    return TRUE;
}
/**������ݣ�ͳ�Ƹ������пͷ���Ӫҵ���ס��������ס��*/
BOOL Staroom_info()
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ͳ��һ�����пͷ���Ӫҵ���ס��������ס��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    ROOM_INFO *gp_room_info=NULL;                   /*�ͷ���Ϣͳ������ͷָ��*/
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    ROOM_INFO *proominfo;

    /*�����û�����*/
    printf("�����뽫Ҫͳ�Ƶ����");
    char year[18];
    gets(year);

    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
        {
            /*����ͳ������ڵ�*/
            proominfo=(ROOM_INFO *)malloc(sizeof(ROOM_INFO));
            proominfo->next=gp_room_info;
            gp_room_info=proominfo;
            /*��ʼ��ͳ������ڵ�*/
            proominfo->income=0;
            proominfo->in_rate=0;
            proominfo->months=0;
            strcpy(proominfo->room_id,proom->room_id);
            proominfo->type=proom->type;
            /*��ʼͳ��*/
            for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
            {
                 /**��������ͬ������ͳ�ƣ�������˷�����Ϊ׼*/
                if(strncmp(year,prenter->date_out,4)==0)
                {
                   proominfo->income+=prenter->realpay;
                   proominfo->months+=prenter->months;
                }
            }
            proominfo->in_rate=proominfo->months/12.0;
        }
    }

    /*���ͳ����Ϣ*/
    char *pt[5];
    pt[0]="�ͷ����";
    pt[1]="�ͷ����";
    pt[2]="Ӫҵ��  ";
    pt[3]="��ס����";
    pt[4]="��ס��  ";
    printf("    %-10s    %-10s    %-10s    %-10s    %-10s    \n",pt[0],pt[1],pt[2],pt[3],pt[4]);
    for(proominfo=gp_room_info;proominfo!=NULL;proominfo=proominfo->next)
        printf("    %-10s    %-10c    %-10.1f    %-10.1f    %-10.2f\n",proominfo->room_id,proominfo->type,
               proominfo->income,proominfo->months,proominfo->in_rate);
    /*�ͷ�ͳ�ƽڵ�*/
    for(proominfo=gp_room_info;proominfo!=NULL;proominfo=proominfo->next)
        free(proominfo);
   return TRUE;
}

/**ͳ�Ƴ����������� 10 �������ⷿ��Ϣ*/
BOOL Starenter_info()
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ͳ�Ƴ����������� 10 �������ⷿ��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    RENTER_INFO *gp_renter_head,*prenter_info;
    gp_renter_head=NULL;
    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
        {
            for(prenter=proom->rnext;prenter!=NULL;prenter=prenter->next)
            {
                if(prenter->date_out[0]!='\0')//��ס��Ͳ�����ͳ��
                {

                if((prenter_info=search_renter_info(gp_renter_head,prenter->id_card))==NULL)//��������֤��δ��ͳ��������
                {
                    prenter_info=(RENTER_INFO *)malloc(sizeof(RENTER_INFO));//��ô�´���һ���ڵ�
                    /*��ֵ�ڵ�*/
                    prenter_info->allmonths=prenter->months;
                    prenter_info->realpay=prenter->realpay;
                    prenter_info->shouldpay=prenter->shouldpay;
                    strcpy(prenter_info->id_card,prenter->id_card);
                    strcpy(prenter_info->name,prenter->name);
                    /*����ڵ�*/
                    prenter_info->next=gp_renter_head;
                    gp_renter_head=prenter_info;
                }
                else//��������֤���Ѿ�������ͳ��������
                {
                    /*ͳ��*/
                    prenter_info->allmonths+=prenter->months;
                    prenter_info->realpay+=prenter->realpay;
                    prenter_info->shouldpay+=prenter->shouldpay;
                }
                }
            }
        }
    }//ͳ�����
    /*�����ⷿ��������������*/
    sortrenter_info(gp_renter_head);
    /*����ۼ��ⷿ��������ǰʮ��ͳ�ƽ��*/
    int amount;
    char *p[5];
    p[0]=" ���֤�� ";
    p[1]="����";
    p[2]="�ۼ�ס������";
    p[3]="Ӧ�ɷ����ܶ�";
    p[4]="ʵ�ɷ����ܶ�";
    printf("%-20s    %-15s    %-15s    %-15s    %-15s    \n",p[0],p[1],p[2],p[3],p[4]);
    for(amount=1,prenter_info=gp_renter_head;amount<=10&&prenter_info!=NULL;amount++,prenter_info=prenter_info->next)
    {
        printf("%-20s    %-15s    %-15.1f    %-15.1f    %-15.1f    \n",prenter_info->id_card,prenter_info->name,
               prenter_info->allmonths,prenter_info->shouldpay,prenter_info->realpay);
    }
    return TRUE;
}
/**ͳ�Ƶ�ǰ���пͷ������ס���*/
BOOL Sta_in()
{
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��ͳ�Ƶ�ǰ���пͷ������ס���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    CLASS_NODE *pclass;
    ROOM_NODE *proom;

    char *p[4];
    p[0]="�ͷ�����";
    p[1]="�ͷ����";
    p[2]="�ͷ����";
    p[3]="��ס���";
    char *ch[2];
    ch[0]="����";
    ch[1]="δ��ס";
    char *pcode[3];
    pcode[0]="���˼�";
    pcode[1]="˫�˼�";
    pcode[2]="���˼�";
    int key;
    printf("    %-10s    %-10s    %-10s    %-10s    \n",p[0],p[1],p[2],p[3]);
    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {
        for(proom=pclass->rnext;proom!=NULL;proom=proom->next)
        {
            if(proom->type=='S')
                key=0;
            if(proom->type=='D')
                key=1;
            if(proom->type=='T')
                key=2;
            if(proom->in=='y')
                printf("    %-10s    %-10s    %-10.1f    %-10s    \n",pcode[key],proom->room_id,proom->deposit,ch[0]);
            else printf("    %-10s    %-10s    %-10.1f    %-10s    \n",pcode[key],proom->room_id,proom->deposit,ch[1]);

        }
    }
    return TRUE;
}
/*=========================================*/
BOOL SaveData()
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    CLASS_NODE * pclass;
    ROOM_NODE *proom;
    RENTER_NODE * prenter;
    FILE * pfout;

    Maintain_in();
    pfout=fopen(gp_class_info_filename,"wb");
    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {
        /*����ͷ�������Ϣ*/
        fwrite(pclass,sizeof(CLASS_NODE),1,pfout);
    }
    fclose(pfout);
    //printf("1");

    pfout=fopen(gp_room_info_filename,"wb");
    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {/*����ͷ�������Ϣ*/
        proom=pclass->rnext;
        while(proom!=NULL)
        {
            fwrite(proom,sizeof(ROOM_NODE),1,pfout);
            proom=proom->next;
        }
    }
    fclose(pfout);
    //printf("2");

    pfout=fopen(gp_renter_info_filename,"wb");
    for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
    {

        proom=pclass->rnext;
        while(proom!=NULL)
        {
            //printf("3") ;
            prenter=proom->rnext;

            while(prenter!=NULL)
            {
                fwrite(prenter,sizeof(RENTER_NODE),1,pfout);
                prenter=prenter->next;
            }
        proom=proom->next;
        }

    }
     fclose(pfout);
     printf("���ݱ���ɹ���\n");

    return bRet;
}
/**���ҿͷ��ڵ�*/
ROOM_NODE * seekroom(CLASS_NODE *hd,char * r_id)
{
    CLASS_NODE * pclass;
    ROOM_NODE *proom;
    ROOM_NODE *proom1;
    int flat=1;//�����˳�ѭ�����ҵ�����Ϊ0.
    for(pclass=hd;pclass!=NULL&&flat;pclass=pclass->next)
    {
        proom=pclass->rnext;
        while(proom!=NULL&&flat)
        {
            proom1=proom;
            if(strcmp(r_id,proom->room_id)==0)
                flat=0;
            proom=proom->next;

        }
    }
    if(flat)
    {
        printf("δ�ҵ���");
        return NULL;
    }
    return proom1;
}
/**������ͽڵ�*/
RENTER_NODE * seekrenter(CLASS_NODE *hd,char *date,char * id_card)
{
    CLASS_NODE *pclass;
    ROOM_NODE *proom;
    RENTER_NODE *prenter;
    for(pclass=hd;pclass!=NULL;pclass=pclass->next)
    {
        proom=pclass->rnext;
        while(proom!=NULL)
        {
            prenter=proom->rnext;
            while(prenter!=NULL)
            {
                if((strncmp(prenter->date_in,date,10)==0||(date[0]=='\0'&&prenter->date_out[0]=='\0'))&&strcmp(prenter->id_card,id_card)==0)
                {
                    return prenter;
                }
                prenter=prenter->next;
            }
            proom=proom->next;
        }

    }
    //printf("û���ҵ������");
    return NULL;
}
/**����prenter_infoָ���������Ƿ���id_card����Ϣ�����ڷ���id_card���ڵĽڵ㣬�����ڷ���NULL**/
RENTER_INFO * search_renter_info(RENTER_INFO * hd,char *id_card)
{
    RENTER_INFO *prenter_info;
    for(prenter_info=hd;prenter_info!=NULL;prenter_info=prenter_info->next)
    {//��������
        if(strncmp(prenter_info->id_card,id_card,18)==0)
            return prenter_info;//����ҵ������ظýڵ�
    }
    return NULL;//�������δ�ҵ������ؿ�ָ��
}
/**���ⷿ����ͳ�������ⷿ������������*/
void sortrenter_info(RENTER_INFO *hd)
{
    RENTER_INFO *prenter_info,*pr;//prenter_info�������ѭ����pr�����ڲ�ѭ��
    RENTER_INFO temp;
    RENTER_INFO *p1,*p2,*p3,*p4;//p1ָ���ⷿ�������Ľڵ�,p2ָ��Ҫ�����Ľڵ�,p3,p4��ʱ����p1,p2��next��ֵ

    float maxmonths;//����ⷿ����
    /*ѡ��������������ָ�򲻱䣬ÿ��ѡȡ����ⷿ�����Ľڵ㣬��������ǰ��ڵ��������*/
    for(prenter_info=hd;prenter_info!=NULL;prenter_info=prenter_info->next)
    {
        maxmonths=prenter_info->allmonths;
        p1=prenter_info;
        for(pr=prenter_info;pr!=NULL;pr=pr->next)
        {
            if(pr->allmonths>maxmonths)//���pr�ڵ����������
                {
                    p1=pr;//p1ָ���������Ľڵ�
                    maxmonths=pr->allmonths;
                }

        }
        if(p1!=prenter_info)//���p1��ֵ���ˣ����н���
        {
            p2=prenter_info;
            p3=p1->next;
            p4=p2->next;//����ָ��
            /*����p1,p2��������*/
            temp=*p1;
            *p1=*p2;
            *p2=temp;
            /*�ָ�ָ��ָ��*/
            p1->next=p3;
            p2->next=p4;
        }
    }
}
BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}
/**��ѯ�ͷ�������Ϣ�ַ���Ϣ*/
BOOL Query(void)
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵����ѯ�ͷ�������Ϣ�ַ���Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    BOOL bRet = TRUE;
    printf("               ***************    0 ����̨\n");
    printf("               ***************    1 ����̨\n");
    printf("               ***************    y �п�����ס\n");
    printf("               ***************    n �޿�����ס\n");
    return bRet;
}
/**��ѯ�ͷ�������*/
BOOL QueryTypeInfo(void)
{
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�����ҿͷ�������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();

    BOOL bRet = TRUE;
    printf("               ***************    S ���˼�\n");
    printf("               ***************    D ˫�˼�\n");
    printf("               ***************    T ���˼�\n");
    return bRet;
}
/**����*/
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵����������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    Clear();
    printf("\n");
    printf("��ϵͳ��ݲ���ָ�ϡ�\n");
	printf(" 1��Alt + F  ����\"�ļ�(F)\"�������˵�;\n");
	printf(" 2��Alt + E  ����\"�༭(E)\"�������˵�;\n");
	printf(" 3��Alt + I  ����\"��ѯ(I)\"�������˵�;\n");
	printf(" 4��Alt + S  ����\"ͳ��(S)\"�������˵�;\n");
	printf(" 5��Alt + H  ����\"����(H)\"�������˵�;\n");
	printf(" 6��ESC  ��  �رյ�������,�ص����˵���;\n");
	printf(" 7��Enter��  ִ����Ӧ�Ĺ��ܺ���;\n");


    return bRet;
}
/**����*/
BOOL AboutDorm(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵������...",
                           "ȷ��",

                          };
    ShowModule(plabel_name, 3);
    Clear();
    printf("               ***************    ���ߣ� ������\n");

    return bRet;
}

BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}
/**��ӡ�ͷ�������Ϣ*/
void printclass(CLASS_NODE *pclass)
{
    printf("               ***************    ");
    printf("�ͷ����    �����ס����    �ͷ�����    �ͷ�δס����\n");
    printf("               ***************    ");
    printf("%-12c%-16d%-12d%d",pclass->type,pclass->pnum,pclass->rnum,pclass->emptyr);
    putchar('\n');
}
/**��ӡ�ͷ�������Ϣ*/
void printroom(ROOM_NODE * proom)
{
/*��ӡ�����Ϣ*/
    printf("               ***************");
    printf("�ͷ���� �绰���� �ͷ���� �ͷ���� ÿ����� �Ƿ�����̨ �Ƿ��п�����ס\n");
    printf("               ***************");
    char *pc[2];
    pc[0]="��";
    pc[1]="��";
    //printf("%s %s",pc[0],pc[1]);
    int key;
    if(proom->in=='y')
        key=1;
    else key=0;
    //printf("\n%d\n",key);
    printf("%-8s %-8s %-8c %-8.1f %-8.1f %-10s %s\n" ,proom->room_id,proom->tel,proom->type,proom->area,proom->deposit,pc[proom->balcony-'0'],pc[key]);

}
/**��ӡ��ͻ�����Ϣ*/
void printrenter(RENTER_NODE *prenter)
{
    char * p[9];
    p[0]="���֤��";
    p[1]="��������";
    p[2]="�ͷ����";
    p[3]="��סʱ��";
    p[4]="�˷�ʱ��";
    p[5]="��ס����";
    p[6]="Ѻ��";
    p[7]="Ӧ�ɷ���";
    p[8]="ʵ�ɷ���";
    printf("%-20s %-8s %-8s %-20s %-20s %-8s %-8s %-8s %-8s\n",p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8]);
    printf("%-20s %-8s %-8s %-20s %-20s %-8.1f %-8.1f %-8.1f %-8.1f\n",prenter->id_card,prenter->name,prenter->room_id,
           prenter->date_in,prenter->date_out,prenter->months,prenter->deposit,prenter->shouldpay,prenter->realpay);
    putchar('\n');
}
/**����*/
BOOL Clear()
{
    InitInterface();
    return TRUE;
}
/**���·�����ס���*/
void Maintain_in(void)
{
        CLASS_NODE *pclass;
        ROOM_NODE *proom;
        RENTER_NODE *prenter;
        int key=1;
        int allroom,emptyroom;
        allroom=emptyroom=0;
        /*����ÿ�������µ�֧������������û�˷�����÷������˾�ס���������˾�ס*/
        for(pclass=gp_head;pclass!=NULL;pclass=pclass->next)
        {
            for(proom=pclass->rnext,allroom=emptyroom=0;proom!=NULL;proom=proom->next,key=1)
            {

                prenter=proom->rnext;
                proom->in='n';
                while(prenter!=NULL&&key)
                {
                    if(prenter->date_out[0]=='\0')
                    {
                        key=0;
                        proom->in='y';
                    }
                    prenter=prenter->next;
                }
                /*û����һ�����䣬��������++��û�ҵ�һ���շ��䣬�շ�����++*/
                allroom++;
                if(proom->in=='n')
                    emptyroom++;
            }
            /*��¼�ܷ������Ϳշ�����*/
            pclass->rnum=allroom;
            pclass->emptyr=emptyroom;
        }
}
/**ͳ����������֮�������*/
float Maintain_month(char * date_in,char * date_out)
{//���ڵĸ�ʽΪ2015/03/06
    char year[5];
    char month[3];
    char day[3];
    int total_in,total_out;
    int i;
    total_in=total_out=0;
    /*�����һ�����ڵ�������*/
    for(i=0;i<=3;i++)
    {
        year[i]=date_in[i];
    }
    year[4]='\0';
    total_in=atoi(year)*365;
    month[0]=date_in[5];
    month[1]=date_in[6];
    month[2]='\0';
    total_in+=atoi(month)*31;
    day[0]=date_in[8];
    day[1]=date_in[9];
    day[2]='\0';
    total_in+=atoi(day);

    /*���date_outΪ�մ�����������ס������0*/
    if(date_out[0]=='\0')
        return 0;

    /*����ڶ������ڵ�������*/
    for(i=0;i<=3;i++)
    {
        year[i]=date_out[i];
    }
    year[4]='\0';
    total_out=atoi(year)*365;
    month[0]=date_out[5];
    month[1]=date_out[6];
    month[2]='\0';
    total_out+=atoi(month)*31;
    day[0]=date_out[8];
    day[1]=date_out[9];
    day[2]='\0';
    total_out+=atoi(day);
    /*�����������������������������Լ��������*/
    float months;
    months=(total_out-total_in)/31.0;
    months=(months-(int)months>0.5)?(int)months+1:(int)months;//�������뷨��������
    return months;

}
/**�ж������Ƿ���ָ����Χ֮�ڣ��Ƿ���1�����Ƿ���0*/
int Judgedate(char *date_in,char *date_out,char *date)
{
    /*������������ڵ���������ͨ�������ж�date�Ƿ���date_in��date_out֮��*/
    int total_in,total_out,total;
    total=total_in=total_out=0;
    char year[5];
    char month[3];
    char day[3];
    int i;

    /*����date_in��������*/
    for(i=0;i<=3;i++)
    {
        year[i]=date_in[i];
    }
    year[4]='\0';
    total_in=atoi(year)*365;
    month[0]=date_in[5];
    month[1]=date_in[6];
    month[2]='\0';
    total_in+=atoi(month)*31;
    day[0]=date_in[8];
    day[1]=date_in[9];
    day[2]='\0';
    total_in+=atoi(day);

    /*����date_out��������*/
    for(i=0;i<=3;i++)
    {
        year[i]=date_out[i];
    }
    year[4]='\0';
    total_out=atoi(year)*365;
    month[0]=date_out[5];
    month[1]=date_out[6];
    month[2]='\0';
    total_out+=atoi(month)*31;
    day[0]=date_out[8];
    day[1]=date_out[9];
    day[2]='\0';
    total_out+=atoi(day);

    /*����date��������*/
    for(i=0;i<=3;i++)
    {
        year[i]=date[i];
    }
    year[4]='\0';
    total=atoi(year)*365;
    month[0]=date[5];
    month[1]=date[6];
    month[2]='\0';
    total+=atoi(month)*31;
    day[0]=date[8];
    day[1]=date[9];
    day[2]='\0';
    total+=atoi(day);
    /*�ж������Ƿ��ڷ�Χ֮��*/
    if(total>=total_in&&total<=total_out)
        return 1;
    return 0;
}
