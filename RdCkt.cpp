#include <iostream>  // basic C++ input/output (e.g., cin, //cout)
#include <fstream>	// needed to open files in C++
#include <sstream>   // needed if you are using sstream (C++)
#include <stdio.h>	// needed to open files in C
#include <cstring>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <list>
#include "ReadLib.h"
#include "ReadLibFunc.h"
#include <chrono> 
#include <deque>   
using namespace std::chrono;
#define MAX_FAN 8
std::ofstream outfile("ckt_traversal.txt");					//Output text file
void find_outputnodes();
void find_fanouts();
//***********To compile the program please use the command mentioned in the next line
//g++ -std=c++11 <Filename>.cpp
using namespace std;
//std::ofstream outfile("ghosh211.txt");				//Output text file store the names of the GATE type
//int num_celltype=0;
class Graph;						//Number of gates counter
map<string, Graph> circuit;
class Graph{
	string GID;
	string type;
	int ready;
	int rev_ready;
	double arrival_time;
	double output_slew;
	double req_arrival_time;
	double node_delay;
	double slack;
	list <string> inputs;
	vector<string> fanin;
	vector<string> fanout;
	vector<double> Fi_Delays;
public:
	Graph(string ID, string t, vector<string> inp, int r, double at, double os, double node_delays)
	{
		GID=ID;
		transform(t.begin(), t.end(), t.begin(), ::toupper);	
		type=t;
		////cout<<GID;
		////cout<<t<<"\n";
		vector<string>::iterator p;
		for(p=inp.begin();p!=inp.end();p++)
		{
			inputs.push_back(*p);	
		}
		fanin=inp;
		ready=r;
		arrival_time=at;
		output_slew=os;
		node_delay=node_delays;
		//outfile << GID << ' ' << ready << ' ' << type << '\n';
		//if (GID == "2259") {
		//	int x = 1;
		//}
	}
	void writeFiDelay(vector<double> v)
	{
		Fi_Delays=v;
	}
	vector<double> getFiDelays()
	{
		return Fi_Delays;
	}
	double getCustomNodeDelay(int i)
	{
		//outfile<<"\n";
		//for(auto t=Fi_Delays.begin();t!=Fi_Delays.end();t++)
		//	outfile<<" "<<*t;
		return Fi_Delays[i];
	}
	string giveGID()
	{
		return GID;
	}
	void writeSlack(double s)
	{
		slack=s;
	}
	void printGATE()
	{
		outfile<<type;
	}
	void displaySlack()
	{
		////cout<<slack;
		outfile<<slack;
	}
	void displaySlackps()
	{
		////cout<<slack;
		outfile<<slack*1000;
	}
	double getSlack()
	{
		return slack;
	}
	void writeNodeDelay(double d)
	{
		node_delay=d;
	}
	void displayNodeDelay()
	{
		////cout<<node_delay;
		outfile<<node_delay;
	}
	double getNodeDelay()
	{
		return node_delay;
	}
	void writeReady(int i)
	{
		ready=i;
	}
	void writeRevReady(int i)
	{
		rev_ready=i;
	}
	int getRevReady()
	{
		return rev_ready;
	}
	void RemoveFanouts()
	{
		if (fanout.size()!=0)
			fanout.clear();
	}
	int checkReady()
	{
		int t=0;
		map<string,Graph>::iterator m=circuit.begin();
		for(vector<string>::iterator p=fanin.begin();p!=fanin.end();p++)
		{
			m=circuit.find(*p);
			t=m->second.getReady();
			if(t==0)
				break;
		}
		return t;
	}
	int checkRevReady()
	{
		int t=0;
		map<string,Graph>::iterator m=circuit.begin();
		for(vector<string>::iterator p=fanout.begin();p!=fanout.end();p++)
		{
			m=circuit.find(*p);
			t=m->second.getRevReady();
			if(t==0)
				break;
		}
		return t;
	}
	void displayReady()
	{
		////cout<<ready;
		outfile<<ready;
	}
	void displayRevReady()
	{
		////cout<<rev_ready;
		outfile<<rev_ready;
	}
	void write_req_arrival_time(double t)
	{
		req_arrival_time=t;
	}
	double give_req_arrival_time()
	{
		return req_arrival_time;
	}
	void display_req_arrival_time()
	{
		////cout<<req_arrival_time;	
		outfile<<req_arrival_time*1000;
	}
	void displayID()
	{
		////cout<<GID;
		outfile<<GID;
	}
	string displayGATE()
	{
		////cout<<" "<<type;
		return type;
	}
	void displayINPUTS()
	{
		list<string>::iterator x;
		for(x=inputs.begin();x!=inputs.end();x++)
		{
		//	//cout<<*x<<"\t";	
		}
		////cout<<"\n";
		////cout<<inputs.front()<<" ";
		////cout<<inputs.back()<<" ";
		
	}
	void displayFANINS()
	{
		vector<string>::iterator i;
		if(i!=fanin.end())
		{	
			//for(i=fanin.begin();i!=fanin.end();i++)
			//cout<<*i<<"\t";	
		}
		else;
			//cout<<"\nNO FANINS____PRIMARY INPUT NODE";
	}
	std::vector<string> getFanin()
	{
		return fanin;
	}
	void updateFanout(string s)
	{
		fanout.push_back(s);
	}
	void writeFanout(vector<string> d)
	{
		fanout=d;
	}
	std::vector<string> getFanout()
	{
		return fanout;
	}
	void displayFANOUTS()
	{
		vector<string>::iterator i;
		//if(i!=fanout.end())
		//{	
		//	for(i=fanout.begin();i!=fanout.end();i++)
		//	//cout<<*i<<"\t";	
		//}
		//else
		//	//cout<<"\nNO FANOUTS____PRIMARY OUTPUT NODE";
	}
	int getReady()
	{
		return ready;
	}
	double getArrivalTime()
	{
		return arrival_time;
	}
	double getOutputSlew()
	{
		return output_slew;
	}
	void writeArrivaltime(double A)
	{
		arrival_time=A;
	}
	void writeOutputSlewtime(double T)
	{
		output_slew=T;
	}
	void displayArrivaltime()
	{
		////cout<<arrival_time;
		outfile<<arrival_time*1000;
	}
	void displayOutputSlew()
	{
		////cout<<output_slew;
		outfile<<output_slew*1000;
	}
};
	
