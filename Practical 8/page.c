#include<stdio.h>   
# define maxn 50  
 typedef struct  page  
 {  
   int frame ;  
   int count[maxn],curr[maxn] ;  
 }page ;  
 struct page p ;  
 void fifo(int pages,int page[]) ;  
 void lru(int pages ,int page[]) ;  
 void optimal(int pages,int page[]) ;  
 void main()  
 {  
  int ch=0,pages=0,i,j,page[maxn],frames=0,temp3,temp4 ;  
  char temp ;   
  do  
  {  
    printf("\n\t------------Menu------------\n") ;  
    printf("\t1.Enter Page Information\n");  
    printf("\t2.Dispaly Page Info\n");  
    printf("\t3.FIFO\n" );  
    printf("\t4.LRU\n") ;  
    printf("\t5.OPTIMAL\n") ;  
    printf("\t6.Exit\n\t----------------------------\n");  
    printf("\tEnter your choice: ");  
    scanf("%d",&ch);  
   switch (ch)  
   {  
    case 1:  
      printf("\n\tEnter No. of Pages: ");  
      scanf("%d",&pages) ;  
      printf("\tEnter page info\n");
      for(i=0;i<pages;i++)        {  
       printf("\t  Page %d: ",i);  
       scanf("%d",&page[i]) ;  
      }  
      printf("\tEnter No. of frames: ");  
      scanf("%d",&p.frame) ;  
      break ;  
    case 2:  
      printf("\n\tNo. of pages: %d\n",pages);  
       printf("\tPage sequence: ");  
       for(i=0;i<pages;i++) {  
       printf("%d ",page[i]);  
       }  
       printf("\n\tNo. of frames: %d\n",p.frame);  
      break ;  
    case 3:  
       fifo(pages,page) ;  
       break ;  
    case 4:  
       lru(pages ,page);  
      break ;  
    case 5:  
        optimal(pages ,page);  
      break ;  
    case 6:  
      break ;  
   }  
 }while(ch!=6 );  
 }  
 void fifo(int pages,int page[])  
 {  
  int i,j,k,flag=0,temp=0,fault=0; 
  printf("\n"); 
  for(i=0;i<p.frame;i++)  
  {  
     p.curr[i]=-1 ;  
     p.count[i]=100 ;  
     printf("\tPage-%d",i+1) ;  
  }  
  printf("\t------Fault------\n");  
  for(i=0;i<pages;i++)    {  
     flag=0 ;  
     temp=0 ;  
     for(j=0;j<p.frame;j++)
     {  
           if(p.curr[j]==page[i])  
           {  
             flag=1 ;  
             break ;  
           }  
           if(temp<p.count[j])  
           {  
               temp=p.count[j] ;  
               k=j ;  
           }  
     }  
     for(j=0;j<p.frame;j++)  

     {  
         if(flag==0 && k==j)  
         {  
           p.curr[j]=page[i] ;  
           p.count[j]=1 ;  
           fault++ ;  
         }  
         else  
         if(j<fault)           p.count[j]++;  
         if(p.curr[j]!=-1)  
         printf("\t%d",p.curr[j]) ;  
     }  
     if(flag==0)  
     printf("\t\t\t*") ;  
     printf("\n") ;  
  }  
  printf("\t-----------------------------------------\n\tNo. of Page Fault: %d\n",fault);  
 }  
 void lru(int pages ,int page[])  
 {  
  int i,j,k,flag=0,temp=0,fault=0;
  printf("\n");   
  for(i=0;i<p.frame;i++)  
  {  
     p.curr[i]=-1 ;  
     p.count[i]=100 ;  
     printf("\tPage%d",i+1) ;  
  }  
  printf("\t------Fault------\n");  
  for(i=0;i<pages;i++)    {  
     flag=0 ;  
     temp=0 ;  
     for(j=0;j<p.frame;j++)  
     {  
           if(p.curr[j]==page[i])  
           {  
             flag=1 ;  
             p.count[j]=0 ;  
             break ;  
           }  
           if(temp<p.count[j])  

           {  
               temp=p.count[j] ;  
               k=j ;  
           }  
     }  
     for(j=0;j<p.frame;j++)
     {  
         if(flag==0 && k==j)  
         {  
           p.curr[j]=page[i] ;  
           p.count[j]=1 ;  
           fault++ ;  
         }  
         else  
         if(j<fault)           p.count[j]++;  
         if(p.curr[j]!=-1)  
         printf("\t%d",p.curr[j]) ;  
     }  
     if(flag==0)  
     printf("\t\t\t*") ;  
     printf("\n") ;  
  }  
  printf("\t-----------------------------------------\n\tNo. of Page Fault: %d\n",fault); 
 }  
 void optimal(int pages,int page[])  
 {  
  int i,j,k,flag=0,temp=0,fault=0,s;
  printf("\n");   
  for(i=0;i<p.frame;i++)  

  {  
     p.curr[i]=-1 ;  
     p.count[i]=100 ;  
     printf("\tPage%d",i+1) ;  
  }  
  printf("\t------Fault------\n");  
  for(i=0;i<pages;i++)    {  
     flag=0 ;  
     temp=0 ;  
     for(j=0;j<p.frame;j++)  

     {  
           if(p.curr[j]==page[i])  
           {  
             flag=1 ;  
             p.count[j]=0 ;  
             break ;  
           }  
           if(temp<p.count[j])  

           {  
               temp=p.count[j] ;  
               k=j ;  
           }  
     }  
     for(j=0;j<p.frame;j++)  

     {  
         if(flag==0 && k==j)  
         {  
           p.curr[j]=page[i] ;  
           p.count[j]=0 ;  
           fault++ ;  
         }  
         else  
         if(j<fault)           {  
           p.count[j]=0 ;  
           for(s=i+1;s<pages;s++)             {  
             if(page[i]==p.curr[j])  
             break ;  
             else  
             p.count[j]++ ;  
           }  
         }  
         p.count[j]++;  
         if(p.curr[j]!=-1)  
         printf("\t%d",p.curr[j]) ;  
     }  
     if(flag==0)  
     printf("\t\t\t*") ;  
     printf("\n") ;  
  }  
  printf("\t-----------------------------------------\n\tNo. of Page Fault: %d\n",fault);
 }


