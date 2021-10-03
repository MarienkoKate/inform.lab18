#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>


namespace std {
	template<typename t1, typename t2>
	std::ostream& operator<<(std::ostream& os, const std::pair<t1, t2>& pair)
	{
		return os << pair.first << " " << pair.second;
	}
}

	class setting {
	protected:
		std::multimap<std::string, int> mas_int;
		std::multimap<std::string, std::string> mas_str;

	public:
		auto erase_int(const std::string& name) {

			auto it = mas_int.erase(name);
			return it;
		}
		auto erase_str(const std::string& name) {
			
			auto it = mas_str.erase(name);
			return it;
	
		}
		int find_int(const std::string& name) {
			auto it = mas_int.begin();
			int n = 0;
			for (; it != mas_int.end(); ++it) {
				if (it->first == name) {
					n = 1;
					break;
				}
			}
			if (n == 0) throw std::exception();
			 
			return it->second;
		}
		std::string finde_str(const std::string& name) {
			auto it = mas_str.begin();
			int n = 0;
			for (; it != mas_str.end(); ++it) {
				if (it->first == name) {
					n = 1;
					break;
				}
			}
			if (n == 0) throw std::exception();

			return it->second;
		}
		void add(const std::string& name, int val) {
			mas_int.insert(std::pair<std::string, int>(name, val));
		};
		void add(const std::string& name, const std::string& val) {
			mas_str.insert(std::pair<std::string, std::string>(name, val));
		};
		
		friend std::ostream& operator<<(std::ostream& out, const setting& S)
		{

			auto it2 = S.mas_int.begin();
			for (auto it1 = S.mas_str.begin(); it1 != S.mas_str.end(); ++it1) std::cout << *it1 << std::endl;
			for (auto it1 = S.mas_int.begin(); it1 != S.mas_int.end(); ++it1) std::cout << *it1 << std::endl;
			return out;
		}
		void save(const std::string& filename) {
			std::ofstream out;         
			out.open(filename); 
			if (out.is_open())
			{
				for (auto it1 = mas_str.begin(); it1 != mas_str.end(); ++it1) out << *it1 << std::endl;
				for (auto it1 = mas_int.begin(); it1 != mas_int.end(); ++it1) out << *it1 << std::endl;
			}
			else std::cout << "file is not open";
			out.close();
		}
		void load(const std::string& filename) {

			std::ifstream in(filename); // окрываем файл для чтения
			std::string name, val_s;
			int val_i;
			std::string mas;
			if (in.is_open())
			{
				while (!in.eof())
				{    
					if (in >> name >> val_s) add(name, val_s);
					else if (in >> name >> val_i) add(name, val_i);
				}

			}
			else { std::cout << "file is not open"; }
			in.close();

		}

	};


	int main() {
		setting S;
		S.add("color", 16);
	    S.add("cool", 32);
		//S.add("cool", "color");
		//S.add("nnn", 2);
		S.erase_int("nnn");
		try {
			int v = S.find_int("ol");
			std::string u = S.finde_str("color");
		}
		catch (const std::exception& err) {
			std::cout << "there is no such element in this set" << std::endl;
		}
	   // S.erase_str("cool");
		
		//S.save("C:\\lab18.txt");
		//S.load("C:\\lab18.txt");
		//std::cout << S.erase_str("cool");
		std::cout << S;
	}
