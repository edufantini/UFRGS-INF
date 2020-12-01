#include <iostream>
#include <vector>
using namespace std;


//----------- CLASSE PARA REPRESENTAR TERMOS LAMBDA ----------------- //

class term
{
  public:
    int    type;
    int    val;
    term*  left;
    term*  right;
    
    term () {
		      type  = 0;
		      val   = 0;
		      left  = NULL;
		      right = NULL;
		    }
};

term* var(int x)
  {
	term* a = new term();
    a -> type  = 0;
    a -> val   = x;
    a -> left  = NULL;
    a -> right = NULL;
    return a;
  }

term* lam(term* t)
  {
    term* a = new term();
	a -> type  = 1;
	a -> val   = 0;
	a -> left  = t;
	a -> right = NULL;
	return a;
  }

term* app(term* t1, term* t2)
  {
	term* a = new term();
	a -> type  = 2;
	a -> val   = 0;
	a -> left  = t1;
	a -> right = t2;
	return a;
  }


void printTerm (term* t){
	
	int a = t->type;
	
	switch(a){
		case 0: cout << t->val ;
		        break;
		case 1: cout << "(\\.";
		        printTerm(t->left);
		        cout << ")";
		        break;
		case 2: cout << "@(";
		        printTerm(t->left);
		        cout << ",";
		        printTerm(t->right);
		        cout <<")";
		        break;
		default:
		        return;
	}
	
}

term* copyTerm(term* t){
	switch(t->type){
		case 0: return var(t->val);
		case 1: return lam(copyTerm(t->left));
		case 2: return app(copyTerm(t->left), copyTerm(t->right));
	}
	cout << "nao devia chegar aqui!" << endl;
    return t;
}

void deleteTerm(term* t){
	switch(t->type){
		case 0: delete(t);
		        return;
		case 1: deleteTerm(t->left);
		        delete(t);
		        return;
		case 2: deleteTerm(t->left);
				deleteTerm(t->right);
				delete(t);
				return;
	}
	cout << "nao devia chegar aqui!" << endl;
    return;
}


//--------------------------------------------------------------------//


//----------- CLASSE PARA REPRESENTAR CONTEXTOS     ----------------- //


class ctx
{
  public:
    int    type;
    term*   arg;
    ctx*   next;
    
    ctx () {
		     type=0;
		     arg=NULL;
		     next=NULL;
		   }
};

ctx* empty()
  {
	return (new ctx());
  }

ctx* B(ctx* s)
  {
    ctx* a = new ctx();
	a -> type  = 1;
	a -> arg   = NULL;
	a -> next  = s;
	return a;
  }

ctx* R(term* t, ctx* s)
  {
    ctx* a = new ctx();
	a -> type  = 2;
	a -> arg   = t;
	a -> next  = s;
	return a;
  }

ctx* L(term* t, ctx* s)
  {
    ctx* a = new ctx();
	a -> type  = 3;
	a -> arg   = t;
	a -> next  = s;
	return a;
  }
  
void printCtx (ctx* s){
	
	int a = s->type;
	
	switch(a){
		case 0: cout << "[]" ;
		        break;
		case 1: cout << "B:";
		        printCtx(s->next);
		        break;
		case 2: cout << "(R ";
		        printTerm(s->arg);
		        cout << "):";
		        printCtx(s->next);
		        break;
		case 3: cout << "(L ";
		        printTerm(s->arg);
		        cout << "):";
		        printCtx(s->next);
		        break;
		default:
		        return;
	}
	
}

//--------------------------------------------------------------------//


// GLOBAL VARS

// find
term* t;
ctx*  c;
term* e = var(0);
int   a,b;
term* u;
term* w;
ctx*  y;
ctx*  z;

// lift
int   i,j;
term*  tl;
ctx*   cl;
int    al;
int    bl;
term*  ul;

term*  yl;
ctx*   zl;

// subs
int    k;
ctx*  cs;
int   as;
term* us;
term* vs;

term* zs;
ctx*  ys;

// combine
int   ac;
ctx*  zc;


// step counter

int step;


void printState(){
	
	cout << "----------------" << endl;
	
	cout << "t = ";
	printTerm(t);
	cout << endl;
	
	cout << "c = ";
	printCtx(c);
	cout << endl;
	
	//cout << "e = ";
	//printTerm(e);
	//cout << endl;
	
	cout << "----------------" << endl;
}

