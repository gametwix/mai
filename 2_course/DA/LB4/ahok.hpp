#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <queue>


class TAhoKarasik{
	private:
		class TElem{
			using elem_ptr = TElem*;
			public:
				long long Sym;
				bool IsLast;
				elem_ptr Suf;
				elem_ptr Stop;
				elem_ptr Parent;
				std::unordered_map<long long,elem_ptr> Childs;
			public:
				TElem(long long S = -1,bool IsL=false):Sym(S),IsLast(IsL),Suf(nullptr),Stop(nullptr),Parent(nullptr){}
				~TElem(){
					for(auto& i: Childs)
					{
						delete(i.second);
					}
				};
		}; //TElem
		using elem_ptr = TElem*;
	public:
		TElem Root;
		~TAhoKarasik(){};
		void Push(std::vector<long long>& vect){
			elem_ptr cur_elem(&Root);
			size_t size_vect = vect.size();
			elem_ptr child;
			for(int i = 0;i < size_vect;++i)
			{
				try
				{	
					std::cout << cur_elem->Childs.at(vect[i]) <<std::endl;
					cur_elem = cur_elem->Childs.at(vect[i]);
				}
				catch(std::out_of_range)
				{
					child = new TElem(vect[i]);
					cur_elem->Childs.insert({vect[i],child});
					child->Parent = cur_elem;
					cur_elem = child;
				}
			}
			cur_elem->IsLast = true;
		}

		void SearchSufPtr()
		{
			std::queue<TElem*> q;
		}
}; //TAhoKarasik