vector<string> inputsonly;
vector<string> outputsonly;
void remove_duplicates(vector <string> V)
{
	auto end = V.end();
	for (auto it = V.begin(); it != end; ++it) 
	{
	        end = std::remove(it + 1, end, *it);
    	}
	V.erase(end, V.end());
}
void update_ready()
{
	map<string, Graph>::iterator c=circuit.begin();
	map<string, Graph>::iterator d=circuit.begin();
	for(c=circuit.begin();c!=circuit.end();c++)
	{
		vector<string> fi=c->second.getFanin();
		vector<string>::iterator k=fi.begin();
		int r=0;
		for(k=fi.begin();k!=fi.end();k++)
		{
			d=circuit.find(*k);
			r=d->second.getReady();
			if(r==0)
				break;
		}
		if(r==1)
		{
			c->second.writeReady(r);
			//outfile << "updating ready : " << c->second.displayGATE() << ' ' << c->second.giveGID() <<'\n';
			r=0;
		}
		else
			c->second.writeRevReady(r);
	}
	//cout<<"\nALL READY UPDATED";
	
}
void update_rev_ready()
{
	map<string, Graph>::iterator c=circuit.begin();
	map<string, Graph>::iterator d=circuit.begin();
	for(c=circuit.begin();c!=circuit.end();c++)
	{
		vector<string> fi=c->second.getFanout();
		vector<string>::iterator k=fi.begin();
		int r=0;
		if(k!=fi.end())
		{
			for(k=fi.begin();k!=fi.end();k++)
			{
				d=circuit.find(*k);
				r=d->second.getRevReady();
				if(r==0)
					break;
			}
			if(r==1)
			{
				c->second.writeRevReady(r);
			}
			else
				c->second.writeRevReady(r);
		}
		
	}
	
}
///////////////////////////////////////////CIRCUIT PARSE/////////////////////////////////////////////////////
void ckt_parse(string file_name)
{
	////cout<<"\nPARSING CIRCUIT FILE INTO FUNCTION";
	
	std::string line;					//This is the string type LINE that will store the line by line read data from file
	
	std::ifstream infile(file_name);		
	if(!infile)						//To check for successful opening of file 
	{
		////cout<<"Could not open File : "<<file_name;
		exit(1);
	}
	int num_celltype=0;
	int num_celltypei=0;
	std::string read="*=*(*)";				//The wildcard string that we have to search for
	vector<string> inputv;					//vector to store the values of delay table one by one
	string ID;
	std::string gatename;
	while (infile.good())
	{
		////cout<<"\nworking";
		getline(infile,line);				// Takes one line at a time
		////cout<<"\n"<<line;
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());			//Removes empty spaces from line read from file
		////cout<<"\n"<<line;
		std::string readinp="INPUT(";
		std::string readop="OUTPUT(";
		if (line.find(readinp,0)!=string::npos)		//Check the gate type by searching for the keyword CELL
		{
			num_celltypei++;				//Updates the no. of Gate types
			char ch4='(';				//Character "("
			int f1=line.find_first_of(ch4);		//Find the first occurence of (
			////cout<<f;
			char ch5=')';				//Character ")"
			int k1=line.find_first_of(ch5);		//Find the last occurence of )
			string t=line.substr(f1+1,k1-f1-1);
			inputsonly.push_back(t);
			vector <string> temp;
			temp.clear();
			circuit.insert(pair<string, Graph> (t,Graph(t,"INPUT",temp,1,0,0.002,0)));  //For input nodes only
		}		
		if (line.find(readop,0)!=string::npos)		//Check the gate type by searching for the keyword CELL
		{
			//num_celltypeo++;				//Updates the no. of Gate types
			char ch4='(';				//Character "("
			int f1=line.find_first_of(ch4);		//Find the first occurence of (
			////cout<<f;
			char ch5=')';				//Character ")"
			int k1=line.find_first_of(ch5);		//Find the last occurence of )
			string t=line.substr(f1+1,k1-f1-1);
			outputsonly.push_back(t);
			//vector <string> temp;
			//temp.clear();
			//circuit.insert(pair<string, Graph> (t,Graph(t,"INPUT",temp,1,0,2,0)));  //For input nodes only
		}		

		if (line.find(read,0)!=string::npos)		//Check the gate type by searching for the keyword CELL
		{
			num_celltype++;				//Updates the no. of Gate types
		}
		char ch1='=';				//Character "("
		int f=line.find_first_of(ch1);		//Find the first occurence of (
		////cout<<f;
		char ch2='(';				//Character ")"
		int k=line.find_first_of(ch2);		//Find the last occurence of )
		char ch3=')';
		int g=line.find_last_of(ch3);		
		string temp_string;
		if (((f>=0)&&(k>=0)&&(g>=0))&&(f<k)&&(k<g)&&(f<g))	//Get into the loop 
		{
			////cout<<"\n"<<line;
			////cout<<"I AM IN";
			
			f=line.find_first_of(ch1);		//Find the first occurence of (
			////cout<<f;
			string ID=line.substr(0,f);
			////cout<<ID;
			
			k=line.find_first_of(ch2);		//Find the last occurence of )
			////cout<<k;
			gatename=line.substr(f+1,k-f-1);//Find the characters in between =  & ) and stores it in the name array
			transform(gatename.begin(), gatename.end(), gatename.begin(), ::toupper);		
			////cout<<gatename;			
			//ch3=')';
			g=line.find_last_of(ch3);
			string input_line=line.substr(k+1,g-k-1); //Find the characters in between ( & ) and stores it in the Array
			////cout<<input_line;
			std::stringstream ss1(input_line);	//Creates string stream from the string
			while (ss1.good())
				{
					string sub1;
					getline(ss1,sub1,',');	//get first string delimited by comma
					////cout<<sub1<<"\t";
					temp_string=sub1;					
					inputv.push_back(sub1);	//push the sub string into the vector from back
				}
			////cout<<"\n";
			//vector<string>::iterator it;	
			//for(it=inputv.begin();it!=inputv.end();it++)
			//{
			////cout<<*it<<"\n";
			//}
			//DFF CHECKING
			if(gatename=="DFF" || gatename=="dff")
			{	
				////cout<<"\nFOUND ONE DFF";
				vector <string> temp;
				temp.clear();
				circuit.insert(pair<string, Graph> (ID,Graph(ID,"DFF",temp,1,0,0.002,0)));  //For input nodes only
				inputsonly.push_back(ID);
				//cout<<"\t"<<temp_string;
				outputsonly.push_back(temp_string);
			}
			else			
			{
				circuit.insert(pair<string, Graph> (ID,Graph(ID,gatename,inputv,0,0,0,0)));
			}

			inputv.clear();

			
		}
		
	}
	//cout<<"\nFINDING FANOUTS";
	find_fanouts();
	//cout<<"\nFINDING FANOUTS COMPLETED";
	//cout<<"\nDONE CIRCUIT PARSE";
}
///////////////////FINDING FANOUTS OF ALL NODES///////////////////////////////////////////	
void find_fanouts()
{

	map<string,Graph>::iterator itr=circuit.begin();
	map<string,Graph>::iterator temp=circuit.begin();
	for(itr=circuit.begin();itr!=circuit.end();itr++)
	{
		std::vector<string> fani;
		fani=itr->second.getFanin();
		for(std::vector<string>::iterator m=fani.begin();m!=fani.end();m++)
		{
			if(m!=fani.end())
			{
				////cout<<*m;
				temp=circuit.find(*m);
				string z=itr->first;
				temp->second.updateFanout(z);	
			}
		}
	}
	//cout<<"\nALL FANOUTS COLLECTED";
	
}

