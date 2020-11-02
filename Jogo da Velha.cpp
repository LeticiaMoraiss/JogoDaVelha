#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <conio.c> //biblioteca para mudar as cores

int maquinajoga ();
int   POSICAO   ( int l, int c );
int   JOGADOR   ();
int   VELHA     ( char jog );
void  LIMPEZA   ();
void  VISUALIZA ();

//Vari�vel de controle para la�os de reiniciar a partida
int joga_dnv;

//Vari�vel de controle para la�os
int qtd_jodada; 

//Op��o do jogador utilizado no programa principal
char opcao;		   

//Op��o de simbolo do jogador utilizado no programa principal 
char simbolo;

//Op��o de simbolo que o jogador definiu para a maquina no programa principal 
char maqSimbolo;

//Recebe o retorno das fun��es que define o fim do jogo
int jogo;

//Vari�vel que define de quem � a vez para jogar
int vezde;	      

//Matriz jogo 3 X 3 
#define lim 3
char jv[lim][lim];	 

using namespace std;

//Programa principal. Jogo da Velha, esta parte do programa � a mais importante.
//Controla de quem � a vez de jogar, chamando as fun��es e procedimentos necess�rios para cada execu��o do programa
int main()
{
	textbackground(WHITE);
	
	setlocale(LC_ALL,"Portuguese");
	
	joga_dnv = 1;
	
	while(joga_dnv == 1)
	{	
		qtd_jodada = 1;
		
//Chama a fun��o para limpeza da matriz
		LIMPEZA();	                
		
//Controle para selecionar de quem � a primeira jogada MAQUINA ou JOGADOR
		do
		{
//Visualiza a matriz 3 X 3 com '0'
			VISUALIZA();	           	
			
	  	    textcolor(BLACK);
			cout<<"\n\t\t Op��es para in�cio do jogo...\n\n";
			cout<<"\t [D] Se voc� deseja que tenha o segundo jogador 1x1. \n";
			cout<<"\t [C] Se voc� deseja que o computador comece o jogo. \n";
			cout<<"\t [J] Se voc� deseja come�ar o jogo. \n";
			cout<<"\t [S] Se voc� deseja sair do jogo. \n";
	        cout<<"\n\t Informe a op��o desejada: ";
			opcao = toupper (getchar());
			
			if ( ( opcao == 'D' ) || ( opcao == 'C' ) || ( opcao == 'J' ) )
	    	{        		
		    	do
				{
					fflush(stdin);
					
					if(opcao != 'D')
					{
						cout<<"\n\t Voc� deseja ser O ou X? ";
					}
						 
					else
					{
					   cout<<"\n\t Voc� deseja ser O ou X - Jogador 1? ";	
					} 
					
					simbolo = toupper (getchar());
						
				}while ( ( simbolo != 'X' ) && ( simbolo != 'O' ) );	
			}
			
			else if( opcao == 'S')
			{
				return 0;
			}
			
			system("cls");

		}while ( ( opcao != 'D' ) && ( opcao != 'C' ) && ( opcao != 'S' ) && ( opcao != 'J' ) );
		
		if(opcao != 'S')
		{	
//Visualiza a matriz 3 X 3 com '0'
		    VISUALIZA();	  
			
			if (simbolo == 'X')
		    {
			    maqSimbolo = 'O';
			}		 
		    
			else
			{
			    maqSimbolo = 'X';	
			}  
		    	
			if ( opcao == 'C' || opcao == 'D')   		
			{
				vezde = 1;
		    }
				 
			else
			{
				vezde = 0;
			} 
				
//Este la�o controla as jogadas e s� termina quando algu�m ganha ou quando der empate: 
//OBS.: uma �tima modifica��o neste programa seria o jogador selecionar se quer parar ou come�ar um novo jogo
			do
			{		
				if(opcao == 'D')
				{
					if ( vezde == 0)
					{			
						jogo = JOGADOR();			
						vezde = 1;
				    }
					else
					{			
						jogo = JOGADOR();			
						vezde = 0;
				    }
				}
				else
				{
					if ( vezde == 0)
					{			
						jogo = JOGADOR();			
						vezde = 1;
				    }
					else
					{			
						jogo = maquinajoga();			
						vezde = 0;
				    }
				}
						    
//Completei esta verifica��o pois: Somente se igualar a 9 jogadas e ninguem vencer e porque deu velha
			    if(qtd_jodada == 8 && jogo == 0)
			   	{
			   		textcolor(LIGHTRED);
			   		cout<<"\n\n DEU VELHA \n";
			    }	
			   	
				qtd_jodada++;
// Este la�o tambem a condi��o jogo tive de mudar de('!jogo' para 'jogo == 0')
		
			}while (( qtd_jodada <= 8 ) && ( jogo == 0 ));
			
			if(( qtd_jodada <= 8 ) || ( jogo == 0 ))		
			{
				joga_dnv = 2;
				
				while( (joga_dnv < 0) || (joga_dnv > 1) )
				{
					textcolor(BLACK);
					fflush(stdin);
					cout<<"\n\n Deseja voltar ao menu e jogavamente ?";
					cout<<"\n Digite 1 para voltar ao menu OU zero (0) para sair : ";
					cin>>joga_dnv;
				}
			}
		}
	}
	textcolor(LIGHTRED);
	cout<<"\n\t OBRIGADO POR JOGAR. VOLTE SEMPRE !";
	
getch();
}

