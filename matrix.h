#include <vector>
#include <map>
#include <algorithm>
#include <utility> 
#include <cassert>
#include <tuple>


struct Key
{
    size_t row, col;
    Key() {}
    Key(size_t _i, size_t _j): row(_i), col(_j) {}
    Key(const Key& k) {row = k.row; col = k.col;}
    bool operator== (const Key& k) const {return (k.row == row && k.col == col)? true: false;}
    bool operator< (const Key& k) const 
    {
        if (row < k.row) return true;
        if (row > k.row) return false;
        return (col < k.col)? true: false;
    }
};

template <class T>
struct Element
{
	Key key;
    T value;
    Element(const Key& _k, T _value): key(_k), value(_value) {}
};

template <class T, T default_value> 
class MIterator;

template <class T, T default_value> 
class ProxyObject;


template <class T, T default_value = -1>
class Matrix
{
 private:
    std::vector<Element<T>> v_values;
    friend class MIterator<T, default_value>;
        
    class MRow
    {
    private:
        Matrix<T, default_value>& m;        
        size_t row;
    public:
        MRow(Matrix<T, default_value>& _m, size_t _row): m(_m), row(_row) {} 
        ProxyObject<T, default_value> operator[] (size_t col) 
        {
            return ProxyObject<T, default_value>(m, row, col);
        }
    };
    
 public:
    Matrix()
    {
    }
    
    MRow operator [](size_t row)
    {
        return MRow(*this, row);
    }
    
    std::tuple<size_t, size_t, T> operator= (const Element<T>& e) const
    {
        
        return std::make_tuple(e.key.row, e.key.col, e.value);
    }
    
    T get_value(size_t i, size_t j) 
    {
        const Key k(i, j);
        typename std::vector<Element<T>>::iterator it;
        it = std::find_if(v_values.begin(), v_values.end(), [&k](const auto& e) {return (e.key == k)? true: false;});        
        if (it != v_values.end())
            return it->value;
        else
            return default_value;
    }
    
    void set_value(Element<T>& element)
    {
    	typename std::vector<Element<T>>::iterator it;
        const Key k(element.key);
        it = std::find_if(v_values.begin(), v_values.end(), [&k](const auto& e) {return (e.key == k)? true: false;});        
        if (it != v_values.end())
            (*it).value = element.value;
        else    
            v_values.push_back(element);
    }

    
    size_t size() const 
    {
    	return v_values.size();    
    }

    MIterator<T, default_value> begin()
    {
        MIterator<T, default_value> it(*this);
        return it;
    }
    
    MIterator<T, default_value> end()
    {
        MIterator<T, default_value> it(*this, v_values.size());
        return it;
    }
        
    void print()
    {
        for (const auto& e: v_values)
            std::cout << e.value << "  ";
        std::cout << std::endl;
    }
};



template <class T, T default_value>
class ProxyObject
{
private:
	Matrix<T, default_value>& obj;
	size_t row, col;
public:
	ProxyObject(Matrix<T, default_value>& _obj, size_t _row, size_t _col): obj(_obj), row(_row), col(_col) {}
	
	operator T ()
	{
		return obj.get_value(row, col);
	}
	
	ProxyObject<T, default_value>& operator= (T val)
	{
		Element<T> e(Key(row, col), val);
		obj.set_value(e);
		return *this;
	}
};


template <class T, T default_value>
class MIterator
{
private:
    Matrix<T, default_value> m;
    size_t index;
public:
    MIterator(Matrix<T, default_value>& _m): m(_m), index(0) {}
    MIterator(Matrix<T, default_value>& _m, size_t _index): m(_m), index(_index) {}
    
    void operator++ ()
    {
        index++;
    }
 
    void operator-- ()
    {
        index--;
    }
 
    bool operator== (const MIterator<T, default_value>& mIterator)
    {
        return index == mIterator.index;
    }
    
    bool operator!= (const MIterator<T, default_value>& mIterator)
    {
        return index != mIterator.index;
    }
     
    std::tuple<int, int, T> operator* ()
    {
        return std::make_tuple(m.v_values[index].key.row, m.v_values[index].key.col, m.v_values[index].value);
    }    
};

