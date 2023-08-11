#include "ReadLib.h"

using namespace std;
//#define NLDM_size 7
//std::ofstream outfile("ghosh211.txt");				//Output text file
string name[100];						//String type variable name array to store the names of the GATE type
int num_celltype=0;						//Number of gates counter

ReadLib::ReadLib(string gname,double ind1array[NLDM_size],double ind2array[NLDM_size],double dtable[NLDM_size][NLDM_size],double stable[NLDM_size][NLDM_size], string incapa)
{
	//cout<<"Calling constructor";
	gate_name=gname;
	for(int i=0;i<NLDM_size;i++)
	{
		for(int j=0;j<NLDM_size;j++)
		{
			gate_delay[i][j]=dtable[i][j];
		}
	}
	for(int i=0;i<NLDM_size;i++)
	{
		for(int j=0;j<NLDM_size;j++)
		{
			gate_slew[i][j]=stable[i][j];
		}
	}
	for(int i=0;i<NLDM_size;i++)
	{
		index_1[i]=ind1array[i];
	}
	for(int i=0;i<NLDM_size;i++)
	{
		index_2[i]=ind2array[i];
	}
	input_capacitance=incapa;


}
double* ReadLib::giveindex1()
{
	return index_1;
}
double* ReadLib::giveindex2()
{
	return index_2;
}

vector<double> ReadLib::giveIndex1()
{
	vector<double> V1;
	for(int i=0;i<NLDM_size;i++)
	{
		V1.push_back(index_1[i]);
	}
	return V1;
}

vector<double> ReadLib::giveIndex2()
{
	vector<double> V2;
	for(int i=0;i<NLDM_size;i++)
	{
		V2.push_back(index_2[i]);
	}
	return V2;
}
string ReadLib::give_capa()
{
	return input_capacitance;
}
void ReadLib::display_capacitance()
{
	cout<<"\n"<<input_capacitance;
}
void ReadLib::display_name()
{
	cout<<gate_name<<"\n";
}
void ReadLib::display_delay()
{
	for(int i=0;i<NLDM_size;i++)
	{
		for(int j=0;j<NLDM_size;j++)
		{
			cout<<gate_delay[i][j]<<", ";
		}
		cout<<"\n";
	}
}
void ReadLib::display_slew()
{
	for(int i=0;i<NLDM_size;i++)
	{
		for(int j=0;j<NLDM_size;j++)
		{
			cout<<gate_slew[i][j]<<", ";
		}
		cout<<"\n";
	}
}
void ReadLib::display_index_1()
{
	cout<<"\n";
	for(int i=0;i<NLDM_size;i++)
	{
		cout<<index_1[i]<<", ";
	}
}
void ReadLib::display_index_2()
{	
	cout<<"\n";
	for(int i=0;i<NLDM_size;i++)
	{
		cout<<index_2[i]<<", ";
	}
}

double ReadLib::give_custom_slew(int x,int y)
{
	return gate_slew[x][y];
}
double ReadLib::give_custom_delay(int x,int y)
{
	return gate_delay[x][y];
}


map<string, ReadLib> lib;					
//FUNCTION TO FIND NO. OF DIFFERENT GATES
void gatetype(string file_name)
{
	std::string line;					//This is the string type LINE that will store the line by line read data from file
	std::ifstream infile(file_name);		
	if(!infile)						//To check for successful opening of file 
	{
		cout<<"Could not open File : "<<file_name;
		exit(1);
	}
	
	std::string gatetype="cell (";				//The exact string that we have to search for, to find the GATE Type
	std::string temp1;					//Just a temporary string for storage purpose once it approaches the start of DELAY TABLE function in the file
	while (infile.good())
	{
		getline(infile,line);				// Takes one line at a time
		if (line.find(gatetype,0)!=string::npos)	//Check the gate type by searching for the keyword CELL
		{
			num_celltype++;				//Updates the no. of Gate types
		}
	}
	//outfile<<num_celltype<<"\n";
	cout<<num_celltype<<"\n";

}

