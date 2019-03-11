#include <iostream>
#include <stdlib.h>

using namespace std;
class mul
{
private:
    int val;
    mul *next;

public:
    friend mul* crea(mul* ,int,int&,int&); // crearea multimi cu minimul maximul si citirea listei
    friend void cop (mul* ,mul *,int&); // copiere
    friend void aran(mul*,int); // aranjare crescatorea
    friend void elimcop(mul*,int&); // eliminarea dublurilor
    friend void afis(mul*); //afisaj
    friend mul* elimdub(mul*,int&);
    friend mul* combinliste(mul*,mul*,int,int);
    friend mul* intersect(mul*,int&);
    //~mul()
    //{
    //delete a;
    //}
};
mul* elimdub(mul *a,int &n)
{
    mul *d=new mul,*pre,*l;
    l=d;
    int j=0;
    if(a->next!=NULL)
        for(int i=0; i<n; i++)
        {
            if(i==0)
            {
                if(a->val!=a->next->val)
                {
                    d->val=a->val;
                    d->next=NULL;
                    j++;
                }
            }
            else
            {
                if(a->next!=NULL)
                    if(a->val!=a->next->val && j==0 && pre->val!=a->val)
                    {
                        d->val=a->val;
                        d->next=NULL;
                        j++;
                    }
                if(a->next!=NULL)
                    if(a->val!=a->next->val && j>0 && pre->val!=a->val)
                    {
                        mul *q=new mul;
                        q->val=a->val;
                        q->next=NULL;
                        d->next=q;
                        d=q;
                    }
                if(pre->val != a->val && a->next==NULL && j==0)
                    {d->val=a->val;
                        d->next=NULL;
                    }
                if(pre->val != a->val && a->next==NULL && j>0)
                {mul *q=new mul;
                        q->val=a->val;
                        q->next=NULL;
                        d->next=q;
                        d=q;
                }

            }
            pre=a;
            a=a->next;

        }
    d=l;
    return d;
}

class multime
{
private:
    mul *c;
    int mi,ma,n;
public:
    friend ostream& operator<< (ostream&, multime&);
    friend istream& operator>> (istream&, multime&);
    friend multime operator + (multime&,multime&);
    friend multime operator - (multime&,multime&);
    friend multime operator * (multime&,multime&);
    friend multime operator > (multime&,multime&);
    //~multime();
};
multime operator >(multime &a,multime &b)
{
    cop(a.c,b.c,a.n);
    return b;
}
mul* combinliste(mul *a,mul *b,int n,int m) // combin 2 liste pentru operatia de reuniune
{
    mul *c=new mul;
    if(a!=NULL)
    {
        mul *e,*g,*h;
        g=a;
        h=b;
        e=c;
        c->val=a->val;
        c->next=NULL;
        if(a->next!=NULL)
            a=a->next;
        for(int i=2; i<=n; i++)
        {
            mul *r=new mul;
            r->val=a->val;
            r->next=NULL;
            c->next=r;
            a=a->next;
            c=r;
        }
        if(b!=NULL)
            for(int i=1; i<=m; i++)
            {
                mul *r=new mul;
                r->val=b->val;
                r->next=NULL;
                c->next=r;
                b=b->next;
                c=r;
            }
        //if()
        c=e;
        b=h;
        a=g;
    }
    return c;
}