void printStateSubs(){
	
	cout << "----------------" << endl;

	cout << "k = " << k << endl;
	
	cout << "e = ";
	printTerm(e);
	cout << endl;
	
	cout << "t = ";
	printTerm(t);
	cout << endl;
	
	cout << "cs = ";
	printCtx(cs);
	cout << endl;
	
	
	cout << "----------------" << endl;
}



int main(){

   

   // length (cons 2 (cons 3 empty))
//   t = app(app(lam(app(lam(app(var(1),app(var(0),var(0)))),lam(app(var(1),app(var(0),var(0)))))),lam(lam(app(app(app(lam(lam(lam(app(app(var(2),var(1)),var(0))))),app(lam(app(var(0),lam(lam(lam(lam(var(0))))))),var(0))),lam(lam(var(0)))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(var(1),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))))),app(app(lam(lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),var(1)),var(0)))),lam(lam(app(var(1),app(var(1),var(0)))))),app(app(lam(lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),var(1)),var(0)))),lam(lam(app(var(1),app(var(1),app(var(1),var(0))))))),lam(lam(lam(var(1))))))) ;
   
   // fatorial 5
   t = app(app(lam(app(lam(app(var(1),app(var(0),var(0)))),lam(app(var(1),app(var(0),var(0)))))),lam(lam(app(app(app(lam(lam(lam(app(app(var(2),var(1)),var(0))))),app(lam(app(app(var(0),lam(lam(lam(var(0))))),lam(lam(var(1))))),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))),lam(lam(app(var(1),var(0))))),app(app(lam(lam(lam(lam(app(app(var(3),app(var(2),var(1))),var(0)))))),var(0)),app(var(1),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))))))),lam(lam(app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),var(0)))))))));

   // fatorial 6
   //t = app(app(lam(app(lam(app(var(1),app(var(0),var(0)))),lam(app(var(1),app(var(0),var(0)))))),lam(lam(app(app(app(lam(lam(lam(app(app(var(2),var(1)),var(0))))),app(lam(app(app(var(0),lam(lam(lam(var(0))))),lam(lam(var(1))))),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))),lam(lam(app(var(1),var(0))))),app(app(lam(lam(lam(lam(app(app(var(3),app(var(2),var(1))),var(0)))))),var(0)),app(var(1),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))))))),lam(lam(app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),var(0))))))))));

   // fatorial 7  (3.553.543 passos, +- 33 minutos, +- 4mb max)
   // t = app(app(lam(app(lam(app(var(1),app(var(0),var(0)))),lam(app(var(1),app(var(0),var(0)))))),lam(lam(app(app(app(lam(lam(lam(app(app(var(2),var(1)),var(0))))),app(lam(app(app(var(0),lam(lam(lam(var(0))))),lam(lam(var(1))))),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))),lam(lam(app(var(1),var(0))))),app(app(lam(lam(lam(lam(app(app(var(3),app(var(2),var(1))),var(0)))))),var(0)),app(var(1),app(lam(app(lam(app(var(0),lam(lam(var(1))))),app(app(var(0),lam(app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),app(lam(app(var(0),lam(lam(var(0))))),var(0))),app(lam(lam(lam(app(var(1),app(app(var(2),var(1)),var(0)))))),app(lam(app(var(0),lam(lam(var(0))))),var(0)))))),app(app(lam(lam(lam(app(app(var(0),var(2)),var(1))))),lam(lam(var(0)))),lam(lam(var(0))))))),var(0)))))))),lam(lam(app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),app(var(1),var(0)))))))))));


   c  = empty();
   cl = empty();
   cs = empty();
   step = 0;


   // ---------------- MAIN CODE ------------------ //

   run:        goto findDown;
   
   findEnd:    k  = 0;
               goto subsDown;
   
   subsEnd:    deleteTerm(e);
               goto combineUp;
   
   combineEnd: step ++;
               goto run;
   
   end:        cout << "Passos: " << step << endl;
               cout << "Termo final: ";
               printTerm(t);
               cout << endl;
	           return 0;
   
   // ---------------- SEARCH REDEX ------------------ //
   
   findDown:
		a = t->type;
		switch(a){
		  case 0: goto findUp;
		  
		  case 1: w = t;
		          t = t->left;
		          c = B(c);
		          delete(w);
		          goto findDown;
		          
		  case 2: w = t;
		          u = t->left;
		          b = u->type;
		          
		          switch(b){
					
					case 1:  e = t->right;
					         t = u->left;
					         delete(u);
					         delete(w);
					         goto findEnd;
					         
					default: c = R(t->right,c);
					         t = t->left;
					         delete(w);
					         goto findDown;
					         
				  } // switch(b) end
		} // switch(a) end
		
    findUp:
		a = c->type;
		switch(a){
			case 0: goto end;
			
			case 1: y = c;
			        t = lam(t);
			        c = c->next;
			        delete(y);
			        goto findUp;
			        
			case 2: y = c;
			        u = t;
			        t = c->arg;
			        c = L(u,c->next);
			        delete(y);
			        goto findDown;
			        
			case 3: y = c;
			        t = app(c->arg,t);
			        c = c->next;
			        delete(y);
			        goto findUp;
		} // switch(a) end
  
  
  // ---------------- SUBSTITUTION  ------------------ //
  
    subsDown:
		
        as = t->type;
        
        switch(as){
			case 0: b = t->val;
			        if (b<k){        // b < k
						
					  goto subsUp;
					  
					}else if(b==k){  // b = k
					  
					  
					  i  = 0;
					  j  = k;
					  tl = copyTerm(e);
					  goto liftDown;
					  
					  liftEnd: delete(t);
					           t  = tl;
					           goto subsUp;
					  					    
					}else{           // b > k
						
					  t->val = b-1;
					  goto subsUp;
					  
					}
			case 1: zs = t;
			        cs = B(cs);
					t = t->left;
					k = k+1;
					delete (zs);
					goto subsDown;
					
			case 2: zs = t;
			        cs = R(t->right,cs);
					t = t->left;
					delete (zs);
					goto subsDown;
		} // switch(as) end
		
    subsUp:
		
        as = cs->type;
        switch(as){
			case 0: goto subsEnd;
			case 1: ys = cs;
			        t  = lam(t);
					cs = cs->next;
					k  = k - 1;
					delete(ys);
					goto subsUp;
					
			case 2: ys = cs;
			        us = t;
					t  = cs->arg;
					cs = L(us,cs->next);
					delete(ys);
					goto subsDown;
					
			case 3: ys = cs;
			        t  = app(cs->arg,t);
					cs = cs->next;
					delete(ys);
					goto subsUp;
					
		} // switch(as) end
		


