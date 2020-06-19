//#include <stdio.h>
//#include <stdlib.h>
//#include<graphics.h>
//#include<string.h>
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
//#define CIPHERROOM 50
//#define ROOMSHOW 100
//#define Caesarseed 4
//#define Multseed 7
//#define Affadd 17
//#define Affmult 15
//typedef struct cipher
//{
//	int type = 0;
//	char id[CIPHERROOM] = { 0 };
//	char password[CIPHERROOM] = { 0 };
//} cip;
//cip p;//����
//cip c;//����
//int mode[ROOMSHOW] = { 0 };
////int getopt()
////{
////	initgraph(1000, 500);
////	MOUSEMSG m;
////	int i, j, w = 1;
////	int x, y, opt = 0;
////	char k[5];
////	setfillcolor(RED);
////	solidcircle(700, 270, 20);
////	outtextxy(740, 270, "��ʹ��");
////	setfillcolor(GREEN);
////	solidcircle(850, 270, 20);
////	outtextxy(890, 270, "δʹ��");
////	rectangle(100, 300, 300, 400);
////	outtextxy(150, 340, "����һ������");
////	rectangle(400, 300, 600, 400);
////	outtextxy(450, 340, "���һ������");
////	rectangle(700, 300, 900, 400);
////	outtextxy(790, 340, "�˳�");
////	for (j = 20; j < 210; j += 60)
////	{
////		for (i = 20; i < 1000; i += 40)
////		{
////
////			_itoa_s(w, k, 10);
////			outtextxy(i - 5, j + 20, k);
////			w++;
////			if (mode[w - 1])
////			{
////				setfillcolor(RED);
////				solidcircle(i, j, 20);
////			}
////			else
////			{
////				setfillcolor(GREEN);
////				solidcircle(i, j, 20);
////			}
////		}
////	}
////	m = GetMouseMsg();
////	while (1)
////	{
////		if (m.uMsg == WM_LBUTTONDOWN)
////		{
////			char s[24];
////			x = m.x / 100;
////			y = m.y / 100;
////			opt = 99;
////			closegraph();
////			if (y == 3)
////			{
////				if ((x - 1) / 2 == 0) { closegraph(); return 1; }
////				if ((x - 4) / 2 == 0) { closegraph(); return 2;}
////				if ((x - 7) / 2 == 0) { closegraph(); return 0; }
////			}
////		}
////	}
////}
//void read(cip* x, FILE* fp, int offset)
//{
//	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
//	fread(x, sizeof(cip), 1, fp);
//}
//void write(cip* x, FILE* fp, int offset)
//{
//	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
//	fwrite(x, sizeof(cip), 1, fp);
//}
//void show(FILE* fp, int offset)
//{
//	cip x;
//	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
//	fread(&x, sizeof(cip), 1, fp);
//	printf_s("����ۣ�%d\n", offset);
//	printf_s("�û�����%s\n", x.id);
//	printf_s("���룺%s\n", x.password);
//}
//void input(cip* x)
//{
//	printf_s("�����û���\n");
//	scanf("%s", x->id);
//	printf_s("��������\n");
//	scanf("%s", x->password);
//}
//void roomcheck(FILE* fp)
//{
//	cip x;
//	int offset;
//	for (offset = 1; offset < ROOMSHOW + 1; offset++)
//	{
//		fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
//		fread(&x, sizeof(cip), 1, fp);
//		mode[offset - 1] = x.type;
//		//printf("mode:%d", mode[offset - 1]);
//		printf("%2d", offset);
//		if (x.type)
//		{
//			printf("%c%c", 0xa8, 0x80);
//			x.type = 0;
//		}
//		else
//		{
//			printf_s("%c%c", 0x10, 0x02);
//		}
//	}
//	printf("\n");
//}
//void Plaintext()
//{
//	c = p;
//	c.type = 1;
//}
//void invPlaintext()
//{
//	p = c;
//}
//void Caesar()
//{
//	int i;
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		c.id[i] = (p.id[i] + Caesarseed) % 128;
//		c.password[i] = (p.password[i] + Caesarseed) % 128;
//	}
//	c.type = 2;
//}
//void invCaesar()
//{
//	int i;
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		p.id[i] = (c.id[i] - Caesarseed) % 128;
//		p.password[i] = (c.password[i] - Caesarseed) % 128;
//	}
//}
//void Mult()
//{
//	int i;
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		c.id[i] = (p.id[i] * Multseed) % 128;
//		c.password[i] = (p.password[i] * Multseed) % 128;
//	}
//	c.type = 3;
//}
//void invMult()
//{
//	int i;
//	int k = 1;
//	while ((k * Multseed) % 128 != 1)
//	{
//		k = k + 1;
//	}
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		p.id[i] = (c.id[i] * k) % 128;
//		p.password[i] = (c.password[i] * k) % 128;
//	}
//}
//void Affine()
//{
//	int i;
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		c.id[i] = (p.id[i] * Affmult + Affadd + 12800) % 128;
//		c.password[i] = (p.password[i] * Affmult + Affadd + 12800) % 128;
//		//printf("���ģ�%c��%d",c.id[i],c.id[i]);
//	}
//	c.type = 4;
//}
//void invAffine()
//{
//	int i;
//	int k = 1;
//	while ((k * Affmult + 12800) % 128 != 1)
//	{
//		k = k + 1;
//		//printf_s("��Ԫ��%d\n",k);
//	}
//	for (i = 0; i < CIPHERROOM; i++)
//	{
//		p.id[i] = ((c.id[i] - Affadd) * k + 12800) % 128;
//		p.password[i] = ((c.password[i] - Affadd) * k + 12800) % 128;
//		//printf("c:%d",c.id[i]);
//		//printf("���ģ�%c��%d\n", p.id[i], p.id[i]);
//	}
//}
//int encrypt()
//{
//	int typ = 99;
//	printf("ѡ����ܷ�ʽ\n");
//	printf("1.����д��\n");
//	printf("2.��������\n");
//	printf("3.�˷�����\n");
//	printf("4.��������\n");
//	scanf_s("%d", &typ);
//	switch (typ)
//	{
//	case 1:
//		Plaintext();
//		break;
//	case 2:
//		Caesar();
//		break;
//	case 3:
//		Mult();
//		break;
//	case 4:
//		Affine();
//		break;
//	}
//	return typ;
//}
//int decrypt(FILE* fp, int offset)
//{
//	int typ;
//	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
//	fread(&c, sizeof(cip), 1, fp);
//	//printf("type:%d", c.type);
//	if (mode[offset - 1] != 0)
//	{
//		typ = c.type;
//		switch (typ)
//		{
//		case 1:
//			invPlaintext();
//			break;
//		case 2:
//			invCaesar();
//			break;
//		case 3:
//			invMult();
//			break;
//		case 4:
//			invAffine();
//			break;
//		}
//		printf_s("����ۣ�%d\n", offset);
//		printf_s("�û�����%s\n", p.id);
//		printf_s("���룺%s\n", p.password);
//		return typ;
//	}
//	else
//	{
//		printf("�ò�δ����ֵ");
//	}
//}
//int main()
//{
//	FILE* fp;
//	int opt = 99;
//	int slot;
//	errno_t err;
//	err = fopen_s(&fp, "D:\\cipher.txt", "ab+");
//	fclose(fp);
//	err = fopen_s(&fp, "D:\\cipher.txt", "rb+");
//	while (opt)
//	{
//		printf_s("\n------------------------���뱾------------------------\n");
//		printf_s("\n--------------------�ռ�ʹ�����-------------------\n");
//		roomcheck(fp);
//		printf_s("��ѡ���ܣ������Ӧ�����֣�\n");
//		printf_s("1.����һ���˻���/����\n");
//		//printf_s("2.�ӱ����������һ���˻���/����\n");
//		printf_s("2.�ӱ������ݽ���һ���˻���/����\n");
//		scanf_s("%d", &opt);
//		//opt=getopt();
//		switch (opt)
//		{
//		case 1:
//			input(&p);
//			printf_s("ѡ�񴢴��\n");
//			scanf_s("%d", &slot);
//			c.type = 0;
//			encrypt();
//			write(&c, fp, slot);
//			printf_s("�����Ѵ���\n");
//			break;
//		case 2:
//			printf_s("ѡ�񴢴��\n");
//			scanf_s("%d", &slot);
//			decrypt(fp, slot);
//			break;
//		}
//	}
//	fclose(fp);
//	return 0;
//}