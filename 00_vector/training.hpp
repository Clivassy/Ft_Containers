#pragma once

template<typename T>
class Vector
{
    public:
        Vector(){

        }

    private:
        T* m_Data = nullptr;
        size_t m_Size = 0;
        size_t m_Capacity = 0;
};

