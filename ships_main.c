#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TABLE_SIZE 5 //Numarul maxim ar trebui sa fie 10
#define NR_VAPOARE 3

typedef struct
{
    char numeJucator[20];
    int pozitiiVapoare[NR_VAPOARE + 1];
    int scorJucator;
    int pozitiiLovite[TABLE_SIZE*TABLE_SIZE + 1];
    int nrLovituri;

}JUCATOR; 

int alegereAleatoare();
void configurareJucator(JUCATOR *);
void configurareAI(JUCATOR *);
void afisare(JUCATOR *, int);
void afisareBorduraOrizontala();
int verificareLovire(int);
void adaugareLovitura(JUCATOR *, int, int );
int esteLovire(JUCATOR * , int);
void afisareCelula(int , int);
void afisareCelula2(int , int);

int main()
{
    JUCATOR player[2];
    
    configurareJucator(&player[0]) ;
    srand(time(NULL));
    configurareAI(&player[1]); 

    int playerW = 0, AIW = 0;
    int nrLovituri = 0;
    while(!playerW || !AIW)
    {
        afisare(player, nrLovituri);
        int lovire;
        //PARTEA DE RUNDA A JUCATORULUI
        do{
            printf("Alegeti coordonatele atacului: ");
            if(scanf("%d",&lovire)!= 1)
            {
                fprintf(stderr, "nu s a citit lovirea");
                exit(-1);
            }
        }while(!verificareLovire(lovire));

        adaugareLovitura(&player[1], lovire, nrLovituri);
       
        if (esteLovire(&player[1], lovire)) 
        {
            player[0].nrLovituri++;
            if(player[0].nrLovituri == NR_VAPOARE)
            {
                playerW = 1;
                break;
            }
        }

        //PARTEA DE RUNDA AI
        lovire = alegereAleatoare();
        adaugareLovitura(&player[0], lovire, nrLovituri);
        if (esteLovire(&player[0], lovire)) 
        {
            player[1].nrLovituri++;
            if(player[1].nrLovituri == NR_VAPOARE)
            {
                AIW = 1;
                break;
            }
        }
        nrLovituri++;

    }

}

void adaugareLovitura(JUCATOR *p , int lovitura, int  i)
{
    p->pozitiiLovite[i] = lovitura; 
}

int esteLovire(JUCATOR * p, int lovitura) // va returna 1 daca lovitura a fost un succes, 0 altfel
{

    for(int i = 0 ; i < NR_VAPOARE; i++)
    {
        if(lovitura == p->pozitiiVapoare[i])
        {
            return 1;
        }
    }
    return 0;
}

int verificareLovire(int numar) // functia va returna 1 daca lovirea este conforma, 0 altfel
{
    if ( (numar % 10 < TABLE_SIZE) && (numar / 10 % 10 < TABLE_SIZE) && (numar < 100) )
    {
        return 1;
    }
    return 0;
}

void configurareAI(JUCATOR *p)
{
    strcpy(p->numeJucator, "AI");
    for(int i = 0 ; i < NR_VAPOARE; i++)
    {
        int pozitieValida ;
        do
        {
            pozitieValida = 1; // Punem o variabila care va masura daca pozitia este valida
            p->pozitiiVapoare[i] = alegereAleatoare();
            if( (p->pozitiiVapoare[i] > 99) || (p->pozitiiVapoare[i] % 10 > TABLE_SIZE-1) || (p->pozitiiVapoare[i] /10 % 10 > TABLE_SIZE-1) )
            {
                pozitieValida = 0; // Cautam daca pozitia este pe tabel
            }

            // Verificăm dacă poziția a fost deja introdusă
            for (int j = 0; j < i; j++)
            {
                if (p->pozitiiVapoare[i] == p->pozitiiVapoare[j]) 
                {
                    pozitieValida = 0; 
                    break;
                }
            }

        } while (!pozitieValida); 
    }
    p->nrLovituri = 0;
}
void afisareBorduraOrizontala()
{
    printf("# ");
    for( int i = 0 ; i < TABLE_SIZE; i++)
    {
        printf("%d ", i);
    }
    printf("# ");
    for(int i = 0 ; i < TABLE_SIZE; i++)
    {
        printf("%d ", i );
    }
    printf("#\n");
}
void afisareCelula(int a, int b)
{
    if( a ) // este vapor
    {
        if ( b ) // este si vapor si lovit
        {
            printf("X ");
        }
        else
        {
            printf("V ");
        }
    }
    else if(b && !a) // lovitura esuata
    {
        printf(". ");
    }
    else 
    {
        printf("  ");
    }
}
void afisareCelula2(int a, int b)
{
    if( a ) // este vapor
    {
        if ( b ) // este si vapor si lovit
        {
            printf("X ");
        }
        else
        {
            printf("  ");
        }
    }
    else if(b && !a) // lovitura esuata
    {
        printf(". ");
    }
    else 
    {
        printf("  ");
    }
}


