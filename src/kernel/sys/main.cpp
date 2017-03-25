class a{
private:
	int b;
	int c;
public:
	void set(int b, int c){this->b=b; this->c=c;};
	void add(){b+=c;}
};

int main(void){
	int hoge;
	a a1;
	a1.set(1,2);
	a1.add();
}


