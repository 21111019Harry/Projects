////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///////  This Program contain generic code for all typs of linked list as
///////  1.Singly Linear Linked List
///////  2.Singly Circular Linked List
///////  3.Doubly Linear Linked List 
///////  4.Doubly Circule Linked List
///////  5.Genric Queue
///////  6.Genric stack
///////
/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//########  SINGLY LINEAR LINKED LIST IN TEMPLATE   #####################///
//####  This is class designed for Singly linear linked list  ##########///		
//#############    BY NIKAM HARSHAL   #####################################///
///////////////////////////////////////////////////////////////////////
#include<iostream>
using namespace std;

#define TRUE 1
#define FALSE 0

///Genric structure for SLLL node

template<class T>
struct node
{
	T            Data;
	struct node* Next;
};

///Genric structure for Queue node

template<class T>
struct qnode
{
	int             P;
	T               data;
	struct qnode*   next;
};

///Genric structure for Stack node

template<class T>
struct snode
{
	T              data;
	struct  snode *next;
};

///Genric structure for DLLL node 

template<class T>
struct dnode
{
	T 	     Data;
	struct dnode* Next;
	struct dnode* Prev;
};

 //Abstract Class of Linked_List
template <class T>
 class Linked_List
 {
 protected:
     virtual void InsertFirst(T) = 0;
     virtual void InsertLast(T) = 0;
     virtual void InsertAtPos(T, int) = 0;
     virtual void Display() = 0;
     virtual int Count() = 0;
     virtual void DeleteFirst() = 0;
     virtual void DeleteLast() = 0;
     virtual void DeleteAtPos(int) = 0;
 };

////////////////////////////////////////////////////////////////////////
///////////////##################################////////////////////////
//#############    CLASS NAME:-  GEN_SLLL   ##############################///
//##########   This class represents singly linear linked list  ##########///
/////////////###################################################///////////////
//////////////////////////////////////////////////////////////////////////////
template<class T>
class GEN_SLLL
{
private:

	struct node<T>*	Head;	//pointing at start of linked list	
	struct node<T>* Tail;	//pointing at end of linked list	
	int size;

public:	
    GEN_SLLL();
	~GEN_SLLL();
    void InsertFirst(T);
	void InsertLast(T);
	void InsertAtPos(T,int);
	inline void Display();
	inline void DisplayR();
	inline int Count();
	void DeleteFirst();
	void DeleteLast();
	void DeleteAtPos(int);
	int Frequency(T);
	int FirstOccurance(T);
	int LastOccurance(T);
	int Summation();
	T Largest();
	T Smallest();
	void ReverseList();
	void Concat(GEN_SLLL<T> &op1,GEN_SLLL<T> &op2);


     template <class X>
     friend bool operator==(GEN_SLLL<X> &op1, GEN_SLLL<X> &op2); //Compares Linked List For Equality
     template <class X>
     friend bool operator>(GEN_SLLL<X> &op1, GEN_SLLL<X> &op2); //Check For Greater than
     template <class X>
     friend bool operator<(GEN_SLLL<X> &op1, GEN_SLLL<X> &op2); //Check for Less Than
};

/////////////////////////////////////////////////////////////////////////////////////////		
///////##################################////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator ==(GEN_SLLL<T> &op1,GEN_SLLL<T> &op2)	  //Compair Linked List for Equality
{
	struct node<T>* temp1=op1.Head;
	struct node<T>* temp2=op2.Head;

	while((temp1!=NULL)&&(temp2!=NULL))
	{
		if(temp1->Data!=temp2->Data)
		{
            break;
		}
        temp1=temp1->Next;
		temp2=temp2->Next;
	} 
    if((temp1==NULL)&&(temp2==NULL))
	{
        return TRUE;
	}
	else
	{
        return FALSE;
	}
}

