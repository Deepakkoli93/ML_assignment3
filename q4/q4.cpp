#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

struct cpt
{
	float d[1][2];
	float i[1][2];
	float g[4][3];
	float s[2][2];
	float l[3][2];

	cpt()
	{
		//cout<<"contructor called";
		for(int ii=0;ii<1;ii++)
			for(int j=0;j<2;j++)
				d[ii][j] = 0;

		for(int ii=0;ii<1;ii++)
			for(int j=0;j<2;j++)
				i[ii][j] = 0;

		for(int ii=0;ii<4;ii++)
			for(int j=0;j<3;j++)
				g[ii][j] = 0;
		
		for(int ii=0;ii<2;ii++)
			for(int j=0;j<2;j++)
				s[ii][j] = 0;
		
		for(int ii=0;ii<3;ii++)
			for(int j=0;j<2;j++)
				l[ii][j] = 0;

	}
};

vector< vector<float> >read(string filename)
{
	string line;
	vector< vector<float> > v;
	fstream f;f.open(filename);
	while(getline(f,line))
	{	//cout<<line;
		vector<float> temp;
		for(int i=0;i<=8;i++)
		{
			if(i%2==0)
			{
				if(line[i]!='?')
					temp.push_back((int)(line[i]-'0'));
					//cout<<" "<<line[i];
				else
					temp.push_back(-1);
			}	
		
		}
		//cout<<endl;
		
		v.push_back(temp);

	}

	return v;
}

cpt fillcpt(vector< vector<float> > v, cpt oldpr)
{
	cpt pr ;


	//filling difficulty table
	for(int i=0;i<v.size();i++)
		{

			if(v[i][0]==0)
				pr.d[0][0]++;
			else if(v[i][0]==1)
				pr.d[0][1]++;
			else
			{
				pr.d[0][0] += oldpr.d[0][0] ;
				pr.d[0][1] += oldpr.d[0][1] ;

			}
		}
	int l = v.size();
	pr.d[0][0] = pr.d[0][0]/(float)l;
	pr.d[0][1] = pr.d[0][1]/(float)l;
	
	//filling intelligence table
	for(int i=0;i<v.size();i++)
		{
			if(v[i][1]==0)
				pr.i[0][0]++;
			else if(v[i][1]==1)
				pr.i[0][1]++;
			else
			{
				pr.i[0][0] += oldpr.i[0][0];
				pr.i[0][1] += oldpr.i[0][1];
			}
		}
	pr.i[0][0] = pr.i[0][0]/(float)l;
	pr.i[0][1] = pr.i[0][1]/(float)l;

	//filling grade table
	//D,I,G,S,L
	int i0d0 = 0;
	int i0d1 = 0;
	int i1d0 = 0;
	int i1d1 = 0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i][1]==0 && v[i][0]==0)  //I=0 D=0
		{	
			i0d0++;
			if(v[i][2]==1)
				pr.g[0][0]++;
			else if (v[i][2]==2)
				pr.g[0][1]++;
			else if (v[i][2]==3)
				pr.g[0][2]++;
			else
			{
				pr.g[0][0] += oldpr.g[0][0];
				pr.g[0][1] += oldpr.g[0][1];
				pr.g[0][2] += oldpr.g[0][2];
			}
		}

		else if(v[i][1]==0 && v[i][0]==1) //I=0 D=1
		{
			i0d1++;
			if(v[i][2]==1)
				pr.g[1][0]++;
			else if (v[i][2]==2)
				pr.g[1][1]++;
			else if (v[i][2]==3)
				pr.g[1][2]++;	
			else 
			{
				pr.g[1][0] += oldpr.g[1][0];
				pr.g[1][1] += oldpr.g[1][1];
				pr.g[1][2] += oldpr.g[1][2];

			}		
		}

		else if(v[i][1]==1 && v[i][0]==0) //I=1 D=0
		{
			i1d0++;
			if(v[i][2]==1)
				pr.g[2][0]++;
			else if (v[i][2]==2)
				pr.g[2][1]++;
			else if (v[i][2]==3)
				pr.g[2][2]++;
			else 
			{
				pr.g[2][0] += oldpr.g[2][0];
				pr.g[2][1] += oldpr.g[2][1];
				pr.g[2][2] += oldpr.g[2][2];

			}
		}


		else if(v[i][1]==1 && v[i][0]==1) //I=1 D=1
		{
			i1d1++;
			if(v[i][2]==1)
				pr.g[3][0]++;
			else if (v[i][2]==2)
				pr.g[3][1]++;
			else if (v[i][2]==3)
				pr.g[3][2]++;
			else 
			{
				pr.g[3][0] += oldpr.g[3][0];
				pr.g[3][1] += oldpr.g[3][1];
				pr.g[3][2] += oldpr.g[3][2];

			}
		}
		
	}
	//cout<<"i1d1 = "<<i1d1<<endl;
	for(int i=0;i<3;i++)
		pr.g[0][i] = pr.g[0][i]/(float)i0d0;
	for(int i=0;i<3;i++)
		pr.g[1][i] = pr.g[1][i]/(float)i0d1;
	for(int i=0;i<3;i++)
		pr.g[2][i] = pr.g[2][i]/(float)i1d0;
	for(int i=0;i<3;i++)
		pr.g[3][i] = pr.g[3][i]/(float)i1d1;


	//filling the sat table
	//D,I,G,S,L
	int i0 = 0;int i1= 0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i][1] == 0)
		{
			i0++;
			if(v[i][3] == 0)
				pr.s[0][0]++;
			else if (v[i][3] == 1)
				pr.s[0][1]++;
			else
			{
				pr.s[0][0] += oldpr.s[0][0];
				pr.s[0][1] += oldpr.s[0][1];
			}
		}

		else if (v[i][1] == 1)
		{
			i1++;
			if(v[i][3] == 0)
				pr.s[1][0]++;
			else if (v[i][3] == 1)
				pr.s[1][1]++;
			else
			{
				pr.s[1][0] += oldpr.s[1][0];
				pr.s[1][1] += oldpr.s[1][1];
			}
		}
	}

	for(int i=0;i<2;i++)
		pr.s[0][i] = pr.s[0][i]/(float)i0;
	for(int i=0;i<2;i++)
		pr.s[1][i] = pr.s[1][i]/(float)i1;


	//filling the letter table 
	// D,I,G,S,L
	int g1=0; int g2=0; int g3=0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i][2]==1)
		{
			g1++;
			if(v[i][4]==0)
				pr.l[0][0]++;
			else if (v[i][4]==1)
				pr.l[0][1]++;
			else
			{
				pr.l[0][0] += oldpr.l[0][0];
				pr.l[0][1] += oldpr.l[0][1];
			}
		}

		else if (v[i][2]==2)
		{
			g2++;
			if(v[i][4]==0)
				pr.l[1][0]++;
			else if (v[i][4]==1)
				pr.l[1][1]++;
			else
			{
				pr.l[1][0] += oldpr.l[1][0];
				pr.l[1][1] += oldpr.l[1][1];
			}
		}

		else if (v[i][2]==3)
		{
			g3++;
			if(v[i][4]==0)
				pr.l[2][0]++;
			else if (v[i][4]==1)
				pr.l[2][1]++;
			else
			{
				pr.l[2][0] += oldpr.l[2][0];
				pr.l[2][1] += oldpr.l[2][1];
			}
		}
	}

	for(int i=0;i<2;i++)
		pr.l[0][i] = pr.l[0][i]/(float)g1;
	for(int i=0;i<2;i++)
		pr.l[1][i] = pr.l[1][i]/(float)g2;
	for(int i=0;i<2;i++)
		pr.l[2][i] = pr.l[2][i]/(float)g3;



