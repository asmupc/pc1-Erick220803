#include<functional>
#include <map>
#include <list>
#include<unordered_map>

class Hashtable {
private:
	unordered_map<long long, list<string>> hashtable;
	long long size;
	function<long long(string, string)> comp;

	void insertarCenter(list<string>& lista, string reg) {
		list<string> stack;
		if (lista.size() < 1) { return; }
		long long middle = lista.size() / 2;
		long long i = 0;
		while (lista.size() >= 1 && i < middle) {
			stack.push_back(lista.back());
			lista.pop_back();
			i++;
		}
		lista.push_back(reg);
		i = 0;
		while (stack.size() >= 1 && i < middle) {
			lista.push_back(stack.front());
			stack.pop_front();
			i++;
		}
	}
public:
	Hashtable() = default;

	Hashtable(function<long long(string, double)> comp) :comp(comp) {
		this->hashtable = unordered_map<long long, list<string>>();
	}
	~Hashtable() {}

	long long getSize() {
		return this->size;
	}

	function<long long(string, double)> gethashfunction() {
		return this->comp;
	}

	void insert(string reg) {
		long long index = comp(reg, reg);
		if (hashtable[index].empty()) {
			hashtable[index].push_back(reg);
		}
		else {
			insertarCenter(hashtable[index], reg);
		}
	}

	void _print(list<string>& lista, long long& cont, function<bool(string)> comp) {
		for (auto item : lista)
		{
			if (comp(item)) {
				cont++;
			}
		}
	}

	long long print(function<bool(string)> comp) {
		long long cont = 0;
		for (auto item : hashtable) {
			_print(item.second, cont, comp);
		}
		return cont;
	}
};