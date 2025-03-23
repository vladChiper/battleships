#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 5 //Numarul maxim ar trebui sa fie 10
#define NR_VAPOARE 3

typedef struct
{
    char numeJucator[20];
    int pozitiiVapoare[NR_VAPOARE + 1];
    int scorJucator;
}JUCATOR; 

int alegereAleatoare();
void configurareJucator(JUCATOR *);
void configurareAI(JUCATOR *);
void afisare(JUCATOR *);

int main()
{
    JUCATOR player[2];
    for(int i = 0 ; i < 2; i++)
    {
         configurareJucator(&player[i]) ; 
    }
    afisare(player);


}

void afisare(JUCATOR *p)
{
    for(int i = 0 ; i < 5 + TABLE_SIZE*2; i++) printf("#");
    printf("\n");
    for(int i = 0 ; i < TABLE_SIZE; i++) // Afisam primul tabel
    {
        printf("#");
        for(int j = 0 ; j < TABLE_SIZE; j++)
        {
            int pozitieNula = 1;
            for(int k = 0 ; k < NR_VAPOARE; k++)
            {
                if( (i*10 + j) == p[0].pozitiiVapoare[k])
                {
                    pozitieNula = 0;
                }
            }
            pozitieNula ? printf(" ") : printf("V");
        }
        printf(" # ");
        for(int j = 0 ; j < TABLE_SIZE; j++)// Afisam p2 tabel
        {
            int pozitieNula = 1;
            for(int k = 0 ; k < NR_VAPOARE; k++)
            {
                if( (i*10 + j) == p[1].pozitiiVapoare[k])
                {
                    pozitieNula = 0;
                }
            }
            pozitieNula ? printf(" ") : printf("V");
        }
        printf("#\n");
    }
    for(int i = 0 ; i < 5 + TABLE_SIZE*2; i++) printf("#");
}

void configurareJucator(JUCATOR  *p)
{
    printf("Introduceti numele jucatorului:\n>>>");
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
            pozitieValida = 1; 
            printf("Introduceti pozitia vaporului nr. %d:\n>>> ", i + 1);
            if (scanf("%d", &p->pozitiiVapoare[i]) != 1)
            {
                fprintf(stderr, "Eroare la citirea pozitiei vaporului.\n");
                exit(-1);
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
}

int alegereAleatoare()
{
    {
        int n;
        srand(time(NULL));
        
        n = (rand() % TABLE_SIZE)*10 + rand() % TABLE_SIZE;
       
        return n;
    }
}