//Esta fun��o utiliza a fun��o random (rand) para selecionar uma nova jogada da m�quina, retornando true (verdadeiro) se a jogada resultou em vit�ria ou false (falso) caso contr�rio
int maquinajoga()
{
  int l,c,rposicao,v;

  rposicao = 1;
 
  srand(time(NULL));
  
  do
  {
	 if(jv[0][0] == simbolo && jv[0][2] == simbolo && jv[0][1] != simbolo && jv[0][1] != maqSimbolo)
	 {	
          l = 0;
          c = 1;
	 }

	 else if(jv[0][0] == simbolo && jv[0][1] == simbolo && jv[0][2] != simbolo && jv[0][2] != maqSimbolo)
	 {
		l = 0;
        c = 2;
	 }

	 else if((jv[0][2] == simbolo) && (jv[0][1] == simbolo) && (jv[0][0] != simbolo) && (jv[0][0] != maqSimbolo))
	 {
		l = 0;
        c = 0;
	 }
	 
	 else if((jv[0][0] == simbolo) && (jv[2][0] == simbolo) && (jv[1][0] != simbolo) && (jv[1][0] != maqSimbolo))
	 {
		l = 1;
        c = 0;
	 }
	 
	 else if((jv[0][0] == simbolo) && (jv[1][0] == simbolo) && (jv[2][0]!=simbolo) && (jv[2][0] != maqSimbolo))
	 {	
		l = 2;
        c = 0;
	 }
	 
	 else if((jv[1][0] == simbolo) && (jv[2][0] == simbolo) && (jv[0][0] != simbolo) && (jv[0][0] != maqSimbolo))
	 {	
		l = 0;
        c = 0;
	 }
	 
	 else if((jv[2][0] == simbolo) && (jv[2][2] == simbolo) && (jv[2][1] != simbolo) && (jv[2][1] != maqSimbolo))
	 {
		l = 2;
        c = 1;
	 }
	 
	 else if((jv[2][0] == simbolo) && (jv[2][1] == simbolo) && (jv[2][2] != simbolo) && (jv[2][2]!=maqSimbolo))
	 {	
		l = 2;
        c = 2;
	 }
	 
	 else if((jv[2][1] == simbolo) && (jv[2][2] == simbolo) && (jv[2][0] != simbolo) && (jv[2][0] != maqSimbolo))
	 {
		l = 2;
        c = 0;
	 }
	 
	 else if((jv[2][2] == simbolo) && (jv[0][2] == simbolo) && (jv[1][2] != simbolo) && (jv[1][2] != maqSimbolo))
	 {
		l = 1;
        c = 2;
	 }
	 
	 else if((jv[2][2] == simbolo) && (jv[1][2] == simbolo) && (jv[0][2] != simbolo) && (jv[0][2] != maqSimbolo))
	 {	
	 	l = 0;
        c = 2;
	 }
	 
	 else if((jv[1][2] == simbolo) && (jv[0][2] == simbolo) && (jv[2][2] != simbolo) && (jv[2][2] != maqSimbolo))
	 {
		l = 2;
        c = 2;
	 }
	 
	 else if((jv[0][1] == simbolo) && (jv[2][1] == simbolo) && (jv[1][1] != simbolo) && (jv[1][1] != maqSimbolo))
	 {	
	 	l = 1;
        c = 1;
	 }
	 
	 else if((jv[0][1] == simbolo) && (jv[1][1] == simbolo) && (jv[2][1] != simbolo) && (jv[2][1] != maqSimbolo))
	 {	
	 	l = 2;
        c = 1;
	 }
	 
	 else if((jv[1][1] == simbolo) && (jv[2][1] == simbolo) && (jv[0][1] != simbolo) && (jv[0][1] != maqSimbolo))
	 {
	 	l = 0;
        c = 1;
	 }
	 
	 else if((jv[0][0] == simbolo) && (jv[2][2] == simbolo) && (jv[1][1] != simbolo) && (jv[1][1] != maqSimbolo))
	 {
		l = 1;
        c = 1;
	 }
	 
	 else if((jv[0][0] == simbolo) && (jv[1][1] == simbolo) && (jv[2][2] != simbolo) && (jv[2][2] != maqSimbolo))
	 {	
		l = 2;
        c = 2;
	 }
	 
	 else if((jv[1][1] == simbolo) && (jv[2][2] == simbolo) && (jv[0][0] != simbolo) && (jv[0][0] != maqSimbolo))
	 {	
		l = 0;
        c = 0;
	 }
	 
	 else if((jv[0][2] == simbolo) && (jv[2][0] == simbolo) && (jv[1][1] != simbolo) && (jv[1][1] != maqSimbolo))
	 {
		l = 1;
        c = 1;
	 }
	 
	 else if((jv[0][2] == simbolo) && (jv[1][1] == simbolo) && (jv[2][0] != simbolo) && (jv[2][0] != maqSimbolo))
	 {	
		 l = 2;
	     c = 0;
	 }
	 
	 else if((jv[2][0] == simbolo) && (jv[1][1] == simbolo) && (jv[0][2] != simbolo) && (jv[0][2] != maqSimbolo))
	 {
		 l = 0;
	     c = 2;	
	 }
	
	 else
	 {
		l = rand()%3;
	 	c = rand()%3;
	 }
	 
	 rposicao = POSICAO(l,c);
	
	 if (rposicao == 1)
	 {
	 	jv[l][c] = maqSimbolo;
	 }
	    	    
  }while (! rposicao == 1);
  
  VISUALIZA();  
  
  v = VELHA(maqSimbolo);
  
  if ( v == 1)
  {
  	 textcolor(LIGHTRED);
     cout<<" A MAQUINA VENCEU O JOGO..........\n";
     return 1;
  }
  
  else
  {
  	return 0;
  } 
}

