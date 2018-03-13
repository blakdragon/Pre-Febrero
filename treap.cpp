#include <bits/stdc++.h>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie
using namespace std;

struct treap{

	int x,y,valor;
	treap *l,*r;

	treap(){}
	treap(int X , int Y = rand() ): x(X) , y(Y) , valor(1), l(NULL) , r(NULL) {}
	
};
typedef treap* ptreap;


int getVal(ptreap p){
	return p?p->valor:0;
}

void split(ptreap raiz, ptreap &izq , ptreap &der,int val){
	if(!raiz){
		izq = der = NULL;
		return;	
	}
	if(raiz -> x <= val ){
		izq = raiz;
		split(raiz -> r , raiz -> r , der , val);
		izq -> valor = getVal(izq -> l ) + getVal(izq -> r ) + 1;
	} else {
		der = raiz;
		split(raiz -> l , izq , raiz -> l , val);
		der -> valor = getVal(der -> l ) + getVal(der -> r ) + 1;
	}

}

void merge(ptreap izq , ptreap der, ptreap &raiz){
	if(!izq || !der ){
		if(izq) raiz = izq;
		else raiz = der;
		return;
	}
	if(izq -> y > der -> y){
		raiz = izq;
		merge(izq -> r , der , izq -> r);
	} else {
		raiz = der;		
		merge(izq, der -> l , der -> l);
	}
	raiz -> valor = getVal(raiz -> l) + getVal(raiz -> r ) + 1;

}

void insert(ptreap &raiz, ptreap elem){
	if(!raiz){
		raiz = elem;
		return;
	} 
	if(elem-> y > raiz -> y){		
		ptreap I,D;
		split(raiz , elem -> l , elem -> r , elem->x);		
		raiz = elem;	
	} else{
		if(elem -> x <= raiz -> x) insert(raiz -> l , elem);
		else insert(raiz -> r , elem);		
	}
	raiz -> valor = getVal(raiz -> l) + getVal(raiz -> r ) + 1;
}

void erase(ptreap &raiz, int x){
	if(!raiz) return;
	if(raiz -> x == x){
		merge( raiz -> l , raiz -> r , raiz );
		return;
	} else {
		erase( x  < raiz -> x? raiz -> l : raiz -> r  , x);		
	}
	raiz -> valor = getVal(raiz -> l) + getVal(raiz -> r ) + 1;
}	

bool dentro(ptreap t , int x){
	while( t && x != t -> x)
		t = x < t -> x ? t -> l : t -> r;
	return t;
}

int kth(ptreap t , int k, int acum = 0) {
	int pos = getVal(t->l) + 1 + acum;
	if(pos == k) return t -> x;
	if(pos < k) return kth(t -> r , k , pos);
	return kth(t-> l , k , acum);
}

int cuenta(ptreap t , int x){
	if(!t) return 0;
	if(t -> x == x ) return getVal(t -> l);
	if(x < t -> x) return cuenta(t -> l , x);
	return cuenta(t -> r,x ) + getVal(t -> l) + 1;
}

int main(){

	srand(time(NULL));
	optimizar_io(0);

	ptreap t = NULL;
	int N,x;
	char tipo;

	cin >> N;
	for(int i = 0 ; i < N ; i ++){
		cin >> tipo >> x;
		if(tipo == 'I'){			
			if(!dentro(t,x)) 
				insert(t,new treap(x));
		} else if(tipo =='D'){			
			erase(t,x);
		} else if(tipo == 'K'){			
			if(x > getVal(t)) cout << "invalid\n";
			else cout << kth(t,x) << '\n';
		} else {			
			cout << cuenta(t,x) << '\n';	
		}
	}

	return 0;
}