template <class T>
bool operator >(GEN_SLLL<T> &op1,GEN_SLLL<T> &op2)					//Check For Greater than
{
	struct node<T>* temp1=op1.Head;
    struct node<T>* temp2=op2.Head;

	while((temp1!=NULL)&&(temp2!=NULL))
	{
		if((temp1->Data) <= (temp2->Data))
		{
			break;
		}
	    temp1=temp1->Next;
		temp2=temp2->Next;
	} 
	if((temp1==NULL)&&(temp2==NULL))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

template <class T>
bool operator <(GEN_SLLL<T> &op1,GEN_SLLL<T> &op2)					//Check for Less than
{
	struct node<T>* temp1=op1.Head;
	struct node<T>* temp2=op2.Head;

	while((temp1!=NULL)&&(temp2!=NULL))
	{
		if((temp1->Data) >= (temp2->Data))
		{
			break;
		}
		temp1=temp1->Next;
		temp2=temp2->Next;
	} 
	if((temp1==NULL)&&(temp2==NULL))
	{
		return TRUE;
	}
    else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_SLLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is Constructor of SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
template<class T>
GEN_SLLL<T>::GEN_SLLL()					
{
	Head=NULL;
	Tail=NULL;
	size=0;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_SLLL
//  Function date    :   9/11/2019
//  Function Author  :   Harshal Nikam
//  Parameter        :   NONE
//  Discription      :   This is Destructor of SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_SLLL<T>::~GEN_SLLL()					
{
	struct node<T>* temp;
	struct node<T>* Navigate;

	if(Head!=NULL)
	{
		Navigate=Head;
		while(Navigate!=NULL)
		{
			temp=Navigate->Next;
			delete Navigate;
			Navigate=temp;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add first node in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::InsertFirst(T tVal)		
{
	struct node<T>* newn=NULL;

	newn=new struct node<T>;
	if(newn==NULL)
	{
		return;
	}

	newn->Next=NULL;
	newn->Data=tVal;

	if(Head==NULL)
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		newn->Next=Head;
		Head=newn;
	}
	size++;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DisplaR
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function display SLLL in Reverse manner
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::DisplayR()
{
	struct node<T>* temp=Head;
	T Arr[size];
	int i=0;
	while(temp!=NULL)
	{
		Arr[i]=temp->Data;
		temp=temp->Next;
		i++;		
	}
	i--;
	while(i>=0)
	{
		cout<<"| "<<Arr[i]<<" |"<<"->";
		i--;
	}
	cout<<"NULL\n";
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function disply SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>										
void GEN_SLLL<T>::Display()					 
{
	struct node<T>* temp=Head;
	while(temp!=NULL)
	{
		cout<<"| "<<temp->Data<<" |"<<"->";
		temp=temp->Next;
	}
	cout<<"NULL\n";
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function counts node in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SLLL<T>::Count()					
{
	return this->size;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function insert the Last node in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::InsertLast(T tVal)
{
	struct node<T>* newn = NULL;
	newn = new struct node<T>;

	if(newn==NULL)
	{
		return;
	}

	newn->Next=NULL;
	newn->Data=tVal;

	if(Head==NULL)
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		Tail->Next=newn;
		Tail=newn;
	}
	size++;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertAtPose
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval,int iPose
//  Discription      :  This function add node at specified position in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::InsertAtPos(T tVal,int iPos)			
{
	if((Head==NULL) || (iPos>size+1) || (iPos<=0))
	{
		return;
	}
	else if(iPos==1)
	{
		InsertFirst(tVal);
	}
	else if(iPos==size+1)
	{
		InsertLast(tVal);
	}
	else
	{
		struct node<T>* newn=NULL;
		struct node<T>* temp=Head;

		newn = new struct node<T>;
		if(newn==NULL)
		{
			return;
		}

		newn->Next=NULL;
		newn->Data=tVal;

		for(int i=1;i<(iPos-1);i++)
		{
			temp=temp->Next;
		}
		newn->Next=temp->Next;
		temp->Next=newn;
		size++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function remove first node in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::DeleteFirst()					
{
	struct node<T>* temp=Head;
	if(Head==NULL)
	{
		return;
	}
	else 
	{
		Head=Head->Next;
		delete (temp);
		size--;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function  node
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::DeleteLast()				  
{
	if(Head==NULL)
	{
		return;
	}
	else if(Head->Next==NULL)
	{
		delete Head;
		Head=NULL;
	        size--;
	}
	else
	{
		struct node<T>* temp=Head;

		while(temp->Next!=Tail)
		{
			temp=temp->Next;
		}
		delete Tail;
		Tail=temp;
		Tail->Next=NULL;
		size--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteAtPose
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  int
//  Discription      :  This function delete node from specified position in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SLLL<T>::DeleteAtPos(int iPos)			
{
	if((Head==NULL) || (iPos<=0) || (iPos>size))
	{
		return;
	}
	else if(iPos==1)
	{
		DeleteFirst();
	}
	else if(iPos==size)
	{
		DeleteLast();
	}
	else
	{
		struct node<T>* target=NULL;
		struct node<T>* Navigate=Head;

		for(int i=1;i<(iPos-1);i++)
		{
			Navigate=Navigate->Next;
		}
		target=Navigate->Next;
		Navigate->Next=target->Next;
		delete target;
		size--;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Frequency
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function count frequency in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SLLL<T>::Frequency(T tVal)
{
	struct node<T>* temp=Head;
	int iCnt=0;
	while(temp!=NULL)
	{
		if(temp->Data==tVal)
		{
			iCnt++;
		}
		temp=temp->Next;
	}
	return iCnt;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  FirstOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search first occurence of data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SLLL<T>::FirstOccurance(T tVal)		
{
	struct node<T>* temp=Head;
	int iCnt=1,iPos=0;
	while(temp!=NULL)
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
			break;
		}
		iCnt++;
		temp=temp->Next;
	}
	return iPos;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  LastOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search last occurance of data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SLLL<T>::LastOccurance(T tVal)			
{
	struct node<T>* temp=Head;
	int iCnt=1,iPos=0;
	while(temp!=NULL)
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
		}
		iCnt++;
		temp=temp->Next;
	}
	return iPos;
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Summation
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function to find summation data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SLLL<T>::Summation()					
{
	struct node<T>* temp=Head;
	int iSum=0;
	while(temp!=NULL)
	{
		iSum=iSum+temp->Data;
		temp=temp->Next;
	}
	return iSum;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Largest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find largest of given data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_SLLL<T>::Largest()					
{
	struct node<T>* temp=Head;
	int tMax=0;
	tMax=temp->Data;
	while(temp!=NULL)
	{
		if((temp->Data)>=tMax)
		{
			tMax=temp->Data;
		}
		temp=temp->Next;
	}
	return tMax;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Smallest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find smallest given data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_SLLL<T>::Smallest()					
{
	struct node<T>* temp=Head;
	int tMin=0;
	tMin=temp->Data;
	while(temp!=NULL)
	{
		if((temp->Data)<=tMin)
		{
			tMin=temp->Data;
		}
		temp=temp->Next;
	}
	return tMin;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ReverseList
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function reverse SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
void GEN_SLLL<T>::ReverseList()
{
	struct node<T>* NEXT=NULL;
	struct node<T>* curr=Head;
	struct node<T>* PREV=NULL;
	
	if(Head==NULL)
	{
		return;
	}
	else
	{
		while(curr!=NULL)
		{
			NEXT=curr->Next;		//make current node's Next node as Next
			curr->Next=PREV;		//store PREV value in current node's Next value
			PREV=curr;				//make current node as PREV for further operations
			curr=NEXT;				//move to Next node;
		}
		Head=PREV;					//at last PREV will contain Last node address
	}		
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Concat
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function concat two LL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/*
template<class T>
void GEN_SLLL<T>::Concat(GEN_SLLL<T> &op1,GEN_SLLL<T> &op2)		
{
	struct node<T>* temp=op1.Head;
	
	if((op1.Head==NULL) && (op2.Head==NULL))
	{
		return;
	}
	
	while(temp->Next!=NULL)       //op1.Tail->Next=op2.Head;
                                      //while(op1.Tail!=op2.Tail)			
	{			      //{
		temp=temp->Next;      //   op1.Tail=op1.Tail->Next
	}			      //}
	temp->Next=op2.Head;          //op1.size=op1.size+op2.size
	op1.size=op1.size+op2.size;
}*/

 template <class T>
 void GEN_SLLL<T>::Concat(GEN_SLLL<T> &op1, GEN_SLLL<T> &op2) ////GENERIC FUNCTION TO CONCAT TWO LINKED LIST          this is add
 {
     struct node<T> *temp = op2.Head;

     if ((op1.Head == NULL) && (op2.Head == NULL))
     {
         return;
     }
     while (temp != NULL)
     {
         struct node<T> *newn = new struct node<T>;
         newn->Next = NULL;
         newn->Data = temp->Data;
         op1.Tail->Next = newn;
         op1.Tail = newn;
         temp = temp->Next;
         op1.size++;
     }
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////#####################################################///////////////////////////////////////////
////############    CLASS NAME:-GEN_SCLL      ##########################################//////////////
////############    Thi class represents singly circular linked list   ##############//////////////////
/////////////################################################################//////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class GEN_SCLL
{
private:
	struct node<T>* Head;  //pointing at start of linked list
	struct node<T>* Tail;  //pointing at end of linked list
	T  iSize;

public:

	GEN_SCLL();
	~GEN_SCLL();

	void InsertFirst(T );
	void InsertLast(T );
	void InsertAtPos(T ,int);
	void DeleteFirst();
	void DeleteLast();
	void DeleteAtPos(int);
	void Display();
	int  Count();
	int FirstOccurance(T);
	int LastOccurance(T);
	T Largest();
	T Smallest();
	int Frequency(T);
    void Concat(GEN_SCLL<T> &op1, GEN_SCLL<T> &op2);


    
     template <class X>
     friend bool operator<(GEN_SCLL<X> &op1, GEN_SCLL<X> &op2); //Check for Less Than
     template <class X>
     friend bool operator>(GEN_SCLL<X> &op1, GEN_SCLL<X> &op2); //Check For Greater than
     template <class X>
     friend bool operator==(GEN_SCLL<X> &op1, GEN_SCLL<X> &op2); //Compares Linked List For Equality
};

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
///######################################################################
////////////////////////////////////////////////////////////////////////////////////

 template <class T>
 bool operator==(GEN_SCLL<T> &op1, GEN_SCLL<T> &op2) //Compaire Linked List For Equality
 {
     struct node<T> *temp1 = op1.Head;
     struct node<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if (temp1->Data != temp2->Data)
         {
             break;
         }

         temp1 = temp1->Next;
         temp2 = temp2->Next;

     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     if ((temp1 == op1.Tail->Next) && (temp2 == op2.Tail->Next))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

 template <class T>
 bool operator>(GEN_SCLL<T> &op1, GEN_SCLL<T> &op2) //Check For Greater than
 {
     struct node<T> *temp1 = op1.Head;
     struct node<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if ((temp1->Data) < (temp2->Data))
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     if ((temp1 == NULL) && (temp2 == NULL))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

 template <class T>
 bool operator<(GEN_SCLL<T> &op1, GEN_SCLL<T> &op2) //Check for Less Than
 {
     struct node<T> *temp1 = op1.Head;
     struct node<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if ((temp1->Data) > (temp2->Data))
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     if ((temp1 == op1.Tail->Next) && (temp2 == op2.Tail->Next))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_SCLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is constructor of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_SCLL<T>::GEN_SCLL()
{
	Head=NULL;
	Tail=NULL;
	iSize=0;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_SCLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is destructor of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_SCLL<T>::~GEN_SCLL()
{
	struct node<T>* temp=NULL;
	if((Head!=NULL)&&(Tail!=NULL))
	{
		do
		{
			temp=Head;
			Head=Head->Next;
			Tail->Next=Head;
			delete temp;

		}while(Head!=Tail->Next);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function displays SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::Display()
{
	struct node<T>* temp=Head;
	if((Head==NULL)&&(Tail==NULL))
	{
		return;
	}
	do
	{
		cout<<"|"<<temp->Data<<"|->";
		temp=temp->Next;
	}while(temp!=Tail->Next);
	
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function count nodes of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SCLL<T>::Count()
{
	return this->iSize;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add first node of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::InsertFirst(T tVal)
{
	struct node<T>* newn=NULL;
	newn=new struct node<T>;

	newn->Next=NULL;
	newn->Data=tVal;

	if((Head==NULL) && (Tail==NULL))
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		newn->Next=Head;
		Head=newn;
	}
	Tail->Next=Head;
	iSize++;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add last node of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::InsertLast(T tVal)
{
	struct node<T>* newn=NULL;

	newn=new struct node<T>;
	newn->Next=NULL;
	newn->Data=tVal;

	if((Head==NULL) && (Tail==NULL))
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		Tail->Next=newn;
		Tail=Tail->Next;
	}
	Tail->Next=Head;
	iSize++;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes first node of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>

void GEN_SCLL<T>::DeleteFirst()
{
	if((Head==NULL)&&(Tail==NULL))
	{
		return;
	}
	else if(Head==Tail)
	{
		delete Head;
		Head=NULL;
		Tail=NULL;
	}
	else
	{
		Head=Head->Next;
		delete Tail->Next;
		Tail->Next=Head;
	}
	iSize--;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes last node of SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::DeleteLast()
{
	if((Head==NULL)&&(Tail==NULL))
	{
		return;
	}
	else if(Head==Tail)
	{
		delete Tail;
		Head=NULL;
		Tail=NULL;
	}
	else
	{
		struct node<T>* temp=Head;
		while(temp->Next!=Tail)
		{
			temp=temp->Next;
		}
		delete Tail;
		Tail=temp;
		Tail->Next=Head;
	}
	iSize--;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval,int iPos
//  Discription      :  This function adds node at specifide position in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::InsertAtPos(T tVal,int iPos)
{
	if((Head==NULL) || (Tail==NULL) || (iPos<=0) || (iPos>iSize+1))
	{
		return;
	}
	else if(iPos==1)
	{
		InsertFirst(tVal);
	}
	else if(iPos==iSize+1)
	{
		InsertLast(tVal);
	}
	else
	{ 
		struct node<T>* newn=NULL;
		struct node<T>* temp=Head;

		newn = new struct node<T>;
		if(newn==NULL)
		{
			return;
		}

		newn->Next=NULL;
		newn->Data=tVal;

		for(int i=1;i<(iPos-1);i++)
		{
			temp=temp->Next;
		}
		newn->Next=temp->Next;
		temp->Next=newn;
		iSize++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  int iPos
//  Discription      :  This function deletes node at specifide position in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_SCLL<T>::DeleteAtPos(int iPos)
{
	if((Head==NULL) || (Tail==NULL) || (iPos<=0) || (iPos>iSize))
	{
		return;
	}
	else if(iPos==1)
	{
		DeleteFirst();
	}
	else if(iPos==iSize)
	{
		DeleteLast();
	}
	else
	{ 
		struct node<T>* temp=Head;
		struct node<T>* target=NULL;

		for(int i=1;i<(iPos-1);i++)
		{
			temp=temp->Next;
		}
		target=temp->Next;
		temp->Next=target->Next;
		delete target;
		iSize--;
    }
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  FirstOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search first occurence of data in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SCLL<T>::FirstOccurance(T tVal)		
{
	struct node<T>* temp=Head;
	int iCnt=1,iPos=0;
	do
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
			break;
			
		}
		iCnt++;
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iPos;
}





/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  LastOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search last occurance of data in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SCLL<T>::LastOccurance(T tVal)			
{
	struct node<T>* temp=Head;
	int iCnt=1,iPos=0;
	do
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
		}
		iCnt++;
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iPos;
}





/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Largest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find largest of given data in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_SCLL<T>::Largest()					
{
	struct node<T>* temp=Head;
	int tMax=0;
	tMax=temp->Data;
	do
	{
		if((temp->Data)>=tMax)
		{
			tMax=temp->Data;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return tMax;
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Smallest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find smallest given data in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T	 GEN_SCLL<T>::Smallest()					
{
	struct node<T>* temp=Head;
	int tMin=0;
	tMin=temp->Data;
	do
	{
		if((temp->Data)<=tMin)
		{
			tMin=temp->Data;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return tMin;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Frequency
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function count frequency in SCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_SCLL<T>::Frequency(T tVal)
{
	struct node<T>* temp=Head;
	int iCnt=0;
	do
	{
		if(temp->Data==tVal)
		{
			iCnt++;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iCnt;
}


/////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////
 //
 //  Function name    :  Concat
 //  Function date    :  9/11/2019
 //  Function Author  :  Harshal Nikam
 //  Parameter        :  None
 //  Discription      :  This function is Concat 
 //
 ////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////

 template <class T>
 void GEN_SCLL<T>::Concat(GEN_SCLL<T> &op1, GEN_SCLL<T> &op2)
 {
     struct node<T> *temp = op1.Head;

     if ((op1.Head == NULL) && (op2.Head == NULL))
     {
         return;
     }
     op1.Tail->Next = op2.Head;
     while (op1.Tail != op2.Tail)
     {
         op1.Tail = op1.Tail->Next;
     }
     op1.Tail->Next = op1.Head;

     op1.size = op1.size + op2.size;
 }

//////////////////////////////////////////////////////////////////////////////////////////
/////////####################################################################/////////////
///######################   CLASS NAME:-GEN_DLLL  ##############################//////////
///############# This class represents doubly linear linked list   ###############///////
////////////##########################################################/////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class GEN_DLLL
{
private:

	struct dnode<T>* Head;   //pointing at start of linked list
	struct dnode<T>* Tail;   //pointing at end of linked list
	int  iSize;
public:

	GEN_DLLL();
	~GEN_DLLL();

	void InsertFirst(T);
	void InsertLast(T);
	void InsertAtPos(T,int);
	void DeleteFirst();
	void DeleteLast();
	void DeleteAtPos(int);
	inline void Display();
	inline void DisplayB();
	inline int Count();
	int LastOccurance(T);
	int FirstOccurance(T);
	T Largest();
	T Smallest();
	int Frequency(T);
    void Concat(GEN_DLLL<T> &op1, GEN_DLLL<T> &op2);


     template <class X>
     friend bool operator==(GEN_DLLL<X> &op1, GEN_DLLL<X> &op2); //Compares Linked List For Equality
     template <class X>
     friend bool operator>(GEN_DLLL<X> &op1, GEN_DLLL<X> &op2); //Check For Greater than
     template <class X>
     friend bool operator<(GEN_DLLL<X> &op1, GEN_DLLL<X> &op2); //Check for Less Than

};

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//################################################################################
///////////////////////////////////////////////////////////////////////////////////
 template <class T>
 bool operator==(GEN_DLLL<T> &op1, GEN_DLLL<T> &op2) //Compares Linked List For Equality
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     while ((temp1 != NULL) && (temp2 != NULL))
     {
         if (temp1->Data != temp2->Data)
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     }
     if ((temp1 == NULL) && (temp2 == NULL))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

 template <class T>
 bool operator>(GEN_DLLL<T> &op1, GEN_DLLL<T> &op2) //Check For Greater than
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     while ((temp1 != NULL) && (temp2 != NULL))
     {
         if ((temp1->Data) < (temp2->Data))
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     }
     if ((temp1 == NULL) && (temp2 == NULL))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

 template <class T>
 bool operator<(GEN_DLLL<T> &op1, GEN_DLLL<T> &op2) //Check for Less Than
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     while ((temp1 != NULL) && (temp2 != NULL))
     {
         if ((temp1->Data) > (temp2->Data))
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     }
     if ((temp1 == NULL) && (temp2 == NULL))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_DLLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is constructor of  DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_DLLL<T>::GEN_DLLL()
{
	Head=NULL;
	Tail=NULL;
	iSize=0;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_DLLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is destructor of DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_DLLL<T>::~GEN_DLLL()
{
	struct dnode<T>* temp=NULL;
	while(Head!=NULL)
	{
		temp=Head;
		Head=Head->Next;
		delete temp;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function display DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
void GEN_DLLL<T>::Display()
{
	struct dnode<T>* temp=Head;
	cout<<"\nNULL";
	while(temp!=NULL)
	{
		cout<<"<-"<<"|"<<temp->Data<<"|"<<"->";
		temp=temp->Next;
	}
	cout<<"NULL\n";
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DisplayB
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function display DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::DisplayB()
{
	struct dnode<T>* temp=Tail;
	cout<<"\nNULL";
	while(temp!=NULL)
	{
		cout<<"<-"<<"|"<<temp->Data<<"|"<<"->";
		temp=temp->Prev;
	}
	cout<<"NULL\n";
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function counts nodes in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DLLL<T>::Count()
{
	return this->iSize;
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add first node from DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
void GEN_DLLL<T>::InsertFirst(T  tVal)
{
	struct dnode<T>* newn=NULL;
	newn=new struct dnode<T>;
	if(newn==NULL)
	{
		return;
	}
	newn->Next=NULL;
	newn->Prev=NULL;
	newn->Data= tVal;

	if(Head==NULL)
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		Head->Prev=newn;
		newn->Next=Head;
		Head=newn;
	}
	iSize++;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add last node from DLLL 
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::InsertLast(T   tVal)
{
	struct dnode<T>* newn=NULL;
	newn=new struct dnode<T>;
	if(newn==NULL)
	{
		return;
	}
	newn->Next=NULL;
	newn->Prev=NULL;
	newn->Data=tVal;

	if(Head==NULL)
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		Tail->Next=newn;
		newn->Prev=Tail;
		Tail=newn;
	}
	iSize++;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes first node from DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::DeleteFirst()
{
	if(Head==NULL)
	{
		return;
	}
	else if(Head->Next==NULL)
	{
		delete Head;
		Head=NULL;
		Tail=NULL;
		iSize--;
	}
	else
	{
		Head=Head->Next;
		delete Head->Prev;
		Head->Prev=NULL;
		iSize--;
	}
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes last node from DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::DeleteLast()
{
	if(Head==NULL)
	{
		return;
	}
	else if(Head->Next==NULL)
	{
		delete Head;
		Head=NULL;
		Tail=NULL;
		iSize--;
	}
	else
	{
		Tail=Tail->Prev;
		delete Tail->Next;
		Tail->Next=NULL;
		iSize--;
	}
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval,int iPos
//  Discription      :  This function add node from specifide position in DLLL 
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::InsertAtPos(T   tVal,int iPos)
{
	if((Head==NULL) || (iPos<1) || (iPos>(Count()+1)))
	{
		return;
	}
	if(iPos==1)
	{
		InsertFirst(tVal);
	}
	else if(iPos==(Count()+1))
	{
		InsertLast(tVal);
	}
	else
	{
		struct dnode<T>* newn = NULL;
		struct dnode<T>* temp=Head;
		newn=new struct dnode<T>;
		if(newn==NULL)
		{
			return;
		}
		newn->Next=NULL;
		newn->Prev=NULL;
		newn->Data=tVal;

		for(T  i=1;i<(iPos-1);i++)
		{
			temp=temp->Next;
		}
		newn->Next=temp->Next;
		temp->Next->Prev=newn;
		temp->Next=newn;
		newn->Prev=temp;
		iSize++;
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  int iPos
//  Discription      :  This function removes node from specified position in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DLLL<T>::DeleteAtPos(int iPos)
{
	if((Head==NULL) || (iPos<1) || (iPos>Count()))
	{
		return;
	}
	if(iPos==1)
	{
		DeleteFirst();
	}
	else if(iPos==Count())
	{
		DeleteLast();
	}
	else
	{
		struct dnode<T>* temp=Head;

		for(int i=1;i<(iPos-1);i++)
		{
			temp=temp->Next;
		}
		temp->Next=temp->Next->Next;
		delete(temp->Next->Prev);
		temp->Next->Prev=temp;
		iSize--;
	}
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  FirstOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search first occurence of data in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DLLL<T>::FirstOccurance(T tVal)		
{
	struct dnode<T>* temp=Head;
	int iCnt=1,iPos=0;
	while(temp!=NULL)
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
			break;
		}
		iCnt++;
		temp=temp->Next;
	}
	return iPos;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  LastOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search last occurance of data in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DLLL<T>::LastOccurance(T tVal)			
{
	struct dnode<T>* temp=Head;
	int iCnt=1,iPos=0;
	while(temp!=NULL)
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
		}
		iCnt++;
		temp=temp->Next;
	}
	return iPos;
}





/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Largest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find largest of given data in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_DLLL<T>::Largest()					
{
	struct dnode<T>* temp=Head;
	int tMax=0;
	tMax=temp->Data;
	while(temp!=NULL)
	{
		if((temp->Data)>=tMax)
		{
			tMax=temp->Data;
		}
		temp=temp->Next;
	}
	return tMax;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Smallest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find smallest given data in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_DLLL<T>::Smallest()					
{
	struct dnode<T>* temp=Head;
	int tMin=0;
	tMin=temp->Data;
	while(temp!=NULL)
	{
		if((temp->Data)<=tMin)
		{
			tMin=temp->Data;
		}
		temp=temp->Next;
	}
	return tMin;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Frequency
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function count frequency in DLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DLLL<T>::Frequency(T tVal)
{
	struct dnode<T>* temp=Head;
	int iCnt=0;
	while(temp!=NULL)
	{
		if(temp->Data==tVal)
		{
			iCnt++;
		}
		temp=temp->Next;
	}
	return iCnt;
}
/////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////
 //
 //  Function name    :  Concat
 //  Function date    :  9/11/2019
 //  Function Author  :  Harshal Nikam
 //  Parameter        :  None
 //  Discription      :  This function is Concat
 //
 ////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////

template <class T>
 void GEN_DLLL<T>::Concat(GEN_DLLL<T> &op1, GEN_DLLL<T> &op2)
 {
     struct dnode<T> *temp = op1.Head;

     if ((op1.Head == NULL) && (op2.Head == NULL))
     {
         return;
     }
     op1.Tail->Next = op2.Head;
     op2.Head->Prev = op1.Tail;

     while (op1.Tail != op2.Tail)
     {
         op1.Tail = op1.Tail->Next;
     }

     op1.size = op1.size + op2.size;
}

/////////////////////////////////////////////////////////////////////////////////////////
////####################################################################/////////////////
///################  CLASS NAME:- GEN_DCLL  ######################################///////
///################  This class represents doubly circular linked list    ########///////
////////////#######################################################################//////
////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class GEN_DCLL
{
private:

	struct dnode<T>* Head;   //pointing at start linked list
	struct dnode<T>* Tail;   //pointing at end linked list
	int   iSize;

public:

	GEN_DCLL();
	~GEN_DCLL();

	void InsertFirst(T );
	void InsertLast(T );
	void InsertAtPos(T ,int);
	void DeleteFirst();
	void DeleteLast();
	void DeleteAtPos(int);
	void Display();
	void DisplayR();
	int Count();
	int FirstOccurance(T);
	int LastOccurance(T);
	T Smallest();
	T Largest();
	int Frequency(T);
    void Concat(GEN_DCLL<T> &op1, GEN_DCLL<T> &op2);

    
     template <class X>
     friend bool operator==(GEN_DCLL<X> &op1, GEN_DCLL<X> &op2); //Compares Linked List For Equality
     template <class X>
     friend bool operator>(GEN_DCLL<X> &op1, GEN_DCLL<X> &op2); //Check For Greater than
     template <class X>
     friend bool operator<(GEN_DCLL<X> &op1, GEN_DCLL<X> &op2); //Check for Less Than

};

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//#################################################################################
///////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator==(GEN_DCLL<T> &op1, GEN_DCLL<T> &op2) //Compares Linked List For Equality
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if (temp1->Data != temp2->Data)
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     if ((temp1 == op1.Tail->Next) && (temp2 == op2.Tail->Next))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

template <class T>
bool operator>(GEN_DCLL<T> &op1, GEN_DCLL<T> &op2) //Check For Greater than
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if ((temp1->Data) < (temp2->Data))
         {
             break;
         }

         temp1 = temp1->Next;
         temp2 = temp2->Next;
     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     cout << op1.Tail->Data;
     cout << op1.Tail->Data;

     if ((temp1 == op1.Tail->Next) && (temp2 == op2.Tail->Next))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }

template <class T>
bool operator<(GEN_DCLL<T> &op1, GEN_DCLL<T> &op2) //Check for Less Than
 {
     struct dnode<T> *temp1 = op1.Head;
     struct dnode<T> *temp2 = op2.Head;

     if ((temp1 == NULL) || (temp2 == NULL))
     {
         cout << "Can't Compare\n";
         return FALSE;
     }

     do
     {
         if ((temp1->Data) > (temp2->Data))
         {
             break;
         }
         temp1 = temp1->Next;
         temp2 = temp2->Next;
     } while ((temp1 != op1.Tail->Next) && (temp2 != op2.Tail->Next));

     if ((temp1 == op1.Tail->Next) && (temp2 == op2.Tail->Next))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_DCLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is constructor of DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_DCLL<T>::GEN_DCLL()
{
	this->Head=NULL;
	this->Tail=NULL;
	this->iSize=0;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_DCLL
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is destructor of DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_DCLL<T>::~GEN_DCLL()
{
	struct dnode<T>* temp=NULL;
	if((Head!=NULL)&&(Tail!=NULL))
	{
		do
		{
			temp=Head;
			Head=Head->Next;
			Tail->Next=Head;
			delete temp;

		}while(Head!=Tail->Next);
	}
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add first node to DCLL 
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::InsertFirst(T  tVal)
{
	struct dnode<T>* newn=new struct dnode<T>;

	newn->Next=NULL;
	newn->Prev=NULL;
	newn->Data=tVal;

	if((Head==NULL) && (Tail==NULL))
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		newn->Next=Head;
		Head->Prev=newn;
		Head=newn;
	}
	Tail->Next=Head;
	Head->Prev=Tail;
	iSize++;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function add last node to DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::InsertLast(T  tVal)
{
	struct dnode<T>* newn=new struct dnode<T>;

	newn->Next=NULL;
	newn->Prev=NULL;
	newn->Data=tVal;

	if((Head==NULL) && (Tail==NULL))
	{
		Head=newn;
		Tail=newn;
	}
	else
	{
		Tail->Next=newn;
		newn->Prev=Tail;
		Tail=newn;
	}
	Tail->Next=Head;
	Head->Prev=Tail;
	iSize++;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function display DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::Display()
{
	struct dnode<T>* temp=Head;
	/*for(int i=1;i<=iSize;i++)
	{
		cout<<"<-|"<<temp->Data<<"|->";
		temp=temp->Next;
	}*/
	temp=Head;
	if((Head==NULL)&&(NULL==Tail))
	{
		return;
	}
	cout<<"\n->";
	do
	{
		cout<<"<-|"<<temp->Data<<"|->";
		temp=temp->Next;
	}while(temp!=Tail->Next);
	cout<<"<-\n";
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DisplayR
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find smallest given data in SLLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::DisplayR()
{
	struct dnode<T>* temp=Tail;
	/*for(int i=1;i<=iSize;i++)
	{
		cout<<"<-|"<<temp->Data<<"|->";
		temp=temp->Prev;
	}*/

	temp=Tail;
	if((Head==NULL)&&(NULL==Tail))
	{
		return;
	}
	cout<<"\n->";
	do
	{
		cout<<"<-|"<<temp->Data<<"|->";
		temp=temp->Prev;
	}while(temp!=Head->Prev);
	cout<<"<-\n";
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteFirst
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes first node from DCLL 
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::DeleteFirst()
{
	if((Head==NULL)&&(NULL==Tail))
	{
		return;
	}
	else if(Head==Tail)
	{
		delete Head;
		Head=NULL;
		Tail=NULL;
	}
	else
	{
		Head=Head->Next;
		delete Head->Prev;
		Tail->Next=Head;
		Head->Prev=Tail;
		iSize--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteLast
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function removes last node from DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
void GEN_DCLL<T>::DeleteLast()
{
	if((Head==NULL)&&(NULL==Tail))
	{
		return;
	}
	else if(Head==Tail)
	{
		delete Tail;
		Head=NULL;
		Tail=NULL;
	}
	else
	{
		Tail=Tail->Prev;
		delete Tail->Next;
		Tail->Next=Head;
		Head->Prev=Tail;
		iSize--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  InsertAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T val,int iPos
//  Discription      :  This function add node at specifide position of DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::InsertAtPos(T  tVal,int iPos)
{
	
	if((iPos<1)||(iPos>iSize+1))
	{
		return;
	}
	if(iPos==1)
	{
		InsertFirst(tVal);
	}
	else if(iPos==iSize+1)
	{
		InsertLast(tVal);
	}
	else
	{
		struct dnode<T>* newn=NULL;
		struct dnode<T>* temp=Head;
		newn=new struct dnode<T>;

		newn->Next=NULL;
		newn->Prev=NULL;
		newn->Data=tVal;

		for(int i=1;i<iPos;i++)
		{
			temp=temp->Next;
		}
		
		temp->Prev->Next=newn;
		newn->Prev=temp->Prev;
		newn->Next=temp;
		temp->Prev=newn;
		iSize++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  DeleteAtPos
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function remove node from specified position of DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_DCLL<T>::DeleteAtPos(int iPos)
{
	if((iPos<1)||(iPos>iSize))
	{
		return;
	}
	if(iPos==1)
	{
		DeleteFirst();
	}
	else if(iPos==iSize)
	{
		DeleteLast();
	}
	else
	{
		struct dnode<T>* temp=Head;
		for(int i=1;i<iPos;i++)
		{
			temp=temp->Next;
		}
		temp->Prev->Next=temp->Next;
		temp->Next->Prev=temp->Prev;
		delete temp;
		iSize--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function count the node
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
int GEN_DCLL<T>::Count()
{
	return this->iSize;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  FirstOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search first occurence of data in DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DCLL<T>::FirstOccurance(T tVal)		
{
	struct dnode<T>* temp=Head;
	int iCnt=1,iPos=0;
	do
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
			break;
			
		}
		iCnt++;
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iPos;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  LastOccurance
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function search last occurance of data in DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DCLL<T>::LastOccurance(T tVal)			
{
	struct dnode<T>* temp=Head;
	int iCnt=1,iPos=0;
	do
	{
		if((temp->Data)==tVal)
		{
			iPos=iCnt;
		}
		iCnt++;
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iPos;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Largest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find largest of given data in DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_DCLL<T>::Largest()					
{
	struct dnode<T>* temp=Head;
	int tMax=0;
	tMax=temp->Data;
	do
	{
		if((temp->Data)>=tMax)
		{
			tMax=temp->Data;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return tMax;
}





/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Smallest
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This function find smallest given data in DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_DCLL<T>::Smallest()					
{
	struct dnode<T>* temp=Head;
	int tMin=0;
	tMin=temp->Data;
	do
	{
		if((temp->Data)<=tMin)
		{
			tMin=temp->Data;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return tMin;
}






/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Frequency
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This function count frequency in DCLL
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
int GEN_DCLL<T>::Frequency(T tVal)
{
	struct node<T>* temp=Head;
	int iCnt=0;
	do
	{
		if(temp->Data==tVal)
		{
			iCnt++;
		}
		temp=temp->Next;
	}while(temp!=Tail->Next);
	return iCnt;
}

/////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////
 //
 //  Function name    :  Concat
 //  Function date    :  9/11/2019
 //  Function Author  :  Harshal Nikam
 //  Parameter        :  None
 //  Discription      :  This function is Concat
 //
 ////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////

template <class T>
void GEN_DCLL<T>::Concat(GEN_DCLL<T> &op1, GEN_DCLL<T> &op2) ////GENERIC FUNCTION TO CONCAT TWO LINKED LIST
{
     struct dnode<T> *temp = op1.Head;

     if ((op1.Head == NULL) && (op2.Head == NULL))
     {
         return;
     }
     op1.Tail->next = op2.Head;
     op2.Head->Prev = op1.Tail;

     while (op1.Tail != op2.Tail)
     {
         op1.Tail = op1.Tail->Next;
     }

     op1.Tail->next = op1.Head;
     op1.Head->Prev = op1.Tail;

     op1.size = op1.size + op2.size;
}


///////////////////////////////////////////////////////////////////
//
//  ClassName       :GEN_STACK
//  Description     :This is class designed for stack
//  Author          :Harshal Nikam
//
///////////////////////////////////////////////////////////////////
template<class T>
class GEN_STACK
{
    private:
        T   *Arr;
        int iTop;
        int iSize;

   public:
     /* Parameterized constructor with default args */
    GEN_STACK(int);
     /* Destructor */
   ~GEN_STACK();
     /* IsEmpty: check stack is empty or not */
    bool IsEmpty();
     /* IsFull: check stack is full or not */
    bool IsFull();
     /* Push: Push element in stack */
    void Push(T);
     /* Pop: Pop element from stack */
    T Pop();
     /* Display elements in stack */
    void Display();

};// end of class GEN_STACK declaration

////////////////////////////////////////////////////////////
//
//  Name        :GEN_STACK
//  Input       :int
//  Returns     :   -
//  Description :constructor
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
GEN_STACK<T>::GEN_STACK(int iNum)
{
    this->iSize = iNum;
    this->iTop = -1;
    this->Arr = new T[this->iSize];
}// end of constructor


////////////////////////////////////////////////////////////
//
//  Name        :~GEN_STACK
//  Input       :   -
//  Returns     :   -
//  Description :destructor
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
GEN_STACK<T>::~GEN_STACK()
{
   delete[] Arr;
}// end of destructor

////////////////////////////////////////////////////////////
//
//  Name        :IsEmpty
//  Input       :void
//  Returns     :bool
//  Description :Check whether stack is empty or not
//  Author      :Harshal Niam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
bool GEN_STACK<T>::IsEmpty()
{
    if(this->iTop == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}// end of IsEmpty

////////////////////////////////////////////////////////////
//
//  Name        :IsFull
//  Input       :void
//  Returns     :bool
//  Description :Check whether stack is full or not
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
bool GEN_STACK<T>::IsFull()
{
    if(this->iTop == iSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}// end of IsFull

////////////////////////////////////////////////////////////
//
//  Name        :Display
//  Input       :void
//  Returns     :void
//  Description :Displays stack elements
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
void GEN_STACK<T>::Display()
{
    if(IsEmpty())
    {
        cout << "Cannot display stack is empty!!\n";
        return;
    }
    int i = 0;
    cout << "Top--->";
    for(i = this->iSize -1; i >= 0; i--)
    {
        cout << "\t| " << this->Arr[i] << " |" << endl;
    }
}// end of Display

////////////////////////////////////////////////////////////
//
//  Name        :Push
//  Input       :int
//  Returns     :void
//  Description :Push els in stack
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
void GEN_STACK<T>::Push(T tData)
{
    if(IsFull())
    {
        cout << "Stack is Full\n";
        return;
    }
    this->iTop++;
    this->Arr[iTop] = tData;
}// end of Push

////////////////////////////////////////////////////////////
//
//  Name        :Pop
//  Input       :void
//  Returns     :int
//  Description :Pop els from stack
//  Author      :Harshal Nikam
//  Date        :6 Sept 2020
//
////////////////////////////////////////////////////////////
template<class T>
T GEN_STACK<T>::Pop()
{
    if(IsEmpty())
    {
        cout << "Stack is Empty\n";
        return T(-1);
    }
    T tData = 0;
    tData = this->Arr[iTop--];
    return tData;
}// end of Pop

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	 
//	ClassName 		:  GEN_QUEUE
//	Description		:  This class represent generic queue	
//	Author			:  Harshal Nikam 
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
struct Node
{
	T 	Data;
	struct Node *Next;
};

template<class T>
class GEN_QUEUE
{
private:

	struct Node<T>* Head;
	struct Node<T>* Tail;	

public:

	GEN_QUEUE();
	~GEN_QUEUE();
	void Enqueue(T);
	T Dequeue();
	void Display();
	int Count();
	
};


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_QUEUE
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is constructor of GEN queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_QUEUE<T>::GEN_QUEUE()
{
	Head=NULL;
	Tail=NULL;
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_QUEUE
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is destructor of GEN queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_QUEUE<T>::~GEN_QUEUE()
{
	struct Node<T>* temp=NULL;
	while(Head!=NULL)
	{
		temp=Head;
		Head=Head->Next;
		delete temp;
	}
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Enqueue
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This is add the element of  queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_QUEUE<T>::Enqueue(T tVal)
{
	struct Node<T>* newn=NULL;

	newn=(struct Node<T>*)malloc(sizeof(struct Node<T>));
	newn->Next=NULL;
	newn->Data=tVal;

	if((Head==NULL)&&(Tail==NULL))
	{
		Head=newn;
		Tail=newn;
	}
	else 
	{
		Tail->Next=newn;
		Tail=newn;
	}	
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Dequeue
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This  is delete the element
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
T GEN_QUEUE<T>::Dequeue()
{
	if((Head==NULL)&&(Tail==NULL))
	{
		cout<<"\nQUEUE is Empty\n";
		return -1;
	}
	if(Head==Tail)
	{
		T temp;
		temp=Head->Data;
		free(Head);
		Head=NULL;
		Tail=NULL;			
		return temp;
	}
	else
	{
		T temp;
		struct Node<T>* p=Head;
		temp=Head->Data;
		Head=Head->Next;
		free(p);
		return temp;
	}
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is display the queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
void GEN_QUEUE<T>::Display()
{
	struct Node<T>* temp=Head;
	while(temp!=NULL)
	{
		cout<<temp->Data<<"\t";
		temp=temp->Next;
	}
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This the element of queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


template<class T>
int GEN_QUEUE<T>::Count()
{
	int iCnt;
	struct Node<T>* temp=Head;
	while(temp!=NULL)
	{
		iCnt++;
		temp=temp->Next;
	}
	return iCnt;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//
//  ClassName       :  GEN_PRI__QUEUE
//  Description     :  This class is designed generic priority queue
//  Author          :  Harshal Nikam
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

 template <class T>
 class GEN_PRI_QUEUE
 {
 private:
     struct qnode<T> *Front;
     struct qnode<T> *Rear;
     int size;

 public:
     GEN_PRI_QUEUE();
     ~GEN_PRI_QUEUE();
     void Enqueue(T, int);
     T Dequeue();
     void Display();
     int Count();
 };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  GEN_PRI_QUEUE
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is constructor of GEN queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<class T>
GEN_PRI_QUEUE<T>::GEN_PRI_QUEUE()
{
    Front=NULL;
    Rear=NULL;
    size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  ~GEN_PRI_QUEUE
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is destructor of GEN Priority queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template <class T>
GEN_PRI_QUEUE<T>::~GEN_PRI_QUEUE()
{
    struct qnode<T> *temp = NULL;
    while (Front != NULL)
    {
        temp = Front;
        Front = Front->next;
        delete temp;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Display
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is display the GEN Priority queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template <class T>
void GEN_PRI_QUEUE<T>::Display()
{
    struct qnode<T> *temp = Front;
    while (temp != NULL)
    {
        cout << "|" << temp->data << ":" << temp->P << "|->";
        temp = temp->next;
    }
    cout << "NULL\n";
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Enqueue
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  T tval
//  Discription      :  This is add the element of  GEN Priority queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
template <class T>
void GEN_PRI_QUEUE<T>::Enqueue(T tVal, int iP)
{
    struct qnode<T> *newn = NULL;

    newn = new struct qnode<T>;
    newn->data = tVal;
    newn->next = NULL;
    newn->P = iP;

    if ((Front == NULL) && (Rear == NULL))
    {
        Front = newn;
        Rear = newn;
    }
    else
    {
        Rear->next = newn;
        Rear = Rear->next;
    }
    size++;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Dequeue
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This  is delete the element
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

 template <class T>
 T GEN_PRI_QUEUE<T>::Dequeue()
 {
     if ((Front == NULL) && (Rear == NULL))
     {
         cout << "QUEUE Underflow\n";
         return -1;
     }
     else if (Front == Rear)
     {
         T tVal = Front->data;
         delete Front;
         Front = NULL;
         Rear = NULL;
         size--;
         return tVal;
     }
     else
     {
         int iCnt = 0;
         int iPos = 0, Pri = 0;
         struct qnode<T> *temp = Front;
         struct qnode<T> *target = NULL;
         Pri = temp->P;
         while (temp != NULL)
         {
             iCnt++;
             if (Pri <= temp->P)
             {
                 Pri = temp->P;
                 iPos = iCnt;
             }
              temp = temp->next;
         }
         if (iPos == 1)
         {
             T tVal = Front->data;
             temp = Front;
             Front = Front->next;
             delete temp;
             size--;
             return tVal;
         }
         else if (iPos == size)
         {
             temp = Front;
             for (int i = 1; i < size - 1; i++)
             {
                 temp = temp->next;
             }
             T tVal = Rear->data;
             delete Rear;
             Rear = temp;
             Rear->next = NULL;
             size--;
             return tVal;
         }
         else
         {
             temp = Front;
             for (int i = 1; i < iPos - 1; i++)
             {
                 temp = temp->next;
             }
             target = temp->next;
             T tVal = target->data;
             temp->next = target->next;
             delete target;
             size--;
             return tVal;
         }
    }
 }

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Count
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This the element of GEN Priority queue
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template <class T>
int GEN_PRI_QUEUE<T>::Count()
{
    return size;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
//  Function name    :  Main
//  Function date    :  9/11/2019
//  Function Author  :  Harshal Nikam
//  Parameter        :  NONE
//  Discription      :  This is the entry point function
//
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


int main()
{
    //Objects of GEN_SLLL Class
    //you can replace GEN_SLL with other classes like GEN_SCLL,GEN_DLLL,GEN_SCLL
	GEN_SLLL<int>   	iobj1,iobj2;
	GEN_SLLL<float>		fobj1;
	GEN_SLLL<char>		cobj1;
	GEN_SLLL<double>	dobj1;


    //Local Variables
	int ch = 0;
	int iRet = 0;
	char cRet = '\0';

	//Objects of GEN_STACK Class
	GEN_STACK<int>      siobj(10);
	GEN_STACK<char>    scobj(5);

    //Objects of GEN_PRI_QUEUE Class
    GEN_PRI_QUEUE<int> pqiobj;

    //Objects of GEN_QUEUE Class
	GEN_QUEUE<int>       qiobj;
	GEN_QUEUE<double>    qdobj;
    GEN_QUEUE<char>      qcobj;


     //Menu driven
     cout << "1. Linked List\n";
     cout << "2. Queue\n";
     cout << "3. Stack\n";
     cout << "4. Priority Queue\n";
     cout << "Enter choice\n";
     cin >> ch;

switch(ch)
{
		case 1:cout<<"InsertFirst in First Linked list\n";
				iobj1.InsertFirst(40);
			    iobj1.InsertFirst(30);
				iobj1.InsertFirst(20);
				iobj1.InsertFirst(10);
				iobj1.Display();

				cout<<"Number of Nodes in first linked list:\t"<<iobj1.Count()<<"\n\n";
				cout<<"SLLL Smallest valeu is:";
				cout<<iobj1.Smallest()<<endl;

				cout<<"InsertFirst Charecter in Linked list\n";
			//	cobj.InsertFirst('L');
				cobj1.InsertFirst('A');
				cobj1.InsertFirst('H');
				cobj1.InsertFirst('S');
				cobj1.InsertFirst('R');
				cobj1.InsertFirst('A');
				cobj1.InsertFirst('H');
				cobj1.InsertLast('L');
				cobj1.Display();
				cout<<"DeleteAtPos :- 3\n\n";
				cobj1.DeleteAtPos(3);
				cobj1.Display();
				cout<<"Number of Charecter in linked list:\t"<<cobj1.Count()<<"\n\n";
		


				fobj1.InsertFirst(2.3);
				fobj1.InsertFirst(3.2);
				fobj1.InsertFirst(2.2);
				fobj1.Display();
				fobj1.Count();
				
				cout<<"InsertFirst in second linked list\n";
				iobj2.InsertFirst(80);
				iobj2.InsertFirst(70);
				iobj2.InsertFirst(60);
				iobj2.InsertFirst(50);
				iobj2.Display();
				cout<<"Number of Nodes in Second linked list:\t"<<iobj1.Count()<<"\n\n";
				
                cout<<"Concat two linked list and store resultant linked list in first linked list\n";
                iobj1.Concat(iobj1,iobj2);
				iobj1.Display();

				cout<<"Concat LL Smallest value is:";
				cout<<iobj1.Smallest()<<endl;

				cout<<"Number of Nodes in First linked list:\t"<<iobj1.Count()<<"\n\n";
				cout<<"InsertLast\n\n";
				iobj2.InsertLast(90);
				iobj2.InsertLast(100);
				iobj2.Display();

				cout<<"Number of Nodes in Second linked list:\t"<<iobj2.Count()<<"\n\n";
				cout<<"InsertAtPos :- 5\n\n";
				iobj2.InsertAtPos(85,5);
				iobj2.Display();

				cout<<"Nomber of Node is:\t"<<iobj2.Count()<<"\n\n";
				cout<<"Smallest value is:";

				cout<<iobj2.Smallest()<<endl;
				cout<<"DeleteLast\n\n";
				iobj1.DeleteLast();
				iobj1.Display();
				iobj2.DeleteLast();
				iobj2.Display();
				cout<<"Number of Nodes in Second linked list:\t"<<iobj2.Count()<<"\n\n";


				cout<<"DeleteAtPos :- 2\n\n";
				iobj1.DeleteAtPos(2);
				iobj1.Display();


				cout<<"ReverseList\n\n";
				iobj1.ReverseList();
				iobj1.Display();
				
				cout<<"Number of in First linked list:\t"<<iobj1.Count()<<"\n\n";



				cout<<iobj2.Frequency(80)<<endl;
				cout<<iobj1.FirstOccurance(10)<<endl;
				cout<<iobj1.LastOccurance(10)<<endl;
				cout<<iobj2.Largest()<<endl;
				cout<<iobj2.Smallest()<<endl;



				iobj1.Display();
				cout<<"\n";
				iobj2.Display();



				if(iobj1==iobj2)
				{
					cout<<"\nBoth linked list are Equal:\n";
				}
				else if(iobj1>iobj2)
				{
					cout<<"\n1st linked list is greather then 2nd\n";
				}
				else if(iobj1<iobj2)
				{
					cout<<"\n2nd linked list is greather then 1st\n";
				}
				else
				{
					cout<<"\nLinked list are Different\n\n";
				}
				break;


		
		
		case 2: cout<<"\nElement Pushed\n\n";
				siobj.Push(50);
				siobj.Push(40);
				siobj.Push(30);
				siobj.Push(20);
				siobj.Push(10);
				siobj.Display();




				cout<<"\n\nElement Poped\n\n";
				cout<<siobj.Pop()<<"\n";
				cout<<siobj.Pop()<<"\n";
				cout<<siobj.Pop()<<"\n";
				cout<<siobj.Pop()<<"\n";
				cout<<siobj.Pop()<<"\n";



				cout<<"\n\nElement Pushed\n\n";
				scobj.Push('H');
				scobj.Push('S');
				scobj.Push('R');
				scobj.Push('A');
				scobj.Push('H');
				scobj.Display();




				cout<<"\n\nElement Poped\n\n";
				cout<<scobj.Pop()<<"\n";
				cout<<scobj.Pop()<<"\n";
				cout<<scobj.Pop()<<"\n";
				cout<<scobj.Pop()<<"\n";
				cout<<scobj.Pop()<<"\n";

				break;


		case 3:	qiobj.Enqueue(33);
				qiobj.Enqueue(22);
                qiobj.Enqueue(11);
				qiobj.Display();
				cout<<"\n"<<qiobj.Count()<<"\n";

				
				cout<<qiobj.Dequeue()<<"\t";
				cout<<qiobj.Dequeue()<<"\t";
                cout<<endl;

				

				qcobj.Enqueue('H');
				qcobj.Enqueue('R');
                qcobj.Enqueue('A');
				qcobj.Display();
                cout<<endl;


				cout<<qcobj.Dequeue()<<"\t";
				cout<<qcobj.Dequeue()<<"\t";
                cout<<endl;
                break;

        case 4:  
                pqiobj.Enqueue(11, 25);
                pqiobj.Enqueue(16, 27);
                pqiobj.Enqueue(19, 18);
                pqiobj.Enqueue(40, 29);
                pqiobj.Enqueue(11, 1);
                pqiobj.Enqueue(17, 6);
                pqiobj.Enqueue(25, 16);
                pqiobj.Enqueue(36, 13);
                pqiobj.Enqueue(51, 35);
                pqiobj.Enqueue(71, 5);
                pqiobj.Enqueue(91, 15);
                pqiobj.Enqueue(81, 40);

                pqiobj.Display();
                cout<<endl;
                cout << "Count of Priority Queue:- "<<pqiobj.Count() << endl;
                cout<<endl;

                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                cout << pqiobj.Dequeue() << endl;
                break;

	return 0;
	}
}
