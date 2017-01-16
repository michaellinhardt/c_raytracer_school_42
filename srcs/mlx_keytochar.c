#include "raytra_gen.h"
#include "raystruct.h"

static void		init_tab3(char tab[255][1])
{
	tab[23][0] = '5';
	tab[22][0] = '6';
	tab[26][0] = '7';
	tab[28][0] = '8';
	tab[25][0] = '9';
	tab[49][0] = '_';
}

static void		init_tab2(char tab[255][1])
{
	tab[9][0] = 'v';
	tab[11][0] = 'b';
	tab[45][0] = 'n';
	tab[46][0] = 'm';
	tab[27][0] = '-';
	tab[78][0] = '-';
	tab[43][0] = ',';
	tab[47][0] = '.';
	tab[65][0] = '.';
	tab[82][0] = '0';
	tab[83][0] = '1';
	tab[84][0] = '2';
	tab[85][0] = '3';
	tab[86][0] = '4';
	tab[87][0] = '5';
	tab[88][0] = '6';
	tab[89][0] = '7';
	tab[91][0] = '8';
	tab[92][0] = '9';
	tab[29][0] = '0';
	tab[18][0] = '1';
	tab[19][0] = '2';
	tab[20][0] = '3';
	tab[21][0] = '4';
	init_tab3(tab);
}

static void		init_tab(char tab[255][1], int i)
{
	while (++i < 255)
		tab[i][0] = '\0';
	tab[12][0] = 'q';
	tab[13][0] = 'w';
	tab[14][0] = 'e';
	tab[15][0] = 'r';
	tab[17][0] = 't';
	tab[16][0] = 'y';
	tab[32][0] = 'u';
	tab[34][0] = 'i';
	tab[31][0] = 'o';
	tab[35][0] = 'p';
	tab[0][0] = 'a';
	tab[1][0] = 's';
	tab[2][0] = 'd';
	tab[3][0] = 'f';
	tab[5][0] = 'g';
	tab[4][0] = 'h';
	tab[38][0] = 'j';
	tab[40][0] = 'k';
	tab[37][0] = 'l';
	tab[6][0] = 'z';
	tab[7][0] = 'x';
	tab[8][0] = 'c';
	init_tab2(tab);
}

char			mlx_keytochar(int key)
{
	static char		tab[255][1];
	static char		init = 0;

	if (!init && ++init)
		init_tab(tab, -1);
	if (key > -1 && key < 255)
		return (tab[key][0]);
	else if (key < 0)
		return ('\0');
	else if (key > 254)
		return ('\0');
	return ('\0');
}
