#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

struct node
{
	int attribute;
	bool isleaf;
	node *yes;
	node *no;
	node *dontknow;
};

//democrat -> 0
//republican -> 1
int choosebestattribute(vector< vector<string> > s);
int choosebestattribute_entropy(vector< vector<string> > s);
int height(node *n,int h);
int max(int x, int y, int z);
int predict(node *n, vector<string> v);
int size(node *n);


node *growtree(vector< vector<string> > s, int max_size)
{	
	if(max_size <= 0)
	{
		node *leaf = new node;
		leaf -> yes = NULL;
		leaf -> no = NULL;
		leaf -> dontknow = NULL;
		leaf -> isleaf = true;

		int democrat = 0;
		int republican = 0;
		for(int i=0;i<s.size();i++)
		{
			if(s[i][0] == "democrat")
				democrat++;
			else
				republican++;
		}

		if(democrat > republican)
			leaf -> attribute = 0;
		else
			leaf -> attribute = 1;

		return leaf;
	}
	if(s.size() <= 0)
		{
		 //cout<<"returninig NULL!!"<<endl;
		 //return NULL;
		 node *leaf = new node;
		leaf -> attribute = 1;
		leaf -> yes = NULL;
		leaf -> no = NULL;
		leaf -> dontknow = NULL;
		leaf -> isleaf = true;

		return leaf;
		}
	string result;
	result = s[0][0];
	int i=0;
	for(i=0;i<s.size();i++)
	{	
		//cout<<s[i][0]<<endl;
		if(s[i][0] != result)
			break;
	}
	//cout<<s.size()<<" "<<i<<endl;
	if(i == s.size())
	{
		node *leaf = new node;
		(result=="democrat")?leaf -> attribute = 0: leaf -> attribute = 1;
		leaf -> yes = NULL;
		leaf -> no = NULL;
		leaf -> dontknow = NULL;
		leaf -> isleaf = true;

		return leaf;
	}

	//else if not all are same
	//cout<<"here"<<endl;
	int bestattribute = choosebestattribute_entropy(s);
	//cout<<"best attribute = "<<bestattribute<<endl;
	vector< vector<string> > s0;
	vector< vector<string> > s1;
	vector< vector<string> > s2;

	for(int i=0;i<s.size();i++)
	{
		if(s[i][bestattribute] == "n")
			s0.push_back(s[i]);
		else if (s[i][bestattribute] == "y")
			s1.push_back(s[i]);
		else if (s[i][bestattribute] == "?")
			s2.push_back(s[i]);

	}
	/*
	cout<<s0.size()<<endl;
	cout<<s1.size()<<endl;
	cout<<s2.size()<<endl;
	cout<<s.size()<<endl;
	*/

	node *root = new node;
	root -> attribute = bestattribute;
	root -> no = growtree(s0, (max_size-1));
	root -> yes = growtree(s1, (max_size-1));
	root -> dontknow = growtree(s2, (max_size-5));
	root -> isleaf = false;

	return root;


}

float log_2(float n)
{
	if(n==0)
		{//cout<<"gotcha....................\n";
			return 0.0;}
	else
		return log(n)/log(2);
}

float entropy(vector< vector<string> > s)
{
	if(s.size()==0)
		return 0;
	int democrat = 0;
	int republican = 0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i][0] == "democrat")
			democrat++;
		else if (s[i][0] == "republican")
			republican++;
	}
	int total = s.size();

	float e = -(((float)democrat/(float)total)*log_2((float)democrat/(float)(float)total))
			  -(((float)republican/(float)total)*log_2((float)republican/(float)total));

	return e;
}

