#include <iostream>
#include <vector>
using namespace std;
class SET{
    public:
        vector <int> st;
        int id;
        int sz; //size of our set
        SET(int id){
             //our set is initialised
            sz=0;    //with size 0
            this->id = id;
        }
        int checkmem(int data){
            for (int i = 0; i < sz; i++)
            {
                if (st[i]==data)
                {
                    return 1;
                }                
            }
            return 0;            
        }
        int insert(int data){
            if(sz==0){
                st.emplace_back(data);
                sz++;
            }
            else{
                if( checkmem(data)==0)
                {
                    st.emplace_back(data);
                    sz++;
                    int req_ind = sz-1;
                    for (int i = sz-2; i >=0; i--)
                    {
                    if(st[i]>st[i+1]){
                        int tmp = st[i];
                        st[i]= st[i+1];
                        st[i+1]=tmp;
                    }   
                    else{
                        break;
                    }
                    }
                }
            }
            return sz;
        }
        int del(int data){
            if(checkmem(data)==0){
                return sz;
            }
            else{
                int req_ind=0;
                for (int i = 0; i < sz; i++)
                {
                    if (st[i]==data){req_ind = i; break;}
                }
                st.erase(st.begin()+req_ind);
                sz--;
                return sz;
            }
        }
        int sze(){ //Returns the size of our class
            return sz;
        }
        void prnt(){ //prints our set
            for (int i = 0; i < sz; i++)
            {
                if(i==sz-1){
                    cout<<st[i]<<endl;
                }
                else{
                    cout<<st[i]<<',';
                }
            }
            
        }
        int unon(SET &st1, SET st2){
            int sz1 = st1.sze();
            int sz2 = st2.sze();
            for (int i = 0; i < sz2; i++)
            {
                if(st1.checkmem(st2.st[i])==0){
                    st1.insert(st2.st[i]);
                }
            }
            return st1.sze();    
        }
        int instec(SET &st1,SET st2){
            int sz1 = st1.sze();
            int sz2 = st2.sze();
            vector <int> com_ele;
            for (int i = 0; i < sz2; i++)
            {
                if(st1.checkmem(st2.st[i])==1){
                    com_ele.push_back(st2.st[i]);
                }
            }
            st1.st.clear();
            st1.st = com_ele;
            st1.sz = com_ele.size();
            return st1.sze();
        }
        int dfr(SET &st1,SET st2){ //returns set difference of st1 and st2
            int sz1 = st1.sze();
            int sz2 = st2.sze();
            for (int i = 0; i < sz2; i++)
            {
                if(st1.checkmem(st2.st[i])==1){
                    st1.del(st2.st[i]);
                }
            }
            return st1.sze();
        }
        int symm_dfr(SET &st1,SET st2){
            int sz1 = st1.sze();
            int sz2 = st2.sze();
            for (int i = 0; i < sz2; i++)
            {
                if(st1.checkmem(st2.st[i])==1){
                    st1.del(st2.st[i]);
                }
                else{
                    st1.insert(st2.st[i]);
                }
            }
            return st1.sze();
        }
};
/*
Code starts Here
This is the reason why there are 300 lines
*/
bool checksetmem(vector <SET> &sets,int num){ //to check the id of set created
        int sz = sets.size();
        for (int i = 0; i < sz; i++)
        {
            if(sets[i].id==num) return true;
        }
        return false;
}
auto getSet(vector <SET> &sets,int num){
        int sz = sets.size();
        for (int i = 0; i < sz; i++)
        {
            if(sets[i].id==num) return &sets[i];
        }    
}
int main(){
    vector <SET> sets; //This will store the sets that are being generated
    int command; 
    while (cin>>command)
    {        
        if (command==1)
        {
            int st_id;
            int data;
            cin>>st_id>>data;
            if (checksetmem(sets,st_id)==false)
            {
                SET st1 = SET(st_id);
                cout<<st1.insert(data)<<endl;
                sets.emplace_back(st1);
            }
            else{
                SET *st = getSet(sets,st_id);
                cout<<(*st).insert(data)<<endl;
            }
        }
        else if(command==2){
            int st_id;
            int data;
            cin>>st_id>>data;
            if(checksetmem(sets,st_id)==false){
                cout<<-1<<endl;
            }
            else{            
            SET *st = getSet(sets,st_id);
            cout<<(*st).del(data)<<endl;
            }
        }
        else if(command ==3){
            int st_id;
            int data;
            cin>>st_id>>data;
            if (checksetmem(sets,st_id)==false)
            {
                cout<<-1<<endl;
            }
            else{
                SET *st = getSet(sets,st_id);
                cout<<(*st).checkmem(data)<<endl;
            }
        }
        else if(command==4){
            int st_id1;
            int st_id2;
            cin>>st_id1>>st_id2;
            if (checksetmem(sets,st_id1)==false)
            {
                SET st = SET(st_id1);
                sets.emplace_back(st);
            }
            if (checksetmem(sets,st_id2)==false)
            {
                SET st = SET(st_id2);
                sets.emplace_back(st);
            }            
            SET *st1 = getSet(sets,st_id1);
            SET *st2 = getSet(sets,st_id2);
            cout<<(*st1).unon(*st1,*st2)<<endl;
        }
        else if(command==5){
            int st_id1;
            int st_id2;
            cin>>st_id1>>st_id2;
            if (checksetmem(sets,st_id1)==false)
            {
                SET st = SET(st_id1);
                sets.emplace_back(st);
            }
            if (checksetmem(sets,st_id2)==false)
            {
                SET st = SET(st_id2);
                sets.emplace_back(st);
            }            
            SET* st1 = getSet(sets,st_id1);
            SET *st2 = getSet(sets,st_id2);
            cout<<(*st1).instec(*st1,*st2)<<endl;
        }
        else if(command==6){
            int st_id;
            cin>>st_id;
            if(checksetmem(sets,st_id)==false){
                SET st = SET(st_id);
                cout<<st.sze()<<endl;
                sets.emplace_back(st);
            }
            else{
            SET *st1 = getSet(sets,st_id);
            cout<<(*st1).sze()<<endl;
            }
        }
        else if(command==7){
            int st_id1;
            int st_id2;
            cin>>st_id1>>st_id2;
            if (checksetmem(sets,st_id1)==false)
            {
                SET st = SET(st_id1);
                sets.emplace_back(st);
            }
            if (checksetmem(sets,st_id2)==false)
            {
                SET st = SET(st_id2);
                sets.emplace_back(st);
            }            
            SET *st1 = getSet(sets,st_id1);
            SET *st2 = getSet(sets,st_id2);
            cout<<(*st1).dfr(*st1,*st2)<<endl;
        }
        else if(command==8){
            int st_id1;
            int st_id2;
            cin>>st_id1>>st_id2;
            if (checksetmem(sets,st_id1)==false)
            {
                SET st = SET(st_id1);
                sets.emplace_back(st);
            }
            if (checksetmem(sets,st_id2)==false)
            {
                SET st = SET(st_id2);
                sets.emplace_back(st);
            }            
            SET *st1 = getSet(sets,st_id1);
            SET *st2 = getSet(sets,st_id2);
            cout<<(*st1).symm_dfr(*st1,*st2)<<endl;
        }
        else if(command==9){
            int set_id;
            cin>>set_id;
            if (checksetmem(sets,set_id)==false)
            {
                cout<<endl;
            }
            else{
                SET* st = getSet(sets,set_id);
                if((*st).sze()==0){
                    cout<<endl;
                }
                else{
                (*st).prnt();
                }
            }
        }
    }    
}