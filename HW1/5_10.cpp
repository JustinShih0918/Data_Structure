#include<iostream>
#include<string.h>
//using namespace std;

char map[105][1005];
int c[105];
char bag[10005], inv[10005];
int r, l, n, bn=0, in=0;

void ftop(int x, int y)
{
    while(map[x][y]<'A' || map[x][y]>'Z') --y;
    //printf("#%d %d\n",x,y);
    c[x] = y;
}
void dig(int x)
{
    if(map[x][c[x]] == 'D' || map[x][c[x]] == 'G')
    {
        bag[bn++] = map[x][c[x]];
        map[x][c[x]] = '_';
        ftop(x, c[x]);
    }
    else if(map[x][c[x]] == 'F' || map[x][c[x]] == 'M')
    {
        inv[in++] = map[x][c[x]];
        map[x][c[x]] = '_';
        ftop(x, c[x]);
    }
    else if(map[x][c[x]] == 'B')
    {
        int y = c[x];
        for(int i=-1; i<2; ++i)
        {
            if(x+i<0 || x+i>=r) continue;
            for(int j=-1; j<2; ++j)
            {
                if(y+j<0) continue;
                map[x+i][y+j] = '_';
                //printf("#%d %d\n",i,j);
            }
            ftop(x+i,c[x+i]); 
        }         
    }
    else if(map[x][c[x]] == 'C')
    {
        int y = 0;
        map[x][c[x]--] = '_';
        for(int i=-2; i<3; ++i)
        {
            if(x+i<0 || x+i>=r) continue;
            y = y>c[x+i] ?y :c[x+i];
        }
        for(int i=-2; i<3; ++i)
        {
            if(x+i<0 || x+i>=r) continue;
            for(int j=1; j<4; ++j)
                map[x+i][y+j] = bag[bn-1];
            c[x+i] = y+3;
        }
    }
    else if(map[x][c[x]] == 'P')
    {
        map[x][c[x]] = '_';
        while(bag[bn-1] == 'G') --bn;
        ftop(x,c[x]);
    }
}

int main()
{
    //std::ios_base::sync_with_stdio(0);std::cin.tie(0); 
    std::cin >> r >> l >> n;
    for(int i=l-1; i>=0; --i)
        for(int j=0; j<r; ++j)
            std::cin >> map[j][i];
    for(int i=0; i<r; ++i)
        ftop(i, l-1);
    while(n--)
    {
        std::string s;
        std::cin >> s;
        if(s == "DIG")
        {
            int x;
            std::cin >> x;
            dig(x);
        }
        else if(s == "USE")
        {
            if(inv[in-1] == 'F')
            {
                --in;   
                int top = 0;
                for(int i=0; i<r; ++i)
                    top = top>c[i] ?top :c[i];
                std::cout << "MINE LEVEL:" << top+1 << "\n";
                for(int i=0; i<r; ++i)
                {
                    if(map[i][top]>='A' && map[i][top]<='Z')
                        std::cout << map[i][top] << " ";
                    else
                        std::cout << "_ ";
                }
                std::cout << "\n";
            }
            else if(inv[in-1] == 'M')
            {
                --in;
                for(int i=0; i<r; ++i) dig(i);
            }
            
        }     
    }
    std::cout << "FINAL BAG:\n";
    for(int i=0; i<bn; ++i) std:: cout << bag[i] << " ";
    std::cout << "\n";
    std::cout << "FINAL MAP:\n";
    int tmp = 0;
    for(int i=0; i<r; ++i)
        tmp = tmp>c[i] ?tmp :c[i];
    for(int i=tmp; i>=0; --i)
    {
        for(int j=0; j<r; ++j)
            if(map[j][i]>='A' && map[j][i]<='Z')
                std::cout << map[j][i] << " ";
            else
                std::cout << "_ ";
        std::cout << "\n";
    }   
    return 0;
}