//
//  HashDictionary.h
//  HashDictionary
//
//  Created by Staffan Brickman & Fredrik Ginsberg on 2019-02-12.
//  Copyright © 2019 kanaljen. All rights reserved.
//
#include <iostream>
#pragma once
#ifndef HashDictionary_h
#define HashDictionary_h
#define TABLESIZE 127 // A prime number

template <typename K, typename V>
class Item {
    V m_value;
    K m_key;
    Item* m_next;
public:
    Item(K key, V value) :
    m_key(key), m_value(value), m_next(NULL)
    { }
    K getKey() { return m_key; }
    Item* getNext() { return m_next; }
    void setValue(K key, V value)
    {
        if (m_key == key)m_value = value;
        else if (m_next != NULL)m_next->setValue(key, value);
        else throw std::invalid_argument("no such key");
    }
    V getValue(K key)
    {
        if (m_key == key)return m_value;
        else if (m_next != NULL)return m_next->getValue(key);
        else throw std::invalid_argument("no such key");
        exit(EXIT_FAILURE);
    }
    void appendItem(K key, V value)
    {
        if (m_key == key)
            throw std::invalid_argument("duplicate key");
        else if (m_next == NULL)m_next = new Item<K, V>(key, value);
        else m_next->appendItem(key, value);
    }
    V popValue(K key)
    {
        if (m_next != NULL)
        {
            if (m_next->getKey() == key)
            {
                Item* t_next = m_next->getNext();
                V t_value = m_next->getValue(key);
                delete m_next;
                m_next = t_next;
                return t_value;
            }
        }
        else if (m_next != NULL)return m_next->popValue(key);
        else throw std::invalid_argument("no such key");
        return NULL;
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
        if (m_items[hash] == NULL)m_items[hash] = new Item<K, V>(key, value);
        else try { m_items[hash]->appendItem(key, value); }
        catch (const std::invalid_argument& e) { std::cerr << "exception: " << e.what() << std::endl; }
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
        try {
            if (m_items[hash] == NULL)throw std::invalid_argument("no such key");
            else return m_items[hash]->getValue(key);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "exception: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    V pop(K key)
    {
        int hash = hashFunction(key);
        try {
            if (m_items[hash] == NULL)throw std::invalid_argument("no such key");
            else if (m_items[hash]->getKey() == key) {
                V t_value = m_items[hash]->getValue(key);
                if (m_items[hash]->getNext() != NULL)m_items[hash] = m_items[hash]->getNext();
                else m_items[hash] = NULL;
                return t_value;
            }
            else return m_items[hash]->popValue(key);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "exception: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
private:
    virtual int hashFunction(K key) = 0;
};
#endif /* HashDictionary_h */
