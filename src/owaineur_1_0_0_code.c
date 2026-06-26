
// Owaineur version 1.0.0

// Source code

// Released into the public domain under CC0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int akt,rnd,i,j,k,l,tm;
double aa[5],bb[5],cc[5],wg[2][25],hn[5],bs[2][5],lr;
char sym;

void nf() {
	double ta = 0;
	int twg = 0;
	for (j = 0; j < 5; j++) {
		bb[j] = 0;
		hn[j] = 0;
	}
	for (j = 0; j < 5; j++) {
		ta = 0;
		for (k = 0; k < 5; k++) {
			ta += aa[k] * wg[0][twg];
			twg++;
		}
		hn[j] = tanh(ta + bs[0][j]);
	}
	twg = 0,ta = 0;
	for (j = 0; j < 5; j++) {
		ta = 0;
		for (k = 0; k < 5; k++) {
			ta += hn[k] * wg[1][twg];
			twg++;
		}
		bb[j] =  tanh(ta + bs[1][j]);
	}
}

void nm() {
	double er,era,sm = 0,ps,psa,o_wg[2][25];
	int twga = 0,twgb = 0,twgc = 0;
	for (j = 0; j < 2; j++) {
		for (k = 0; k < 25; k++) {
			o_wg[j][k] = wg[j][k];
		}
	}
	for (j = 0; j < 5; j++) {
		ps = 1 - (bb[j] * bb[j]);
		er = (cc[j] - bb[j]) * ps;
		for (k = 0; k < 5; k++) {
			wg[1][twga] += lr * er * hn[k];
			twga++;
		}
		bs[1][j] += lr * er;
	}
	for (j = 0; j < 5; j++) {
		sm = 0;
		ps = 1 - (hn[j] * hn[j]);
		twga = twgc;
		for (k = 0; k < 5; k++) {
			psa = 1 - (bb[k] * bb[k]);
			er = (cc[k] - bb[k]) * psa;
			sm += er * o_wg[1][twga];
			twga+=5;
		}
		era = sm * ps;
		for (k = 0; k < 5; k++) {
			wg[0][twgb] += lr * era * aa[k];
			twgb++;
		}
		bs[0][j] += lr * era;
		twgc++;
	}
}

int main()
{
	printf("\nPUBLIC DOMAIN SOFTWARE");
	printf("\nOwaineur");
	printf("\nVersion 1.0.0\n");
	srand(time(NULL));
	int num;
	printf("\nR/S?");
	scanf(" %c",&sym);
	if (sym == 'r') {
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 5; j++) {
				double na = 0 - 0.5,nb = 0.5;
				bs[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 25; j++) {
				double na = 0 - 0.5,nb = 0.5;
				wg[i][j] = na + ((double)rand() / RAND_MAX) * (nb - na);
			}
		}
	}
	if (sym == 's') {
		num = 1;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 5; j++) {
				printf("\nBias %d:",num);
				scanf("%lf",&bs[i][j]);
				num++;
			}
		}
		num = 1;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 25; j++) {
				printf("\nWG %d:",num);
				scanf("%lf",&wg[i][j]);
				num++;
			}
		}
	}
	akt = 1;
	do
	{
		for (i = 0; i < 5; i++) {
			printf("\nI %d:",i+1);
			scanf("%lf",&aa[i]);
		}
		for (i = 0; i < 5; i++) {
			printf("\nT %d:",i+1);
			scanf("%lf",&cc[i]);
		}
		printf("\nTime:");
		scanf("%d",&tm);
		printf("\nLR:");
		scanf("%lf",&lr);
		for (i = 0; i < tm; i++) {
			nf();
			nm();
		}
		nf();
		for (i = 0; i < 5; i++)
			printf("\nO %d: %lf",i+1,bb[i]);
		printf("\n ");
		scanf(" %c",&sym);
		if (sym == 'i') {
			num = 1;
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 25; j++) {
					printf("\nWG %d: %lf",num,wg[i][j]);
					num++;
				}
			}
			num = 1;
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 5; j++) {
					printf("\nBias %d: %lf",num,bs[i][j]);
					num++;
				}
			}
		}
		if (sym == 'x') akt = 0;
	}
	while (akt == 1);
	return 0;
}