//FUNCTION TO PERFORM REST OF THE PARSING OPERATIONS
void parse(string file_name)
{

	//cout<<"\nPARSING....";
//	gatetype(file_name);
	std::string line;					//This is the string type LINE that will store the line by line read data from file
//	std::string name[100];					//String type variable name array to store the names of the GATE type
	double ind_1[NLDM_size];				//Array to store index 1 values
	double ind_2[NLDM_size];				//Array to store index 2 values
	double delay_table[NLDM_size][NLDM_size];		//FLoat type 7x7 array to store the delay times
	double slew_table[NLDM_size][NLDM_size];		//FLoat type 7x7 array to store the delay times
	//std::ofstream outfile("ghosh211.txt");		//Output text file
	std::ifstream infile(file_name);		
	if(!infile)						//To check for successful opening of file 
	{
		cout<<"Could not open File : "<<file_name;
		exit(1);
	}
	int num_celltype=0;
	std::string gatetype="cell (";				//The exact string that we have to search for, to find the GATE Type
	std::string delaytable="cell_delay(Timing_7_7) {";	//The exact string that we have to search for, for delay times
	std::string slewtable="output_slew(Timing_7_7) {";	//The exact string that we have to search for, for slew times
	std::string ind1="index_1 (";				//The exact string that we have to search for, for index 1
	std::string ind2="index_2 (";				//The exact string that we have to search for, for index 2
	std::string cap="capacitance		:";		//The exact string that we have to search for, for Input Capaciatnce
	std::string temp1;					//Just a temporary string for storage purpose
	int row_count=0;					//Variable to count the row number of 7x7 Table
	int line_count=0;					//To keep an eye on the line number of execuion once it approaches the start of DELAY TABLE function in the file
	vector<string> delay;					//vector to store the values of delay table one by one
	vector<string> slew;					//vector to store the values of delay table one by one
	vector<string> in1;					//vector to store the values of index 1
	vector<string> in2;					//vector to store the values of index 2
	string in_cap;	
	int row_counts=0;					//Variable to count the row number of 7x7 Table
	int line_counts=0;					//To keep an eye on the line number of execuion once it approaches the start of DELAY TABLE function in the file
	int i1_count=0;
	int i2_count=0;
	int cap_count=0;
	while (infile.good())
	{
		getline(infile,line);				// Takes one line at a time
		if (line.find(gatetype,0)!=string::npos)	//Check the gate type by searching for the keyword CELL
		{
			num_celltype++;				//Updates the no. of Gate types
		}
		
		if (line.find(gatetype,0)!=string::npos)	//Get into the loop if CELL keyword is found
		{
			char ch1='(';				//Character "("
			int f=line.find_first_of(ch1);		//Find the first occurence of (
			//cout<<f;
			char ch2=')';				//Character ")"
			int k=line.find_last_of(ch2);		//Find the last occurence of )
			//cout<<k;
			std::string tempo=line.substr(f+1,k-f-1);//Find the characters in between ( & ) and stores it in the name array
			auto it = std::remove_if(tempo.begin(),tempo.end(), [](char const &c) 
			{
        			return !std::isalnum(c);
    			});
 
			tempo.erase(it, tempo.end());
			name[num_celltype]=tempo;
			//cout<<"\n"<<name[num_celltype]<<"\n";		//Displays the name of Gate types
			//outfile<<"\n"<<name[num_celltype]<<"\n";	//Stores it in the txt file
			
		}
//**********************************************PARSING INPUT CAPACITANCE***************************************************
		if(line.find(cap,0)!=string::npos)
		{
			//cout<<"CAPACITANCE RUNNING";
			//cout<<"\n"<<line_count<<"\n";
			char ch1=':';				//Charater " to extract the string in betweeen the semicolons
			char ch2=';';				
			char dtrow[1024];			//Character array for holding temporary sub strings
			int s=line.find_first_of(ch1);	//Looks for the first "
			int e=line.find_last_of(ch2);	//Looks for the last "
			temp1=line.substr(s+1,e-s-1);	//Extracts the string in between the two colons
			//strcpy(dtrow,temp1.c_str());	
			std::stringstream ss(temp1);	//Creates string stream from the string
			//cout<<s;
			//cout<<e;

			while (ss.good())
			{
				string sub;
				getline(ss,sub,',');	//get first string delimited by comma
				//cout<<"\t"<<sub<<"\t";
				in_cap=sub;	//push the sub string into the vector from back
			}
			cap_count=1;
		//	line_count=0;
		//	in1.clear();
		}

//*********************************************PARSING INDEX 1********************************************************
		else if(line.find(ind1,0)!=string::npos)
		{
			//cout<<"INDEX 1 RUNNING";
			in1.clear();				//CLears the vector after every line is executed. I found it from https://www.tutorialspoint.com/cpp_standard_library/cpp_vector_clear.htm
			//cout<<"\n"<<line_count<<"\n";
			char ch='"';				//Charater " to extract the string in betweeen the semicolons
			char dtrow[1024];			//Character array for holding temporary sub strings
			int s=line.find_first_of(ch);	//Looks for the first "
			int e=line.find_last_of(ch);	//Looks for the last "
			temp1=line.substr(s+1,e-s-1);	//Extracts the string in between the two colons
			//strcpy(dtrow,temp1.c_str());	
			std::stringstream ss(temp1);	//Creates string stream from the string
			//cout<<s;
			//cout<<e;

			while (ss.good())
			{
				string sub;
				getline(ss,sub,',');	//get first string delimited by comma
				//cout<<"\t"<<sub<<"\t";
				in1.push_back(sub);	//push the sub string into the vector from back
			}
			for(int i=0;i<NLDM_size;i++)
			{
				ind_1[i]=std::stof(in1[i]); 	//Converts the string type to float and stores it into the 7x7 array of delay table
				//cout<<ind_1[i];		//Displays the value of delay table stored
				//outfile<<delay_table[row_count][i];		//STores the delay times in the output file
				//if(i<6)
				{
				//	cout<<", ";				//Displays a comma after every value except the last one
				//	outfile<<", ";	
				}
				//else	
				{
				//	cout<<";";	//DIsplays a semi colon after every last data displayed
				//	outfile<<";";
				}
			}
				//cout<<"\n";			//Change a line after every row is displayed completely 
				//outfile<<"\n";
				//row_count++;			//Updates the row number of the DElay table 7x7 array
			i1_count=1;
		//	line_count=0;
		//	in1.clear();
		}
//*********************************************PARSING INDEX 2************************************************************
		else if(line.find(ind2,0)!=string::npos)
		{
			//cout<<"INDEX 2 RUNNING";
			in2.clear();				//CLears the vector after every line is executed. I found it from https://www.tutorialspoint.com/cpp_standard_library/cpp_vector_clear.htm
			//cout<<"\n"<<line_count<<"\n";
			char ch='"';				//Charater " to extract the string in betweeen the semicolons
			char dtrow[1024];			//Character array for holding temporary sub strings
			int s=line.find_first_of(ch);	//Looks for the first "
			int e=line.find_last_of(ch);	//Looks for the last "
			temp1=line.substr(s+1,e-s-1);	//Extracts the string in between the two colons
			//strcpy(dtrow,temp1.c_str());	
			std::stringstream ss(temp1);	//Creates string stream from the string
			//cout<<s;
			//cout<<e;

			while (ss.good())
			{
				string sub;
				getline(ss,sub,',');	//get first string delimited by comma
				in2.push_back(sub);	//push the sub string into the vector from back
			}
			for(int i=0;i<NLDM_size;i++)
			{
				ind_2[i]=std::stof(in2[i]); 	//Converts the string type to float and stores it into the 7x7 array of delay table
				//cout<<delay_table[row_count][i];		//Displays the value of delay table stored
				//outfile<<delay_table[row_count][i];		//STores the delay times in the output file
				//if(i<6)
				{
				//	cout<<", ";				//Displays a comma after every value except the last one
				//	outfile<<", ";	
				}
				//else	
				{
				//	cout<<";";	//DIsplays a semi colon after every last data displayed
				//	outfile<<";";
				}
			}
				//cout<<"\n";			//Change a line after every row is displayed completely 
				//outfile<<"\n";
				//row_count++;			//Updates the row number of the DElay table 7x7 array
			i2_count=1;
		//	line_count=0;
		//	in2.clear();
		}
//*********************************************PARSING DELAY TABLE************************************************************
		else if(line.find(delaytable,0)!=string::npos)
		{
			line_count=1;				//This is the point from where the Line_counter should be activated to make sure we read and extract data of only the 7 rows of delay table
			row_count=0;					// and not the index1 and index2
		}

		if ((line_count>=1)&&(line_count<=11)) 
								//Checks if the line_count is appropriate and contains the delay times
		{	
			//cout<<"\n"<<line_count;
			//cout<<"\nDELAY TABLE RUNNING"<<name;
			line_count++;				//Counter to keep an eye on the line no.which increements after coming across the delaytable string
			delay.clear();				//CLears the vector after every line is executed. I found it from https://www.tutorialspoint.com/cpp_standard_library/cpp_vector_clear.htm
			//cout<<"\n"<<line_count<<"\n";
			char ch='"';				//Charater " to extract the string in betweeen the semicolons
			char dtrow[1024];			//Character array for holding temporary sub strings
			if (line_count>=5 && line_count<=11)	//Checks if the line number is in the range of 4-10 i.e. the lines containing delay times
			{	//cout<<"\n"<<line_count;
				int s=line.find_first_of(ch);	//Looks for the first "
				int e=line.find_last_of(ch);	//Looks for the last "
				temp1=line.substr(s+1,e-s-1);	//Extracts the string in between the two colons
				//strcpy(dtrow,temp1.c_str());	
				std::stringstream ss(temp1);	//Creates string stream from the string
				//cout<<s;
				//cout<<e;

				while (ss.good())
				{
					string sub;
					getline(ss,sub,',');	//get first string delimited by comma
					delay.push_back(sub);	//push the sub string into the vector from back
				}
				for(int i=0;i<NLDM_size;i++)
				{
					delay_table[row_count][i]=std::stof(delay[i]); 	//Converts the string type to float and stores it into the 7x7 array of delay table
					//cout<<delay_table[row_count][i];		//Displays the value of delay table stored
					//outfile<<delay_table[row_count][i];		//STores the delay times in the output file
					if(i<6)
					{
					//	cout<<", ";				//Displays a comma after every value except the last one
					//	outfile<<", ";	
					}
					else	
					{
					//	cout<<";";	//DIsplays a semi colon after every last data displayed
					//	outfile<<";";
					}
				}
				//cout<<"\n";			//Change a line after every row is displayed completely 
				//outfile<<"\n";
				row_count++;			//Updates the row number of the DElay table 7x7 array
			}
		
		
		//if(row_count==NLDM_size||row_count==0)
		//{
		//	row_count=0;
		//	line_count=0;
		//	delay.clear();
		}
//*****************************************************PARSING SLEW TABLE****************************************************
		else if(line.find(slewtable,0)!=string::npos)
		{
			line_counts=1;				//This is the point from where the Line_counter should be activated to make sure we read and extract data of only the 7 rows of delay table
			row_counts=0;					// and not the index1 and index2
		}

		if ((line_counts>=1)&&(line_counts<=11)) 
								//Checks if the line_count is appropriate and contains the delay times
		{	
			//cout<<"\n"<<line_count;
			//cout<<"\nSLEW TABLE RUNNING"<<name;
			line_counts++;				//Counter to keep an eye on the line no.which increements after coming across the delaytable string
			slew.clear();				//CLears the vector after every line is executed. I found it from https://www.tutorialspoint.com/cpp_standard_library/cpp_vector_clear.htm
			//cout<<"\n"<<line_count<<"\n";
			char ch='"';				//Charater " to extract the string in betweeen the semicolons
			char dtrow[1024];			//Character array for holding temporary sub strings
			if (line_counts>=5 && line_counts<=11)	//Checks if the line number is in the range of 4-10 i.e. the lines containing delay times
			{	//cout<<"\n"<<line_count;
				int s=line.find_first_of(ch);	//Looks for the first "
				int e=line.find_last_of(ch);	//Looks for the last "
				temp1=line.substr(s+1,e-s-1);	//Extracts the string in between the two colons
				//strcpy(dtrow,temp1.c_str());	
				std::stringstream ss(temp1);	//Creates string stream from the string
				//cout<<s;
				//cout<<e;

				while (ss.good())
				{
					string sub;
					getline(ss,sub,',');	//get first string delimited by comma
					slew.push_back(sub);	//push the sub string into the vector from back
				}
				for(int i=0;i<NLDM_size;i++)
				{
					slew_table[row_counts][i]=std::stof(slew[i]); 	//Converts the string type to float and stores it into the 7x7 array of delay table
					//cout<<slew_table[row_counts][i];		//Displays the value of delay table stored
					//outfile<<slew_table[row_counts][i];		//STores the delay times in the output file
					if(i<6)
					{
					//	cout<<", ";				//Displays a comma after every value except the last one
					//	outfile<<", ";	
					}
					else	
					{
					//	cout<<";";	//DIsplays a semi colon after every last data displayed
					//	outfile<<";";
					}
				}
				//cout<<"\n";			//Change a line after every row is displayed completely 
				//outfile<<"\n";
				row_counts++;			//Updates the row number of the DElay table 7x7 array
			//lib.insert(pair<string, gate_library>(name[num_celltype],gate_library(name[num_celltype],delay_table,slew_table)));   
			}
		if(row_counts==NLDM_size && row_count==NLDM_size && i1_count==1 && i2_count==1 &&cap_count==1)
		{
			lib.insert(pair<string, ReadLib>(name[num_celltype],ReadLib(name[num_celltype],ind_1,ind_2,delay_table,slew_table,in_cap)));   
			row_counts=0;
			line_counts=0;
			row_count=0;
			line_count=0;
			i1_count=0;
			i2_count=0;
			cap_count=0;
			in1.clear();
			in2.clear();
			delay.clear();
			slew.clear();
			
		}
			
		}  	
//*************************************************************************************************************************
	}
}

