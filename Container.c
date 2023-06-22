#include <iostream>
#include <map>


using namespace std;

template<class Key, class Value>
 
class dictionary
{
public:
	virtual ~dictionary() = default; 

	virtual const Value& get(const Key& key) const = 0;

	virtual void set(const Key& key, const Value& value) = 0;

	virtual bool is_set(const Key& key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception
{
public:
	virtual const Key& get_key() const noexcept = 0;
};


template<class Key, class Value>
class SimpleArray :public std::map<Key, Value>, public dictionary <Key, Value> {

public:

	const Value& get(const Key& key) const
	{
		try
		{
			return  SimpleArray::map<Key, Value>::at(key);
		}
		catch (out_of_range)
		{
			throw simple_array_exeption<Key>("not_found_exception");
		}
	}

	void  set(const Key& key, const Value& value)
	{
		SimpleArray::map<Key, Value>::insert({key,value});
	}

	 bool is_set(const Key& key) const
	{
		try
		{
			return map<Key, Value>::contains(key);
		}
		catch (out_of_range)
		{
			throw simple_array_exeption<Key>("not_found_exception");

		}
	}

private:
	Key key;
	Value value;

};


template<class Key>
class simple_array_exeption : public not_found_exception <Key>
{

public:
	simple_array_exeption(const Key& message) : message{ message }
	{}
	const  Key& get_key() const noexcept 
	{
		return (message);
	}


private:
	
	Key message; // сообщение об ошибке

};


int main()
 {

	SimpleArray<std::string, std::string> Array;
	Array.set("key2", "val2");
	Array.set("key11", "val11");
	Array.is_set("key2");
	Array.get("key2");
	std::cout << Array.is_set("12") << std::endl;
	try 
	{
		Array.get("21");
	}
	catch (const simple_array_exeption<std::string>& err)
	{
		std::cout << err.get_key() << std::endl;
	}
	
}
