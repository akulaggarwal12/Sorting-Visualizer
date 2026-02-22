#include <iostream>
#include "raylib.h"
#include <time.h>
#include <algorithm>
using namespace std;

//Global Variables
int num_fireball=0;
int x=0;
int y=0;
int X=0;
int N=0;
bool flagpoint=true;
bool Gamestate=true;


//Soldiers Structure
struct Soldier
{
    int height;
    int hp;
    bool alive;
};


//Soldier Swapping
void swap(Soldier &a,Soldier &b)
{
    Soldier temp=a;
    a=b;
    b=temp;
}


//Fierball Structure
struct Fireball
{
    Vector2 pos;
    float speed;
    bool active;
};


//Soldier Stats
void SoldierStats(Soldier army[],int size)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        army[i].height=GetRandomValue(10,100);
        army[i].hp=army[i].height;
        army[i].alive=true;
    }
    
    //Frontline Stats
    N=size-1;
    X=100+30*size;
}

//Sorted Array
void cpyarray(Soldier army[], int arr[], int size)
{
    for(int i=0;i<size;i++)
    arr[i]=army[i].height;
    
    //Bubble Sorting
    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int k=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=k;
            }
        }
    }
}

//Number of Fireballs
void Num_Fireball(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        if(arr[i]%10==0)
        num_fireball+=arr[i]/10;
        else
        num_fireball+=arr[i]/10+1;
    }
}


//Fireball Stats
void FireballStats(Fireball wave[],int arr[],int size)
{
    int k=0;
    for(int i=size-1;i>=0;i--)
    {
        if(arr[i]%10==0)
        {
            for(int j=k;j<k+arr[i]/10;j++)
            {
                wave[j].pos={(float)1000+j*20,(float)GetRandomValue(500-4*arr[i],460)};
                wave[j].active=true;
                wave[j].speed=2.0f;
            }
            
            //Dynamic Fireball
            wave[k].pos.y=500-4*arr[i];
            k+=arr[i]/10;
        }
        else
        {
            for(int j=k;j<k+arr[i]/10+1;j++)
            {
                wave[j].pos={(float)1000+j*20,(float)GetRandomValue(500-4*arr[i],460)};
                wave[j].active=true;
                wave[j].speed=2.0f;
            }
            
            //Dynamic Fireball
            wave[k].pos.y=500-4*arr[i];
            k+=arr[i]/10+1;
        }
    }
}

//Bubblesort Graphics
void BubbleSort(Soldier army[],Fireball wave[],int size)
{
    InitWindow(1000,600,"Game");
    SetTargetFPS(60);
    static int i=0;
    static int j=0;
    static float font_size=0.0f;
    static int fontx=0;
    while(!WindowShouldClose())
    {
        //Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            //Army Bars
            for(int k=0;k<size;k++)
            {
                x=100+k*30;
                y=500-army[k].height*4;
                if(army[k].alive)
                {
                    if(k==j || k==j+1)
                    DrawRectangle(x,y,25,army[k].height*4,BLUE);
                    else
                    DrawRectangle(x,y,25,army[k].height*4,GREEN);
                    DrawText(TextFormat("%d",army[k].hp),x+5,y-15,10,RED);
                }
                else
                DrawText("DEAD",x,480,10,RED);
            }
            
            //Fireballs
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                DrawCircleV(wave[k].pos,5,RED);
            }
            
            //General
            DrawLine(90,500,110+30*size,500,BLACK);
            
            
            //Game Over Text
            if(!Gamestate)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("GAME OVER",(int)font_size);
                DrawText("GAME OVER",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
            
            //Victory Text
            if(N<0)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("VICTORY",(int)font_size);
                DrawText("VICTORY",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
        EndDrawing();
        
        
        if(Gamestate)
        {
            //Fireball Update
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                {
                    wave[k].pos.x-=wave[k].speed;
                    if(wave[k].pos.x<-50)
                    wave[k].active=false;
                    
                    //Collision
                    if(wave[k].pos.x==X)
                    {
                        wave[k].active=false;
                        if(army[N].hp>=10)
                        army[N].hp-=10;
                        else
                        army[N].hp=0;
                        
                        //Dead Soldier
                        if(army[N].hp==0)
                        {
                            army[N].alive=false;
                            
                            //Frontline Update
                            X-=30;
                            --N;
                        }
                        
                        //Fireball Misses
                        if(500-4*army[N].height>wave[k].pos.y && wave[k].pos.x==X)
                        {
                            Gamestate=false;
                            wave[k].active=true;
                        }
                    }
                }
            }

        
            //Space-Sorting
            if(flagpoint && IsKeyPressed(KEY_SPACE))
            {
                cout << "Space Pressed, j is: " << j << endl;
                if(army[j].height>army[j+1].height)
                {
                    swap(army[j].height,army[j+1].height);
                    army[j].hp=army[j].height;
                    army[j+1].hp=army[j+1].height;
                }
                j++; 
                
                //Resetting Sorting
                if(j>=size-1-i)
                {
                    j=0;
                    i++;
                }
                if(i>size-1)
                flagpoint=false;
            }
        }
    }
    CloseWindow();
}


