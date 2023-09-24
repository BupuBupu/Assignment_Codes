#include "CubicProbing.h"
void mergeIntervals4(std::vector<int>& v, int s, int m, int e) {
	std::vector<int> temp;
	int i, j;
	i = s;
	j = m + 1;
	while (i <= m && j <= e) {
		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}
	}
	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}
	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}
	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}
void mSort4(std::vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mSort4(v, s, m);
		mSort4(v, m + 1, e);
		mergeIntervals4(v, s, m, e);
	}
}
//
int fast_Power4(long long x, unsigned int y, int p) //fast power modulo
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
int spmod2(int k,int m){
    int k1 = k%((long long)(m));
    if (k1>=0)
    {
        return k1;
    }
    else{
        return m+k1;
    }
}
CubicProbing::CubicProbing(){
    table_size=109919;
    db_size = 0;
    for (int i = 0; i < table_size; i++)
    {
        Account k1;
        k1.balance=-1;
        k1.id='x';
        bankStorage1d.emplace_back(k1);
    }
}
void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account ac= Account();
    ac.id = id;
    ac.balance= count;
    int pr = 0;
    int sg=-1;
    int table_id=hash(id);
    while (bankStorage1d[spmod2((table_id+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance>=0)
    {
        pr++;
        sg*=-1;
    }
    bankStorage1d[spmod2((table_id+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)] = ac; 
    db_size++;
}

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> balance;
    for (int i = 0; i < table_size; i++)
    {
        if (bankStorage1d[i].balance>=0)
        {
            balance.emplace_back(bankStorage1d[i].balance);
        }
    }
    int sz1 = databaseSize();
    mSort4(balance,0,sz1-1);
    std::vector<int> topk;
    if(sz1<k){
        k = sz1;
    }
    for (int i = 0; i < k; i++)
    {
        int w1 = balance[sz1-1-i];
        topk.emplace_back(w1);
    }
    return topk;; // Placeholder return value
}

int CubicProbing::getBalance(std::string id) {
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
            int sg= 1;
            int init = table_id;
            int prp=0;
            while (prp<table_size)
            {
                if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance==-1){
                    return -1;
                }
                else if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].id==id){
                    return bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance;
                }
                else{
                    pr++;
                    sg*=-1;
                    prp++;
                }
            }
            return -1;
        }
    } // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
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
            int sg= 1;
            int init = table_id;
            int prp=0;
            while (prp<table_size)
            {
                if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance==-1){
                    createAccount(id,count);
                    return;
                }
                else if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].id==id){
                    bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance+=count;
                    return;
                }
                else{
                    pr++;
                    sg*=-1;
                    prp++;
                }
            }
            return;
        }
    }
}

bool CubicProbing::doesExist(std::string id) {
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
            int sg= 1;
            int init = table_id;
            int prp=0;
            while (prp<table_size)
            {
                if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance==-1){
                    return false;
                }
                else if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].id==id){
                    return true;
                }
                else{
                    pr++;
                    sg*=-1;
                    prp++;
                }
            }
            return false;
        }
    } // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
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
            int sg= 1;
            int init = table_id;
            int prp=0;
            while (prp<table_size)
            {
                if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance==-1){
                    return false;
                }
                else if(bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].id==id){
                    bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].id= 'x';
                    bankStorage1d[spmod2((init+(((int(((long long)pr*(long long)pr*(long long)pr)%table_size))+table_size)%table_size)*sg),table_size)].balance = -2;
                    db_size--;
                    return true;
                }
                else{
                    pr++;
                    sg*=-1;
                    prp++;
                }
            }
            return false;
        }
    }
    return false; // Placeholder return value
}
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return db_size; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int res=1;
    int ln = id.size();
    std::vector<int> primes={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < ln; i++)
    {   if(i==11){
            continue;
        }
        else
        {
            int prime = primes[i];
            int req = fast_Power4(id[i],prime,table_size);
            req = int(((long long)req)%((long long)table_size));
            res = ((((long long)(res))*((long long)(req)))%((long long)table_size) + table_size)%table_size;
        }     
    }   
    return res; // Placeholder return value
}