//will return the number of the best attribute
// not the index!!! it will start from 1
int choosebestattribute_entropy(vector< vector<string> > s)
{
	float information[17];//this will have entropy of all the attributes
	//highest will be chosen
	float h_s = entropy(s);

	for(int z=1; z<=16; z++)
	{
		vector< vector<string> > s0;
	    vector< vector<string> > s1;
	    vector< vector<string> > s2;


	    //s0 <- (x,y) s.t. x_z == n
	    //s1 <- (x,y) s.t. x_z == y
	    //s1 <- (x,y) s.t. x_z == ?
	    for(int j=0; j<s.size(); j++)
	    {
	    	if(s[j][z] == "n")
	    		s0.push_back(s[j]);
	    	else if (s[j][z] == "y")
	    		s1.push_back(s[j]);
	    	else if (s[j][z] == "?")
	    		s2.push_back(s[j]);
	    }
	    float s0_size = (float)s0.size();
	    float s1_size = (float)s1.size();
		float s2_size = (float)s2.size();
		float s_size = (float)s.size();


	   information[z] = h_s -((s0_size/s_size)*entropy(s0))-((s1_size/s_size)*entropy(s1))-((s2_size/s_size)*entropy(s2));

	   //cout<<s0.size()<<" "<<s1.size()<<" "<<s2.size()<<endl;
	   	if(((s0.size()==0)&&(s1.size()==0))||((s1.size()==0)&&(s2.size()==0))||((s2.size()==0)&&(s0.size()==0)))
	   		information[z]=-1000000;
	}

	int max = -1;
	for(int i=1;i<=16;i++)
		{	
			//cout<<information[i]<<endl;
			if(information[i] > information[max])
			max = i;
		}
		//cout<<"max info = "<<information[max]<<endl;
		//if(max==-1)
		//	cout<<"that should not have happened \n";
	return max;
}



//will return the number of the best attribute
// not the index!!! it will start from 1
int choosebestattribute(vector< vector<string> > s)
{
	int error[17];//will have the errors of all the 16 attributes
	//let the first index be emptty



	for(int z=1;z<=16;z++)
	{
		vector< vector<string> > s0;
	    vector< vector<string> > s1;
	    vector< vector<string> > s2;


	    //s0 <- (x,y) s.t. x_z == n
	    //s1 <- (x,y) s.t. x_z == y
	    //s1 <- (x,y) s.t. x_z == ?
	    for(int j=0; j<s.size(); j++)
	    {
	    	if(s[j][z] == "n")
	    		s0.push_back(s[j]);
	    	else if (s[j][z] == "y")
	    		s1.push_back(s[j]);
	    	else if (s[j][z] == "?")
	    		s2.push_back(s[j]);
	    }
	    //cout<<s0.size()<<endl;
	    //cout<<s1.size()<<endl;
	    //cout<<s2.size()<<endl;

	    //y0 <- most common value of y in s0;
	    //y1 <- most common value of y in s1;
	    //y2 <- most common value of y in s2;

	    string y0,y1,y2;
	    int democrat = 0;
	    int republican = 0;
	    for(int i=0;i<s0.size();i++)
	    {
	    	if(s0[i][0] == "democrat")
	    		democrat++;
	    	else if (s0[i][0]=="republican")
	    		republican++;
	    }

	    
	    (democrat>republican)?(y0="democrat"):(y0="republican");

		democrat = 0;
	    republican = 0;
	    for(int i=0;i<s1.size();i++)
	    {
	    	if(s1[i][0] == "democrat")
	    		democrat++;
	    	else if (s1[i][0]=="republican")
	    		republican++;
	    }

	    
	    (democrat>republican)?(y1="democrat"):(y1="republican");


		democrat = 0;
	    republican = 0;
	    for(int i=0;i<s2.size();i++)
	    {
	    	if(s2[i][0] == "democrat")
	    		democrat++;
	    	else if (s2[i][0]=="republican")
	    		republican++;
	    }

	   
	    (democrat>republican)?(y2="democrat"):(y2="republican");

	    int j0,j1,j2;
	    j0=0;j1=0;j2=0;
	    //j0 <- no. of examples with y != y0
	    //j1 <- no. of examples with y != y1;
	    //j2 <- no. of examples with y != y2;

	    for(int i=0;i<s0.size();i++)
	    	if(s0[i][0] != y0)
	    		j0++;
	    
	    for(int i=0;i<s1.size();i++)
	    	if(s1[i][0] != y1)
	    		j1++;

	    for(int i=0;i<s2.size();i++)
	    	if(s2[i][0] != y2)
	    		j2++;

	    int j = j0 + j1 + j2;
	    if(((s0.size()==0)&&(s1.size()==0))||((s1.size()==0)&&(s2.size()==0))||((s2.size()==0)&&(s0.size()==0)))
	    	j+=10000000;
	    error[z] = j;
	    //cout<<"error = "<<j<<endl;
	    //cout<<y0<<" "<<y1<<" "<<y2<<endl;
	}
	//cout<<"xxxxxxxxxx  "<<s.size()<<endl;
	int min_error = error[1];
	int min_index = 1;
	for(int i=1;i<=16;i++)
		if(error[i] < min_error)
			min_index = i;

	return min_index;

}