//Cocktail Sort Graphics
void CocktailSort(Soldier army[],Fireball wave[],int size)
{
    InitWindow(1000,600,"Game");
    SetTargetFPS(60);
    static int start=0;
    static int end=size-1;
    static int current=0;
    static bool Forward=true;
    static float font_size=0.0f;
    static int fontx=0;
    while(!WindowShouldClose())
    {
        //Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            //Army Bars
            for(int k=0;k<size;k++)
            {
                x=100+k*30;
                y=500-army[k].height*4;
                if(army[k].alive)
                {
                    if(Forward && (k==current || k==current+1))
                    DrawRectangle(x,y,25,army[k].height*4,BLUE);
                    else if(!Forward && (k==current || k==current-1))
                    DrawRectangle(x,y,25,army[k].height*4,YELLOW);
                    else
                    DrawRectangle(x,y,25,army[k].height*4,GREEN);
                    DrawText(TextFormat("%d",army[k].hp),x+5,y-15,10,RED);
                }
                else
                DrawText("DEAD",x,480,10,RED);
            }
            
            //Fireballs
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                DrawCircleV(wave[k].pos,5,RED);
            }
            
            //General
            DrawLine(90,500,110+30*size,500,BLACK);
            
            
            //Game Over Text
            if(!Gamestate)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("GAME OVER",(int)font_size);
                DrawText("GAME OVER",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
            
            //Victory Text
            if(N<0)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("VICTORY",(int)font_size);
                DrawText("VICTORY",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
        EndDrawing();
        
        
        if(Gamestate)
        {
            //Fireball Update
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                {
                    wave[k].pos.x-=wave[k].speed;
                    if(wave[k].pos.x<-50)
                    wave[k].active=false;
                    
                    //Collision
                    if(wave[k].pos.x==X)
                    {
                        wave[k].active=false;
                        if(army[N].hp>=10)
                        army[N].hp-=10;
                        else
                        army[N].hp=0;
                        
                        //Dead Soldier
                        if(army[N].hp==0)
                        {
                            army[N].alive=false;
                            
                            //Frontline Update
                            X-=30;
                            --N;
                        }
                        
                        //Fireball Misses
                        if(500-4*army[N].height>wave[k].pos.y && wave[k].pos.x==X)
                        {
                            Gamestate=false;
                            wave[k].active=true;
                        }
                    }
                }
            }
            
        
            if(flagpoint && IsKeyPressed(KEY_SPACE))
            {
                if(start<end)
                {
                    
                    //Forward Pass
                    if(Forward)
                    {
                        if(army[current].height>army[current+1].height)
                        swap(army[current],army[current+1]);
                        current++;

                        //End Check
                        if(current>=end)
                        {
                            end--;
                            Forward=false;
                            current=end;
                        }
                    }
                    else
                    {
                        
                        //Backward Pass
                        if(army[current].height<army[current-1].height)
                        swap(army[current],army[current-1]);
                        current--;
                        
                        //Start Check
                        if(current<=start)
                        {
                            start++;
                            Forward=true;
                            current=start;
                        }
                    }
                }
                else
                flagpoint = false;
            }
        }
    }
    CloseWindow();
}