void afisare(JUCATOR *p, int nrLovituri)
{
    printf("\033[H\033[J"); //clear la ecranul anterior
    afisareBorduraOrizontala();
    for(int i = 0 ; i < TABLE_SIZE; i++) // Afisam primul tabel
    {
        printf("%d ", i);
        for(int j = 0 ; j < TABLE_SIZE; j++)
        {
            int pozitieVapor = 0;
            int pozitieLovita = 0;
            for(int k = 0 ; k < NR_VAPOARE; k++)
            {
                if( (i*10 + j) == p[0].pozitiiVapoare[k])
                {
                    pozitieVapor = 1;
                }
            }
            for(int k = 0 ; k < nrLovituri; k++)
            {
                if( (i*10 + j) == p[0].pozitiiLovite[k])
                {
                    pozitieLovita = 1;
                }
            }
            afisareCelula(pozitieVapor, pozitieLovita);
            
        }
        printf("%d ", i);
        for(int j = 0 ; j < TABLE_SIZE; j++)// Afisam p2 tabel
        {
            int pozitieVapor = 0;
            int pozitieLovita = 0;
            for(int k = 0 ; k < NR_VAPOARE; k++)
            {
                if( (i*10 + j) == p[1].pozitiiVapoare[k])
                {
                    pozitieVapor = 1;
                }
            }
            for(int k = 0 ; k < nrLovituri; k++)
            {
                if( (i*10 + j) == p[1].pozitiiLovite[k])
                {
                    pozitieLovita = 1;
                }
            }
            afisareCelula2(pozitieVapor, pozitieLovita);
            
        }
        printf("#\n");
    }
    for(int i = 0 ; i < 5 + TABLE_SIZE*4; i++) printf("#");
    printf("\n");
}

void configurareJucator(JUCATOR  *p)
{
    printf("Nume locotenent: ");
    if ( scanf("%19s", p->numeJucator) != 1)
    {
        fprintf(stderr, "nu s a citit bine nume jucator");
        exit(-1);
    }
    for(int i = 0 ; i < NR_VAPOARE; i++)
    {
        int pozitieValida ;
        do
        {
            pozitieValida = 1; // Punem o variabila care va masura daca pozitia este valida
            printf("Introduceti pozitia vaporului nr. %d:\n>>> ", i + 1);
            if (scanf("%d", &p->pozitiiVapoare[i]) != 1)
            {
                fprintf(stderr, "Eroare la citirea pozitiei vaporului.\n");
                exit(-1);
            }
            if( (p->pozitiiVapoare[i] > 99) || (p->pozitiiVapoare[i] % 10 > TABLE_SIZE-1) || (p->pozitiiVapoare[i] /10 % 10 > TABLE_SIZE-1) )
            {
                printf("Aceasta pozitie este invalida, coordonatele xy trebuie sa fie < %d\n", TABLE_SIZE);
                pozitieValida = 0; // Cautam daca pozitia este pe tabel
            }

            // Verificăm dacă poziția a fost deja introdusă
            for (int j = 0; j < i; j++)
            {
                if (p->pozitiiVapoare[i] == p->pozitiiVapoare[j]) 
                {
                    printf("Aceasta pozitie este deja ocupata de vaporul %d. Introduceti alta pozitie.\n", j + 1);
                    pozitieValida = 0; 
                    break;
                }
            }

        } while (!pozitieValida); 
    }
    p->nrLovituri = 0;
}

int alegereAleatoare()
{
    {
        int n;
        n = (rand() % TABLE_SIZE)*10 + rand() % TABLE_SIZE;
       
        return n;
    }
}