/////////////////////////////////CALCULATE DI FROM NLDM LUT//////////////////////////////
vector<double> get_di(string typ,vector<double> inp_slew,double cap,double s)
{
	////cout<<"\nARRIVAL TIMES OF INPUTS OF GATE "<<typ;	
	map<string,ReadLib>::iterator h=lib.find(typ);
	vector<double> delay;
	//h->second.display_index_1();
	//h->second.display_index_2();
	vector<double> index1_array=h->second.giveIndex1();
	vector<double> index2_array=h->second.giveIndex2();
	//for(vector<double>::iterator i=index1_array.begin();i!=index1_array.end();i++)
	//{
	//	//cout<<"\t"<<*i;
	//}
	int row=0;
	int ind1_found=0;
	int col=0;
	int ind2_found=0;
	double T1,T2,C1,C2;
	int r1=0,r2=0,c1=0,c2=0;
	double temp_delay;
	////cout<<"\nOUTPUT CAP "<<cap;
	////cout<<"\nINPUT SLEW OF FANINS ";
	for(vector<double>::iterator g=inp_slew.begin();g!=inp_slew.end();g++)		//Traversing though all the input pins
	{
		
		////cout<<*g;
		for(int i=0;i<NLDM_size;i++)						//Checking all index_1 values
		{	
			row=i;
			if(index1_array[i]==*g)
			{					
				ind1_found=1;						//Exact match of Input slew found
				break;
			}
		}
		for(int j=0;j<NLDM_size;j++)						//Checking all index_2 values
		{
			col=j;
			if(index2_array[j]==cap)					
			{
				ind2_found=1;						//Exact match of load capciatance found
				break;
			}
		}
		if(ind1_found==1 && ind2_found==1)					//If both indices exact match found
		{
			temp_delay=h->second.give_custom_delay(row,col);
			
		}
		if(ind1_found==0)							//If exact Ti is not found in LUT
		{
			int counter=0;
			if(*g>index1_array.back())
			{
				r1=NLDM_size-2;
				r2=r1+1;
				
			}
			else{			
			while(*g>index1_array[counter])
			{
				r1=counter;
				r2=r1+1;
				counter++;
			}
			}
		}
		if(ind2_found==0)							//If exact Cl is not found in LUT
		{
			int counter=0;
			if(cap>index2_array.back())
			{
				c1=NLDM_size-2;
				c2=c1+1;
				
			}
			else{			
			while(cap>index2_array[counter])
			{
				c1=counter;
				c2=c1+1;
				counter++;
			}
			}
		}
		if(ind1_found==0 && ind2_found==0)// 2D Interpolation in case of Ti and Cl mismatch in LUT
		{	
			T1=index1_array[r1];
			T2=index1_array[r2];
			C1=index2_array[c1];
			C2=index2_array[c2];
			//outfile<<"\nT1="<<T1;
			//outfile<<"\nT2="<<T2;
			//outfile<<"\nC1="<<C1;
			//outfile<<"\nC2="<<C2;
			double v11=h->second.give_custom_delay(r1,c1);
			//outfile<<"\nV11="<<v11;		
			double v12=h->second.give_custom_delay(r1,c1+1);
			//outfile<<"\nV12="<<v12;		
			double v21=h->second.give_custom_delay(r1+1,c1);
			//outfile<<"\nV21="<<v21;		
			double v22=h->second.give_custom_delay(r1+1,c1+1);
			//outfile<<"\nV22="<<v22;		
			temp_delay=((v11*(C2-cap)*(T2-*g))+(v12*(cap-C1)*(T2-*g))+(v21*(C2-cap)*(*g-T1))+(v22*(cap-C1)*(*g-T1)))/((C2-C1)*(T2-T1));
			//outfile<<"\nTEMP DELAY:"<<temp_delay;
			
		}
		if(s>2)
		{
			temp_delay=temp_delay*(s/2);
		}
		//outfile<<"\n2D Interpolation V="<<temp_delay;
		delay.push_back(temp_delay);						//Delay from LUT is added to vector;
		ind1_found=0;
		ind2_found=0;
		row=0;
		col=0;
		r1=0;r2=0;c1=0;c2=0;
	}
	
	return delay;		
}

