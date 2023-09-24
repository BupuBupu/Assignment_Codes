#include "LinearProbing.h"
//merge sort
void mergeIntervals2(std::vector<int>& v, int s, int m, int e) {
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
void mSort2(std::vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mSort2(v, s, m);
		mSort2(v, m + 1, e);
		mergeIntervals2(v, s, m, e);
	}
}
//
int fast_power2(long long x, unsigned int y, int p) //fast power modulo
{
    int res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0)
    {
        if (y%2==1){
            res = ((res*x) % p +p)%p;
        }
        y = y/2;
        x = ((x*x) % p +p)%p;
    }
    return res;
}
LinearProbing::LinearProbing(){
    table_size=100000+3;
    db_size = 0;
    for (int i = 0; i < table_size; i++)
    {
        Account k1;
        k1.balance=-1;
        k1.id='x';
        bankStorage1d.emplace_back(k1);
    }
}
void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account ac= Account();
    ac.id = id;
    ac.balance= count;
    int pr = 0;
    int table_id = hash(id);
    while (bankStorage1d[((table_id+pr)%table_size + table_size)%table_size].balance>=0)
    {
        pr++;
    }
    bankStorage1d[((table_id+pr)%table_size + table_size)%table_size] = ac;
    db_size++;
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> balance1;
    for (int i = 0; i < table_size; i++)
    {
        if (bankStorage1d[i].balance>=0)
        {
            balance1.emplace_back(bankStorage1d[i].balance);
        }
    }
    int sz1 = balance1.size();
    mSort2(balance1,0,sz1-1);
    
    std::vector<int> topk;
    if(sz1<k){
        k = sz1;
    }
    for (int i = 0; i < k; i++)
    {
        int w1 = balance1[sz1-1-i];
        topk.emplace_back(w1);
    }
    return topk;// Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id= hash(id);
    if (bankStorage1d[table_id].balance==-1)
    {
        return -1;
    }
    else{
        if (bankStorage1d[table_id].id==id)
        {
            return bankStorage1d[table_id].balance;
        }
        else{
            int pr = 1;
            int init = table_id;
            while ((init+pr)%table_size!=init)
            {
                if(bankStorage1d[(init+pr)%table_size].balance==-1){
                    return -1;
                }
                else if(bankStorage1d[(init+pr)%table_size].id==id){
                    return bankStorage1d[(init+pr)%table_size].balance;
                }
                else{
                    pr++;
                }
            }
            return -1;
        }
    }
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int table_id= hash(id);
    if (bankStorage1d[table_id].balance==-1)
    {
        createAccount(id,count);
        return;
    }
    else{
        if (bankStorage1d[table_id].id==id)
        {
            bankStorage1d[table_id].balance+=count;
            return;
        }
        else{
            int pr = 1;
            int init = table_id;
            while ((init+pr)%table_size!=init)
            {
                if(bankStorage1d[(init+pr)%table_size].balance==-1){
                    createAccount(id,count);
                    return;
                }
                else if(bankStorage1d[(init+pr)%table_size].id==id){
                    bankStorage1d[(init+pr)%table_size].balance+=count;
                    return;
                }
                else{
                    pr++;
                }
            }
            createAccount(id,count);
            return;
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id= hash(id);
    if (bankStorage1d[table_id].balance==-1)
    {
        return false;
    }
    else{
        if (bankStorage1d[table_id].id==id)
        {
            return true;
        }
        else{
            int pr = 1;
            int init = table_id;
            while ((init+pr)%table_size!=init)
            {
                if(bankStorage1d[(init+pr)%table_size].balance==-1){
                    return false;
                }
                else if(bankStorage1d[(init+pr)%table_size].id==id){
                    return true;
                }
                else{
                    pr++;
                }
            }
            return false;
        }
    }
    // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int table_id= hash(id);
    if (bankStorage1d[table_id].balance==-1)
    {
        return false;
    }
    
    else{
        if (bankStorage1d[table_id].id==id)
        {
            bankStorage1d[table_id].id='x';
            bankStorage1d[table_id].balance = -2;
            db_size--;
            return true;
        }
        else{
            int pr = 1;
            int init = table_id;
            while ((init+pr)%table_size!=init)
            {
                if(bankStorage1d[(init+pr)%table_size].balance==-1){
                    return false;
                }
                else if(bankStorage1d[(init+pr)%table_size].id==id){
                    bankStorage1d[(init+pr)%table_size].id= 'x';
                    bankStorage1d[(init+pr)%table_size].balance = -2;
                    db_size--;
                    return true;
                }
                else{
                    pr++;
                }
            }
            return false;
        }
    }
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return db_size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
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
            int req = fast_power2(id[i],prime,table_size);
            req = int(((long long)req)%((long long)table_size));
            res = ((((long long)(res))*((long long)(req)))%((long long)table_size) + table_size)%table_size;
        }    
    }   
    return res; // Placeholder return value
}