//Esta fun��o recebe uma posi��o da matriz e verifica se esta posi��o j� foi selecionada, retornando true (verdadeiro) se j� tiver sido selecionada ou false (falso) caso contr�rio
int POSICAO( int l, int c)
{
//Este trecho ele percorre a matriz inteira
    for(int i = 0; i < 9; i++)
    {
    	for(int j = 0; j < 9; j++)
   		{

// Ele pega os valores passados em nossa fun��o ('l','c') e compara com as posi��es; se ela for igual entra e faz uma outra compara��o   			
   			if(i == l && c == j)
   			{

// Apos validar as posi��es da matriz que estamos ele ainda verifica se aquela posi��o ja foi ocupada por um valor.
//Se esta posi��o estiver com caractere diferente de '0' o e porque ela foi usada ja logo a fun��o ir� retornar 1 'true';				
   				if(jv[i][j] != 'X' && jv[i][j] != 'O')
			    {
			    	return 1;
			    }

//Caso contrario a fun��o ir� retornar 0 'false' pois aquela posi��o ainda pode ser usada*
			    else
				{
			    	return 0;
				}
   			}	    	
		}
    }    
}

int JOGADOR()
{
// Este codigo e nada mais e nada menos que o mesmo que usamos para a maquina o diferencial e que pedimos o usuario para informar um valor('J') para linha e coluna   
    int l, c, veia;
	int rposicao = 1;
	
//Ele entra nesse la�o pois enquanto o jogador n�o informar uma posi��o v�lida ele fica repetindo as mesmas perguntas
	  do
	  {	
	    char jogando = 0;
	   
		for( ;(jogando < '1') || (jogando > '9'); )
		{	 
			if(opcao != 'D')
			{
				cout<<"\n  Digite a posi��o em que quer jogar o "<<simbolo<<" :";
			}				
			
			else
			{
				 if(vezde == 1)				
				 {
				  	cout<<"\n  Digite a posi��o em que quer jogar o "<<simbolo<<" - Jogador 1 :";
				 } 				
			     
				 else
			     {
			  	    cout<<"\n  Digite a posi��o em que quer jogar o "<<maqSimbolo<<" - Jogador 2 :";
			     } 								
			}
			
			cin>>jogando;
			fflush(stdin);			
		}
		
//Verifica se a linha e coluna que o usario informou � valida, ou seja, se ela ja foi usada (Independente se foi a maquina ou ele que usou) ou n�o.		
		if(jogando == '1')
		{
			l = 0; c = 0;
		}
		
		if(jogando == '2')
		{
			l = 0; c = 1;
		}
		
		if(jogando == '3')
		{
			l = 0; c = 2;
		}		
		
		if(jogando == '4')
		{
			l = 1; c = 0;
		}
		
		if(jogando == '5')
		{
			l = 1; c = 1;
		}
		
		if(jogando == '6')
		{
			l = 1; c = 2;
		}
		
		if(jogando == '7')
		{
			l = 2; c = 0;
		}
		
		if(jogando == '8')
		{
			l = 2; c = 1;
		}
		
		if(jogando == '9')
		{
			l = 2; c = 2;
		}			
			
		rposicao = POSICAO(l,c);

// Verificamos aqui se a posi��o � igual a 1, pois se for ele atribui o valor "J" a matriz de acordo com a posi��o que o usuario informou
 		if (rposicao == 1)
 		{
 			if(opcao != 'D')
 			{
 				jv[l][c] = simbolo;
 			}
 			
			else
 			{
 			   if(vezde == 1)	
 			   {
    		     jv[l][c] = simbolo;
			   }	 				
			   
			   else
			   {
			   	 jv[l][c] = maqSimbolo;
			   } 	
 			}
 		}		    
		    
//Tive de mudar a condi��o de la�o nesta fun��o e na fun��o da maquina para poder funcionar
//Ou seja enquanto rposi��o estiver 'Usada' ele repete essa msg e pede ao usuario um novo valor
	  }while (! rposicao == 1);
	  
//Manda visualizar a matriz apos a nova inser��o	  	  
	  VISUALIZA();
	  
//Pega o retorno da valida��o se h� um vencedor ou deu velha
	  veia = VELHA(simbolo);
	  
	  if(opcao != 'D')
 	  {
 	       veia = VELHA(simbolo);
 	  }
 	  
 	  else
 	  {
 	    if (vezde == 1)	
 		{
 		  veia = VELHA(simbolo);
		}	 				
		
		else
		{
		  veia = VELHA(maqSimbolo);
		} 	
      }
	  
//Somente se o jogador ganhar (v==1) ele joga essa msg na tela... mudei na fun��o maquina tambem e coloquei da mesma forma.
	  if ( veia == 1 )
	  {
	  	 textcolor(LIGHTRED);
	  	 if(opcao != 'D')
	     {
	       cout<<" O JOGADOR VENCEU O JOGO..........\n";
		 }
		 
	     else
	     {
	       if (vezde == 1)	
 	       {
 	         cout<<" O JOGADOR 1 VENCEU O JOGO..........\n";
		   }    			
		   
		   else
		   {
		   	 cout<<" O JOGADOR 2 VENCEU O JOGO..........\n";
		   } 
	     }
	     return 1;
	  }
	 
	  else
	  {
	    return 0;
	  } 
}

