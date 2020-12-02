namespace alloc
{
    template <typename T,size_t size_mem>
    class custom_allocator
    {
        private:
            T* memory; 
            T** free_memory_pos;
            size_t size_free = size_mem;
            size_t size = size_mem;

        public:
            
            void destroy()
            {
                delete[] memory;
                delete[] free_memory_pos;
            }

            void create(const size_t &size)
            {
                size_free = size;
                memory = new T[size];
                free_memory_pos = new T*[size];
                for(size_t i = 0; i < size;++i)
                {
                    free_memory_pos[i] = memory[i];
                }
            }

            custom_allocator()
            {
                memory = new T[size];
                free_memory_pos = new T*[size];
                for(size_t i = 0; i < size;++i)
                {
                    free_memory_pos[i] = memory + i;
                }
            }

            ~custom_allocator()
            {
                destroy();
            }

            void free()
            {
                size_free = size;
            }

            T* allocate()
            {
                if(size_free > 0)
                {
                    --
                    return free_memory_pos[size_free];
                }
                else
                    return nullptr;
            }

            void deallocate(T* point)
            {
                free_memory_pos[size_free] = point;
                ++size_free;
            }

    };
}
