#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
struct Point
{
    int x, y;
};
Point p0;
int pozitie_punct(Point ac1[],Point ac2[], int n1,int n2)
{
    if(n1!=n2)
        {cout<<"Punctul A se afla in exterior";  // acoperirile convexe au numar diferit de elemente, deci nu coincid
        return 0;}

    int verif=0;
    for(int i=0;i<n1;i++)
        if(ac1[i].x!=ac2[i].x||ac1[i].y!=ac2[i].y)
        verif=1;

    if(verif==0)
        return 1;

        cout<<"Punctul A se afla in exterior";
        return 0;
        //acoperirile convexe coincid
        //punctul se afla fie in interior, fie pe una din laturi




}


Point next_to_top(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}


// Fac o functie care imi gaseste orientarea tripletului (p, q, r).
// si imi va return una din cele 3 valori:
// 0 --> p, q si r sunt coliniare
// 1 --> clockwise
// 2 --> counterclockwise
int orientare(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // coliniar
    if(val > 0)
    return 1;

    return 2; // clockwise sau counterclockwise
}

//functie de comparare pentru qsort
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   // gaseste orientarea
   int o = orientare(p0, *p1, *p2);
   if (o == 0)


     if(pow(((*p1).x-(*p2).x),2)+pow(((*p1).y-(*p2).y),2)>= pow((p0.x-(*p1).x),2)+pow((p0.y-(*p1).y),2))
        return -1;
     return 1;



   if (o == 2)
    return -1;
   return 1;
}

// functie pentru acoperirea convexa a n puncte
void acoperire_convexa(Point points[], int n, Point ac[], int &nr)
{
   // punctul cu y minim
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     // se alege punctul cu y minim sau cel mai din stanga, pentru egalitate
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   // punctul cu y minim se pune pe prima pozitie
   swap(points[0], points[min]);

   // se sorteaza punctele, cu exceptia primului
   // un punct p1 este situat inainte de p2 daca p2 are un unghi polar mai mare decat p2(counterclockwise)
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);


   //daca 2 sau mai multe puncte fac acelasi unghi cu p0, se sterg toate punctele mai putin cel mai indepartat de p0
   int m = 1;
      for (int i=1; i<n; i++)
   {

       while (i < n-1 && orientare(p0, points[i],
                                    points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;     }

   //daca sunt mai putin de 3 puncte, acoperirea convexa nu se poate realiza
   if (m < 3) return;

   // se creaza o stiva si se adauga primele 3 puncte
   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);


   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      //varful stivei este eliminat cat timp punctul din varf, al doilea punct si punctul i nu formeaza un viraj la stanga
      while (orientare(next_to_top(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   // stiva contine acoperirea convexa
   while (!S.empty())
   {
       Point p = S.top();
       ac[nr]=p;
       nr++;
       cout << "(" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}








void sortare(int n,Point v[])
{
    int k,i,j;
    do{
        k=0;
        for(i=0;i<n-1;i++)
            if(v[i].x>v[i+1].x||((v[i].x==v[i+1].x)&&(v[i].y>v[i+1].y)))
        {
            Point aux=v[i];
            v[i]=v[i+1];
            v[i+1]=aux;
            k=1;
        }
        }while(k==1);
}
int verif_lat(Point x1, Point x2, Point aux)
{
    float a,b,c;
    a = sqrt(pow((x1.x-x2.x),2)+pow((x1.y-x2.y),2));
    b = sqrt(pow((x1.x-aux.x),2)+pow((x1.y-aux.y),2));
    c = sqrt(pow((aux.x-x2.x),2)+pow((aux.y-x2.y),2));
    if(b+c == a)
        return 1;
    return 0;
}



// AVEM DE TRATAT 3 CAZURI!
/*
 1.Daca e in afara, acoperirea convexa se schimba
 2.1 Daca e pe vreo latura
 2.2 Daca e in interior
*/
int main()
{
    int n;
    cout<<"Numar varfuri poligon=";
    cin>>n;
    Point points[n],points1[n+1];
    for(int i=0; i<n; i++)
    {
        cout << "Varful " << i + 1 << endl;
        cout << "x=";
        cin >> points[i].x;
        cout << "y=";
        cin >> points[i].y;
        points1[i].x = points[i].x;
        points1[i].y = points[i].y;
        }

    cout << endl;
    cout << "Punct A\n";
    Point A;
    cout << "x=";
    cin >> A.x;
    cout << "y=";
    cin >> A.y;
    points1[n].x = A.x;
    points1[n].y = A.y;
    Point acoperire1[n];
    Point acoperire2[n+1];
    int nr_ac1 = 0, nr_ac2 = 0;
    acoperire_convexa(points1, n,acoperire1, nr_ac1);
    acoperire_convexa(points1, n+1,acoperire2, nr_ac2);

    Point aux[nr_ac2];

    for(int i=0;i<nr_ac1;i++)
        cout<<acoperire1[i].x<<' '<<acoperire1[i].y<<endl;
    cout<<endl;

        for(int i=0;i<nr_ac2;i++)
        cout<<acoperire2[i].x<<' '<<acoperire2[i].y<<endl;
    cout<<endl;

    for(int i=0; i<nr_ac2; i++)
       {
        aux[i].x = acoperire2[i].x;
        aux[i].y = acoperire2[i].y;
       }
    //sortam cele 2 acoperiri convexe crescator dupa x(y in caz de egalitate)
    sortare(nr_ac1,acoperire1);
    sortare(nr_ac2,acoperire2);
   // cout << pozitie_punct(acoperire1,acoperire2,nr_ac1,nr_ac2) << "\n";
    int ok = 0; Point aux1, aux2;
    if(pozitie_punct(acoperire1,acoperire2,nr_ac1,nr_ac2))
    //verific cazul in care este pe o latura
        {
            for(int i=0; i<n-1; i++)
            if(verif_lat(aux[i], aux[i+1], A) == 1)
                {
                    ok = 1;
                    aux1.x = aux[i].x;
                    aux1.y = aux[i].y;
                    aux2.x = aux[i+1].x;
                    aux2.y = aux[i+1].y;
                }
            if(verif_lat(aux[0],aux[n-1],A)==1)
            {
                 ok = 1;
                    aux1.x = aux[0].x;
                    aux1.y = aux[0].y;
                    aux2.x = aux[n-1].x;
                    aux2.y = aux[n-1].y;
            }

        if(ok == 1)
            cout<<"Varful se afla pe latura: "<<"x: "<<aux1.x<<" y: "<<aux1.y<<"\n"<<"x: "<<aux2.x<<" y: "<<aux2.y<<"\n";
        else
            cout<<"Varful este in interior";
        }

    return 0;
}
