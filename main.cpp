#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
int gcd(int x, int y){
	if(y==0)
		return x;
	return gcd(y, x%y);
}
struct fraction {
	int a, b; //form of a/b
	string s;
	fraction(int x, int y, string ss){
		a = x;
		b = y;
		s = ss;
	}
	void normalize(){
		int m = gcd(a,b);
		a /= m;
		b /= m;
	}
	bool nonzero(){
		return a!=0;
	}
	fraction operator+(fraction f1){
		int fa = f1.a * b + f1.b * a;
		int fb = f1.b * b;
		string fs = "(" + s + "+" + f1.s + ")";
		fraction f = fraction(fa, fb, fs);
		f.normalize();
		return f;
	}
	fraction operator-(fraction f1){
		int fa = f1.b * a - f1.a * b;
		int fb = f1.b * b;
		string fs = "(" + s + "-" + f1.s + ")";
		fraction f = fraction(fa, fb, fs);
		f.normalize();
		return f;
	}
	fraction operator*(fraction f1){
		int fa = f1.a * a;
		int fb = f1.b * b;
		string fs = "(" + s + "*" + f1.s + ")";
		fraction f = fraction(fa, fb, fs);
		f.normalize();
		return f;
	}
	fraction operator/(fraction f1){
		int fa = a * f1.b;
		int fb = b * f1.a;
		string fs = "(" + s + "/" + f1.s + ")";
		fraction f = fraction(fa, fb, fs);
		f.normalize();
		return f;
	}
	bool operator==(fraction f1){
		if(a == f1.a && b == f1.b)
			return true;
		else
			return false;
	}
	void print(){
		if(b == 1)
			printf("%d ", a);
		else
			printf("%d/%d ", a, b);
	}
};
struct frac_list{
	int count;
	vector<fraction> l;
	frac_list(){
		count = 0;
	}
	void push(fraction x){
		l.push_back(x);
		count++;
	}
	void pop(int idx){
		l.erase(l.begin() + idx);
		count--;
	}
	void print(){
		for(int i=0 ; i<count ; i++){
			l[i].print();
		}
		printf("\n");
	}
	fraction get(int idx){
		return l[idx];
	}
};
queue<frac_list> solver;
int number_of_solutions, n, a;
void add_and_push(frac_list fl, fraction f){
	fl.push(f);
	solver.push(fl);
}
void do_six_op(frac_list fl, int idx1, int idx2){
	fraction a = fl.get(idx1);
	fraction b = fl.get(idx2);
	fl.pop(idx2);
	fl.pop(idx1);
	
	fraction f = a + b;
	add_and_push(fl, f);
	f = a - b;
	add_and_push(fl, f);
	f = b - a;
	add_and_push(fl, f);
	f = a * b;
	add_and_push(fl, f);
	if(b.nonzero()){
		f = a / b;
		add_and_push(fl, f);
	}
	if(a.nonzero()){
		f = b / a;
		add_and_push(fl, f);
	}
}
void solve(){
	while(!solver.empty()){
		frac_list fl = solver.front();
		//fl.print();
		solver.pop();
		if(fl.count == 1){
			if(fl.get(0) == fraction(24, 1, "")){
				number_of_solutions++;
				cout << fl.get(0).s << "\n";
			}
		}
		else
		{
			for(int i=0 ; i<fl.count ; i++){
				for(int j=i+1 ; j<fl.count ; j++){
					do_six_op(fl,i,j);
				}
			}
		}
	}
	
}
int main(int argc, char* argv[]) {
	scanf("%d", &n);
	frac_list init_set;
	for(int i=0 ; i<n ; i++){
		scanf("%d", &a);
		fraction f = fraction(a, 1, to_string(a));
		init_set.push(f);
	}
	solver.push(init_set);
	solve();
	printf("total number of solutions: %d\n", number_of_solutions);
	return 0;
}