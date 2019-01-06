#include <stdio.h>

#define BOARDSIZE 8
#define SIRO 1
#define KURO -1
#define NONE 0
#define SIROKOMA "@"
#define KUROKOMA "*"
void osero( void );
void init( int[BOARDSIZE][BOARDSIZE] );
void disp( int[BOARDSIZE][BOARDSIZE] );
int getinviro( int );
int hantei( int[BOARDSIZE][BOARDSIZE], int, int[2], int[2] );
void inv( int[BOARDSIZE][BOARDSIZE], int, int, int[2], int[2] );
int put( int[BOARDSIZE][BOARDSIZE], int, int[2] );
int pass_chk( int[BOARDSIZE][BOARDSIZE], int );
int puttest( int[BOARDSIZE][BOARDSIZE], int, int[2] );
void count( int[BOARDSIZE][BOARDSIZE], int*, int* );

void osero( void ) {
	int ban[BOARDSIZE][BOARDSIZE];
	int ii;
	int jj;
	int sirocnt;
	int kurocnt;
	int ichi[2];
	int teban;
	char passed;

	passed = 0;
	for ( ii = 0; ii < BOARDSIZE; ii++ ) {
		for ( jj = 0; jj < BOARDSIZE; jj++ ) {
			ban[ii][jj] = NONE;
		}
	}
	init( ban );
	disp( ban );
	teban = SIRO;
	while ( 1 ) {
		count( ban, &sirocnt, &kurocnt );
		if ( sirocnt + kurocnt == BOARDSIZE * BOARDSIZE ) {
			break;
		}
		printf( "%s:%d %s:%d\n", SIROKOMA, sirocnt, KUROKOMA, kurocnt );
		if ( teban == SIRO ) {
			printf( "%sÇÃéËî‘\n", SIROKOMA );
		} else if ( teban == KURO ) {
			printf( "%sÇÃéËî‘\n", KUROKOMA );
		} else {
			printf( "ERROR\n" );
			break;
		}
		if ( pass_chk( ban, teban ) == 0 ) {
			if ( passed ) {
				break;
			}
			passed = 1;
			printf( "ÉpÉX\n" );
			teban = getinviro( teban );
			continue;
		}
		scanf( "%d %d", &ichi[0] , &ichi[1] );
		if ( ichi[0] < 0 || ichi[1] < 0 ) {
			break;
		}
		if ( put( ban, teban, ichi ) == -1 ) {
			printf( "ÇæÇﬂÇ≈Ç∑\n" );
			continue;
		}
		disp( ban );
		teban = getinviro( teban );
		passed = 0;
	}
	count( ban, &sirocnt, &kurocnt );
	printf( "%s:%d %s:%d\n", SIROKOMA, sirocnt, KUROKOMA, kurocnt );
	if ( sirocnt > kurocnt ) {
		printf( "%sÇÃèüÇø\n", SIROKOMA );
	} else if ( sirocnt < kurocnt ) {
		printf( "%sÇÃèüÇø\n", KUROKOMA );
	} else {
		printf( "à¯Ç´ï™ÇØ\n" );
	}

}
int puttest( int ban[BOARDSIZE][BOARDSIZE], int iro, int ichi[2] ) {
	int ii;
	int jj;
	int houkou[2];
	int kosu;

	kosu = 0;
	for ( ii = -1; ii <= 1; ii++ ) {
		for ( jj = -1; jj <= 1; jj++ ) {
			if ( ii == 0 && jj == 0 ) {
				continue;	
			}
			houkou[0] = ii;
			houkou[1] = jj;
			kosu += hantei( ban, iro, ichi, houkou );
		}
	}
	return kosu;
}
int pass_chk( int ban[BOARDSIZE][BOARDSIZE], int iro ) {
	int ii;
	int jj;
	int kosu;
	int ichi[2];

	for ( ii = 0; ii < BOARDSIZE; ii++ ) {
		for ( jj = 0; jj < BOARDSIZE; jj++ ) {
			if ( ban[ii][jj] != NONE ) {
				continue;
			}
			ichi[0] = ii;
			ichi[1] = jj; 
			if ( puttest( ban, iro, ichi ) > 0 ) {
				return 1;
			}
		}
	}
	return 0;
}
void init( int ban[BOARDSIZE][BOARDSIZE] ) {
	int ii;
	int jj;

	for ( ii = 0; ii < BOARDSIZE; ii++ ) {
		for ( jj = 0; jj < BOARDSIZE; jj++ ) {
			ban[ii][jj] = NONE;
		}
	}
	ban[BOARDSIZE / 2][BOARDSIZE / 2] = SIRO;
	ban[BOARDSIZE / 2 - 1][BOARDSIZE / 2 - 1] = SIRO;
	ban[BOARDSIZE / 2][BOARDSIZE / 2 - 1] = KURO;
	ban[BOARDSIZE / 2 - 1][BOARDSIZE / 2] = KURO;

}
void disp( int ban[BOARDSIZE][BOARDSIZE] ) {
	int ii;
	int jj;
	int sirokosu;
	int kurokosu;

	printf( "   " );
	for ( ii = 0; ii < BOARDSIZE; ii++ ){
		printf( "%d ", ii );
	}
	printf( "\n" );
	printf( "   " );
	for ( ii = 0; ii < BOARDSIZE; ii++ ){
		printf( "_ ", ii );
	}
	printf( "\n" );
	for ( ii = 0; ii < BOARDSIZE; ii++ ) {
		printf( "%d |", ii );
		for ( jj = 0; jj < BOARDSIZE; jj++ ) {
			switch ( ban[jj][ii] ) {
			case KURO:
				printf( "%s|", KUROKOMA );
				break;
			case SIRO:
				printf( "%s|", SIROKOMA );
				break;
			case NONE:
				printf( "_|" );
				break;
			default:
				break;
			}
			if ( jj == BOARDSIZE - 1 ) {
				printf( "\n" );
			}
		}
	}
}
void count( int ban[BOARDSIZE][BOARDSIZE], int *sirocnt, int *kurocnt ) {
	int ii;
	int jj;
	int sirokosu;
	int kurokosu;

	*sirocnt = 0;
	*kurocnt = 0;
	for ( ii = 0; ii < BOARDSIZE; ii++ ) {
		for ( jj = 0; jj < BOARDSIZE; jj++ ) {
			switch ( ban[jj][ii] ) {
			case KURO:
				(*kurocnt)++;
				break;
			case SIRO:
				(*sirocnt)++;
				break;
			case NONE:
				break;
			default:
				break;
			}
		}
	}
}
int getinviro( int iro ) {
	if ( iro == SIRO ) {
		return KURO;
	} else if ( iro == KURO ) {
		return SIRO;
	} else {
		return NONE;
	}

}
int hantei( int ban[BOARDSIZE][BOARDSIZE], int iro, int ichi[2], int houkou[2] ) {
	int x;
	int y;
	int kosu;
	int inviro;
	
	kosu = 0;
	x = ichi[0] + houkou[0];
	y = ichi[1] + houkou[1];
	if ( ban[x][y] == NONE || ban[x][y] == iro ) {
		kosu = 0;
		return kosu;
	}
	inviro = getinviro( iro );
	for ( x = ichi[0] + houkou[0], y = ichi[1] + houkou[1]; x >=0 && x < BOARDSIZE && y >= 0 && y < BOARDSIZE; x += houkou[0], y += houkou[1] ) {
		if ( ban[x][y] == inviro ) {
			kosu++;
		} else if ( ban[x][y] == iro ) {
			break;
		} else {
			kosu = 0;
			break;
		}
			
	}
	if ( x == -1 || x == BOARDSIZE || y == -1 || y == BOARDSIZE ) {
		kosu = 0;
	}
	return kosu;
}
void inv( int ban[BOARDSIZE][BOARDSIZE], int iro, int kosu, int ichi[2], int houkou[2]  ) {
	int ii;
	int x;
	int y;

	x = ichi[0] + houkou[0];
	y = ichi[1] + houkou[1];
	for ( ii = 0; ii < kosu; ii++ ) {
		ban[x][y] = iro;	
		x += houkou[0];
		y += houkou[1];
	}
}
int put( int ban[BOARDSIZE][BOARDSIZE], int iro, int ichi[2] ) {
	int ii;
	int jj;
	int houkou[2];
	int kosu;
	int totalkosu;
	int inviro;
	totalkosu = 0;
	inviro = getinviro( iro );
	if ( ban[ichi[0]][ichi[1]] != NONE ) {
		return -1;
	}
	for ( ii = -1; ii <= 1; ii++ ) {
		for ( jj = -1; jj <= 1; jj++ ) {
			if ( ii == 0 && jj == 0 ) {
				continue;
			}
			houkou[0] = ii;
			houkou[1] = jj;
			kosu = hantei( ban, iro, ichi, houkou );
//			printf( "kosu:%d ichi: %d,%d houkou:%d,%d\n", kosu, ichi[0], ichi[1], houkou[0], houkou[1] );
			if ( kosu > 0 ) {
				inv( ban, iro, kosu, ichi, houkou );
				totalkosu += kosu;
			}
		}
	}
	if ( totalkosu == 0 ) {
		return -1;
	}
	ban[ichi[0]][ichi[1]] = iro;
}

void main( void ) {
	osero();
}