return pr;
}

void printcpt(cpt pr)
{
	cout<<"\nDifficulty\n";
	cout<<pr.d[0][0]<<" "<<pr.d[0][1]<<endl;

	cout<<"\n\nIntelligence\n";
	cout<<pr.i[0][0]<<" "<<pr.i[0][1]<<endl;

	cout<<"\n\nGrade\n";
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
			cout<<pr.g[i][j]<<" ";
		cout<<endl;
	}

	cout<<"\n\nSAT\n";
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
			cout<<pr.s[i][j]<<" ";
		cout<<endl;
	}

	cout<<"\n\nLetter\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<2;j++)
			cout<<pr.l[i][j]<<" ";
		cout<<endl;
	}

}

vector< vector<float> > fillmissingvalues(vector< vector<float> > v, cpt pr, vector< pair<int,int> > missing)
{
	//D,I,G,S,L
	for(int i=0;i<missing.size();i++)
	{
		// filling it with the prob of being "one"
		// same for grade also

		//filling difficulty
		if(missing[i].second == 0)
			v[missing[i].first][missing[i].second] = pr.d[0][1];

		//filling intelligence
		else if (missing[i].second == 1)
			v[missing[i].first][missing[i].second] = pr.i[0][1];

		//filling grade
		else if (missing[i].second == 2)
		{	
			int ii = v[missing[i].first][1];
			int dd = v[missing[i].first][0];
			if(ii==0 && dd==0)
				v[missing[i].first][2] = pr.g[0][0]; //i=0 d=0
			else if (ii==0 && dd==1)
				v[missing[i].first][2] = pr.g[1][0]; // i=0 d=1
			else if (ii==1 && dd==0)
				v[missing[i].first][2] = pr.g[2][0]; // i=1 d=0
			else if (ii==1 && dd==1)
				v[missing[i].first][2] = pr.g[3][0]; // i=1 d=1
		}

		//filling SAT
		else if (missing[i].second == 3)
		{
			if(v[missing[i].first][1] == 0) // i=0
				v[missing[i].first][3] = pr.s[0][1];

			else if(v[missing[i].first][1] == 1) // i=1
				v[missing[i].first][3] = pr.s[0][1];
		}

		//filling letter
		else if (missing[i].second == 4)
		{
			int gg = v[missing[i].first][2]; // whats the value of grade?
			if(gg == 1)
				v[missing[i].first][4] = pr.l[0][1];
			else if (gg == 2)
				v[missing[i].first][4] = pr.l[1][1];
			else if (gg==3)
				v[missing[i].first][4] = pr.l[2][1];
		}

	}

	return v;
}