multime operator +(multime &a,multime &b) // operatorul de reuniune
{
    multime e;
    e.c=new mul;
    e.n=a.n+b.n;
    e.c=combinliste(a.c,b.c,a.n,b.n);
    aran(e.c,e.n);
    elimcop(e.c,e.n);
    if(a.mi<b.mi)
        e.mi=a.mi;
    else e.mi=b.mi;
    if(a.ma>b.ma)
        e.ma=a.ma;
    else e.ma=b.ma;
    return e;

}
mul* intersect(mul *a,int &n) // intersectia a unei liste combinate
{
    int j=0,q=0;
    mul *ne,*pre,*p=new mul,*o;
    pre=a;
    o=p;
    if(a->next!=NULL)
        a=a->next;
    if(a->next!=NULL)
        ne=a->next;
    else ne=a;
    while(1)
    {
        if(a->val==pre->val && j==0)
        {
            q++;
            p->val=a->val;
            p->next=NULL;
            delete a;
            pre->next=ne;
            a=pre;
            j++;
        }
        else if(a->val==pre->val && j>0)
        {
            q++;
            mul *l=new mul;
            l->val=a->val;
            l->next=NULL;
            p->next=l;
            p=l;
            delete a;
            pre->next=ne;
            a=pre;
            j++;
        }
        else pre=pre->next;


        if(a->next!=NULL)
        {
            a=a->next;
            if(a->next!=NULL)
                ne=a->next;
            else
            {
                if(a->val==pre->val && j==0)
                {
                    p->val=a->val;
                    p->next=NULL;
                    delete a;
                    q++;
                    pre->next=NULL;
                    a=pre;
                }
                else if(a->val==pre->val && j>0)
                {
                    mul *l=new mul;
                    l->val=a->val;
                    l->next=NULL;
                    p->next=l;
                    p=l;
                    q++;
                    delete a;
                    pre->next=NULL;
                    a=pre;
                }
            }
        }
        if(a->next==NULL)
        {
            break;
        }
    }
    n=q;
    p=o;
    return p;
}
multime operator *(multime &a,multime &b) // intersectia a doua multimi
{
    multime e;
    e.n=a.n+b.n;
    e.c=combinliste(a.c,b.c,a.n,b.n);
    aran(e.c,e.n);
    e.c=intersect(e.c,e.n);
    if(a.mi<b.mi)
        e.mi=a.mi;
    else e.mi=b.mi;
    if(a.ma>b.ma)
        e.ma=a.ma;
    else e.ma=b.ma;
    return e;
}
multime operator -(multime &a,multime &b) // diferenta a doua multimi
{
    multime l,k;
    int i;
    i=a.n+b.n;
    k.c=combinliste(a.c,b.c,a.n,b.n);
    aran(k.c,i);
    k.c=intersect(k.c,i);
    k.c=combinliste(a.c,k.c,a.n,i);
    k.n=a.n+i;
    aran(k.c,k.n);
    k.c=elimdub(k.c,k.n);
    if(a.mi<b.mi)
        k.mi=a.mi;
    else k.mi=b.mi;
    if(a.ma>b.ma)
        k.ma=a.ma;
    else k.ma=b.ma;

    return k;




}
void cop(mul *a,mul *b,int &n) // copierea unei liste a in b
{
    mul *d;
    d=b;;
    if (n==0)
        a=NULL;
    else
    {
        b->val=a->val;
        b->next=NULL;
        a=a->next;

        while(a!=NULL)
        {
            mul *g= new mul;
            g->val=a->val;
            g->next=NULL;
            b->next=g;
            b=g;
            a=a->next;
        }
        b=d;
    }

}

void afis(mul *a)// afisarea unei liste
{
    mul *d;
    d=a;
    while(d!=NULL)
    {
        if(d==NULL)
            break;
        if(d->next==NULL)
        {
            cout<<d->val<<" ";
            d=d->next;
            break;
        }
        cout<<d->val<<" ";
        d=d->next;
    }
}
void elimcop(mul *a,int &n)// eliminarea dublurilor
{
    mul *ne,*pre,*o;
    o=a;
    pre=a;
    if(a->next!=NULL)
        a=a->next;
    if(a->next!=NULL)ne=a->next;
    else ne=a;
    while(1)
    {
        if(a->val==pre->val)
        {
            n--;
            delete a;
            pre->next=ne;
            a=pre;
        }
        else pre=pre->next;


        if(a->next!=NULL)
        {
            a=a->next;
            if(a->next!=NULL)
                ne=a->next;
            else
            {
                if(a->val==pre->val)
                {
                    n--;
                    delete a;
                    pre->next=NULL;
                    a=pre;
                }
            }
        }
        if(a->next==NULL)
        {
            break;
        }
    }
    a=o;
}
void aran(mul *a,int n) // sortarea crescatoare a listei
{
    mul *c,*d,*o;
    d=a;
    o=a;
    if(a->next!=NULL)
        c=a->next;
    else c=a;
    int i,j;
    for(i=0; i<n; i++)
    {

        for(j=i+1; j<n; j++)
        {
            if(d->val>c->val)
                d=c;
            if(a->next!=NULL)c=c->next;

        }
        if(d->val<a->val)
        {
            int f;
            f=d->val;
            d->val=a->val;
            a->val=f;
        }
        if(i==n-2)
        {
            if(a->val>a->next->val)
            {
                int k=0;
                k=a->val;
                a->val=a->next->val;
                a->next->val=k;
            }
        }
        if(a!=NULL)c=a->next;
        else c=a;
        if(a->next!=NULL)a=a->next;
        d=a;
    }
    a=o;

}
mul* crea(mul *a,int n,int &e, int &r) // crearea listei
{
    mul *c= new mul;
    c=a;
    if (n==0)
        a=NULL;
    else if(n==1)
    {
        int d;
        cin>>d;
        a->val=d;
        e=r=d;
        a->next=NULL;
    }
    else

    {
        int d;
        cin>>d;
        a->val=d;
        e=r=d;
        a->next=NULL;
        for(int i=1; i<n; i++)
        {
            mul *g= new mul;
            cin>>g->val;
            if(g->val<e)
                e=g->val;
            if(g->val>r)
                r=g->val;
            g->next=NULL;
            a->next=g;
            a=g;
        }
    }
    a=c;
    return a;

}

