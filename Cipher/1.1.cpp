#include <stdio.h>
#include <stdlib.h>
#include<graphics.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#define CIPHERROOM 50
#define ROOMSHOW 100
#define Caesarseed 4
#define Multseed 7
#define Affadd 17
#define Affmult 15
#define Linearseed 265
#define Linearlength 4
#define USEDCOLOR  0x3c14dc
#define UNUSEDCOLOR 0xffcc00
#define BGCOLOR 0
typedef struct cipher
{
	int type = 0;
	char id[CIPHERROOM] = { 0 };
	char password[CIPHERROOM] = { 0 };
} cip;
cip p;//明文
cip c;//密文
int gslot = 1;
int offset = 0;
int typ = 5;
int getopt(FILE* fp)
{
	/*initgraph(1000, 540);*/
	setfillcolor(BGCOLOR);
	solidrectangle(0, 0, 1000, 540);
	MOUSEMSG m;
	cip ci;
	int distan;
	int i, j, w = 1;
	int x, y, opt = 0;
	char k[5];
	char numgslot[5];
	char stroff[5];
	setfillcolor(USEDCOLOR);
	solidcircle(700, 270, 15);
	outtextxy(740, 270, "已使用");
	setfillcolor(UNUSEDCOLOR);
	solidcircle(850, 270, 15);
	outtextxy(890, 270, "未使用");
	rectangle(90, 300, 300, 400);
	outtextxy(150, 340, "输入一组数据");
	rectangle(400, 300, 600, 400);
	outtextxy(450, 340, "输出一组数据");
	rectangle(700, 300, 900, 400);
	rectangle(90, 410, 300, 500);
	rectangle(700, 410, 900, 520);
	outtextxy(790, 340, "退出");
	outtextxy(400, 420, "槽位选择：");
	outtextxy(550, 500, "加密方式选择→");
	outtextxy(710, 420, "    明文写入");
	outtextxy(710, 440, "    凯撒密码");
	outtextxy(710, 460, "    乘法密码");
	outtextxy(710, 480, "    仿射密码");
	outtextxy(710, 500, "    线性反馈密码");
	_itoa_s(offset, stroff, 10);
	outtextxy(470, 420, stroff);
	outtextxy(710, 400 + typ * 20, "●");
	if (gslot)
	{
		outtextxy(100, 420, "槽位:");
		_itoa_s(gslot, numgslot, 10);
		outtextxy(140, 420, numgslot);
		outtextxy(100, 440, "用户名:");
		outtextxy(160, 440, p.id);
		outtextxy(100, 460, "密码:");
		outtextxy(160, 460, p.password);
	}
	else
	{
		outtextxy(160, 440, "该槽未存贮值");
	}
	for (j = 20; j < 210; j += 60)
	{
		for (i = 20; i < 1000; i += 40)
		{

			_itoa_s(w, k, 10);
			outtextxy(i - 5, j + 20, k);

			fseek(fp, (w - 1) * sizeof(cip), SEEK_SET);
			fread(&ci, sizeof(cip), 1, fp);
			if (ci.type)
			{
				setfillcolor(USEDCOLOR);
				solidcircle(i, j, 15);
				ci.type = 0;
			}
			else
			{
				setfillcolor(UNUSEDCOLOR);
				solidcircle(i, j, 15);
			}
			w++;
		}
	}
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			char s[24];
			x = m.x / 100;
			y = m.y / 100;
			opt = 99;
			sprintf_s(s, "[%d,%d,%d]", m.x, m.y, opt);
			setfillcolor(BGCOLOR);
			solidrectangle(10, 520, 100, 560);
			outtextxy(10, 520, s);
			if (y == 3)
			{
				if ((x - 1) / 2 == 0) { opt = 1; break; }
				if ((x - 4) / 2 == 0) { opt = 2; break; }
				if ((x - 7) / 2 == 0) { opt = 0; break; }
			}
			if (m.y <= 221)
			{
				for (j = 20; j < 210; j += 60)
				{
					for (i = 20; i < 1000; i += 40)
					{
						distan = pow(i - m.x, 2) + pow(j - m.y, 2);
						if (distan <= 400)
						{
							offset = 25 * ((j - 20) / 60) + ((i - 20) / 40) + 1;
							_itoa_s(offset, stroff, 10);
							setfillcolor(BGCOLOR);
							solidrectangle(200, 250, 300, 270);
							outtextxy(470, 420, stroff);
						}
					}
				}
			}
			if (m.y > 420 && m.x > 700)
			{

				typ = (m.y - 400) / 20;
				setfillcolor(BGCOLOR);
				solidrectangle(710, 420, 724, 519);
				if ((typ <= 5) && (typ >= 1))
				{
					outtextxy(710, 400 + typ * 20, "●");
				}
			}

		}
	}
	//closegraph();
	return opt;
}
void read(cip* x, FILE* fp)
{
	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
	fread(x, sizeof(cip), 1, fp);
}
void write(cip* x, FILE* fp)
{
	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
	fwrite(x, sizeof(cip), 1, fp);
}
void show(FILE* fp)
{
	cip x;
	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
	fread(&x, sizeof(cip), 1, fp);
	printf_s("储存槽：%d\n", offset);
	printf_s("用户名：%s\n", x.id);
	printf_s("密码：%s\n", x.password);
}
void input(cip* x)
{
	outtextxy(100, 260, "输入用户名");
	scanf("%s", x->id);
	outtextxy(100, 260, "输入密码    ");
	scanf("%s", x->password);
}
void roomcheck(FILE* fp)
{
	cip x;
	int offst;
	for (offst = 1; offst < ROOMSHOW + 1; offst++)
	{
		fseek(fp, (offst - 1) * sizeof(cip), SEEK_SET);
		fread(&x, sizeof(cip), 1, fp);
		if (x.type)
		{
			x.type = 0;
		}
	}
	printf("\n");
}
void Plaintext()
{
	c = p;
	c.type = 1;
}
void invPlaintext()
{
	p = c;
}
void Caesar()
{
	int i;
	for (i = 0; i < CIPHERROOM; i++)
	{
		c.id[i] = (p.id[i] + Caesarseed) % 128;
		c.password[i] = (p.password[i] + Caesarseed) % 128;
	}
	c.type = 2;
}
void invCaesar()
{
	int i;
	for (i = 0; i < CIPHERROOM; i++)
	{
		p.id[i] = (c.id[i] - Caesarseed) % 128;
		p.password[i] = (c.password[i] - Caesarseed) % 128;
	}
}
void Mult()
{
	int i;
	for (i = 0; i < CIPHERROOM; i++)
	{
		c.id[i] = (p.id[i] * Multseed) % 128;
		c.password[i] = (p.password[i] * Multseed) % 128;
	}
	c.type = 3;
}
void invMult()
{
	int i;
	int k = 1;
	while ((k * Multseed) % 128 != 1)
	{
		k = k + 1;
	}
	for (i = 0; i < CIPHERROOM; i++)
	{
		p.id[i] = (c.id[i] * k) % 128;
		p.password[i] = (c.password[i] * k) % 128;
	}
}
void Affine()
{
	int i;
	for (i = 0; i < CIPHERROOM; i++)
	{
		c.id[i] = (p.id[i] * Affmult + Affadd + 12800) % 128;
		c.password[i] = (p.password[i] * Affmult + Affadd + 12800) % 128;
		//printf("明文：%c：%d",c.id[i],c.id[i]);
	}
	c.type = 4;
}
void invAffine()
{
	int i;
	int k = 1;
	while ((k * Affmult + 12800) % 128 != 1)
	{
		k = k + 1;
		//printf_s("逆元：%d\n",k);
	}
	for (i = 0; i < CIPHERROOM; i++)
	{
		p.id[i] = ((c.id[i] - Affadd) * k + 12800) % 128;
		p.password[i] = ((c.password[i] - Affadd) * k + 12800) % 128;
		//printf("c:%d",c.id[i]);
		//printf("密文：%c：%d\n", p.id[i], p.id[i]);
	}
}
void Linear()
{
	int i, j;
	int r[Linearlength];
	srand(Linearseed);
	for (i = 0; i < Linearlength; i++)
	{
		r[i] = rand() % 2;
	}
	for (i = 0; i < CIPHERROOM; i++)
	{
		c.id[i] = p.id[i] + r[1];
		c.password[i] = p.password[i] + r[1];
		for (j = 1; j < Linearlength - 1; j++)
		{
			r[j] = r[j + 1];
		}
		r[Linearlength - 1] = (r[1] + r[2]) % 2;
	}
	c.type = 5;
}
void invLinear()
{
	int i, j;
	int r[Linearlength];
	srand(Linearseed);
	for (i = 0; i < Linearlength; i++)
	{
		r[i] = rand() % 2;
	}
	for (i = 0; i < CIPHERROOM; i++)
	{
		p.id[i] = c.id[i] - r[1];
		p.password[i] = c.password[i] - r[1];
		for (j = 1; j < Linearlength - 1; j++)
		{
			r[j] = r[j + 1];
		}
		r[Linearlength - 1] = (r[1] + r[2]) % 2;
	}

}
void encrypt()
{
	//int typ = 99;
	//printf("选择加密方式\n");
	//printf("1.明文写入\n");
	//printf("2.凯撒密码\n");
	//printf("3.乘法密码\n");
	//printf("4.仿射密码\n");
	//printf("5.线性反馈移位寄存器密码\n");
	//scanf_s("%d", &typ);
	switch (typ)
	{
	case 1:
		Plaintext();
		break;
	case 2:
		Caesar();
		break;
	case 3:
		Mult();
		break;
	case 4:
		Affine();
		break;
	case 5:
		Linear();
		break;
	}
	//return typ;
}
int decrypt(FILE* fp)
{
	int loctype;
	fseek(fp, (offset - 1) * sizeof(cip), SEEK_SET);
	fread(&c, sizeof(cip), 1, fp);
	//printf("type:%d", c.type);
	if (c.type)
	{
		loctype = c.type;
		gslot = offset;
		switch (loctype)
		{
		case 1:
			invPlaintext();
			break;
		case 2:
			invCaesar();
			break;
		case 3:
			invMult();
			break;
		case 4:
			invAffine();
			break;
		case 5:
			invLinear();
			break;
		}
		//printf_s("储存槽：%d\n", offset);
		//printf_s("用户名：%s\n", p.id);
		//printf_s("密码：%s\n", p.password);
		return loctype;
	}
	else
	{
		//printf("该槽未存贮值");
		gslot = 0;
	}
}
int main()
{
	FILE* fp;
	int opt = 99;
	errno_t err;
	err = fopen_s(&fp, "D:\\cipher.txt", "ab+");
	fclose(fp);
	err = fopen_s(&fp, "D:\\cipher.txt", "rb+");
	initgraph(1000, 540);
	while (opt)
	{

		opt = getopt(fp);
		switch (opt)
		{
		case 1:
			input(&p);
			c.type = 0;
			encrypt();
			write(&c, fp);
			printf_s("数据已储存\n");
			break;
		case 2:
			decrypt(fp);
			break;
		}
	}
	fclose(fp);
	closegraph();
	return 0;
}