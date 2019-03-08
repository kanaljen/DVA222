//
//  HashDictionary.h
//  HashDictionary
//
//  Created by Staffan Brickman & Fredrik Ginsberg on 2019-02-12.
//  Copyright © 2019 kanaljen. All rights reserved.
//
#pragma once
using namespace System;

#ifndef HashDictionary_h
#define HashDictionary_h
#define TABLESIZE 997 // A prime number

template <typename K, typename V> // K = key, V = value. Template that allos any key or value in theory
class Item {
	V m_value;
	K m_key;
	Item* m_next;
public:

	Item(K key, V value) :
		m_key(key), m_value(value), m_next(NULL)
	{ }
	K getKey() { return m_key; }
	V returnValue() { return m_value; }
	Item* getNext() { return m_next; }
	void setm_value(V value) // simply accesses the member value
	{
		m_value = value;
	}
	void setValue(K key, V value) // recursive method
	{
		if (m_key == key)m_value = value;
		else if (m_next != NULL)m_next->setValue(key, value);
		else throw std::invalid_argument("no such key");
	}
	V getValue(K key) // recursive method
	{
		if (m_key == key)return m_value;
		else if (m_next != NULL)return m_next->getValue(key);
		else throw std::invalid_argument("no such key");
		
	}
	int lengthoflist(const int index)
	{


		if (m_next == NULL) return 1;

		else if (m_next != NULL)
			return 1 + lengthoflist;
	}
	void appendItem(K key, V value) // recursive append, goes to end of linked list or will abort giving "duplicate key" error
	{

		if (m_key == key)
			throw std::invalid_argument("duplicate key");
		else if (m_next == NULL)
			m_next = new Item<K, V>(key, value);
		else m_next->appendItem(key, value);
	}
	V popValue(K key)
	{
		if (m_next != NULL) // if at end of data 
		{
			if (m_next->getKey() == key) // if correct key, free it and link to next item after. Return value of deleted item.
			{
				Item* t_next = m_next->getNext();
				V t_value = m_next->getValue(key);
				delete m_next;
				m_next = t_next;
				return t_value;
			}
		}
		else throw
			std::invalid_argument("no such key");

		return m_next->popValue(key);
	}
};

template <typename K, typename V>
class HashDictionary {
	Item<K, V>* m_items[TABLESIZE];
public:
	HashDictionary() { for (int i = 0; i < TABLESIZE; i++)m_items[i] = NULL; }
	void append(K key, V value)
	{
		int hash = hashFunction(key);
		if (m_items[hash] == NULL)
			m_items[hash] = new Item<K, V>(key, value);
		else try
		{
			m_items[hash]->appendItem(key, value);
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "exception: " << e.what() << std::endl;
		}
	}
	void set(K key, V value)
	{
		int hash = hashFunction(key);
		try {
			if (m_items[hash] == NULL)throw std::invalid_argument("no such key");
			else m_items[hash]->setValue(key, value);
		}
		catch (const std::invalid_argument& e) { std::cerr << "exception: " << e.what() << std::endl; }
	}
	V get(K key)
	{
		int hash = hashFunction(key);

		if (m_items[hash] == NULL)throw std::invalid_argument("no such key, Returning trash template"); // no value is returned, trash data most likely read.
		else return m_items[hash]->getValue(key); // Found match

	}
	V pop(K key)
	{
		int hash = hashFunction(key);
		try {
			if (m_items[hash] == NULL) // if at end of list
				throw std::invalid_argument("no such key");
			else if (m_items[hash]->getKey() == key) // if have found the key
			{
				V t_value = m_items[hash]->getValue(key);
				if (m_items[hash]->getNext() != NULL) // if next is not null
					m_items[hash] = m_items[hash]->getNext(); /// go to next
				else m_items[hash] = NULL; // else set current to null
				return t_value; // return t_value
			}
			else return m_items[hash]->popValue(key); // apply recursive pop on the nextvalue
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "exception: " << e.what() << std::endl;
			throw std::invalid_argument("In function Pop: no such key, returning trash template"); // yes throws double exceptions here

		}
	}

	int printAll(void)
	{
		int totalLength = 0;
		for (int i; i < TABLESIZE; i++) // iterate through array of linked list
		{
			for (auto *val = m_items[i]; val != NULL; val = val->getNext()) // iterate through linked list
			{
				printItem(val->returnValue());
				totalLength++;
			}
		}

		std::cout << "TOTAL LENGTH:" << totalLength << std::endl;
		return totalLength;

	}
	Item<K,V>& HashDictionary::operator[] (const K index)
	{
		
		for (int i; i < TABLESIZE; i++) //iterate through array of linked lists
		{
			for (auto *val = m_items[i]; val != NULL; val = val->getNext()) // iterate through linked list
			{
				if (m_items[i]->getKey() == index) // see if 
					return (*(m_items[i]));// return reference, unreferencing pointer before returning.

			}
		}

		throw std::invalid_argument("Can't return value, possibly missing index");
	}

private:
	virtual int hashFunction(K key) = 0;
	virtual void printItem(V value) = 0;

};

#endif /* HashDictionary_h */