int VELHA(char jog)
{
//O codigo abaixo ele percorre as linhas 1,2,3 e verifica se um dos jogadores venceu 
    if(jv[0][0] == jog && jv[0][1] == jog && jv[0][2] == jog)
    {
    	return 1;
	}	 
    	 
    else if(jv[1][0] == jog && jv[1][1] == jog && jv[1][2] == jog)
    {
    	return 1;
	}	 
    	 
    else if(jv[2][0] == jog && jv[2][1] == jog && jv[2][2] == jog)
    {
    	return 1;
	}	 
    
//O codigo abaixo ele percorre as colunas 1,2,3 e verifica se um dos jogadores venceu
    else if(jv[0][0] == jog && jv[1][0] == jog && jv[2][0] == jog)
	{
    	return 1;
	}	 
	     
    else if(jv[0][1] == jog && jv[1][1] == jog && jv[2][1] == jog)
	{
    	return 1;
	}	 
	     
    else if(jv[0][2] == jog && jv[1][2] == jog && jv[2][2] == jog)
    {
    	return 1;
	}	 
    	 
//O codigo abaixo ele percorre as diagonais(principal,secundaria) e verifica se um dos jogadores venceu    	 
 	else if(jv[0][0] == jog && jv[1][1] == jog && jv[2][2] == jog)
	{
    	return 1;
	}	 
		 
    else if(jv[0][2] == jog && jv[1][1] == jog && jv[2][0] == jog)
    {
    	return 1;
	}	 
    	 
    else
	{
	    return 0;	
	} 
}
		                                
