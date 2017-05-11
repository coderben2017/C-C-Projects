#include <stdio.h>  
#include <string.h>  
  
//定义路由表结构RTable  
typedef struct node{  
    char dstNet[5];  
    int  distance;  
    char nextSkip[5];  
}RTable;  
  
RTable RT1[1000];//当前路由器路由表  
RTable RT2[1000];//相邻路由器的路由表  
RTable RT3[1000];  
  
int i,l1,l2,l3;  
char nearR1[5],nearR2[5];  
  
//基于当前路由器的路由表初始化函数  
void InitRTable( RTable* RT ){  
    printf("请为当前路由器添加路由表项(目的网络 距离 下一跳路由器)：\n");  
    for( i=0;i<1000;++i ){  
        scanf("%s%d%s",RT[i].dstNet,&RT[i].distance,RT[i].nextSkip);  
  
        if( RT[i].distance==0 ){  
            break;  
        }  
    }  
    l1 = i;//记录RT1[]的长度  
}  
  
//相邻路由器添加函数  
void AddNearRouter(){  
    printf("\n请输入第一个相邻路由器名称：\n");  
    scanf("%s",nearR1);  
    printf("请输入第二个相邻路由器名称：\n");  
    scanf("%s",nearR2);  
}  
  
//基于相邻路由器的路由表初始化函数  
void InitNearRTable(){  
    printf("\n请为相邻路由器%s添加路由表项(目的网络 距离 下一跳路由器)：\n",nearR1);  
    for( i=0;i<1000;++i ){  
        scanf("%s%d%s",RT2[i].dstNet,&RT2[i].distance,RT2[i].nextSkip);  
  
        if( RT2[i].distance==0 ){  
            break;  
        }  
    }  
    l2 = i;//记录RT2[]的长度  
  
    printf("\n请为相邻路由器%s添加路由表项(目的网络 距离 下一跳路由器)：\n",nearR2);  
    for( i=0;i<1000;++i ){  
        scanf("%s%d%s",RT3[i].dstNet,&RT3[i].distance,RT3[i].nextSkip);  
  
        if( RT3[i].distance==0 ){  
            break;  
        }  
    }  
    l3 = i;//记录RT3[]的长度  
}  
  
//路由表更新函数  
void UpdateRTable( RTable* RT1,RTable* RT2,char* nearR ){  
    int p,q;//p——RT2[]，q——RT1[]  
    for( p=0;p<l2;++p ){  
        int finded=0;  
        for( q=0;q<l1;++q ){  
            if( strcmp( RT2[p].dstNet,RT1[q].dstNet )==0 ){//当前表中找到与发来的表目的网络相同的一条路由信息  
                finded = 1;  
                if( strcmp( RT1[q].nextSkip,nearR )==0 ){//下一跳路由器正好是这个相邻路由器  
                    RT1[q].distance = RT2[p].distance + 1;  
                }  
                else{//下一跳路由器不是这个  
                    if( RT2[p].distance+1<RT1[q].distance ){  
                        RT1[q].distance = RT2[p].distance + 1;  
                        strcpy( RT1[q].nextSkip,nearR );  
                    }  
                }  
            }  
        }  
        if( !finded ){//当前表中没有这条路由信息，就加上  
            strcpy( RT1[l1].dstNet,RT2[p].dstNet );  
            RT1[l1].distance = RT2[p].distance + 1;  
            strcpy( RT1[l1].nextSkip,nearR );  
            ++l1;  
        }  
    }  
}  
  
void Print1(){  
    printf("\n----------当前路由器的路由表---------\n");  
}  
  
void Print2(){  
    printf("\n----------相邻路由器的路由表---------\n");  
}  
  
//路由表打印函数  
void PrintRTable( RTable* RT,int len ){  
    printf("    目的网络   距离   下一跳路由器\n");  
    for( i=0;i<len;++i ){  
        printf("      %s      %d          %s\n",RT[i].dstNet,RT[i].distance,RT[i].nextSkip);  
    }  
    printf("-------------------------------------\n");  
}  
  
//路由表更新函数  
void Choose_Update(){  
    printf("\n请选择一个传递更新信息的相邻路由器(1 or 2)：\n");  
    int choose;  
    scanf("%d",&choose);  
    if( choose==1 ){  
        UpdateRTable(RT1,RT2,nearR1);  
    }  
    else if( choose==2 ){  
        UpdateRTable(RT1,RT3,nearR2);  
    }  
  
    printf("\n-------当前路由器更新后的路由表------\n");  
    PrintRTable(RT1,l1);  
}  
  
  
int main()  
{  
    printf("\n-----------距离向量算法的过程模拟------------\n\n");  
  
    //初始化当前路由器  
    InitRTable(RT1);  
  
    //添加相邻路由器  
    AddNearRouter();  
  
    //初始化相邻路由器  
    InitNearRTable();  
  
    //打印当前路由表  
    Print1();  
    PrintRTable(RT1,l1);  
  
    //打印相邻路由表  
    Print2();  
    PrintRTable(RT2,l2);  
    Print2();  
    PrintRTable(RT3,l3);  
  
    //进行路由表更新  
    Choose_Update();  
}  
