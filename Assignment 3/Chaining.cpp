#include "Chaining.h"
//merge sort
void MergeIntervals1(std::vector<int>& v, int s, int m, int e) {
	std::vector<int> temp;
	int i, j;
	i = s;
	j = m + 1;
	while (i <= m && j <= e) {
		if (v[i] <= v[j]) {
			temp.emplace_back(v[i]);
			++i;
		}
		else {
			temp.emplace_back(v[j]);
			++j;
		}
	}
	while (i <= m) {
		temp.emplace_back(v[i]);
		++i;
	}
	while (j <= e) {
		temp.emplace_back(v[j]);
		++j;
	}
	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}
void mSort1(std::vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mSort1(v, s, m);
		mSort1(v, m + 1, e);
		MergeIntervals1(v, s, m, e);
	}
}
//
int fast_power1(long long x, unsigned int y, int p) //fast power modulo
{
    int res = 1;
    x = (x % p);
    if (x == 0) return 0;
    while (y > 0)
    {
        if (y%2==1){
            res = ((res*x) % p +p)%p;
        }
        y = y/2;
        x = ((x*x) % p + p)%p;
    }
    return res;
}
Chaining::Chaining(){
    db_size = 0;
    table_size = 5003;
    for (int i = 0; i < table_size; i++)
    {
        std::vector <Account> k1;
        bankStorage2d.emplace_back(k1);
    }  
}
void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account ac = Account();
    ac.id= id;
    ac.balance = count;
    int table_id = hash(id);
    std::vector<Account> k1 = bankStorage2d[table_id];
    k1.emplace_back(ac);
    bankStorage2d[table_id] = k1;
    db_size++;
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> balance1;
    for (int i = 0; i < table_size; i++)
    {
        std::vector<Account> a1 = bankStorage2d[i];
        int sz = a1.size();
        if(sz>0){
        for (int j = 0; j < sz; j++)
        {
            Account ac = a1[j];
            if (ac.balance>-1)
            {
                balance1.emplace_back(ac.balance);
            }
        }
        }
    }
    int sz1 = balance1.size();
    mSort1(balance1,0,balance1.size()-1);
    if (k>sz1)
    {
        k=sz1;
    }
    std::vector<int> topk;
    for (int i = 0; i < k; i++)
    {
        int w1 = balance1[sz1-1-i];
        topk.emplace_back(w1);
    }
    return topk; // Placeholder return value
}
int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id = hash(id);
    std::vector<Account> k1 = bankStorage2d[table_id];
    int sz = k1.size();
    int bal = -1;
    for (int i = 0; i < sz; i++)
    {
        Account ac = k1[i];
        if(ac.id==id){
            bal = ac.balance;
        }
    }
    return bal; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id))
    {
        int table_id = hash(id);
        for (int i = 0; i < bankStorage2d[table_id].size(); i++)
        {
            if (bankStorage2d[table_id][i].id==id)
            {
                bankStorage2d[table_id][i].balance+=count;
            }   
        }
    }
    else{
        createAccount(id,count);
    }
    
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id = hash(id);
    std::vector<Account>k1= bankStorage2d[table_id];
    int sz=k1.size();
    for (int i = 0; i < sz; i++)
    {
        Account ac= k1[i];
        if (ac.id==id)
        {
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id = hash(id);
    std::vector<Account>k1= bankStorage2d[table_id];
    int sz=k1.size();
    for (int i = 0; i < sz; i++)
    {
        Account ac= k1[i];
        if (ac.id==id)
        {
            k1.erase(k1.begin()+i);
            bankStorage2d[table_id]=k1;
            db_size--;
            return true;
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return db_size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int res=0;
    int ln = id.size();
    std::vector<int> primes={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < ln; i++)
    {   if(i==11){
            continue;
        }
        else
        {
            int prime = primes[i];
            int req = fast_power1(id[i],prime,table_size);
            req = int(((long long)req)%((long long)table_size));
            res = ((((long long)(res))*((long long)(req)))%((long long)table_size) + table_size)%table_size;
        }    
    }   
    return res; // Placeholder return value
}