void LIMPEZA() 
{ 
    
	jv[0][0] = '1';
	jv[0][1] = '2';
	jv[0][2] = '3';
	
	jv[1][0] = '4';
	jv[1][1] = '5';
	jv[1][2] = '6';
	
	jv[2][0] = '7';
	jv[2][1] = '8';
	jv[2][2] = '9';
}
  
//Procedimento utilizado para visualizar o conte�do da matriz
void VISUALIZA()
{	
	system("cls");	
    int w,k;  
	
	textcolor(BLACK); 
	cout<<"\n\t\t SEJA BEM VINDO AO JOGO DA VELHA. DIVIRTA-SE !!\n";
    cout<<"*******************************************************************************\n\n";
    
	
	for (w=0;w<lim;w++)
    {
       cout<<"\t\t\t\t  ";
    	
	   for (k=0;k<lim;k++)
		{
			textcolor(YELLOW);
			if(k == 1)
		    {
		    	cout<<" | ";
		    	textcolor(LIGHTRED);
				cout<<jv[w][k];
				textcolor(YELLOW);
				cout<<" | ";
			}	
		    
			else
		    { 
		       textcolor(LIGHTRED);
		   	   cout<<jv[w][k];
		    } 
		}   
		
		if(w < 2)
		{
			textcolor(YELLOW);
			cout<<"\n\t\t\t\t----+---+----\n"; 
		}       
    }
    textcolor(BLACK); 
    cout<<"\n\n*******************************************************************************\n\n";
}           