///////////////////////////////CALCULATE FINAL TOUT////////////////////////////////////
double find_Tout(string typ,double tdi,double cap,double size)
{
outfile<<"\nCALCULATING FINAL TOUT OF "<<typ<<" Corresponding to C "<<cap<<" and Slew "<<tdi;
	map<string,ReadLib>::iterator h=lib.find(typ);
	vector<double> index1_array=h->second.giveIndex1();
	vector<double> index2_array=h->second.giveIndex2();
//	//cout<<"\nIn_slew\t"<<tdi<<"\tCapacitance"<<cap;
	int row=0;
	int ind1_found=0;
	int col=0;
	int ind2_found=0;
	double T1,T2,C1,C2;
	int r1=0,r2=0,c1=0,c2=0;	
	double temp_Tout;
	for(int i=0;i<NLDM_size;i++)						//Checking all index_1 values
	{	
		row=i;
		if(index1_array[i]==tdi)
		{					
			ind1_found=1;						//Exact match of Input slew found
			break;
		}
	}
	for(int j=0;j<NLDM_size;j++)						//Checking all index_2 values
	{
		col=j;
		if(index2_array[j]==cap)					
		{
			ind2_found=1;						//Exact match of load capciatance found
			break;
		}
	}
	if(ind1_found==1 && ind2_found==1)					//If both indices exact match found
	{
		temp_Tout=h->second.give_custom_slew(row,col);
	}
	if(ind1_found==0)							//If exact Ti is not found in LUT
	{
		int counter=0;
		if(tdi>index1_array.back())
			{
				r1=NLDM_size-2;
				r2=r1+1;
				
			}
		else
		{			
			while(tdi>index1_array[counter])
			{
				r1=counter;
				r2=r1+1;
				counter++;
			}
		}
			
	}
	if(ind2_found==0)							//If exact Cl is not found in LUT
	{
		int counter=0;
		if(cap>index2_array.back())
			{
				c1=NLDM_size-2;
				c2=c1+1;
				
			}
		else
		{			
			while(cap>index2_array[counter])
			{
				c1=counter;
				c2=c1+1;
				counter++;
			}
		}
	}
	if(ind1_found==0 && ind2_found==0)					// 2D Interpolation in case of Ti and Cl mismatch in LUT
	{
		T1=index1_array[r1];
		T2=index1_array[r2];
		C1=index2_array[c1];
		C2=index2_array[c2];
//		//cout<<"\nT1="<<T1;
//		//cout<<"\nT2="<<T2;
//		//cout<<"\nC1="<<C1;
//		//cout<<"\nC2="<<C2;			
		double v11=h->second.give_custom_slew(r1,c1);
		//outfile<<"\nV11="<<v11;		
		double v12=h->second.give_custom_slew(r1,c1+1);
		//outfile<<"\nV12="<<v12;		
		double v21=h->second.give_custom_slew(r1+1,c1);
//outfile<<"\nV21="<<v21;		
		double v22=h->second.give_custom_slew(r1+1,c1+1);
//outfile<<"\nV22="<<v22;		
		temp_Tout=((v11*(C2-cap)*(T2-tdi))+(v12*(cap-C1)*(T2-tdi))+(v21*(C2-cap)*(tdi-T1))+(v22*(cap-C1)*(tdi-T1)))/((C2-C1)*(T2-T1));		
		//outfile<<"\n2D Interpolation V="<<temp_Tout;
	}
	ind1_found=0;
	ind2_found=0;
	if(size>2)
	{
		temp_Tout=temp_Tout*(size/2);
	}
	row=0;
	col=0;
	r1=0;r2=0;c1=0;c2=0;
	return temp_Tout;
		
}
////////////////////////////////CALCULATE T_INS FROM NLDM LUT/////////////////////////////
vector <double> get_Tout(string typ,vector<double> inp_slew,double cap,double s)
{
		
//	//cout<<"\nCALCULATION T_INS OF "<<typ;	
	map<string,ReadLib>::iterator h=lib.find(typ);
	vector<double> toutslew;
	vector<double> index1_array=h->second.giveIndex1();
	vector<double> index2_array=h->second.giveIndex2();
	int row=0;
	int ind1_found=0;
	int col=0;
	int ind2_found=0;
	double T1,T2,C1,C2;
	int r1=0,r2=0,c1=0,c2=0;
	double temp_Tout;
//	//cout<<"\nOUTPUT CAP "<<cap;
//	//cout<<"\nINPUT SLEW OF FANINS ";
	
	for(vector<double>::iterator g=inp_slew.begin();g!=inp_slew.end();g++)		//Traversing though all the input pins
	{
//		//cout<<"n"<<*g;
		for(int i=0;i<NLDM_size;i++)						//Checking all index_1 values
		{	
			row=i;
			if(index1_array[i]==*g)
			{					
				ind1_found=1;						//Exact match of Input slew found
				break;
			}
		}
		for(int j=0;j<NLDM_size;j++)						//Checking all index_2 values
		{
			col=j;
			if(index2_array[j]==cap)					
			{
				ind2_found=1;						//Exact match of load capciatance found
				break;
			}
		}
		if(ind1_found==1 && ind2_found==1)					//If both indices exact match found
		{
			temp_Tout=h->second.give_custom_slew(row,col);
		}
		if(ind1_found==0)							//If exact Ti is not found in LUT
		{
			int counter=0;
			if(*g>index1_array.back())
			{
				r1=NLDM_size-2;
				r2=r1+1;
				
			}
			else{			
			while(*g>index1_array[counter])
			{
				r1=counter;
				r2=r1+1;
				counter++;
			}
			}
		}
		if(ind2_found==0)							//If exact Cl is not found in LUT
		{
			int counter=0;
			if(cap>index2_array.back())
			{
				c1=NLDM_size-2;
				c2=c1+1;
				
			}
			else{			
			while(cap>index2_array[counter])
			{
				c1=counter;
				c2=c1+1;
				counter++;
			}
			}
		}
		if(ind1_found==0 && ind2_found==0)// 2D Interpolation in case of Ti and Cl mismatch in LUT
		{
			T1=index1_array[r1];
			T2=index1_array[r2];
			C1=index2_array[c1];
			C2=index2_array[c2];
			//outfile<<"\nT1="<<T1;
			///outfile<<"\nT2="<<T2;
			//outfile<<"\nC1="<<C1;
			//outfile<<"\nC2="<<C2;
			double v11=h->second.give_custom_slew(r1,c1);
			//outfile<<"\nV11"<<v11;
			double v12=h->second.give_custom_slew(r1,c1+1);
			//outfile<<"\nV12"<<v12;			
			double v21=h->second.give_custom_slew(r1+1,c1);
			//outfile<<"\nV21"<<v21;
			double v22=h->second.give_custom_slew(r1+1,c1+1);
			//outfile<<"\nV22"<<v22;
			temp_Tout=((v11*(C2-cap)*(T2-*g))+(v12*(cap-C1)*(T2-*g))+(v21*(C2-cap)*(*g-T1))+(v22*(cap-C1)*(*g-T1)))/((C2-C1)*(T2-T1));
			//outfile<<"\n2D Interpolation V="<<temp_Tout;		
		}
		if(s>2)
		{
				temp_Tout=temp_Tout*(s/2);
		}
		toutslew.push_back(temp_Tout);						//Output slew from LUT is added to vector;
	}	
	
		
		ind1_found=0;
		ind2_found=0;
		row=0;
		col=0;
		r1=0;r2=0;c1=0;c2=0;
	return toutslew;		

}

