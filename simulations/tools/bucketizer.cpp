#include <iostream>
#include <stdlib.h>
#include "stringtools.h"

void ReadLines(const std::string &data, std::vector<std::string> &ret)
{
	std::string curr;
	for(size_t i=0,l=data.size();i<l;++i)
	{
		char ch=data[i];
		if(ch=='\n' || ch=='\r')
		{
			if(ch=='\n')
			{
				if(!curr.empty())
				{
					ret.push_back(curr);
					curr.clear();
				}
			}
		}
		else
		{
			curr+=ch;
		}
	}
	if(!curr.empty())
	{
		ret.push_back(curr);
	}
}

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		std::cout << "Error: Start with bucketizer [datafile] [bucketsize] ([colums])" << std::endl;
		return 2;
	}
	
	std::string columns;
	if(argc>3)
	{
		columns=argv[3];
	}
	
	std::cout << "Reading file..." << std::endl;
	std::string data=getFile(argv[1]);
	std::cout << "Data size: " << data.size() << std::endl;
	int bucketsize=atof(argv[2]);
	std::vector<std::string> lines;
	std::cout << "Reading lines..." << std::endl;
	ReadLines(data, lines);
	std::cout << lines.size() << " lines" << std::endl;
	std::vector<std::pair<double, size_t> > bucket_data;
	std::string outdata="Bucket,Value\n";
	std::cout << "Creating buckets" << std::endl;
	std::vector<std::string> s_cols;
	std::vector<int> cols;
	Tokenize(columns, s_cols, ":");
	for(size_t j=0;j<s_cols.size();++j)
	{
		cols.push_back(atoi(s_cols[j].c_str()));
	}
	for(size_t i=1,lc=lines.size();i<lc;++i)
	{
		std::string l=lines[i];
		if(!l.empty())
		{
			std::vector<std::string> toks;
			Tokenize(l, toks, ",");
			while(bucket_data.size()<toks.size())
			{
				bucket_data.push_back(std::pair<double, size_t>(0,0) );
			}
			
			for(size_t j=0;j<toks.size();++j)
			{
				bucket_data[j].first+=atof(toks[j].c_str());
				++bucket_data[j].second;
			}
			
			if(!bucket_data.empty() && bucket_data[0].second>=bucketsize )
			{
				bool hask=false;
				for(size_t j=0;j<bucket_data.size();++j)
				{
					bool found=cols.empty();
					for(size_t k=0;k<cols.size();++k)
					{
						if(cols[k]==j)
						{
							found=true;
						}
					}
					if(found)
					{
						if(bucket_data[j].second!=0)
						{
							outdata+=nconvert(bucket_data[j].first/bucket_data[j].second);
						}
						else
						{
							outdata+="0";
						}
						outdata+=",";
						hask=true;
					}
					bucket_data[j].first=0;
					bucket_data[j].second=0;
				}
				if(hask)
					outdata.erase(outdata.size()-1,1);
					
				outdata+="\n";
			}
		}
	}
	std::cout << "Writing output" << std::endl;
	writestring(outdata,(std::string)argv[1]+"-bt.dat");
	return 0;
}