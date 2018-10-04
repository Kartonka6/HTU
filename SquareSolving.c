#include<stdio.h>
#include<math.h>
#include<assert.h>


            //Function prototypes//
int SolveSquare(double a, double b, double c, double* px1, double* px2);
int SolveLiner(double b, double c, double* px1);


            //Function Main//
int main()
{
    printf("#SquareEqsd (c) Yegor\n");
    printf("# Enter a, b, c:\n");
    double a = NAN, b = NAN, c = NAN;
    if ((scanf("%lg %lg %lg", &a, &b, &c) != 3) || (a != a) || (b != b) || (c != c))    //Checking for input//
    {
        printf("Invalid input data\n");
        return -100;
    }
    double x1 = NAN, x2 = NAN;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);
    switch(nRoots)
    {
        case 1:
            printf("SolveSquare has 1 root:\n");
            printf("x1 = %lg\n", x1);
            break;
        case 2:
            printf("SolveSquare has 2 roots:\n");
            printf("x1 = %lg\n x2 = %lg\n", x1, x2);
            break;
        case 0:
            printf("SolveSquare doesn't have any roots\n");
            break;
        case -1:
            printf("Infinite value of roots\n");
            break;
        default:
            printf("Strange nRoots = %d in SolveSquare(%lg, %lg, %lg)\n", nRoots, a, b, c);
            return 1;
    }
    return 0;
}


    //SolvelSquare Function//
int SolveSquare(double a, double b, double c, double* px1, double *px2)
{
    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);
    assert(a == a);
    assert(b == b);
    assert(c == c);
    double D = (b*b - 4*a*c);
    assert(D == D);
    if (a == 0)
    {
        return SolveLiner(b, c, px1);
    }
    if (D < 0)
    {
        return 0;
    }
    else 
    {
        if(D == 0)
        {
            *px1 = -b/(2*a);
            return 1;
        }
        else 
        {  
            *px1 = (-b + sqrt(D))/(2*a);
            *px2 = (-b - sqrt(D))/(2*a);
            return 2;
        }
    }
}


    // SolveLiner Function//
int SolveLiner(double b, double c, double* px1)
{
    assert((b == b) || (c == c) || (px1 == NULL));
    if (b == 0)
    {
        if (c != 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else 
    {
        *px1 = -c/b;
        return 1;
    }
}

        




