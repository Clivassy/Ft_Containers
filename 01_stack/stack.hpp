#include "../00_vector/vector.hpp"
#include <deque>
#include <list>

namespace ft 
{
    template <class T, class Container = std::deque<T> > 
    class stack
    {
        public:
            typedef typename Container::value_type      value_type;
            typedef typename Container::size_type       size_type;
            typedef Container                           container_type;

        protected:
            Container c;

        public:
            explicit stack(const Container& = Container())
            { }
            bool empty() const { return c.empty(); }

            size_type size() const { return c.size(); }

            value_type& top() { return c.back(); }

            const value_type& top() const { return c.back(); }

            void push(const value_type& x) { c.push_back(x); }

            void pop() { c.pop_back(); }
    };

        template <class T, class Container>
        bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
        {
            if (x.size() != y.size())
                return (false);
            stack temp1(*x);
            stack temp2(*y);
            while (!temp1.empty() && !temp2.empty())
            {
                if (temp1.top() != temp2.top())
                    return (false);
                temp1.pop();
                temp2.pop();
            }
            return (true);
        }

        template <class T, class Container>
        bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
        { 

        }
        
        template <class T, class Container>
        bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
        {

        }
        
        template <class T, class Container>
        bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
        {

        }
        
        template <class T, class Container>
        bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
        {

        }
        
        template <class T, class Container>
        bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
        {

        }
}