////////////////////////////////CALCULATE ARRIVAL TIME///////////////////////////
void calculate_arrival_time(string s)
{
	//outfile<<"\nCALCULATING ARRIVAL TIME OF NODE "<<s;
	map<string,Graph>::iterator m=circuit.begin();	
	m=circuit.find(s);
	string ty=m->second.displayGATE();
	transform(ty.begin(), ty.end(), ty.begin(), ::toupper);
	vector<string> J=m->second.getFanin();
	vector<string> K=m->second.getFanout();
	vector<double> Ti;
	double load_cap=0;
	vector<double> At;
	vector<double> Tdi;
	//Gathering all Arrival times of Fanins
	for(vector<string>::iterator u=J.begin();u!=J.end();u++)
	{
		m=circuit.find(*u);
		double Atime=m->second.getArrivalTime();
		At.push_back(Atime);	
		////cout<<"\nALL ARRIVAL TIMES OF FANINS GATHERED";
	}

	//Gathering all Output slew of Fanins
	for(vector<string>::iterator t=J.begin();t!=J.end();t++)
	{
		m=circuit.find(*t);
		double Slew=m->second.getOutputSlew();
		Ti.push_back(Slew);
		//if(s =="202")
			//outfile<<"\nOutput slew of Fanins of node "<<s<<" are: "<<Slew;
		//outfile<<"\nAT of Fanins of node "<<m->second.getArrivalTime();
	}
	//Gathering all Input capacitances of Fanouts
	vector<string>::iterator c=K.begin();
	vector<string>::iterator ccc = std::find (outputsonly.begin(), outputsonly.end(), s);
	if(c!=K.end() && ccc!=outputsonly.end())	//When node is primary output node and also feeding some other gate
	{
		////cout<<"\nI AM HERE";
		for(c=K.begin();c!=K.end();c++)
		{
			////cout<<"\nALL INPUT CAPACITANCES GATHERED";	
			map<string,Graph>::iterator g=circuit.begin();
			g=circuit.find(*c);		
			string t=g->second.displayGATE();
			transform(t.begin(), t.end(), t.begin(), ::toupper);
			map<string, ReadLib>::iterator n =lib.find(t);
			string cl=n->second.give_capa();
			double cll=std::stod(cl);
			//if(s =="202")
				//outfile<<"\nCapacitance of node "<<s<<" are: "<<cll;
			load_cap=load_cap+cll; //Final Load capacitance of node under test
			
		}
		map<string, ReadLib>::iterator n =lib.find("INV");
		string cl=n->second.give_capa();
		double cll=std::stod(cl);
		double ddd=4*cll;
		load_cap=load_cap+ddd;
	}
	else if(c!=K.end() && ccc==outputsonly.end())		//when node is not ouputnode but feeding another gate	
	{	////cout<<"\nI AM HERE";
		for(c=K.begin();c!=K.end();c++)
		{
			////cout<<"\nALL INPUT CAPACITANCES GATHERED";	
			map<string,Graph>::iterator g=circuit.begin();
			g=circuit.find(*c);		
			string t=g->second.displayGATE();
			transform(t.begin(), t.end(), t.begin(), ::toupper);
			map<string, ReadLib>::iterator n =lib.find(t);
			string cl=n->second.give_capa();
			double cll=std::stod(cl);
			load_cap=load_cap+cll; //Final Load capacitance of node under test
			
		}
	}
	else if(c==K.end())					//When gate is output node and not feeding any other gate
	{
		map<string, ReadLib>::iterator n =lib.find("INV");
		string cl=n->second.give_capa();
		double cll=std::stod(cl);
		load_cap=4*cll;
	}
	//Counting number of Inputs to the GATE and collecting Tdi and Touti
	double size=J.size();
	vector <double> di;
	vector <double> Tout;
	//for(vector<double>::iterator y=Ti.begin();y!=Ti.end();y++)
	{
		m=circuit.find(s);
		string ty=m->second.displayGATE();
		transform(ty.begin(), ty.end(), ty.begin(), ::toupper);
		////cout<<"\nCALLING DI";
//		outfile<<"\nLOAD CAPACITANCE : "<<load_cap;
//		outfile<<"\nSIZE :"<<size;
//		outfile<<"\nTYPE: "<<ty;
//		outfile<<"\nINput slews of fanins for node "<<s<<"\t";

//		for(auto i=Ti.begin();i!=Ti.end();i++)
//		{
//			outfile<<*i<<"\t";	
//		}
		di = get_di(ty,Ti,load_cap,size);
//outfile<<"\nALL DELAYS : ";
//for(auto i=di.begin();i!=di.end();i++)
	{
//		outfile<<*i<<"\t";	
	}
	//	outfile<<"\nDELAY COLLECTED FROM LUT for node"<<s<<"\t";
	//	for(auto i=di.begin();i!=di.end();i++)
		{
	//		outfile<<*i<<"\t";	
		}
		Tout=get_Tout(ty,Ti,load_cap,size);
//		outfile<<"\nALL OUTPUT SLEW : ";
//for(auto i=Tout.begin();i!=Tout.end();i++)
	{
//		outfile<<*i<<"\t";	
	}
	}
	vector <double> aout;
	vector<double>::iterator w=At.begin();
	vector<double>::iterator x=di.begin();
	for(w=At.begin(),x=di.begin();w!=At.end(),x!=di.end();w++,x++)
	{
		aout.push_back(*w+*x);
	}
	
	double maxAout=*max_element(aout.begin(),aout.end());	//Arrival time (Final)
	vector<double>::iterator it=find(aout.begin(),aout.end(),maxAout);
	int tdi_index=distance(aout.begin(), it);
	double d_i=di[tdi_index];
	m->second.writeFiDelay(di);
	//outfile<<"\nDELAY CORRESPONDING TO DIFFERENT INPUT SLEW for node"<<s<<"\t";
	//for(auto i=di.begin();i!=di.end();i++)
	//{
	//	outfile<<*i<<"\t";	
	//}
	//cout<<d_i<<"\t";
//	m->second.writeNodeDelay(d_i);
//	outfile<<"\nLOAD CAPACIATANCE: "<<load_cap;
	//double maxTout=find_Tout(ty,d_i,load_cap,size);
	double maxTout=Tout[tdi_index];
	m=circuit.find(s);
	////cout<<"\nMAX ARRIVAL TIME "<<maxAout;
	////cout<<maxTout;
	m->second.writeArrivaltime(maxAout);	
	m->second.writeOutputSlewtime(maxTout);
	//outfile<<"\nOUTPUT SLEW/AT : "<<maxTout << ' ' << maxAout << ' ' << m->second.giveGID() << ' ' << m->second.displayGATE() ;
	m->second.writeReady(1);
	J.clear();
	K.clear();
	Ti.clear();
	At.clear();
	Tdi.clear();
	aout.clear();
	//cout<<"\nARRIVAL TIME CALCULATED AND UPDATED IN MAP";
}