//Selection Sort Graphics
void SelectionSort(Soldier army[],Fireball wave[],int size)
{
    InitWindow(1000,600,"Game");
    SetTargetFPS(60);
    static int start=size-1;
    static int read=size-1;
    static int max=size-1;
    static float font_size=0.0f;
    static int fontx=0;
    while(!WindowShouldClose())
    {
        //Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            //Army Bars
            for(int k=0;k<size;k++)
            {
                x=100+k*30;
                y=500-army[k].height*4;
                if(army[k].alive)
                {
                    if(k==max)
                    DrawRectangle(x,y,25,army[k].height*4,BLUE);
                    else if(k==read)
                    DrawRectangle(x,y,25,army[k].height*4,YELLOW);
                    else
                    DrawRectangle(x,y,25,army[k].height*4,GREEN);
                    DrawText(TextFormat("%d",army[k].hp),x+5,y-15,10,RED);
                }
                else
                DrawText("DEAD",x,480,10,RED);
            }
            
            //Fireballs
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                DrawCircleV(wave[k].pos,5,RED);
            }
            
            //General
            DrawLine(90,500,110+30*size,500,BLACK);
            
            
            //Game Over Text
            if(!Gamestate)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("GAME OVER",(int)font_size);
                DrawText("GAME OVER",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
            
            //Victory Text
            if(N<0)
            {
                if(font_size<100.0f)
                font_size+=2.0f;
                fontx=MeasureText("VICTORY",(int)font_size);
                DrawText("VICTORY",500-fontx/2,300-(int)font_size/2,(int)font_size,BLACK);
            }
        EndDrawing();
        
        
        if(Gamestate)
        {
            //Fireball Update
            for(int k=0;k<num_fireball;k++)
            {
                if(wave[k].active)
                {
                    wave[k].pos.x-=wave[k].speed;
                    if(wave[k].pos.x<-50)
                    wave[k].active=false;
                    
                    //Collision
                    if(wave[k].pos.x==X)
                    {
                        wave[k].active=false;
                        if(army[N].hp>=10)
                        army[N].hp-=10;
                        else
                        army[N].hp=0;
                        
                        //Dead Soldier
                        if(army[N].hp==0)
                        {
                            army[N].alive=false;
                            
                            //Frontline Update
                            X-=30;
                            --N;
                        }
                        
                        //Fireball Misses
                        if(500-4*army[N].height>wave[k].pos.y && wave[k].pos.x==X)
                        {
                            Gamestate=false;
                            wave[k].active=true;
                        }
                    }
                }
            }
            
            
            //Selection Sorting
            if(flagpoint && IsKeyPressed(KEY_SPACE))
            {
                if(start>=0)
                {
                
                    //Selecting the bar
                    if(army[max].height<army[read].height)
                    max=read;
                    read--;
                    
                    //End Check
                    if(read<0)
                    {
                        if(max!=start)
                        swap(army[start],army[max]);
                        start--;
                        read=start-1;
                        max=start;
                    }
                }
                else
                flagpoint = false;
            }
        }
    }
    CloseWindow();
}


//Main 
int main()
{
    SetRandomSeed(time(NULL));
    int n,ch;
    cout << "Enter the size of the array: ";
    cin >> n;
    
    //Soldiers
    Soldier* army=new Soldier[n];
    SoldierStats(army,n);
    
    //Sorted Array
    int a[n];
    cpyarray(army,a,n);
    
    
    //Number of Fireball
    Num_Fireball(a,n);
    
    
    //Fireballs
    Fireball* wave=new Fireball[num_fireball];
    FireballStats(wave,a,n);
    
    cout << "Input value of the Sort\n1- Bubblesort: \n2- Cocktailsort: \n3- Selectionsort (Reversed): \n";
    cin >> ch;
    
    //Sorting Choice
    switch(ch)
    {
        case 1:
            BubbleSort(army,wave,n);
            break;
        case 2:
            CocktailSort(army,wave,n);
            break;
        case 3:
            SelectionSort(army,wave,n);
            break;
        default:
            cout << "Invalid Input, Enter 1, 2 or 3 only";
    }
    
    
    //Cleaning memory
    delete[] army;
    delete[] wave;
    return 0;
}