vector< vector<string> > read(string filename)
{
	string line;
	vector< vector<string> > v;
	fstream f;f.open(filename);
	while(getline(f,line))
	{
		//cout<<line<<endl;
		//std::vector<std::string> x = split(line , ',');
		//cout<<x.size()<<endl;
		vector<string> temp;
		int begin=0;int end=0;
		char delimilter = ',';
		for(end=0;end<line.length();end++)
		{
			if(line[end] != delimilter)
				continue;

			else
			{
				temp.push_back(line.substr(begin,end-begin));
				begin = end+1;
			}

		}
		temp.push_back(line.substr(begin,end-begin));
     	// hope that temp has the tokens
		/*for(int i=0;i<temp.size();i++)
		{
			cout<<temp[i]<<" ";
		}
		cout<<endl;
*/
		v.push_back(temp);
	}

	f.close();

	return v;
}


int main()
{
	

	/*
	for(int i=0;i<v.size();i++)
	{
		vector<string> str = v[i];
		for(int j=0;j<str.size();j++)
		{
			cout<<str[j]<<" ";
		}
		cout<<endl;
	}
	*/
	vector< vector<string> > v = read("data/test.data");
	//cout<<"height of the tree = "<<height(root,0)<<endl;

	vector< vector<string> > v2 = read("data/train.data");
	vector< vector<string> > v3 = read("data/validation.data");
	fstream f1; f1.open("graphs/q1btrain.txt");
	fstream f2; f2.open("graphs/q1bvalidation.txt");
	fstream f3; f3.open("graphs/q1btest.txt");

//		cout<<choosebestattribute_entropy(v)<<" "<<choosebestattribute_entropy(v2)<<endl;
//return 0;

	//for(int zz=9;zz>=0;zz--)
	//{
	node *root = new node;
	root = growtree(v2, 999);
	float correct = 0;float total=0;
	for(int i=0;i<v.size();i++)
	{
		int pred = predict(root, v[i]);
		//cout<<pred<<" "<<v2[i][0]<<endl;
		total++;

		if(((pred==0)&&(v[i][0]=="democrat")) || ((pred==1)&&(v[i][0]=="republican")))
			correct++;
	}

	cout<<"correct = "<<correct<<endl;
	float accuracy = ((float)correct/(float)total) * 100;
	cout<<"accuracy = "<<accuracy<<" %"<<endl;
	cout<<"height = "<<height(root,0)<<endl;
	cout<<"size = "<<size(root)<<endl;
	f3<<size(root)<<" "<<accuracy<<endl;
	//cout<<"expected height = "<<zz<<" and actual size = "<<size(root)<<endl;
	cout<<"/********************************/\n";
	//}
	//cout<<choosebestattribute_entropy(v2);
	f3.close();
	return 0;

}

//give it an initial height = 0
int height(node *n, int h)
{
	if(n == NULL)
		return h;

	else
		return max(height(n->no,h+1),height(n->yes,h+1),height(n->dontknow,h+1));
}

int size(node *n)
{
	if(n==NULL)
		return 0;
	else
		return 1+size(n->no)+size(n->yes)+size(n->dontknow);
}

int max(int x, int y, int z)
{
	int max = x;
	if(y > max)
		max=y;
	if(x > max)
		max=z;

	return max;
}

//predict 0 if democrat and 1 if republican
int predict(node *n, vector<string> v)
{
	if(n==NULL)
		cout<<"NULL\n";
	if(n->isleaf)
		{//cout<<"LEAF";cout<<n->attribute;
	return n->attribute;}

	//cout<<n->attribute<<" "<<v[n->attribute]<<endl;
	if(v[n->attribute]=="n")
		{//cout<<"no"<<endl;
			return predict(n -> no, v);
			}
	if(v[n->attribute]=="y")
		{//cout<<"yes"<<endl;
			return predict(n -> yes, v);
			}
	if(v[n->attribute]=="?")
		{//cout<<"dnktknow"<<endl;
			return predict(n -> dontknow, v);
			}
	
	cout<<"how did it come here!!!!!!!!!!!!!!\n";
		//return -1;
}