////////////////////////////////CALCULATE REQUIRED TIME///////////////////////////
void calculate_required_time(string s)
{
	////cout<<"\nCALCULATING REQUIRED TIMES";
	map<string,Graph>::iterator m=circuit.find(s);
	double d_i;
	vector<string> Fanouts=m->second.getFanout();
	double rt;
	double min=10000;
	vector<string>::iterator j;
	for(vector<string>::iterator i=Fanouts.begin();i!=Fanouts.end();i++)
	{
		m=circuit.find(*i);
		double rt=m->second.give_req_arrival_time();
	//	//cout<<"\nRT= "<<rt;
		if(rt<min)
		{
			min=rt;
			j=i;
		}
	//	//cout<<"\nMIN ="<<min;
	}
			m=circuit.find(*j);
			int ind=0;
			vector<string> g=m->second.getFanin();
			auto it = find(g.begin(), g.end(), s);
			int index = it - g.begin();
			d_i=m->second.getCustomNodeDelay(index);
	//outfile<<"\n"<<min<<" "<<d_i;
	double req_time=min-d_i;
	//outfile<<"\n"<<req_time;
	m=circuit.find(s);
	m->second.write_req_arrival_time(req_time);
	m->second.writeRevReady(1);
	Fanouts.clear();	
//	//cout<<"\nTEST";
}
void update_req_arr_time(double t);
////////////////////////////////////CIRCUIT DELAY////////////////////////////////
void circuit_delay()
{
	//cout<<"\nFINDING CIRCUIT DELAY";
	vector<string>::iterator i=outputsonly.begin();
	double at,max=0;
	for(i=outputsonly.begin();i!=outputsonly.end();i++)
	{
		map<string,Graph>::iterator j=circuit.find(*i);
		at=j->second.getArrivalTime();
		if(at>max)
			max=at;
	}
	//cout<<"\nTOTAL CIRCUIT DELAY : "<<max<<" pico seconds";
	outfile<<"\nCircuit Delay : "<<max*1000<<" ps";
	//outfile<<"\nREQUIRED ARRIVAL TIME : "<<1.1*max<<" pico seconds";
	update_req_arr_time(1.1*max);
	//cout<<"\nFINISHED DELAY";
}
/////////////////UPDATE REQUIRED ARRIVAL TIME OF OUTPUT NODES////////////////////
void update_req_arr_time(double t)
{
	map<string,Graph>::iterator itr=circuit.begin();
	////cout<<"\t"<<t;
	for(vector<string>::iterator i=outputsonly.begin();i!=outputsonly.end();i++)
	{
		itr=circuit.find(*i);
		itr->second.write_req_arrival_time(t);
		itr->second.writeRevReady(1);
	}
	//update_rev_ready();
}
/////////////////////////////////FORWARD TRAVERSAL///////////////////////////////
void forward_traversal()
{
	//cout<<"\nFORWARD TRAVERSAL STARTED";	
	map<string,Graph>::iterator c=circuit.begin();
	vector<string>::iterator i=inputsonly.begin();
	std::queue<string> Q;
	vector<string> V;
	for(i=inputsonly.begin();i!=inputsonly.end();i++)
	{
		////cout<<*i;
		c=circuit.find(*i);
		V=c->second.getFanout();		
		for(vector<string>::iterator z=V.begin();z!=V.end();z++)
		{	////cout<<"\t"<<*z;
			c=circuit.find(*z);
			int a=c->second.checkReady();
			////cout<<"\t"<<a;
			if(a==1)
			{
				////cout<<*z;
				Q.push(*z);
			}		
		}
		V.clear();		
	}
	if(Q.empty())
	{
		////cout<<"\nNO ELEMENTS ARE READY";
	}
	//cout<<"\nGETTING INTO WHILE LOOP";
	while(!Q.empty())
	{
		//cout<<"\nQUEUE NOT EMPTY";
		string s=Q.front();
		Q.pop();
		////cout<<"\nCALCULATING ARRIVAL TIME";
		//auto start_arrtime = high_resolution_clock::now();
		calculate_arrival_time(s);
		//auto stop_arrtime = high_resolution_clock::now();
		//auto duration = duration_cast<microseconds>(stop_arrtime - start_arrtime);
		//outfile<<"\nTIME TAKEN FOR FINDING ARRIVAL TIME : ";
		//outfile << duration.count() <<" micro seconds"<< endl;
		map<string,Graph>::iterator b=circuit.find(s);
		vector<string> d=b->second.getFanout();
		vector<string>::iterator i=d.begin();
		if(i!=d.end())		
		{	
			////cout<<"\nLOOKING FOR READY FANOUTS";
			for(i=d.begin();i!=d.end();i++)	
			{	
				b=circuit.find(*i);
				int u=b->second.checkReady();
				if(u==1)
				{
					////cout<<"\nADDED TO QUEUE";
					Q.push(*i);
				}			
			}
		}	
		d.clear();		
	}	
	//cout<<"\nFORWARD TRAVERSAL COMPLETED";
}
/////////////////////////////////BACKWARD TRAVERSAL///////////////////////////////
void backward_traversal()
{
	////cout<<"\nBACKWARD TRAVERSAL STARTED";	
	map<string,Graph>::iterator c=circuit.begin();
	vector<string>::iterator i=outputsonly.begin();
	std::queue<string> Q;
	vector<string> V;
	for(i=outputsonly.begin();i!=outputsonly.end();i++)
	{
		////cout<<*i;
		c=circuit.find(*i);
		V=c->second.getFanin();		
		for(vector<string>::iterator z=V.begin();z!=V.end();z++)
		{	////cout<<"\t"<<*z;
			c=circuit.find(*z);
			int a=c->second.checkRevReady(); 
			////cout<<"\t"<<a;
			if(a==1)
			{
				////cout<<*z;
				Q.push(*z);
			}		
		}
		V.clear();		
	}
	if(Q.empty())
	{
	//	//cout<<"\nNO ELEMENTS ARE READY";
	}
	////cout<<"\nGETTING INTO WHILE LOOP";
	while(!Q.empty())
	{
	//	//cout<<"\nQUEUE NOT EMPTY";
		string s=Q.front();
		Q.pop();
		calculate_required_time(s);
		map<string,Graph>::iterator b=circuit.find(s);
		vector<string> d=b->second.getFanin();
		vector<string>::iterator i=d.begin();
		if(i!=d.end())		
		{	
			for(i=d.begin();i!=d.end();i++)	
			{	
				b=circuit.find(*i);
				int u=b->second.checkRevReady();
				if(u==1)
				{
					Q.push(*i);
				}			
			}
		}	
		d.clear();		
	}	
}