// ---------------- LIFTING  ------------------ //
 
     liftDown:
     
		al = tl->type;

		switch(al){

			case 0: bl = tl->val;
			
					if (bl >= i){
						tl->val = bl+j;
						goto liftUp;
					}else{
						goto liftUp;
					}

			case 1: yl = tl;
			        tl = tl->left;
					cl = B(cl);
					i  = i + 1;
					delete(yl);
					goto liftDown;

			case 2: yl = tl;
			        cl = R(tl->right,cl);
					tl = tl->left;
					delete(yl);
					goto liftDown;
					
		} // switch(al) end


     liftUp:
     
		al = cl->type;
		
		switch(al){
			
			case 0: goto liftEnd;
			
			case 1: zl = cl;
			        tl = lam(tl);
					cl = cl->next;
					i  = i-1;
					delete(zl);
					goto liftUp;
					
			case 2: zl = cl;
			        ul = tl;
					tl = cl->arg;
					cl = L(ul,cl->next);
					delete(zl);
					goto liftDown;
					
			case 3: zl = cl;
			        tl = app(cl->arg,tl);
					cl = cl->next;
					delete(zl);
					goto liftUp;
		} // switch(al) end



// ---------------- COMBINE  ------------------ //

     combineUp:
        
        
        ac = c->type;

        switch(ac){
			case 0: goto combineEnd;
			
			case 1: zc = c;
			        t  = lam(t);
					c  = c->next;
					delete(zc);
					goto combineUp;
					
			case 2: zc = c;
			        t = app(t,c->arg);
					c = c->next;
					delete(zc);
					goto combineUp;
					
			case 3: zc = c;
			        t  = app(c->arg,t);
					c  = c->next;
					delete(zc);
					goto combineUp;
		} // switch(ac) end


// ---------------------------------------- //

 
	
	
	
	return 0;
}