vector< pair<int ,int> > findmissingindices(vector< vector<float> > v)
{
	vector< pair<int,int> > indices;
	for(int i=0;i<v.size();i++)
	{
		for(int j=0;j<5;j++)
			if(v[i][j] == -1)
				{
					indices.push_back(make_pair(i,j));
					break;
				}
	}

	return indices;
}

float difference(cpt pr1, cpt pr2)
{
	float error = 0;
	for(int i=0;i<2;i++)
		error += pow((pr1.d[0][i] - pr2.d[0][i]), 2);

	for(int i=0;i<2;i++)
		error += pow((pr1.i[0][1] - pr2.i[0][i]), 2);

	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++)
			error += pow((pr1.g[i][j] - pr2.g[i][j]), 2);

	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			error += pow((pr1.s[i][j] - pr1.s[i][j]), 2);

	for(int i=0;i<3;i++)
		for(int j=0;j<2;j++)
			error += pow((pr1.l[i][j] - pr2.l[i][j]), 2);

	return error;
}

float log_2(float n)
{
	return (log(n)/log(2.713));
}

float loglikelihood(vector< vector<float > >v, cpt pr)
{	
	//D,I,G,S,L
	float ll = 0; int ii; int dd;
	for(int i=0;i<v.size(); i++)
	{
		ll = ll + log(pr.d[0][ (int)v[i][0] ]) + log(pr.i[0][ (int)v[i][1] ]) + log(pr.s[ (int)v[i][1] ][ (int)v[i][3] ])
				+ log(pr.l[ (int)v[i][2]-1 ][ (int)v[i][4] ]);
		ii = (int)v[i][1]; dd = (int)v[i][0];
		if(ii==0 && dd==0)
			ll+= log(pr.g[0][ (int)v[i][2]-1 ]);
		else if (ii==0 && dd==1)
			ll+= log(pr.g[1][ (int)v[i][2]-1 ]);
		else if (ii==1 && dd==0)
			ll+= log(pr.g[2][ (int)v[i][2]-1 ]);
		else if (ii==1 && dd==1)
			ll+= log(pr.g[2][ (int)v[i][2]-1 ]);		
	}

	return ll;
}

int main()
{
	vector< vector<float> > v,test;

	vector<string> names;
	names.push_back("data/train-0.data");
	names.push_back("data/train-5.data");
	names.push_back("data/train-10.data");
	names.push_back("data/train-15.data");
	names.push_back("data/train-20.data");
	names.push_back("data/train-25.data");
	
	fstream f; f.open("ll_graph.txt");

	test = read("data/test.data");
	cpt init_cpt;
	cout<<"log likelihood of test data using fully observed data is = "<<loglikelihood(test,fillcpt(read("data/train-0.data"),init_cpt));
	cpt pr,oldpr;
	for(int i=0;i<6;i++)
	{
		v = read(names[i]);
		

		vector< pair<int,int> > indices = findmissingindices(v);
		vector< vector<float> > v1;

		//for(int i=0;i<20;i++)
		float epsilon = 0.00000001;
		float old_diff = 10000;
		float new_diff;
		while(true)
		{
			pr = fillcpt(v, oldpr);
			v1 = fillmissingvalues(v,pr,indices);
			v = v1;
			oldpr = pr;
			//printcpt(pr);
			new_diff = difference(pr, oldpr);
			//cout<<new_diff<<endl;
			if(abs(new_diff-old_diff) < epsilon)
				break;
			old_diff = new_diff;
	    }
	    f<<i*5<<" "<<loglikelihood(test,pr)<<endl;

    }
    printcpt(pr);

	return 0;
}