//////////////////////////DISPLAY NODES/////////////////////////////////////////////////
void data_extract(string lib_filename, string ckt_filename, string arr)
{
	////cout<<"\nPARSING LIBRARY FILENAME";
	parse(lib_filename);
	////cout<<"\nPARSING CIRCUIT FILE NAME";
	ckt_parse(ckt_filename);
	////cout<<"\nALL PRIMARY INPUT NODES";
	//for(vector<string>::iterator g=inputsonly.begin();g!=inputsonly.end();g++)
	//{
	//	//cout<<*g<<"\t";
	//}
	////cout<<"\nALL PRIMARY OUTPUT NODES";
	//for(vector<string>::iterator h=outputsonly.begin();h!=outputsonly.end();h++)
	//{
	//	//cout<<*h<<"\t";
	//}
	//for(int i=0;i<s;i++)
	{	
		string s1;
		//Display ID Number		
		////cout<<arr<<" ";
		map<string,Graph>::iterator k=circuit.end();
		//DIsplay GATE type
		////cout<<"\nFINDING NODE...............";
		k=circuit.find(arr);
		if(k !=circuit.end())
		{
			s1=k->second.displayGATE();
			transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
			////cout<<"\nDISPLAY INPUTS TO THE NODE \n";
			//k->second.displayINPUTS();
			////cout<<"\nDISPLAY FANINS TO THE NODE \n";
			k->second.displayFANINS();
			////cout<<"\nDISPLAY FANOUTS TO THE NODE \n";
			k->second.displayFANOUTS();
			map<string, ReadLib>::iterator m =lib.end();
			m=lib.find(s1);
			if (m !=lib.end())	
			{	
			//	//cout<<"\nGATE NAME\n";
				m->second.display_name();
			//	//cout<<"\nINDEX 1\n";
				m->second.display_index_1();
			//	//cout<<"\nINDEX 2\n";
				m->second.display_index_2();
			//	//cout<<"\nDELAY TABLE\n";
				m->second.display_delay();
			//	//cout<<"\nSLEW TABLE\n";
				m->second.display_slew();
			}
		}
		else
		{
			////cout<<"UNDEFINED NODE";
			
		}
	}
}
///////////////////////////CALCULATING SLACK///////////////////////////////////////////
void slack()
{
	map<string,Graph>::iterator i=circuit.begin();
	for(i=circuit.begin();i!=circuit.end();i++)
	{
		double at=i->second.getArrivalTime();
		double rat=i->second.give_req_arrival_time();
		double sl=rat-at;
		i->second.writeSlack(sl);
	}
}
//////////////////////////////FINDING CRITICAL PATH////////////////////////////////////
void critical_path()
{	
	deque<string> Q;
	////cout<<"\n\nCRITICAL PATH IS : ";
  	outfile<<"\n\nCritical Path: ";
	double min=10000;
	string abc;
	map<string,Graph>::iterator i=circuit.begin();
	map<string,Graph>::iterator k=circuit.begin();
	map<string,Graph>::iterator m=circuit.begin();
	map<string,Graph>::iterator h=circuit.begin();
	for(vector<string>::iterator j=outputsonly.begin();j!=outputsonly.end();j++)
	{
		i=circuit.find(*j);
		double s=i->second.getSlack();
		if(s<min)
		{		
			min=s;
			k=circuit.find(*j);
			abc=*j;
		}
	}
	Q.push_front(abc);
	string str;
	vector<string> FanI=k->second.getFanin();
	while(!FanI.empty())
	{ 
		double min=10000;
		for(vector<string>::iterator l=FanI.begin();l!=FanI.end();l++)
		{
			m=circuit.find(*l);
			double s=m->second.getSlack();
			if(s<min)
			{		
				min=s;
				h=circuit.find(*l);
				str=*l;
			}
		}
		Q.push_front(str);
		FanI=h->second.getFanin();
	//	//cout<<"---->";
		//outfile<<"---->";
		
	}
	while (!Q.empty())
	{	
		string z=Q.front();
		Q.pop_front();
		h=circuit.find(z);
		h->second.printGATE();
		outfile<<"-n";
		h->second.displayID();
		outfile<<",";
	}
	
}
//////////////////////////DISPLAY CIRCUIT FILE INFORMATION/////////////////////////////
void circuit_info(string lib_filename, string ckt_filename)
{
	//outfile<<"\nFILE AUTO GENERATED BY RdCkt.cpp. Designed and developed by Subhadip Ghosh, UMN ID: 5801977,\nghosh211@umn.edu as part of the course EE5301 Course Project Title STATIC TIMING ANALYSIS\n\n"; 
	////cout<<"\nPARSING LIBRARY FILENAME";
	parse(lib_filename);
	//outfile<<"\n\nNLDM FILE : "<<lib_filename;
	////cout<<"\nPARSING CIRCUIT FILE NAME";
	//auto start_ckt_parse = high_resolution_clock::now();
	ckt_parse(ckt_filename);
	//auto stop_ckt_parse = high_resolution_clock::now();
	//outfile<<"\n\nCIRCUIT FILE : "<<ckt_filename;
	//auto start_duplicates = high_resolution_clock::now();
	remove_duplicates(outputsonly);
	remove_duplicates(inputsonly);
	//auto stop_duplicates = high_resolution_clock::now();
 	//cout<<"\n\nALL PRIMARY INPUT NODES IN THE CIRCUIT ARE AS FOLLOWS\n";
	//for(vector<string>::iterator g=inputsonly.begin();g!=inputsonly.end();g++)
	//{
		//cout<<*g<<"\t";
		//outfile<<*g<<"\t";
	//}
	//cout<<"\nALL PRIMARY OUTPUT NODES";
	//outfile<<"\n\nALL PRIMARY OUTPUT NODES IN THE CIRCUIT ARE AS FOLLOWS\n";
	//for(vector<string>::iterator h=outputsonly.begin();h!=outputsonly.end();h++)
	//{
		//cout<<*h<<"\t";
		//outfile<<*h<<"\t";
	//}
	
	
	////cout<<"\nUPDATING READY STATUS";
	//auto start_ready = high_resolution_clock::now();
	//update_ready();
	//auto stop_ready = high_resolution_clock::now();
	//auto start_forward = high_resolution_clock::now();
	forward_traversal();
	//auto stop_forward = high_resolution_clock::now();
	//auto start_ckt_delay = high_resolution_clock::now();
	circuit_delay();
	//auto stop_ckt_delay = high_resolution_clock::now();
	////cout<<"\nCIRCUIT DELAY CALCULATED";
	//auto start_backward = high_resolution_clock::now();
	backward_traversal();
	//auto stop_backward = high_resolution_clock::now();	
	//auto start_slack = high_resolution_clock::now();
	slack();
	//auto stop_slack = high_resolution_clock::now();
	////cout<<"\nALL PRIMARY INPUT NODES";
	//outfile<<"\n\nALL PRIMARY INPUT NODES IN THE CIRCUIT ARE AS FOLLOWS\n";
	//for(vector<string>::iterator g=inputsonly.begin();g!=inputsonly.end();g++)
	{
		////cout<<*g<<"\t";
	//	outfile<<*g<<"\t";
	}
	////cout<<"\nALL PRIMARY OUTPUT NODES";
	//outfile<<"\n\nALL PRIMARY OUTPUT NODES IN THE CIRCUIT ARE AS FOLLOWS\n";
	//for(vector<string>::iterator h=outputsonly.begin();h!=outputsonly.end();h++)
	{
		////cout<<*h<<"\t";
	//	outfile<<*h<<"\t";
	}
	//outfile<<"\n";
	map<string, Graph>::iterator i= circuit.begin();
	////cout<<"\n\nGATE ID\tARR TIME(ps)\tOUTPUT SLEW\tREQ TIME\tSLACK";
	//outfile<<"\n\nGATE ID\t\tARR TIME(ps)\t\tOUTPUT SLEW\tREQ TIME\t\tSLACK";
	outfile<<"\n\nGate Slacks:";
	for(i=circuit.begin();i!=circuit.end();i++)	
	{
		
	//	//cout<<"\n";
		outfile<<"\n";
		i->second.printGATE();
		outfile<<"-n";
		i->second.displayID();
		outfile<<": ";
		//outfile<<"\t";
		//i->second.displayReady();
	//	//cout<<"\t";
	//	outfile<<"\t";
	//	i->second.displayArrivaltime();
		//cout<<"\t";
	//	outfile<<"\t\t";
	//	i->second.displayOutputSlew();
		//outfile<<"\t";
		//i->second.displayNodeDelay();
		////cout<<"\t\t";
		//outfile<<"\t";
		//i->second.displayRevReady();
	//	//cout<<"\t\t";
	//	outfile<<"\t\t";
	//	i->second.display_req_arrival_time();
		//cout<<"\t\t";
	//	outfile<<"\t\t";
		i->second.displaySlackps();
		outfile<<" ps";
		
	}
	//auto start_critical_path = high_resolution_clock::now();
	critical_path();
	//auto stop_critical_path = high_resolution_clock::now();

	//auto duration = duration_cast<microseconds>(stop_ckt_parse - start_ckt_parse);
	//outfile<<"\nTIME TAKEN FOR CIRCUIT PARSING : ";
	//outfile << duration.count() <<" micro seconds"<< endl;

	//duration = duration_cast<microseconds>(stop_duplicates - start_duplicates);
	//outfile<<"\nTIME TAKEN FOR REMOVING DUPLICATES : ";
	//outfile << duration.count() <<" micro seconds"<< endl;
	
 	//duration = duration_cast<microseconds>(stop_ready - start_ready);
	//outfile<<"\nTIME TAKEN FOR UPDATING READY : ";
	//outfile << duration.count() <<" micro seconds"<< endl;

	//duration = duration_cast<microseconds>(stop_forward - start_forward);
	//outfile<<"\nTIME TAKEN FOR FORWARD TRAVERSAL : ";
	//outfile << duration.count() <<" micro seconds"<< endl;
 
	//duration = duration_cast<microseconds>(stop_ckt_delay - start_ckt_delay);
	//outfile<<"\nTIME TAKEN FOR CALCULATING CIRCUIT DELAY : ";
	//outfile << duration.count() <<" micro seconds"<< endl;
	
	//duration = duration_cast<microseconds>(stop_backward - start_backward);
	//outfile<<"\nTIME TAKEN FOR BACKWARD TRAVERSAL : ";
	//outfile << duration.count() <<" micro seconds"<< endl;

	//duration = duration_cast<microseconds>(stop_slack - start_slack);
	//outfile<<"\nTIME TAKEN FOR SLACK CALCULATION : ";
	//outfile << duration.count() <<" micro seconds"<< endl;
	
	//duration = duration_cast<microseconds>(stop_critical_path - start_critical_path);
	//outfile<<"\nTIME TAKEN FOR FINDING CRITICAL PATH : ";
	//outfile << duration.count() <<" micro seconds"<< endl;
	

}


int main(int argc,char *argv[])
{	
	//auto start = high_resolution_clock::now();		///TAKEN FROM https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
	string lfile,cfile;
	string nodes[100];
	int n=1;
	circuit_info(std::string (argv[1]),std::string(argv[2]));
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//outfile<<"\nTOTAL TIME TAKEN FOR COMPLETE STA EXECUTION : ";
	//outfile << duration.count() <<" microseconds"<< endl;
	return 0;
}