ostream& operator<<(ostream &out, multime &a) // operatorul de afisare
{
    cout<<"Multimea este["<<a.mi<<","<<a.ma<<"]"<<endl;
    afis(a.c);
    return out;
}
istream& operator>>(istream &in, multime &a) // operatorul de citire
{
    int n;
    cout<<"Cate elemente are vectorul"<<endl;
    cin>>n;
    a.n=n;
    a.c=new mul;
    crea(a.c,n,a.mi,a.ma);
    return in;
}

int main()
{

    int n;
    cout<<"Numar de multimi";
    cin>>n;
    multime a[n];
    int op;
    if(n!=0)
        while(1)
        {
            cout<<endl;
            cout<<"Optiune"<<endl;
            cout<<"1-Citire/Afisare"<<endl;
            cout<<"2-Reuniunea celor doua multimi"<<endl;
            cout<<"3-Diferenta intre doua multimi"<<endl;
            cout<<"4-Intersectia a doua multimi"<<endl;
            cout<<"-Copierea multimi"<<endl;
            cin>>op;
            if(op<1 || op >6)break;
            switch(op)
            {
            case 1:
            {
                int j=0;
                int aux=n,r[n];
                int d=0;
                for(int i=0; i<n; i++)
                {
                    cout<<"Multimea "<<i<<endl;
                    cin>>a[i];
                }
                if(n!=0)
                {
                    cout<<"2-Afisez?";
                    int opd;

                    cin>>opd;
                    if(opd==2)
                        while(1)
                        {
                            cout<<"Care Multime";
                            int e;
                            cin>>e;
                            e--;
                            if(e<n && e>=0)
                                cout<<a[e];
                            cout<<endl;
                            cout<<"1-Continui?//Daca nu, 0";
                            cout<<endl;
                            cin>>e;
                            if(e==0)
                                break;
                        }
                }
                break;

            }
            case 2:
            {
                cout<<"Cele doua multime care vor fi reunite "<<endl;
                cout<<"Primul"<<endl; // in ordinea citire cum ar fi de exemplu prima multime este notata in vector 0 dar la citire se de 1 deoarece este prima multime
                int j;
                cin>>j;
                j--;
                cout<<"Al doilea"<<endl;
                int d;
                cin>>d;
                d--;
                multime p;
                p=a[j]+a[d];
                cout<<p;
                break;
            }
            case 3:
            {
                cout<<"Cele doua multimi care vor fi diferentiate "<<endl;
                cout<<"Primul"<<endl;
                int j;
                cin>>j;
                j--;
                cout<<"Al doilea"<<endl;
                int d;
                cin>>d;
                d--;
                multime p;
                p=a[j]-a[d];
                cout<<p;
                break;
            }
            /*case 5:
            {
                cout<<"Multime din care copiez in care "<<endl;
                cout<<"Primul"<<endl;
                int j;
                cin>>j;
                j--;
                cout<<"Al doilea"<<endl;
                int d;
                cin>>d;
                d--;
                //a[d].c=a[j].c;
                cout<<"Multimea nou"<<a[j]<<endl;
                break;
            }
            */
            case 4:
            {
                cout<<"Cele doua multimi care vor fi intersectate "<<endl;
                cout<<"Primul"<<endl;
                int j;
                cin>>j;
                j--;
                cout<<"Al doilea"<<endl;
                int d;
                cin>>d;
                d--;
                multime p;
                p=a[j]*a[d];
                cout<<p;
                break;
            }

            }

        }
    else cout<<"Nu se poate";
    return 0;
}
