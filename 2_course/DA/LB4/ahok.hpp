#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>


class TAhoKarasik{
	private:
		class TElem{
			public:
				using elem_ptr = std::shared_ptr<TElem>;
				long long Sym;
				bool IsLast;
				elem_ptr Suf;
				elem_ptr Stop;
				std::unordered_map<long long,elem_ptr> Childs;
			public:
				TElem(long long S = -1,bool IsL=false):Sym(S),IsLast(IsL),Suf(nullptr),Stop(nullptr){}
		}; //TElem
	public:
		TElem Root;
		void Push(std::vector<long long>& vect)
		{
			
		}

}; //TAhoKarasik